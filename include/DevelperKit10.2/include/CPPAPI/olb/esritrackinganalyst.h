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

#ifndef __ESRITRACKINGANALYST_OLB__
#define __ESRITRACKINGANALYST_OLB__

#if defined(ESRI_UNIX)

#include "esrisystem.h"
#include "esricontrols.h"
#include "esrigeometry.h"
#include "esridisplay.h"
#include "esrioutput.h"
#include "esrigeodatabase.h"
#include "esridatasourcesfile.h"
#include "esridatasourcesgdb.h"
#include "esrigeodatabasedistributed.h"
#include "esridatasourcesraster.h"
#include "esrilocation.h"
#include "esrigisclient.h"
#include "esricarto.h"
#include "esrinetworkanalysis.h"
#include "esrigeoanalyst.h"
#include "esrispatialanalyst.h"
#include "esri3danalyst.h"
#include "esriserver.h"
#include "esrigeoprocessing.h"
#include "esriglobecore.h"
#include "tlh/esritrackinganalyst.tlh"

#elif defined(ESRI_WINDOWS)

#include "esrisystem.h"
#include "esricontrols.h"
#include "esrigeometry.h"
#include "esridisplay.h"
#include "esrioutput.h"
#include "esrigeodatabase.h"
#include "esridatasourcesfile.h"
#include "esridatasourcesgdb.h"
#include "esrigeodatabasedistributed.h"
#include "esridatasourcesraster.h"
#include "esrilocation.h"
#include "esrigisclient.h"
#include "esricarto.h"
#include "esrinetworkanalysis.h"
#include "esrigeoanalyst.h"
#include "esrispatialanalyst.h"
#include "esri3danalyst.h"
#include "esriserver.h"
#include "esrigeoprocessing.h"
#include "esriglobecore.h"
#import "esritrackinganalyst.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude( "OLE_HANDLE", "OLE_COLOR", "UINT_PTR", "IMessage", "IServer" )

#endif /* ESRI_UNIX,ESRI_WINDOWS */

#endif /* __ESRITRACKINGANALYST_OLB__ */

