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

#ifndef __ESRISCHEMATICCONTROLS_OLB__
#define __ESRISCHEMATICCONTROLS_OLB__

#if defined(ESRI_UNIX)

#include "esrisystem.h"
#include "esrisystemui.h"
#include "esrigeometry.h"
#include "esridisplay.h"
#include "esrischematic.h"
#include "esricarto.h"
#include "tlh/esrischematiccontrols.tlh"

#elif defined(ESRI_WINDOWS)

#include "esrisystem.h"
#include "esrisystemui.h"
#include "esrigeometry.h"
#include "esridisplay.h"
#include "esrischematic.h"
#include "esricarto.h"
#import "esrischematiccontrols.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude( "OLE_HANDLE", "OLE_COLOR", "UINT_PTR" )

#endif /* ESRI_UNIX,ESRI_WINDOWS */

#endif /* __ESRISCHEMATICCONTROLS_OLB__ */

