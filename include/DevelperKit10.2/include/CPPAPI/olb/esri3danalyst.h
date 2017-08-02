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

#ifndef __ESRI3DANALYST_OLB__
#define __ESRI3DANALYST_OLB__

#if defined(ESRI_UNIX)

#include "esrisystem.h"
#include "esrigraphicscore.h"
#include "esrisystemui.h"
#include "esrigeometry.h"
#include "esridisplay.h"
#include "esrigeodatabase.h"
#include "esridatasourcesraster.h"
#include "esridatasourcesfile.h"
#include "esrioutput.h"
#include "esricarto.h"
#include "esrianimation.h"
#include "esrigeoprocessing.h"
#include "tlh/esri3danalyst.tlh"

#elif defined(ESRI_WINDOWS)

#include "esrisystem.h"
#include "esrigraphicscore.h"
#include "esrisystemui.h"
#include "esrigeometry.h"
#include "esridisplay.h"
#include "esrigeodatabase.h"
#include "esridatasourcesraster.h"
#include "esridatasourcesfile.h"
#include "esrioutput.h"
#include "esricarto.h"
#include "esrianimation.h"
#include "esrigeoprocessing.h"
#import "esri3danalyst.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude( "OLE_HANDLE", "OLE_COLOR", "UINT_PTR" )

#endif /* ESRI_UNIX,ESRI_WINDOWS */

#endif /* __ESRI3DANALYST_OLB__ */

