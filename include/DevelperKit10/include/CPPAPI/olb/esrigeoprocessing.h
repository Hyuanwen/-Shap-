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

#ifndef __ESRIGEOPROCESSING_OLB__
#define __ESRIGEOPROCESSING_OLB__

#if defined(ESRI_UNIX)

#include "esrisystem.h"
#include "esrisystemui.h"
#include "esriserver.h"
#include "esrigisclient.h"
#include "esrigeometry.h"
#include "esrigeodatabase.h"
#include "esridatasourcesfile.h"
#include "esridatasourcesraster.h"
#include "esridatasourcesnetcdf.h"
#include "esrigeodatabasedistributed.h"
#include "esricarto.h"
#include "esridisplay.h"
#include "esrigeoanalyst.h"
#include "esrigeodatabasedistributed.h"
#include "tlh/esrigeoprocessing.tlh"

#elif defined(ESRI_WINDOWS)

#include "esrisystem.h"
#include "esrisystemui.h"
#include "esriserver.h"
#include "esrigisclient.h"
#include "esrigeometry.h"
#include "esrigeodatabase.h"
#include "esridatasourcesfile.h"
#include "esridatasourcesraster.h"
#include "esridatasourcesnetcdf.h"
#include "esrigeodatabasedistributed.h"
#include "esricarto.h"
#include "esridisplay.h"
#include "esrigeoanalyst.h"
#include "esrigeodatabasedistributed.h"
#import "esrigeoprocessing.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude( "OLE_HANDLE", "OLE_COLOR", "UINT_PTR" )

#endif /* ESRI_UNIX,ESRI_WINDOWS */

#endif /* __ESRIGEOPROCESSING_OLB__ */

