/*
  COPYRIGHT © 2006 ESRI

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

/******************************************************************************
 *                                                                            *
 *  ArcObjects General Control Xt Widget                                      *
 *                                                                            *
 *  Ctl.h -- public header file                                               *
 *                                                                            *
 ******************************************************************************/

#ifndef __ESRI__ARCSDK__AXCTL_XMAXCTL_H__
#define __ESRI__ARCSDK__AXCTL_XMAXCTL_H__

#ifndef ESRI_X11_REDEFINES
#define Cursor      ESRIXCursor
#define Object      ESRIXObject
#define ObjectClass ESRIXObjectClass
#define Time        ESRIXTime
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#undef Cursor
#undef Object
#undef ObjectClass
#undef Time
#define ESRI_X11_REDEFINES
#endif /* ESRI_X11_REDEFINES */

#ifndef ESRIXWINDOWTYPE_DEFINED
typedef Window  ESRIXWindowType;
#define ESRIXWINDOWTYPE_DEFINED
#endif /* ESRIXWINDOWTYPE_DEFINED */

#ifndef ESRIXDISPLAYTYPE_DEFINED
typedef Display ESRIXDisplayType;
#define ESRIXDISPLAYTYPE_DEFINED
#endif /* ESRIXDISPLAYTYPE_DEFINED */

#ifndef ESRIXSCREENTYPE_DEFINED
typedef Screen ESRIXScreenType;
#define ESRIXSCREENTYPE_DEFINED
#endif /* ESRIXSCREENTYPE_DEFINED */

#include <AxCtl/AxContainer.h>
#include <AxCtl/ControlData.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* Resource names                                                               *
*******************************************************************************/

#define MwNmeaninglessValue "meaninglessValue"
#define MwCMeaninglessValue "MeaninglessValue"

#define MwNprogID           "progID"
#define MwCProgID           "ProgID"

#define MwNshellWidget      "shellWidget"
#define MwCShellWidget      "ShellWidget"

#define MwDEFAULT_MEANINGLESS_VALUE    0xfedcba98
#define MwDEFAULT_SHELL_WIDGET         0x0

/*******************************************************************************
* Class record constants                                                       *
*******************************************************************************/

externalref WidgetClass mwCtlWidgetClass;

typedef struct _MwCtlClassRec * MwCtlWidgetClass;
typedef struct _MwCtlRec      * MwCtlWidget;

#ifndef   MwIsControl
#define   MwIsControl(w) (XtIsSubclass(w, mwCtlWidgetClass))
#endif /* MwIsControl */


/*******************************************************************************
* Public Function Declarations                                                 *
*******************************************************************************/

HRESULT        MwCtlGetInterface(Widget w, IUnknown **ppUnk);
AxContainerPtr MwCtlGetContainer(Widget w);
AxContainerPtr MwCtlGetVerifiedContainer(Widget w, ControlData *cd);
Window         MwCtlGetWindow(Widget w);
Boolean        MwCtlDestroyControl(Widget w);
void           MwCtlCheckMessageQueue();
void           MwCtlAppMainLoop(XtAppContext app);
Window         MwCtlGetControlWidgetWindow(Widget w);
HRESULT        MwCtlSetCursor(HCURSOR cur);

#ifdef __cplusplus
}
#endif

#endif /* __ESRI__ARCSDK__AXCTL_XMAXCTL_H__ */
