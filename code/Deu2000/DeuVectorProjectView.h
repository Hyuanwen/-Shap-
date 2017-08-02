/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     作者：	Create By hushichen
//     描述:	矢量 转换显示视图框架 
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
	CDeuVectorProjectView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDeuVectorProjectView();	

public:
	CDeuVectorProjectDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
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
	
	/* 创建TabCtrl页内容 */
	void OnAddTab();
	BOOL AddView(CRuntimeClass* pViewClass, LPCTSTR lpszTitle, int nIcon);
	void DelTab(int nIndex);
	void DelTabAll();
	void TabSelectSel(int nIndex);

	/* 激活父框架 */
	void ActiveParentFrm();
	
	/* 执行转换过程 */
	void ProcessTask();

	virtual void OnInitialUpdate();
	//刷新新任务Xml
	void RefreshTaskXml();

};






