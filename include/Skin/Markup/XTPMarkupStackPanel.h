// XTPMarkupStackPanel.h: interface for the CXTPMarkupStackPanel class.
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

#if !defined(__XTPMARKUPSTACKPANEL_H__)
#define __XTPMARKUPSTACKPANEL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupPanel.h"

class _XTP_EXT_CLASS CXTPMarkupStackPanel : public CXTPMarkupPanel
{
	DECLARE_MARKUPCLASS(CXTPMarkupStackPanel)
protected:
	CXTPMarkupStackPanel();
	virtual ~CXTPMarkupStackPanel();

public:
	XTPMarkupOrientation GetOrientation() const;
	void SetOrientation(XTPMarkupOrientation orientation);

protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual CSize ArrangeOverride(CSize szFinalSize);



protected:
	static CXTPMarkupDependencyProperty* m_pOrientationProperty;
};

class _XTP_EXT_CLASS CXTPMarkupWrapPanel : public CXTPMarkupPanel
{
	DECLARE_MARKUPCLASS(CXTPMarkupWrapPanel)
protected:
	CXTPMarkupWrapPanel();
	virtual ~CXTPMarkupWrapPanel();

public:
	XTPMarkupOrientation GetOrientation() const;
	void SetOrientation(XTPMarkupOrientation orientation);

protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual CSize ArrangeOverride(CSize szFinalSize);

protected:
	void ArrangeLine(int nPanelHeight, int nLineHeight, int nFirstElement, int nCount);


protected:
	static CXTPMarkupDependencyProperty* m_pOrientationProperty;
	static CXTPMarkupDependencyProperty* m_pItemHeightProperty;
	static CXTPMarkupDependencyProperty* m_pItemWidthProperty;

};

enum XTPMarkupDock
{
	xtpMarkupDockLeft,
	xtpMarkupDockTop,
	xtpMarkupDockRight,
	xtpMarkupDockBottom
};

class _XTP_EXT_CLASS CXTPMarkupDockPanel : public CXTPMarkupPanel
{
	DECLARE_MARKUPCLASS(CXTPMarkupDockPanel)
protected:
	CXTPMarkupDockPanel();
	virtual ~CXTPMarkupDockPanel();

public:
	static XTPMarkupDock AFX_CDECL GetDock(CXTPMarkupUIElement* pElement);
	static void AFX_CDECL SetDock(CXTPMarkupUIElement* pElement, XTPMarkupDock dock);

public:
	BOOL GetLastChildFill() const;
	void SetLastChildFill(BOOL bLastChildFill);


protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual CSize ArrangeOverride(CSize szFinalSize);

private:
	static void AFX_CDECL OnDockChanged(CXTPMarkupObject* d, CXTPMarkupPropertyChangedEventArgs* e);
	static CXTPMarkupObject* AFX_CDECL ConvertDock(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pObject);


protected:
	static CXTPMarkupDependencyProperty* m_pLastChildFillProperty;
	static CXTPMarkupDependencyProperty* m_pDockProperty;
};


class _XTP_EXT_CLASS CXTPMarkupUniformGrid : public CXTPMarkupPanel
{
	DECLARE_MARKUPCLASS(CXTPMarkupUniformGrid)
protected:
	CXTPMarkupUniformGrid();
	virtual ~CXTPMarkupUniformGrid();

public:
	int GetColumns() const;
	int GetRows() const;

	void SetColumns(int nColumns);
	void SetRows(int nRows);

	int GetFirstColumn() const;
	void SetFirstColumn(int nFirstColumn);

protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual CSize ArrangeOverride(CSize szFinalSize);



private:
	void UpdateComputedValues();

private:
	int m_nColumns;
	int m_nRows;
	int m_nFirstColumn;

public:
	static CXTPMarkupDependencyProperty* m_pFirstColumnProperty;
	static CXTPMarkupDependencyProperty* m_pColumnsProperty;
	static CXTPMarkupDependencyProperty* m_pRowsProperty;
};




AFX_INLINE void CXTPMarkupDockPanel::SetLastChildFill(BOOL bLastChildFill) {
	SetValue(m_pLastChildFillProperty, CXTPMarkupBool::CreateValue(bLastChildFill));
}
AFX_INLINE BOOL CXTPMarkupDockPanel::GetLastChildFill() const {
	CXTPMarkupBool* pLastChildFill = MARKUP_STATICCAST(CXTPMarkupBool, GetValue(m_pLastChildFillProperty));
	return pLastChildFill != NULL ? (BOOL)*pLastChildFill : TRUE;
}
AFX_INLINE int CXTPMarkupUniformGrid::GetColumns() const {
	CXTPMarkupInt* pColumns = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pColumnsProperty));
	return pColumns != NULL ? (int)*pColumns : 0;
}
AFX_INLINE int CXTPMarkupUniformGrid::GetRows() const{
	CXTPMarkupInt* pRows = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pRowsProperty));
	return pRows != NULL ? (int)*pRows : 0;
}
AFX_INLINE int CXTPMarkupUniformGrid::GetFirstColumn() const {
	CXTPMarkupInt* pFirstColumn = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pFirstColumnProperty));
	return pFirstColumn != NULL ? (int)*pFirstColumn : 0;
}
AFX_INLINE void CXTPMarkupUniformGrid::SetFirstColumn(int nFirstColumn){
	SetValue(m_pFirstColumnProperty, new CXTPMarkupInt(nFirstColumn));
}
AFX_INLINE void CXTPMarkupUniformGrid::SetColumns(int nColumns){
	SetValue(m_pColumnsProperty, new CXTPMarkupInt(nColumns));
}
AFX_INLINE void CXTPMarkupUniformGrid::SetRows(int nRows){
	SetValue(m_pRowsProperty, new CXTPMarkupInt(nRows));
}


#endif // !defined(__XTPMARKUPSTACKPANEL_H__)
