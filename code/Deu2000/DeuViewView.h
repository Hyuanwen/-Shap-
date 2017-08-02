// Deu2000View.h : CDeuViewView ��Ľӿ�
//

#pragma once

#include "deudmap.h"
#include "DeuViewerDoc.h"
#include "DeuTaskProcess.h"

class CDeuViewView : public CFormView
{

	DECLARE_DYNCREATE(CDeuViewView)

public: // �������л�����
	CDeuViewView();

// ����
public:
	enum { IDD = IDD_DLG_VIEW };

// ����
public:
	CDeuViewerDoc* GetDocument() const;
	//BOOL AddView(CRuntimeClass* pViewClass);	

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDeuViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
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
	
	void OnZoomLoad(const char* sz_file);  //������ͼ
	void OnZoomOut();	 //��ͼ�Ŵ�
	void OnZoomIn();	 //��ͼ��С
	void OnZoomMove();	 //��ͼƽ��
	void OnZoomAllPic(); //��ͼȫͼ

	void OnZoomPre();   //��һ����ͼ
	void OnZoomNext();  //��һ����ͼ
	void OnSelect();	
	void OnSelectCancel();
	void OnClearLayers();
	void OnDefaultState(); //Ĭ��״̬

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	void SelectBoxFinalMap(long left, long right, long bottom, long top);
public:
	CDeuDMap m_MapCtrl;
	CDeuTaskProcess m_TaskProcess;
};

//#ifndef _DEBUG  // Deu2000View.cpp �еĵ��԰汾
//inline CDeuViewerDoc* CDeuViewView::GetDocument() const
//   { return reinterpret_cast<CDeuViewerDoc*>(m_pDocument); }
//#endif

