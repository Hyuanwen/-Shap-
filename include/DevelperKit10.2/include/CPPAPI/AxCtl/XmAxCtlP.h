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
 *  CtlP.h -- private header file                                             *
 *                                                                            *
 ******************************************************************************/

#ifndef __ESRI__ARCSDK__AXCTL_XMAXCTLP_H__
#define __ESRI__ARCSDK__AXCTL_XMAXCTLP_H__

#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>

#include <AxCtl/ControlData.h>

#include <AxCtl/XmAxCtl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * new fields for the MwCtl widget class record
 */
typedef struct _MwCtlClassPart {
	int extension;
} MwCtlClassPart;

/*
 * full class record declaration
 */
typedef struct _MwCtlClassRec {
	CoreClassPart  core_class;
	MwCtlClassPart mwctl_class;
} MwCtlClassRec;

/*
 * new fields for the MwCtl widget record
 */
typedef struct _MwCtlPart {
	/* resources */
	unsigned int meaningless_value;
/*	XtCallbackList abc_callback, def_callback; */
	ControlData *prog_id;
	Widget shell_widget;
	AxContainerPtr container;
	Window ax_top_level;
} MwCtlPart;

/*
 * full instance record declaration
 */
typedef struct _MwCtlRec {
	CorePart  core;
	MwCtlPart mw;
} MwCtlRec;

AxContainerPtr MwCtlDefaultInitialize();

#ifdef __cplusplus
}
#endif

#endif /* __ESRI__ARCSDK__AXCTL_XMAXCTLP_H__ */
