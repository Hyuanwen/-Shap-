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

#ifndef __ESRINETWORKANALYST_OLB__
#define __ESRINETWORKANALYST_OLB__

#if defined(ESRI_UNIX)

#include "esrisystem.h"
#include "esrigeometry.h"
#include "esridisplay.h"
#include "esriserver.h"
#include "esrioutput.h"
#include "esrigeodatabase.h"
#include "esrigisclient.h"
#include "esridatasourcesfile.h"
#include "esridatasourcesraster.h"
#include "esricarto.h"
#include "esrigeoprocessing.h"
#include "tlh/esrinetworkanalyst.tlh"

#elif defined(ESRI_WINDOWS)

#include "esrisystem.h"
#include "esrigeometry.h"
#include "esridisplay.h"
#include "esriserver.h"
#include "esrioutput.h"
#include "esrigeodatabase.h"
#include "esrigisclient.h"
#include "esridatasourcesfile.h"
#include "esridatasourcesraster.h"
#include "esricarto.h"
#include "esrigeoprocessing.h"
#import "esrinetworkanalyst.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude( "OLE_HANDLE", "OLE_COLOR", "UINT_PTR" )

#endif /* ESRI_UNIX,ESRI_WINDOWS */

#endif /* __ESRINETWORKANALYST_OLB__ */

