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

#ifndef __ESRI_ARCSDK_AXCTL_WXAXCTL_H__
#define __ESRI_ARCSDK_AXCTL_WXAXCTL_H__

#if defined(ESRI_UNIX) && defined(__ESRI__ARCSDK__SDKINC_H__)

#ifdef GetClassInfo
#  undef GetClassInfo
#endif /* GetClassInfo */
#ifdef SetFocus
#  undef SetFocus
#endif /* SetFocus */
#ifdef GetCharWidth
#  undef GetCharWidth
#endif /* GetCharWidth */
#ifdef wsprintf
#  undef wsprintf
#endif /* wsprintf */

#endif /* ESRI_UNIX && __ESRI__ARCSDK__AXCONT_H__ */

#if !defined(wxUSE_UNICODE) && defined(ESRI_UNIX)
#undef _T
#undef UNICODE
#undef _UNICODE
#endif /* ! ESRI_WXCTL_UNICODE */

#include <AxCtl/ControlData.h>

#if defined(ESRI_WINDOWS)
#define WXUSINGDLL 1
#endif

#include <wx/wx.h>

class wxAxCtlImpl;

class ESRI_EXT_CLASS wxAxCtl
	: public wxWindow
{
public:
	wxAxCtl();
	wxAxCtl(wxWindow *parent, wxWindowID id, ControlDataPtr progID       , const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxString &name=wxPanelNameStr);
	wxAxCtl(wxWindow *parent, wxWindowID id, const char    *progID = NULL, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxString &name=wxPanelNameStr);
	~wxAxCtl();
	bool Show(bool show=true);
	HRESULT GetInterface(IUnknown **ppUnk);
	HRESULT AxSetCursor(HCURSOR cur);
	bool ProcessEvent(wxEvent &event);
private:
	void Initialize(const char *progID);
	wxAxCtlImpl *m_aximpl;
	DECLARE_DYNAMIC_CLASS(wxWindow)
};

#endif /* __ESRI_ARCSDK_AXCTL_WXAXCTL_H__ */
