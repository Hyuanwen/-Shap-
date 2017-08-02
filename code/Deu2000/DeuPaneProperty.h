#if !defined(AFX_DIALOGPANESDLG_H__96F8256D_412A_41BA_A8E6_75A9693E03C1__INCLUDED_)
#define AFX_DIALOGPANESDLG_H__96F8256D_412A_41BA_A8E6_75A9693E03C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "DeuGlobal.h"

/********************************************

			 Ù–‘»ŒŒÒ ˜

*********************************************/
class CDeuPanelPropertyTree : public CWnd
{
	DECLARE_DYNAMIC(CDeuPanelPropertyTree)

public:
	CDeuCtrlTaskTree m_wndSolutionView;
	CImageList m_ilSolutionView;
	CDeuPanelPropertyTree();
	virtual ~CDeuPanelPropertyTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
}; 

class CDeuPaneProperty : public CXTPDialog
{
public:
	CDeuPaneProperty(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_DLG_PROPERTY };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	CXTPDockingPaneManager m_paneManager;
	CXTPPropertyGrid m_wndPropertyGrid;
	CString m_strIniFileName;

protected:
	HICON m_hIcon;
	CEdit m_wndEdit[3];
	CFont m_fntEdit;
	CDeuPanelPropertyTree m_wndTaskPanel;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);		
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGPANESDLG_H__96F8256D_412A_41BA_A8E6_75A9693E03C1__INCLUDED_)




