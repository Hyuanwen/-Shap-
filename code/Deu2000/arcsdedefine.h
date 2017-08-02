#ifndef _ARCSDE_DEFINE_H
#define _ARCSDE_DEFINE_H


	#include <ArcSDK.h>

	#pragma warning(push)
	#pragma warning(disable : 4146)
	#pragma warning(disable : 4192)
	#pragma warning(disable : 4482)
	#pragma warning(disable : 4067)
	#pragma warning(disable : 4819)
	#pragma warning(disable : 4278)
	#pragma warning(disable : 4244)


	#import ".\esriSystem.olb" raw_interfaces_only raw_native_types no_namespace named_guids rename("OLE_COLOR", "esriOLE_COLOR") rename("OLE_HANDLE", "esriOLE_HANDLE")\
		rename("IName", "esriIName") 
	#import ".\esriSystemUI.olb" raw_interfaces_only raw_native_types no_namespace named_guids rename("OLE_COLOR", "esriOLE_COLOR") rename("OLE_HANDLE", "esriOLE_HANDLE")\
		rename("IProgressDialog", "esriIProgressDialog") rename("ICommand", "esriICommand")
	#import ".\esriGeometry.olb" raw_interfaces_only raw_native_types no_namespace named_guids rename("OLE_COLOR", "esriOLE_COLOR") rename("OLE_HANDLE", "esriOLE_HANDLE") \
		rename("wkbXDR", "esriwkbXDR") rename("wkbNDR", "esriwkbNDR") rename("wkbPoint", "esriwkbPoint") rename("wkbPolygon", "esriwkbPolygon")\
		rename("wkbMultiPolygon", "esriwkbMultiPolygon") rename("wkbMultiPoint", "esriwkbMultiPoint") rename("wkbGeometryCollection", "esriwkbGeometryCollection") //与gdal头文件枚举类型定义重复
	#import ".\esriDisplay.olb" raw_interfaces_only raw_native_types no_namespace named_guids rename("OLE_COLOR", "esriOLE_COLOR") rename("OLE_HANDLE", "esriOLE_HANDLE")
	#import ".\esriGeoDatabase.olb" raw_interfaces_only raw_native_types no_namespace named_guids rename("OLE_COLOR", "esriOLE_COLOR") rename("OLE_HANDLE", "esriOLE_HANDLE")\
		rename("IRow", "esriIRow") rename("ICursor", "esriICursor") rename("IRelationship", "esriIRelationship")
	#import ".\esriDataSourcesFile.olb" raw_interfaces_only raw_native_types no_namespace named_guids rename("OLE_COLOR", "esriOLE_COLOR") rename("OLE_HANDLE", "esriOLE_HANDLE")
	#import ".\esriDataSourcesGDB.olb" raw_interfaces_only raw_native_types no_namespace named_guids rename("OLE_COLOR", "esriOLE_COLOR") rename("OLE_HANDLE", "esriOLE_HANDLE")
	#import ".\esriDataSourcesRaster.olb" raw_interfaces_only raw_native_types no_namespace named_guids rename("OLE_COLOR", "esriOLE_COLOR") rename("OLE_HANDLE", "esriOLE_HANDLE")


	#pragma warning(pop)


#endif



