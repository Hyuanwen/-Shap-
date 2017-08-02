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

/*
 * Ao/AoControls.h
 * ESRI Controls
 * Public Header
 */

#ifndef __ESRI__ARCSDK_CTL_AO_AOCONTROLS_H__
#define __ESRI__ARCSDK_CTL_AO_AOCONTROLS_H__

#include <olb/esricontrols.h>
#include <olb/esripublishercontrols.h>
#include <olb/esrisystemutility.h>

#include <AxCtl/ControlData.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

ESRI_EXT_CLASS extern ControlDataPtr AoPROGID_GlobeControl;
ESRI_EXT_CLASS extern ControlDataPtr AoPROGID_MapControl;
ESRI_EXT_CLASS extern ControlDataPtr AoPROGID_PageLayoutControl;
ESRI_EXT_CLASS extern ControlDataPtr AoPROGID_ReaderControl;
ESRI_EXT_CLASS extern ControlDataPtr AoPROGID_SceneControl;
ESRI_EXT_CLASS extern ControlDataPtr AoPROGID_TOCControl;
ESRI_EXT_CLASS extern ControlDataPtr AoPROGID_ToolbarControl;
ESRI_EXT_CLASS extern ControlDataPtr AoPROGID_SymbologyControl;
ESRI_EXT_CLASS extern ControlDataPtr AoPROGID_GlobeReaderControl;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESRI__ARCSDK_CTL_AO_AOCONTROLS_H__ */
