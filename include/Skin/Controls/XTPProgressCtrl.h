// XTPProgressCtrl.h interface for the CXTPProgressCtrl class.
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
#if !defined(__XTPPROGRESSCTRL_H__)
#define __XTPPROGRESSCTRL_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Common/XTPWinThemeWrapper.h"

#ifndef PBS_MARQUEE
#define PBS_MARQUEE             0x08
#endif

#ifndef PBM_SETMARQUEE
#define PBM_SETMARQUEE          (WM_USER+10)
#endif


class _XTP_EXT_CLASS CXTPProgressCtrl : public CProgressCtrl
{
	DECLARE_DYNAMIC(CXTPProgressCtrl)

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPProgressCtrl object
	//-----------------------------------------------------------------------
	CXTPProgressCtrl();


public:
	void SetBarColor(COLORREF clrBarColor);
	BOOL SetMarquee(BOOL fMarqueeMode, int nInterval);
	COLORREF SetBkColor(COLORREF clrNew);
	COLORREF SetTextColor(COLORREF clrNew);


public:
	void SetTheme(XTPControlTheme nTheme);

	BOOL GetUseVisualStyle() const;

	void SetUseVisualStyle(BOOL bUseVisualStyle = TRUE);

	BOOL GetFlatStyle() const;

	void SetFlatStyle(BOOL bFlatStyle = TRUE);

protected:

protected:
	void RefreshMetrics();
	void DrawNcBorders(CDC* pDC, CRect rc);
	void DoPaint(CDC* pDC);
	void PaintOffice2007(CDC* pDC);
	COLORREF GetBackColor();
	void DoStep(int nStep);

//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()

	BOOL PreCreateWindow(CREATESTRUCT& cs);
	void PreSubclassWindow();
	void Init();

	//{{AFX_MSG(CXTPEdit)

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();

	LRESULT OnSetPos(WPARAM /*wParam*/, LPARAM /*lParam*/);
	LRESULT OnStepIt(WPARAM /*wParam*/, LPARAM /*lParam*/);
	void OnTimer(UINT_PTR nIDEvent);
	LRESULT OnStartMarquee(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
//}}AFX_CODEJOCK_PRIVATE


protected:
	BOOL m_bPreSubclassInit;
	int m_nMarqueePos;

	BOOL m_bUseVisualStyle;
	int m_nMarqueeDelay;
	CXTPWinThemeWrapper m_wrapperProgress;
	int m_nTheme;

	CXTPPaintManagerColor m_clrBorderNormal;
	CXTPPaintManagerColor m_clrBarColor;
	CXTPPaintManagerColor m_clrTextColor;
	CXTPPaintManagerColor m_clrBackColor;
	BOOL m_bFlatStyle;
};
AFX_INLINE BOOL CXTPProgressCtrl::SetMarquee(BOOL fMarqueeMode, int nInterval) {
	ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, PBM_SETMARQUEE, (WPARAM)fMarqueeMode, (LPARAM)nInterval);
}


AFX_INLINE BOOL CXTPProgressCtrl::GetUseVisualStyle() const {
	return m_bUseVisualStyle;
}
AFX_INLINE BOOL CXTPProgressCtrl::GetFlatStyle() const{
	return m_bFlatStyle;
}
AFX_INLINE void CXTPProgressCtrl::SetFlatStyle(BOOL bFlatStyle/* = TRUE*/) {
	m_bFlatStyle = bFlatStyle;
	if (m_hWnd) Invalidate(FALSE);
}

#endif // #if !defined(__XTPPROGRESSCTRL_H__)
