// Deu2000View.h : CDeuViewView 类的接口
//

#pragma once

#include "deudmap.h"
#include "DeuViewerDoc.h"
#include "DeuTaskProcess.h"

class CDeuViewView : public CFormView
{

	DECLARE_DYNCREATE(CDeuViewView)

public: // 仅从序列化创建
	CDeuViewView();

// 属性
public:
	enum { IDD = IDD_DLG_VIEW };

// 操作
public:
	CDeuViewerDoc* GetDocument() const;
	//BOOL AddView(CRuntimeClass* pViewClass);	

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDeuViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	virtual void OnInitialUpdate();
	
public:
	//CDeuDlgVector m_Dlg;
	//CButton m_button;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	void OnZoomLoad(const char* sz_file);  //加载视图
	void OnZoomOut();	 //视图放大
	void OnZoomIn();	 //视图缩小
	void OnZoomMove();	 //视图平移
	void OnZoomAllPic(); //视图全图

	void OnZoomPre();   //上一张视图
	void OnZoomNext();  //下一张视图
	void OnSelect();	
	void OnSelectCancel();
	void OnClearLayers();
	void OnDefaultState(); //默认状态

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	void SelectBoxFinalMap(long left, long right, long bottom, long top);
public:
	CDeuDMap m_MapCtrl;
	CDeuTaskProcess m_TaskProcess;
};

//#ifndef _DEBUG  // Deu2000View.cpp 中的调试版本
//inline CDeuViewerDoc* CDeuViewView::GetDocument() const
//   { return reinterpret_cast<CDeuViewerDoc*>(m_pDocument); }
//#endif

