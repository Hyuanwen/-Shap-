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

/* ControlData.h */

#ifndef __ESRI__ARCSDK___CTLBASE_CONTROLDATA_H__
#define __ESRI__ARCSDK___CTLBASE_CONTROLDATA_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _ControlData
{
	const char *str;
	void *reserved;
} ControlData, *ControlDataPtr;
#define CONTROLDATA_DEFINED

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESRI__ARCSDK___CTLBASE_CONTROLDATA_H__ */

