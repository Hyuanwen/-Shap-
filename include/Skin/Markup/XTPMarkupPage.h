// XTPMarkupPage.h: interface for the CXTPMarkupPage class.
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
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

#if !defined(__XTPMARKUPPAGE_H__)
#define __XTPMARKUPPAGE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupFrameworkElement.h"

class _XTP_EXT_CLASS CXTPMarkupPage : public CXTPMarkupFrameworkElement
{
	DECLARE_MARKUPCLASS(CXTPMarkupPage);
protected:
	CXTPMarkupPage();
	virtual ~CXTPMarkupPage();

public:
	void SetContent(CXTPMarkupUIElement* pContent);
	CXTPMarkupUIElement* GetContent() const;

public:
	virtual int GetVisualChildrenCount() const;
	virtual CXTPMarkupVisual* GetVisualChild(int nIndex) const;

protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual CSize ArrangeOverride(CSize szFinalSize);
	virtual void SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent);
	virtual BOOL HasContentObject() const;

	CXTPMarkupInputElement* InputHitTestOverride(CPoint /*point*/) const;


protected:
	CXTPMarkupUIElement* m_pContent;
};

AFX_INLINE int CXTPMarkupPage::GetVisualChildrenCount() const {
	return m_pContent != NULL ? 1 : 0;
}
AFX_INLINE CXTPMarkupVisual* CXTPMarkupPage::GetVisualChild(int nIndex) const {
	return nIndex == 0 ? m_pContent : NULL;
}


#endif // !defined(__XTPMARKUPPAGE_H__)
