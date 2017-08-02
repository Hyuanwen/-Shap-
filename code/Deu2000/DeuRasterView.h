#pragma once

#include "resource.h"
#include "DeuRasterDoc.h"
#include "DeuRasterTranDlg.h"
#include "DeuTabControl.h"

class CDeuRasterView : public CView
{
	DECLARE_DYNCREATE(CDeuRasterView)

protected:
	CDeuRasterView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDeuRasterView();

public:
	CDeuRasterDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP() 
	
public:	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnTabClose(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CDeuTabControl m_wndTabControl;
	int nTabHistoryIndex;

public:
	/* ����TabCtrlҳ���� */
	void OnAddTab();
	BOOL AddView(CRuntimeClass* pViewClass, LPCTSTR lpszTitle, int nIcon);
	void DelTab(int nTabIndex);	
	void DelTabAll();
	void TabSelectSel(int nIndex);

	/* ������ */	
	void ActiveParentFrm();
	afx_msg void OnDestroy();

	/* ִ��ת������ */
	void ProcessTask();
	virtual void OnInitialUpdate();

	//ˢ��������Xml
	void RefreshTaskXml();
};


