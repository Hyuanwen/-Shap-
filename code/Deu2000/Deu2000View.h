// Deu2000View.h : interface of the CDeu2000View class
//


#pragma once
#include "DeuPertySheet.h"
#include "Deu2000Doc.h"
#include "DeuDlgContainer.h"

class CDeu2000View : public CScrollView
{
protected: // create from serialization only
	CDeu2000View();
	DECLARE_DYNCREATE(CDeu2000View)

// Attributes
public:
	CDeu2000Doc* GetDocument() const;

// Operations
public:
	
public:
	int m_HScrollMax;
	int m_HScrollPos;
 
// Overrides
public:
	//afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	virtual void OnInitialUpdate(); // called first time after construct
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDeu2000View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	//CDeuPertySheet *m_Sheet;
	//CDeuPertySheet m_Sheet(CBCGPPropertySheet::PropSheetLook_OneNoteTabs,IDB_TOOLBAR256, 16,TRUE);

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

public:
	CDeuDlgContainer m_DlgContainer;
	afx_msg void OnPaint();	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	void InitTaskTab();

};

#ifndef _DEBUG  // debug version in Deu2000View.cpp
inline CDeu2000Doc* CDeu2000View::GetDocument() const
   { return reinterpret_cast<CDeu2000Doc*>(m_pDocument); }
#endif

