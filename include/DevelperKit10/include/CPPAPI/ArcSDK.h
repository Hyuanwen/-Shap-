/*
 COPYRIGHT ?2008 ESRI

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

#ifndef __ESRI__ARCSDK__SDKINC_H__
#define __ESRI__ARCSDK__SDKINC_H__

#if  defined(ESRI_WINDOWS)
#define PRODUCTSTRING(ver) L"" L#ver
#elif defined(__SUNPRO_CC) || defined(__SUNPRO_C)
#define PRODUCTSTRING(ver) L"" L#ver
#elif defined(__GNUC__)
#define PRODUCTSTRING(ver) L"" #ver
#else
#define PRODUCTSTRING(ver) L"" #ver
#endif


#define ESRI_SET_VERSION(prod,vers) \
{ \
	HRESULT hr; \
	VARIANT_BOOL vb; \
	CComBSTR bsVer(PRODUCTSTRING(vers)); \
	IArcGISVersionPtr ipVersion(_CLSID_VERSION_MANAGER); \
	if(!SUCCEEDED(hr = ipVersion->LoadVersion(prod, bsVer, &vb))) \
	fprintf(stderr, "LoadVersion() failed with code 0x%.8x\n", hr); \
  else if(vb != VARIANT_TRUE) \
  fprintf(stderr, "LoadVersion() failed\n"); \
}




#if defined(ESRI_UNIX)

#if defined(__SUNPROC_C) || defined(__SUNPRO_CC)
#include <widec.h>
#define _wcsnicmp  wsncasecmp
#else /* LINUX */
#define _wcsnicmp  wcsncasecmp
#endif

#include "sdkdynamics.h"
#include "sdkcomdef.h"

#include "regoverride.h"
#include <atlbase.h>
extern CComModule _Module;

#include "sdkatldef.h"

#include "olb/tlh/arcgisversion.tlh"
#define _CLSID_VERSION_MANAGER CLSID_VersionManager

#ifdef ARCGIS_VERSION
extern "C" HRESULT AoInitializeEx(LPVOID pvReserved); /* CoInitialize Wrapper */
#define AoInitialize(pvRes) \
	AoInitializeEx(pvRes); \
	ESRI_SET_VERSION(esriArcGISEngine,ARCGIS_VERSION)
#else
extern "C" HRESULT AoInitialize(LPVOID pvReserved); /* CoInitialize     */
#endif

extern "C" void    AoUninitialize();                /* CoUninitialize   */

extern "C" HRESULT AoCreateObject(
	REFCLSID rclsid,
	LPUNKNOWN pUnkOuter,
	DWORD dwClsContext,
	REFIID riid,
	LPVOID *ppv);                                   /* CoCreateInstance */

extern "C" BSTR    AoAllocBSTR(const OLECHAR *sz);  /* SysAllocString   */
extern "C" void    AoFreeBSTR(BSTR bstr);           /* SysFreeString    */
extern "C" VOID    AoExit (int status);             /* Mw_Exit */

#ifndef ESRI_EXT_CLASS
#define ESRI_EXT_CLASS
#endif /* ESRI_EXT_CLASS */

#ifndef ESRI_QUICK
#include "esricomplete.h"
#endif /* ESRI_QUICK */

#elif defined(ESRI_WINDOWS)

#define STRICT
#define _WIN32_WINNT 0x0501
#define _ATL_APARTMENT_THREADED
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used fstuff from Windows headers

#include <windows.h>
#include <ocidl.h>
#include <atlbase.h>


#import "libid:6FCCEDE0-179D-4D12-B586-58C88D26CA78" no_namespace raw_interfaces_only no_implementation rename("esriProductCode", "esriVersionProductCode")
#define _CLSID_VERSION_MANAGER __uuidof(VersionManager)


#ifdef ARCGIS_VERSION
#define AoInitialize(pvRes) \
	CoInitialize(pvRes); \
	ESRI_SET_VERSION(esriArcGISEngine,ARCGIS_VERSION)
#else
#define AoInitialize(pvRes) CoInitialize(pvRes)
#endif

#define AoUninitialize CoUninitialize
#define AoCreateObject CoCreateInstance
#define AoAllocBSTR    SysAllocString
#define AoFreeBSTR     SysFreeString
#define AoExit         exit

#ifndef ESRI_EXT_CLASS
#define ESRI_EXT_CLASS __declspec( dllimport )
#endif /* ESRI_EXT_CLASS */

#ifndef ESRI_QUICK
#include "esricomplete.h"
#endif /* ESRI_QUICK */

#else /* ESRI_UNIX,ESRI_WINDOWS */

#error Please define ESRI_UNIX or ESRI_WINDOWS macro

#endif /* ESRI_UNIX,ESRI_WINDOWS */
#endif /* __ESRI__ARCSDK__SDKINC_H__ */

