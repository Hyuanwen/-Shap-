// XTPMarkupImage.h: interface for the CXTPMarkupImage class.
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

#if !defined(__XTPMARKUPIMAGE_H__)
#define __XTPMARKUPIMAGE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupFrameworkElement.h"

class CXTPImageManagerIcon;
class CXTPImageManager;

#include "XTPMarkupShape.h"

class _XTP_EXT_CLASS CXTPMarkupImage : public CXTPMarkupFrameworkElement
{
	DECLARE_MARKUPCLASS(CXTPMarkupImage)

protected:
	CXTPMarkupImage();
	virtual ~CXTPMarkupImage();

public:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize constraint);
	virtual CSize ArrangeOverride(CSize arrangeSize);
	virtual void OnRender(CXTPMarkupDrawingContext* pDC);

	CString GetSource();
	void SetSource(LPCTSTR lpszSource);

	XTPMarkupStretch GetStretch() const;
	void SetStretch(XTPMarkupStretch stretch);

protected:
	void LoadImage(int cx);
	CSize MeasureArrangeHelper(CSize inputSize);




protected:
	CXTPImageManager* m_pImageManager;
	CXTPImageManagerIcon* m_pImage;

public:
	static CXTPMarkupDependencyProperty* m_pSourceProperty;
	static CXTPMarkupDependencyProperty* m_pStretchProperty;
};

AFX_INLINE XTPMarkupStretch CXTPMarkupImage::GetStretch() const {
	CXTPMarkupEnum* pValue =  MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pStretchProperty));
	return pValue != NULL ? (XTPMarkupStretch)(int)*pValue : xtpMarkupStretchNone;
}
AFX_INLINE void CXTPMarkupImage::SetStretch(XTPMarkupStretch stretch) {
	SetValue(m_pStretchProperty, CXTPMarkupEnum::CreateValue(stretch));
}


#endif // !defined(__XTPMARKUPIMAGE_H__)
