/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005
 *					All rights reserved
 *
 *  This file is part of GPAC / DirectX audio and video render module
 *
 *  GPAC is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *   
 *  GPAC is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *   
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *		
 */


#include "dx_hw.h"

#define DDCONTEXT	DDContext *dd = (DDContext *)dr->opaque;


GF_Err DD_SetupHardware(GF_VideoOutput *dr, void *os_handle, void *os_display, Bool no_proc_override, GF_GLConfig *cfg)
{
	RECT rc;
	DDCONTEXT
	dd->hWnd = (HWND) os_handle;
	
	DD_SetupWindow(dr);
	/*fatal error*/
	if (!dd->hWnd) return GF_IO_ERR;
	
	GetWindowRect(dd->hWnd, &rc);
	dd->is_3D_out = cfg ? 1 : 0;
	return InitDirectDraw(dr, rc.right - rc.left, rc.bottom - rc.top);
}

static void RestoreWindow(DDContext *dd) 
{
	HWND hWnd = dd->hWnd;
	if (!dd->NeedRestore) goto exit;

	if (!dd->owns_hwnd && dd->switch_res) hWnd = GetParent(dd->hWnd);

	dd->NeedRestore = 0;
	if (dd->is_3D_out) {
		ChangeDisplaySettings(NULL,0);
		SetForegroundWindow(GetDesktopWindow());
		SetForegroundWindow(dd->hWnd);
	} else {
#ifdef USE_DX_3
		IDirectDraw_SetCooperativeLevel(dd->pDD, hWnd, DDSCL_NORMAL);
#else
		IDirectDraw7_SetCooperativeLevel(dd->pDD, hWnd, DDSCL_NORMAL);
#endif

		dd->NeedRestore = 0;
	}

	if (dd->owns_hwnd || dd->is_3D_out) SetWindowLong(dd->hWnd, GWL_STYLE, dd->prev_styles);
		
	if (dd->owns_hwnd) SetWindowText(dd->hWnd, "GPAC DirectDraw Output");

	if (!dd->switch_res || dd->owns_hwnd) {
		SetWindowPos(dd->hWnd, NULL, dd->rcWnd.left, dd->rcWnd.top, dd->rcWnd.right - dd->rcWnd.left, dd->rcWnd.bottom - dd->rcWnd.top, SWP_NOZORDER);
	} else {
		/*post a message to the parent wnd*/
		RECT rc = dd->rcWnd;
		HWND hWnd = GetParent(dd->hWnd);
		if (!hWnd) hWnd = dd->hWnd;
		if (dd->is_3D_out) SetWindowPos(dd->hWnd, NULL, dd->rcChildWnd.left, dd->rcChildWnd.top, dd->rcChildWnd.right - dd->rcChildWnd.left, dd->rcChildWnd.bottom - dd->rcChildWnd.top, SWP_NOZORDER);
		SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);
	}

exit:
	/*store client rect*/
	GetWindowRect(dd->hWnd, &dd->rcWnd);
}

void DestroyObjects(DDContext *dd)
{
	RestoreWindow(dd);

	/*remove all surfaces*/
	while (gf_list_count(dd->surfaces)) {
		DDSurface *pS = gf_list_get(dd->surfaces, 0);
		gf_list_rem(dd->surfaces, 0);
		SAFE_DD_RELEASE(pS->pSurface);
		free(pS);
	}

	SAFE_DD_RELEASE(dd->pPrimary);
	SAFE_DD_RELEASE(dd->pBack);
	SAFE_DD_RELEASE(dd->pDD);
	dd->ddraw_init = 0;

	/*delete openGL context*/
	if (dd->gl_HRC) {
		wglDeleteContext(dd->gl_HRC);
		dd->gl_HRC = NULL;
	}
	if (dd->gl_HDC) {
		ReleaseDC(dd->hWnd, dd->gl_HDC);
		dd->gl_HDC = NULL;
	}
}

static void DD_Shutdown(GF_VideoOutput *dr)
{
	DDCONTEXT
	DestroyObjects(dd);

	DD_ShutdownWindow(dr);
}

GF_Err DD_SetupOpenGL(GF_VideoOutput *dr) 
{
    PIXELFORMATDESCRIPTOR pfd; 
	GF_Event evt;
    s32 pixelformat; 
	DDCONTEXT

	/*already setup*/
	if (dd->gl_HRC) return GF_OK;

	dd->gl_HDC = GetDC(dd->hWnd);
	if (!dd->gl_HDC) return GF_IO_ERR;

    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.dwLayerMask = PFD_MAIN_PLANE;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = pfd.cDepthBits = 16;
    if ( (pixelformat = ChoosePixelFormat(dd->gl_HDC, &pfd)) == FALSE ) return GF_IO_ERR; 
    if (SetPixelFormat(dd->gl_HDC, pixelformat, &pfd) == FALSE) return GF_IO_ERR; 
	dd->gl_HRC = wglCreateContext(dd->gl_HDC);
	if (!dd->gl_HRC) return GF_IO_ERR;
	if (!wglMakeCurrent(dd->gl_HDC, dd->gl_HRC)) return GF_IO_ERR;
	evt.type = GF_EVT_GL_CHANGED;
	dr->on_event(dr->evt_cbk_hdl, &evt);	
	return GF_OK;
}

