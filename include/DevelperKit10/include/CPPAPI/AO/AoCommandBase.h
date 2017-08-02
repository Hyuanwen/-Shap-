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

// AoCommandBase.h: interface for the CAoCommandBase class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ESRI__ARCSDK_CTL_AO_AOCOMMANDBASE_H__
#define __ESRI__ARCSDK_CTL_AO_AOCOMMANDBASE_H__

class CAoCommandBase  
{
public:
	CAoCommandBase(){};
	virtual ~CAoCommandBase(){};

// pseudo-ICommand
	virtual HRESULT get_Enabled(VARIANT_BOOL* Enabled) = 0;
	virtual HRESULT get_Checked(VARIANT_BOOL* Checked) = 0;
	virtual HRESULT get_Name(BSTR* Name) = 0;
	virtual HRESULT get_Caption(BSTR* Caption) = 0;
	virtual HRESULT get_Tooltip(BSTR* Tooltip) = 0;
	virtual HRESULT get_Message(BSTR* Message) = 0;
	virtual HRESULT get_Bitmap(OLE_HANDLE* bitmapFile) = 0;
	virtual HRESULT get_Category(BSTR* categoryName) = 0;
	virtual HRESULT OnCreate(IDispatch* hook) = 0;
	virtual HRESULT OnClick() = 0;
};

extern "C" ESRI_EXT_CLASS HRESULT AoToolbarAddCommand(IToolbarControl *pToolbarControl, CAoCommandBase *commandBase, enum esriCommandStyles style);

#endif /* __ESRI__ARCSDK_CTL_AO_AOCOMMANDBASE_H__ */
