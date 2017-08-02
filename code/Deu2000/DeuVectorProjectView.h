/////////////////////////////////////////////////////////////////////
//     ��Ŀ:	�����ǻ�ת�����
//     ���ߣ�	Create By hushichen
//     ����:	ʸ�� ת����ʾ��ͼ��� 
//	   CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////

#pragma once

#include "DeuVectorProjectDoc.h"
#include "DeuVectorProjectTranDlg.h"
#include "DeuTabControl.h"


class CDeuVectorProjectView : public CView
{
	DECLARE_DYNCREATE(CDeuVectorProjectView)

protected:
	CDeuVectorProjectView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDeuVectorProjectView();	

public:
	CDeuVectorProjectDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	int nTabHistoryIndex;

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	
public:
	CDeuTabControl m_wndTabControl;	
	
	/* ����TabCtrlҳ���� */
	void OnAddTab();
	BOOL AddView(CRuntimeClass* pViewClass, LPCTSTR lpszTitle, int nIcon);
	void DelTab(int nIndex);
	void DelTabAll();
	void TabSelectSel(int nIndex);

	/* ������ */
	void ActiveParentFrm();
	
	/* ִ��ת������ */
	void ProcessTask();

	virtual void OnInitialUpdate();
	//ˢ��������Xml
	void RefreshTaskXml();

};






