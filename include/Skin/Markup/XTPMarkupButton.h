// XTPMarkupButton.h: interface for the CXTPMarkupButton class.
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

#if !defined(__XTPMARKUPBUTTON_H__)
#define __XTPMARKUPBUTTON_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupControl.h"
#include "Common/XTPWinThemeWrapper.h"

class CXTPMarkupBrush;
class CXTPMarkupBuilder;

class _XTP_EXT_CLASS CXTPMarkupButtonBase : public CXTPMarkupContentControl
{
	DECLARE_MARKUPCLASS(CXTPMarkupButtonBase);

protected:
	CXTPMarkupButtonBase();

protected:
	void OnMouseLeave(CXTPMarkupMouseEventArgs* e);
	void OnMouseEnter(CXTPMarkupMouseEventArgs* e);

	void OnMouseLeftButtonUp(CXTPMarkupMouseButtonEventArgs* e);
	void OnMouseLeftButtonDown(CXTPMarkupMouseButtonEventArgs* e);

	void OnLostMouseCapture(CXTPMarkupMouseEventArgs* e);

public:
	BOOL IsPressed() const;

protected:
	void SetPressed(BOOL bPressed);

protected:
	virtual void OnClick();



protected:
	BOOL m_bPushed;
	BOOL m_bMouseOver;
	CXTPWinThemeWrapper m_themeButton;

public:
	static CXTPMarkupDependencyProperty* m_pIsPressedProperty;
	static CXTPMarkupRoutedEvent* m_pClickEvent;
};

class _XTP_EXT_CLASS CXTPMarkupButton : public CXTPMarkupButtonBase
{
	DECLARE_MARKUPCLASS(CXTPMarkupButton);

protected:
	CXTPMarkupButton();
	virtual ~CXTPMarkupButton();

protected:
	void OnRender(CXTPMarkupDrawingContext* pDC);
	void OnRenderFocusVisual(CXTPMarkupDrawingContext* drawingContext);
	CSize ArrangeOverride(CSize szFinalSize);
	CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);

public:
};

class _XTP_EXT_CLASS CXTPMarkupToggleButton : public CXTPMarkupButtonBase
{
	DECLARE_MARKUPCLASS(CXTPMarkupToggleButton);

public:
	void SetChecked(BOOL bChecked);
	BOOL GetChecked() const;

	BOOL IsThreeState() const;
	void SetThreeState(BOOL bThreeState);

protected:
	virtual void OnClick();
	virtual void OnToggle();

	virtual void OnChecked(CXTPMarkupRoutedEventArgs* e);
	virtual void OnUnchecked(CXTPMarkupRoutedEventArgs* e);
	virtual void OnIndeterminate(CXTPMarkupRoutedEventArgs* e);

protected:
	static void AFX_CDECL OnIsCheckedChanged(CXTPMarkupObject* d, CXTPMarkupPropertyChangedEventArgs* e);
	static CXTPMarkupObject* AFX_CDECL ConvertIsChecked(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pObject);



public:
	static CXTPMarkupDependencyProperty* m_pIsThreeStateProperty;
	static CXTPMarkupDependencyProperty* m_pIsCheckedProperty;
	static CXTPMarkupRoutedEvent* m_pCheckedEvent;
	static CXTPMarkupRoutedEvent* m_pUncheckedEvent;
	static CXTPMarkupRoutedEvent* m_pIndeterminateEvent;

};

class _XTP_EXT_CLASS CXTPMarkupCheckBox : CXTPMarkupToggleButton
{
	DECLARE_MARKUPCLASS(CXTPMarkupCheckBox);

protected:
	CXTPMarkupCheckBox();
	~CXTPMarkupCheckBox();

	void OnRender(CXTPMarkupDrawingContext* pDC);
	void OnRenderFocusVisual(CXTPMarkupDrawingContext* drawingContext);
	CSize ArrangeOverride(CSize szFinalSize);
	CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);

};

class _XTP_EXT_CLASS CXTPMarkupRadioButton : CXTPMarkupToggleButton
{
	DECLARE_MARKUPCLASS(CXTPMarkupRadioButton);

protected:
	CXTPMarkupRadioButton();
	~CXTPMarkupRadioButton();

protected:
	void OnRender(CXTPMarkupDrawingContext* pDC);
	void OnRenderFocusVisual(CXTPMarkupDrawingContext* drawingContext);
	CSize ArrangeOverride(CSize szFinalSize);
	CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);

protected:
	void OnToggle();
	void OnChecked(CXTPMarkupRoutedEventArgs* e);

private:
	void UpdateRadioButtonGroup();

};


AFX_INLINE void CXTPMarkupToggleButton::SetChecked(BOOL bChecked) {
	SetValue(m_pIsCheckedProperty, CXTPMarkupEnum::CreateValue(bChecked));
}
AFX_INLINE BOOL CXTPMarkupToggleButton::GetChecked() const {
	CXTPMarkupEnum* pValue = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pIsCheckedProperty));
	return pValue != NULL ? (BOOL)(int)*pValue : FALSE;
}
AFX_INLINE BOOL CXTPMarkupToggleButton::IsThreeState() const {
	CXTPMarkupBool* pValue = MARKUP_STATICCAST(CXTPMarkupBool, GetValue(m_pIsThreeStateProperty));
	return pValue != NULL ? (BOOL)*pValue : FALSE;
}
AFX_INLINE void CXTPMarkupToggleButton::SetThreeState(BOOL bThreeState) {
	SetValue(m_pIsThreeStateProperty, CXTPMarkupBool::CreateValue(bThreeState));
}
AFX_INLINE BOOL CXTPMarkupButtonBase::IsPressed() const {
	CXTPMarkupBool* pValue = MARKUP_STATICCAST(CXTPMarkupBool, GetValue(m_pIsPressedProperty));
	return pValue ? (BOOL)*pValue : FALSE;
}
#endif // !defined(__XTPMARKUPBUTTON_H__)
