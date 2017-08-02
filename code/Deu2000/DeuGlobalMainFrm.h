/////////////////////////////////////////////////////////////////////
//     ��Ŀ:	�����ǻ�ת�����	
//     ����:	���ĵ��������
//     ���ߣ�		hushichen
//     �޸��ߣ�		---
//     ��Ҫ������   ---
//     �汾:		v1.0
//     CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
#include "DeuGlobalParam.h"
#include "DeuPanelTask.h"
#include "DeuPaneProperty.h"
#include "DeuDlgDataSrc.h"
#include "DeuDlgDataSrcCustom.h"
#include "DeuDlgGridSetting.h"

#pragma once
class CDeuGlobalMainFrame : public CXTPMDIFrameWnd
{ 
	DECLARE_DYNAMIC(CDeuGlobalMainFrame)
public:
	CDeuGlobalMainFrame();
	virtual ~CDeuGlobalMainFrame();

public:
	CXTPTabClientWnd	   m_MTIClientWnd;
	CXTPDockingPaneManager m_paneManager;

public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeuGlobalMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CXTPStatusBar  m_wndStatusBar;	
	CEdit          m_wndPanes[6];	

protected:
	afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void    OnClose();
	afx_msg void    OnCustomize();
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowTranResult(WPARAM wParam, LPARAM lParam);
	afx_msg int     OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);

	afx_msg void    OnShow();
	afx_msg void    OnShowView();
	afx_msg void    ViewZoomIn();
	afx_msg void    ViewZoomOut();
	afx_msg void    ViewZoomMove();
	afx_msg void    ViewZoomAll();     //ȫͼ
	afx_msg void    ViewSelect();
	afx_msg void    ViewSelectCancel();
	afx_msg void    ViewClearLayers(); //�����
	afx_msg void    ViewSetDefault();  //�����
	afx_msg void    ViewOverLap();     //�ص��ȶ�
	afx_msg void    ViewPrve();
	afx_msg void    ViewLast();

	//add by chenyong 2013-4-7
	afx_msg void	OnDefineElliposid();
	afx_msg void	OnDefineHorizatol();
	afx_msg void	OnDefineTran();
	afx_msg void	OnDefineLinear();
	afx_msg void	OnDefineAngular();
	afx_msg void	OnShowDataSource();//ȫͼ
	DECLARE_MESSAGE_MAP()

public:
	CDeuPanelTask    m_wndTaskPanel;
	CDeuPaneProperty m_Dlgpanel;
	CXTPDockingPane* pwndOverviewPane;
	CXTPDockingPane* pwndMessagePane;
	CEdit            m_Edit_msg;

	/* ӥ��������ʾ */
	void ShowOverviewPanel();
	
	/* �û������ڵ���ʾ */
	void ShowUsersManager();

	/* �û��鴰�ڵ���ʾ */
	void ShowUserGroupsManager();

	void ShowMessagePane(BOOL IsClear, CString m_str);

	void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);
};




