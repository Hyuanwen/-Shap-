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

// AoToolBase.h: interface for the CAoToolBase class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ESRI__CTL_AO_AOTOOLBASE_H__
#define __ESRI__CTL_AO_AOTOOLBASE_H__

#include "AoCommandBase.h"

class CAoToolBase : virtual public CAoCommandBase
{
public:
	CAoToolBase(){};
	virtual ~CAoToolBase(){};

// ITool
	virtual HRESULT get_Cursor(OLE_HANDLE *Cursor) = 0;
	virtual HRESULT OnMouseDown(long button, long shift, long x, long y) = 0;
	virtual HRESULT OnMouseMove(long button, long shift, long x, long y) = 0;
	virtual HRESULT OnMouseUp(long button, long shift, long x, long y) = 0;
	virtual HRESULT OnDblClick() = 0;
	virtual HRESULT OnKeyDown(long keyCode, long shift) = 0;
	virtual HRESULT OnKeyUp(long keyCode, long shift) = 0;
	virtual HRESULT OnContextMenu(long x, long y, VARIANT_BOOL *handled) = 0;
	virtual HRESULT Refresh(OLE_HANDLE hdc) = 0;
	virtual HRESULT Deactivate(VARIANT_BOOL *complete) = 0;
};

extern "C" ESRI_EXT_CLASS HRESULT AoToolbarAddTool(IToolbarControl *pToolbarControl, CAoToolBase *commandBase, enum esriCommandStyles style);

#endif /* __ESRI__CTL_AO_AOTOOLBASE_H__ */