static GF_Err DD_SetFullScreen(GF_VideoOutput *dr, Bool bOn, u32 *outWidth, u32 *outHeight)
{
	GF_Err e;
	char *sOpt;
	u32 MaxWidth, MaxHeight;
	DDCONTEXT;

	if (!dd->width ||!dd->height) return GF_BAD_PARAM;
	if (bOn == dd->fullscreen) return GF_OK;
	dd->fullscreen = bOn;

	
	/*whenever changing card display mode relocate fastest YUV format for blit (since it depends
	on the dest pixel format)*/
	dd->yuv_init = 0;
	if (dd->fullscreen) {
		char *sOpt = gf_modules_get_option(dr, "Video", "SwitchResolution");
		if (sOpt && !stricmp(sOpt, "yes")) dd->switch_res = 1;
		/*get current or best fitting mode*/
		if (GetDisplayMode(dd) != GF_OK) return GF_IO_ERR;
	}

	MaxWidth = MaxHeight = 0;
	sOpt = gf_modules_get_option(dr, "Video", "MaxResolution");
	if (sOpt) sscanf(sOpt, "%dx%d", &MaxWidth, &MaxHeight);

	dd->is_resizing = 1;

	if (dd->is_3D_out) {
		DEVMODE settings;
		e = GF_OK;

		/*recreate the GL context whenever changing display settings, it's safer...*/
		DestroyObjects(dd);
		/*Setup FS*/
		if (dd->fullscreen) {
			/*change display mode*/
			if (dd->switch_res) {
				/*when switching res weird messages are sent to parent -> store current rect and post
				a size/pos message on restore */
				if (!dd->owns_hwnd) {
					HWND hWnd = GetParent(dd->hWnd);
					if (!hWnd) hWnd = dd->hWnd;
					GetWindowRect(hWnd, &dd->rcWnd);
				}
			}

			if ((MaxWidth && (dd->fs_width >= MaxWidth)) || (MaxHeight && (dd->fs_height >= MaxHeight)) ) {
				dd->fs_width = MaxWidth;
				dd->fs_height = MaxHeight;
			}

			/*force size change (we do it whether we own or not the window)*/
			dd->prev_styles = GetWindowLong(dd->hWnd, GWL_STYLE);
			GetWindowRect(dd->hWnd, &dd->rcChildWnd);
			SetWindowLong(dd->hWnd, GWL_STYLE, WS_POPUP);
			SetWindowPos(dd->hWnd, NULL, 0, 0, dd->fs_width, dd->fs_height, SWP_NOZORDER | SWP_SHOWWINDOW);
			SetForegroundWindow(dd->hWnd);

			memset(&settings, 0, sizeof(DEVMODE));
			settings.dmSize = sizeof(DEVMODE);
			settings.dmPelsWidth = dd->fs_width;
			settings.dmPelsHeight = dd->fs_height;
			settings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
			if ( ChangeDisplaySettings(&settings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL ) {
				fprintf(stdout, "cannot change display settings...\n");
				e = GF_IO_ERR;
			} 

			dd->NeedRestore = 1;
			dd->fs_store_width = dd->fs_width;
			dd->fs_store_height = dd->fs_height;
		}
		if (!e) e = DD_SetupOpenGL(dr);
		
	} else {
		e = InitDirectDraw(dr, dd->width, dd->height);
	}
	
	dd->is_resizing = 0;

	if (bOn) {
		dd->store_width = *outWidth;
		dd->store_height = *outHeight;
		*outWidth = dd->fs_width;
		*outHeight = dd->fs_height;
	} else {
		*outWidth = dd->store_width;
		*outHeight = dd->store_height;
	}
	return e;
}


static GF_Err DD_Resize(GF_VideoOutput *dr, u32 width, u32 height)
{
	DDCONTEXT;

	if (dd->is_3D_out) {
		dd->width = width;
		dd->height = height;
		return DD_SetupOpenGL(dr);
	}
	if (!dd->ddraw_init) 
		return InitDirectDraw(dr, width, height);
	else
		return CreateBackBuffer(dr, width, height);
}


static GF_Err DD_FlushVideo(GF_VideoOutput *dr, GF_Window *dest)
{
	RECT rc;
	HRESULT hr;
	DDCONTEXT;

	if (!dd) return GF_BAD_PARAM;
	if (dd->is_3D_out) {
		SwapBuffers(dd->gl_HDC);
		return GF_OK;
	}
	if (!dd->ddraw_init) return GF_BAD_PARAM;

	if (dest) {
		POINT pt;
		pt.x = dest->x;
		pt.y = dest->y;
		ClientToScreen(dd->hWnd, &pt);
		dest->x = pt.x;
		dest->y = pt.y;
		MAKERECT(rc, dest);
		hr = IDirectDrawSurface_Blt(dd->pPrimary, &rc, dd->pBack, NULL, DDBLT_WAIT, NULL );
	} else {
		hr = IDirectDrawSurface_Blt(dd->pPrimary, NULL, dd->pBack, NULL, DDBLT_WAIT, NULL );
	}
	if (hr == DDERR_SURFACELOST) {
		IDirectDrawSurface_Restore(dd->pPrimary);
		IDirectDrawSurface_Restore(dd->pBack);
	}
	return FAILED(hr) ? GF_IO_ERR : GF_OK;
}



#ifdef USE_DX_3
HRESULT WINAPI EnumDisplayModes( LPDDSURFACEDESC lpDDDesc, LPVOID lpContext)
#else
HRESULT WINAPI EnumDisplayModes( LPDDSURFACEDESC2 lpDDDesc, LPVOID lpContext)
#endif
{
	DDContext *dd = (DDContext *) lpContext;
	
	//check W and H
	if (dd->width <= lpDDDesc->dwWidth  && dd->height <= lpDDDesc->dwHeight
		//check FSW and FSH
		&& dd->fs_width > lpDDDesc->dwWidth && dd->fs_height > lpDDDesc->dwHeight) {

		if (lpDDDesc->dwHeight == 200)
			return DDENUMRET_OK;
		
		dd->fs_width = lpDDDesc->dwWidth;
		dd->fs_height = lpDDDesc->dwHeight;

		return DDENUMRET_CANCEL;
	}
	return DDENUMRET_OK;
}

GF_Err GetDisplayMode(DDContext *dd)
{
	if (dd->switch_res) {
		HRESULT hr;
		Bool temp_dd = 0;;
		if (!dd->pDD) {
			LPDIRECTDRAW ddraw;
			DirectDrawCreate(NULL, &ddraw, NULL);
#ifdef USE_DX_3
			IDirectDraw_QueryInterface(ddraw, &IID_IDirectDraw, (LPVOID *)&dd->pDD);
#else
			IDirectDraw_QueryInterface(ddraw, &IID_IDirectDraw7, (LPVOID *)&dd->pDD);
#endif		
			temp_dd = 1;
		}
		//we start with a hugde res and downscale
		dd->fs_width = dd->fs_height = 50000;

#ifdef USE_DX_3
		hr = IDirectDraw_EnumDisplayModes(dd->pDD, 0L, NULL, dd,  (LPDDENUMMODESCALLBACK) EnumDisplayModes);
#else
		hr = IDirectDraw7_EnumDisplayModes(dd->pDD, 0L, NULL, dd,  (LPDDENUMMODESCALLBACK2) EnumDisplayModes);
#endif
		if (temp_dd) SAFE_DD_RELEASE(dd->pDD);
		if (FAILED(hr)) return GF_IO_ERR;
	} else {
		dd->fs_width = GetSystemMetrics(SM_CXSCREEN);
		dd->fs_height = GetSystemMetrics(SM_CYSCREEN);
	}
	return GF_OK;
}



static void *NewVideoOutput()
{
	DDContext *pCtx;
	GF_VideoOutput *driv = (GF_VideoOutput *) malloc(sizeof(GF_VideoOutput));
	memset(driv, 0, sizeof(GF_VideoOutput));
	GF_REGISTER_MODULE(driv, GF_VIDEO_OUTPUT_INTERFACE, "DirectX Video Output", "gpac distribution", 0);

	pCtx = malloc(sizeof(DDContext));
	memset(pCtx, 0, sizeof(DDContext));
	pCtx->surfaces = gf_list_new();
	driv->opaque = pCtx;
	driv->FlushVideo = DD_FlushVideo;
	driv->Resize = DD_Resize;
	driv->SetFullScreen = DD_SetFullScreen;
	driv->SetupHardware = DD_SetupHardware;
	driv->Shutdown = DD_Shutdown;
	driv->PushEvent = DD_PushEvent;
	driv->bHas3DSupport = 1;

	DD_SetupDDraw(driv);

	return (void *)driv;
}

static void DeleteVideoOutput(void *ifce)
{
	GF_VideoOutput *driv = (GF_VideoOutput *) ifce;
	DDContext *dd = (DDContext *)driv->opaque;

	gf_list_del(dd->surfaces);
	free(dd);
	free(driv);
}

/*interface query*/
Bool QueryInterface(u32 InterfaceType)
{
	if (InterfaceType == GF_VIDEO_OUTPUT_INTERFACE) return 1;
	if (InterfaceType == GF_AUDIO_OUTPUT_INTERFACE) return 1;
	return 0;
}
/*interface create*/
void *LoadInterface(u32 InterfaceType)
{
	if (InterfaceType == GF_VIDEO_OUTPUT_INTERFACE) return NewVideoOutput();
	if (InterfaceType == GF_AUDIO_OUTPUT_INTERFACE) return NewAudioOutput();
	return NULL;
}
/*interface destroy*/
void ShutdownInterface(void *ifce)
{
	GF_VideoOutput *dd = (GF_VideoOutput *)ifce;
	switch (dd->InterfaceType) {
	case GF_VIDEO_OUTPUT_INTERFACE:
		DeleteVideoOutput(dd);
		break;
	case GF_AUDIO_OUTPUT_INTERFACE:
		DeleteAudioOutput(ifce);
		break;
	}
}
