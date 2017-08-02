// XTPComboBox.h interface for the CXTPComboBox class.
//
// This file is a part of the XTREME CONTROLS MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

//{{AFX_CODEJOCK_PRIVATE
#if !defined(__XTPCOMBOBOX_H__)
#define __XTPCOMBOBOX_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Common/XTPWinThemeWrapper.h"

class _XTP_EXT_CLASS CXTPComboBoxEditCtrl : public CEdit
{

protected:

//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()

	//{{AFX_MSG(CXTPComboBox)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	void OnMouseLeave();
	void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
//}}AFX_CODEJOCK_PRIVATE

};

class _XTP_EXT_CLASS CXTPComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CXTPComboBox)

public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPComboBox object
	//-----------------------------------------------------------------------
	CXTPComboBox();

	~CXTPComboBox();

public:
	void SetTheme(XTPControlTheme nTheme);


	BOOL GetUseVisualStyle() const;

	void SetUseVisualStyle(BOOL bUseVisualStyle = TRUE);

	BOOL GetFlatStyle() const;

	void SetFlatStyle(BOOL bFlatStyle = TRUE);


	//-----------------------------------------------------------------------
	// Summary:
	//     This member function enables or disables auto completion.
	// Parameters:
	//     bEnable - TRUE to enable auto completion, otherwise FALSE.
	//-----------------------------------------------------------------------
	void EnableAutoCompletion(BOOL bEnable = TRUE);


protected:

	HBRUSH GetClientBrush(CDC* pDC);
	void FillSolidRect(HDC hdc, int x, int y, int cx, int cy, HBRUSH hBrush);
	void DrawFrame(HDC hdc, LPRECT lprc, int nSize, HBRUSH hBrush);
	void RefreshMetrics();
	void SetHighlighted(BOOL bHot);
	void RedrawFocusedFrame();
	BOOL NeedRedraw();


//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()

	BOOL PreCreateWindow(CREATESTRUCT& cs);
	void PreSubclassWindow();
	void Init();
	BOOL PreTranslateMessage(MSG* pMsg);

	//{{AFX_MSG(CXTPComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	void OnMouseLeave();
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnSysColorChange();

	BOOL OnEndSel();
	BOOL OnEditUpdate();
	//}}AFX_MSG
//}}AFX_CODEJOCK_PRIVATE


protected:
	BOOL m_bPreSubclassInit;

	BOOL m_bUseVisualStyle;
	int m_nTheme;
	BOOL m_bFlatStyle;

	CXTPWinThemeWrapper m_wrapperComboBox;

	BOOL m_bHighlighted;
	BOOL m_bFocused;

	int m_nThumbWidth;

	BOOL m_bAutoComp;
	BOOL m_bDisableAC;

	COLORREF m_clrBorderHot;
	COLORREF m_clrBorderNormal;
	COLORREF m_clrButtonNormal;
	COLORREF m_clrButtonPressed;
	COLORREF m_clrButtonHot;

	COLORREF m_clrButtonArrowPressed;
	COLORREF m_clrButtonArrowHot;
	COLORREF m_clrButtonArrowNormal;

	CXTPComboBoxEditCtrl m_wndEdit;
	friend class CXTPComboBoxEditCtrl;

};

AFX_INLINE BOOL CXTPComboBox::GetUseVisualStyle() const {
	return m_bUseVisualStyle;
}
AFX_INLINE BOOL CXTPComboBox::GetFlatStyle() const{
	return m_bFlatStyle;
}
AFX_INLINE void CXTPComboBox::SetFlatStyle(BOOL bFlatStyle/* = TRUE*/) {
	m_bFlatStyle = bFlatStyle;
	if (m_hWnd) Invalidate(FALSE);
}
AFX_INLINE void CXTPComboBox::EnableAutoCompletion(BOOL bEnable/*=TRUE*/) {
	m_bAutoComp = bEnable;
}


#endif // #if !defined(__XTPCOMBOBOX_H__)
