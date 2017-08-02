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

#ifndef __ESRI__ARCSDK_GTK_GTKCTL_AXCTL_H__
#define __ESRI__ARCSDK_GTK_GTKCTL_AXCTL_H__

#include <gdk/gdk.h>
#include <gtk/gtkwidget.h>

#if !defined(ESRI_X11_REDEFINES) && defined(ESRI_UNIX)
#define Cursor      ESRIXCursor
#define Object      ESRIXObject
#define ObjectClass ESRIXObjectClass
#define Status      ESRIXStatus
#define Time        ESRIXTime
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#undef Cursor
#undef Object
#undef ObjectClass
#undef Status
#undef Time
#endif /* ESRI_X11_REDEFINES */

#if defined(ESRI_UNIX) && !defined (ESRI_X11_TYPEDEFS)
typedef Window        ESRIXWindowType;
typedef Display       ESRIXDisplayType;
typedef Screen        ESRIXScreenType;
#elif defined(ESRI_WINDOWS) && !defined (ESRI_X11_TYPEDEFS)
typedef HWND           ESRIXWindowType;
typedef unsigned long ESRIXDisplayType;
typedef unsigned long ESRIXScreenType;
#endif /* ESRI_UNIX|ESRI_WINDOWS */

#include <AxCtl/AxContainer.h>
#include <AxCtl/ControlData.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GTK_AXCTL(obj)         GTK_CHECK_CAST       (obj  , gtk_axctl_get_type(), GtkAxCtl     )
#define GTK_AXCTL_CLASS(klass) GTK_CHECK_CLASS_CAST (klass, gtk_axctl_get_type(), GtkAxCtlClass)
#define GTK_IS_AXCTL(obj)      GTK_CHECK_TYPE       (obj  , gtk_axctl_get_type()               )

typedef struct _GtkAxCtl      GtkAxCtl;
typedef struct _GtkAxCtlClass GtkAxCtlClass;

#if   defined(ESRI_UNIX)
#define ESRI_EXT_CLASS
#elif defined(ESRI_WINDOWS)
#ifndef ESRI_EXT_CLASS
#define ESRI_EXT_CLASS __declspec(dllimport)
#endif
#endif

struct _GtkAxCtl
{
	GtkWidget widget;
	AxContainerPtr cont;
	ControlData *ctldata;
	gboolean initial_resize_complete;
	gint pwX, pwY; /* parent window position */
};

struct _GtkAxCtlClass
{
	GtkWidgetClass parent_class;
};

ESRI_EXT_CLASS GtkWidget *gtk_axctl_new      (ControlDataPtr cd);
ESRI_EXT_CLASS GtkType    gtk_axctl_get_type ();

ESRI_EXT_CLASS void    gtk_axctl_initialize_message_queue();
ESRI_EXT_CLASS HRESULT gtk_axctl_get_interface(GtkWidget *axctl, IUnknown **ppUnk);
ESRI_EXT_CLASS HRESULT gtk_axctl_set_cursor(HCURSOR cur);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __ESRI__ARCSDK_GTK_GTKCTL_AXCTL_H__ */
