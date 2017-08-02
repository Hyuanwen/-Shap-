/*
 COPYRIGHT © 2008 ESRI

 TRADE SECRETS: ESRI PROPRIETARY AND CONFIDENTIAL
 Unpublished material - all rights reserved under the
 Copyright Laws of the United States and applicable international
 laws, treaties, and conventions.

 For additional information, contact:
 Environmental Systems Research Institute, Inc.
 Attn: Contracts and Legal Services Department
 380 New York Street
 Redlands, California, 92373
 USA

 email: contracts@esri.com
*/

#ifndef __ESRI__ARCSDK__AXCONT_H__
#define __ESRI__ARCSDK__AXCONT_H__

#ifdef __cplusplus

#ifndef AX_CONTAINER_SOURCE
#include <ArcSDK.h>
#endif /* AX_CONTAINER_SOURCE */

#else /* __cplusplus */

#if defined(ESRI_UNIX)
typedef long IUnknown;
typedef long HRESULT;
typedef void *HCURSOR;
#endif /* ESRI_UNIX */

#endif /* __cplusplus */

#ifndef AXCONTAINERPTR_DEFINED
typedef void *AxContainerPtr;
#endif /* AXCONTAINERPTR_DEFINED */

#ifndef AX_CONTAINER_SOURCE
#include <AxCtl/AxContainer_redef.h>
#endif /* AX_CONTAINER_SOURCE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

ESRI_EXT_CLASS AxContainerPtr  AxContainerCreate           (const char *progID);
ESRI_EXT_CLASS void            AxContainerRealize          (AxContainerPtr axp);
ESRI_EXT_CLASS void            AxContainerDestroy          (AxContainerPtr axp);
ESRI_EXT_CLASS void            AxContainerCheckMessageQueue();
ESRI_EXT_CLASS void            AxContainerShow             (AxContainerPtr axp);
ESRI_EXT_CLASS void            AxContainerHide             (AxContainerPtr axp);
ESRI_EXT_CLASS void            AxContainerSetHostWindow    (AxContainerPtr axp, ESRIXWindowType hostWin);
ESRI_EXT_CLASS void            AxContainerSetXDisplay      (AxContainerPtr axp, ESRIXDisplayType *dpy);
ESRI_EXT_CLASS HRESULT         AxContainerGetInterface     (AxContainerPtr axp, IUnknown **ppUnk);
ESRI_EXT_CLASS ESRIXWindowType AxContainerGetXWindow       (AxContainerPtr axp);
ESRI_EXT_CLASS void            AxContainerSetScreenDisplay (AxContainerPtr axp, ESRIXScreenType *scr, ESRIXDisplayType *dpy);
ESRI_EXT_CLASS void            AxContainerRedraw           (AxContainerPtr axp);
ESRI_EXT_CLASS HRESULT         AxContainerSetCursor        (HCURSOR cur);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __ESRI__ARCSDK__AXCONT_H__ */
