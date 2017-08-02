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

#ifndef __ESRI__ARCSDK__AXCONT_REDEF_H__
#define __ESRI__ARCSDK__AXCONT_REDEF_H__

#if defined(ESRI_UNIX)
#define AxContainerCreate            AxContainerCreate__ESRI_WRAPPER
#define AxContainerRealize           AxContainerRealize__ESRI_WRAPPER
#define AxContainerDestroy           AxContainerDestroy__ESRI_WRAPPER
#define AxContainerCheckMessageQueue AxContainerCheckMessageQueue__ESRI_WRAPPER
#define AxContainerShow              AxContainerShow__ESRI_WRAPPER
#define AxContainerHide              AxContainerHide__ESRI_WRAPPER
#define AxContainerSetHostWindow     AxContainerSetHostWindow__ESRI_WRAPPER
#define AxContainerSetXDisplay       AxContainerSetXDisplay__ESRI_WRAPPER
#define AxContainerGetInterface      AxContainerGetInterface__ESRI_WRAPPER
#define AxContainerGetXWindow        AxContainerGetXWindow__ESRI_WRAPPER
#define AxContainerSetScreenDisplay  AxContainerSetScreenDisplay__ESRI_WRAPPER
#define AxContainerRedraw            AxContainerRedraw__ESRI_WRAPPER
#define AxContainerSetCursor         AxContainerSetCursor__ESRI_WRAPPER
#endif /* ESRI_UNIX */

#endif /* __ESRI__ARCSDK__AXCONT_REDEF_H__ */
