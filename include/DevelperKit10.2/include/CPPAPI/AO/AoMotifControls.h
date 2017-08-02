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


#ifndef __ESRI__ARCSDK_CTL_AO_AOMOTIFCONTROLS_H__
#define __ESRI__ARCSDK_CTL_AO_AOMOTIFCONTROLS_H__

#include <Ao/AoControls.h>
#include <AxCtl/XmAxCtl.h>

#ifdef __cplusplus
extern "C" {
#endif

IGlobeControl      *AoGlobeControlGetInterface     (Widget w); /* deprecated */
IMapControl2       *AoMapControlGetInterface       (Widget w); /* deprecated */
IPageLayoutControl *AoPageLayoutControlGetInterface(Widget w); /* deprecated */
IARControl         *AoReaderControlGetInterface    (Widget w); /* deprecated */
ISceneControl      *AoSceneControlGetInterface     (Widget w); /* deprecated */
ITOCControl        *AoTOCControlGetInterface       (Widget w); /* deprecated */
IToolbarControl    *AoToolbarControlGetInterface   (Widget w); /* deprecated */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __ESRI__ARCSDK_CTL_AO_AOMOTIFCONTROLS_H__ */

