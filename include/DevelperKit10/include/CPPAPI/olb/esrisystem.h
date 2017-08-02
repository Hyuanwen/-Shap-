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

#ifndef __ESRISYSTEM_OLB__
#define __ESRISYSTEM_OLB__

#if defined(ESRI_UNIX)

#include "tlh/stdole2.tlh"
#include <msxml.h>
#include "tlh/esrisystem.tlh"

#elif defined(ESRI_WINDOWS)

#import "esrisystem.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude( "OLE_HANDLE", "OLE_COLOR", "UINT_PTR" )

#endif /* ESRI_UNIX,ESRI_WINDOWS */

#endif /* __ESRISYSTEM_OLB__ */

