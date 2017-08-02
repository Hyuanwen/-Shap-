#pragma once

#include "resource.h"
#include "DeuRasterDoc.h"
#include "DeuRasterTranDlg.h"
#include "DeuTabControl.h"

class CDeuRasterView : public CView
{
	DECLARE_DYNCREATE(CDeuRasterView)

protected:
	CDeuRasterView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDeuRasterView();

public:
	CDeuRasterDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
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
	/* 创建TabCtrl页内容 */
	void OnAddTab();
	BOOL AddView(CRuntimeClass* pViewClass, LPCTSTR lpszTitle, int nIcon);
	void DelTab(int nTabIndex);	
	void DelTabAll();
	void TabSelectSel(int nIndex);

	/* 激活父框架 */	
	void ActiveParentFrm();
	afx_msg void OnDestroy();

	/* 执行转换任务 */
	void ProcessTask();
	virtual void OnInitialUpdate();

	//刷新新任务Xml
	void RefreshTaskXml();
};


