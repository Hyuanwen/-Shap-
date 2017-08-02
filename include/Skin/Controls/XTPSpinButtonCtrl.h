// XTPSpinButtonCtrl.h interface for the CXTPSpinButtonCtrl class.
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
#if !defined(__XTPSPINBUTTONCTRL_H__)
#define __XTPSPINBUTTONCTRL_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Common/XTPWinThemeWrapper.h"

class CXTPEdit;

class _XTP_EXT_CLASS CXTPSpinButtonCtrl : public CSpinButtonCtrl
{
	DECLARE_DYNAMIC(CXTPSpinButtonCtrl)

public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPSpinButtonCtrl object
	//-----------------------------------------------------------------------
	CXTPSpinButtonCtrl();

	~CXTPSpinButtonCtrl();

public:
	void SetTheme(XTPControlTheme nTheme);

	BOOL GetUseVisualStyle() const;

	void SetUseVisualStyle(BOOL bUseVisualStyle = TRUE);


protected:
	UINT HitTest(CPoint pt);
	void OnDraw(CDC* pDC);
	void RefreshMetrics();
	BOOL HasSharedBorder() const;

	CXTPEdit* GetEditBuddy() const;

	void DrawVisualStyle(CDC* pDC);
	void DrawOffice2007(CDC* pDC);
	void DrawFlat(CDC* pDC);
	void DrawFlatButton(CDC* pDC, UINT nButton);
	void DrawArrowGlyph2(CDC* pDC, CRect rcArrow, BOOL bHorz, BOOL bUpArrow, BOOL bEnabled);
	void DrawStandard(CDC* pDC);
	BOOL IsVertical() const;
	CRect GetButtonRect(int nButton);
	void Init();

protected:

	//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	void PreSubclassWindow();


	//{{AFX_MSG(CXTPSpinButtonCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
//}}AFX_CODEJOCK_PRIVATE


protected:
	CXTPWinThemeWrapper m_themeSpin;
	BOOL m_bUseVisualStyle;
	int m_nTheme;
	BOOL m_bPreSubclassInit;

	COLORREF m_crBackPushed;
	COLORREF m_crBackHilite;
	COLORREF m_crBorderHilite;
	COLORREF m_crBorder;
	COLORREF m_crBack;
	UINT m_nHotButton;
	UINT m_nPressedButton;
};


AFX_INLINE BOOL CXTPSpinButtonCtrl::GetUseVisualStyle() const {
	return m_bUseVisualStyle;
}

#endif // #if !defined(__XTPSPINBUTTONCTRL_H__)
