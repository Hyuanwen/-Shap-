#pragma once

#include "resource.h"
#include "DeuProjectView.h"

/*-----------------------------------
		 ¸¡¶¯Ãæ°å´°¿Ú
------------------------------------*/
class CDeuPaneProject : public CXTPDialog
{
public:
	CDeuPaneProject(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_DLG_PANEL_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedTaskBatAdd();
	afx_msg void OnBnClickedTaskRemove();
	afx_msg void OnBnClickedTaskRemoveAll();
	afx_msg void OnBnClickedTaskProcess();
	afx_msg void OnLbnSelchange();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedTaskAdd();
	
protected:
	HICON m_hIcon;
	CEdit m_wndEdit[3];
	CFont m_fntEdit;
	CString m_strIniFileName;

private:
	CListBox m_ListBox;
	int nListIndex;

public:
	CDeuProjectView* p_View;
	void DelTaskItem(int nIndex);
	void InsertListItem(const char *p_ItemName);
	//CButton m_Btn_TaskAdd;
	//CButton m_Btn_TaskBatAdd;
	//CButton m_Btn_TaskRemove;
	//CButton m_Btn_TaskRemoveAll;
	//CButton m_Btn_TaskProcess;
};
