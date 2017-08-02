// XTPMarkupPanel.h: interface for the CXTPMarkupPanel class.
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

#if !defined(__XTPMARKUPPANEL_H__)
#define __XTPMARKUPPANEL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupFrameworkElement.h"

class CXTPMarkupBrush;

class _XTP_EXT_CLASS CXTPMarkupUIElementCollection : public CXTPMarkupCollection
{
public:
	CXTPMarkupUIElementCollection();
	~CXTPMarkupUIElementCollection();

public:
	CXTPMarkupUIElement* GetItem(int nIndex) const;

};

class _XTP_EXT_CLASS CXTPMarkupPanel : public CXTPMarkupFrameworkElement
{
	DECLARE_MARKUPCLASS(CXTPMarkupPanel)

protected:
	CXTPMarkupPanel();
	virtual ~CXTPMarkupPanel();

public:
	CXTPMarkupUIElementCollection* GetChildren() const;

public:
	void SetBackground(CXTPMarkupBrush* brush);
	CXTPMarkupBrush* GetBackground() const;

protected:
	virtual int GetVisualChildrenCount() const;
	virtual CXTPMarkupVisual* GetVisualChild(int nIndex) const;

protected:
	virtual void SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent);
	virtual BOOL HasContentObject() const;
	virtual void OnRender(CXTPMarkupDrawingContext* drawingContext);
	virtual CXTPMarkupInputElement* InputHitTestOverride(CPoint point) const;

protected:
	CXTPMarkupUIElementCollection* m_pChildren;




public:
	static CXTPMarkupDependencyProperty* m_pBackgroundProperty;
};


AFX_INLINE CXTPMarkupUIElementCollection* CXTPMarkupPanel::GetChildren() const {
	return m_pChildren;
}
AFX_INLINE int CXTPMarkupPanel::GetVisualChildrenCount() const {
	return m_pChildren->GetCount();
}
AFX_INLINE CXTPMarkupVisual* CXTPMarkupPanel::GetVisualChild(int nIndex) const {
	return m_pChildren->GetItem(nIndex);
}

AFX_INLINE CXTPMarkupUIElement* CXTPMarkupUIElementCollection::GetItem(int nIndex) const {
	return nIndex >= 0 && nIndex < m_arrItems.GetSize() ? (CXTPMarkupUIElement*)m_arrItems[nIndex] : NULL;
}


#endif // !defined(__XTPMARKUPPANEL_H__)
