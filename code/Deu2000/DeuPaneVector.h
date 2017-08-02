/*-----------------------------------
		 ¸¡¶¯Ãæ°å´°¿Ú
------------------------------------*/

#include "resource.h"
#include "DeuVectorView.h"

class CDeuPaneVector : public CXTPDialog
{
public:
	CDeuPaneVector(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_DLG_PANEL_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLbnSelchange();
	afx_msg void OnBnClickedTaskBatAdd();
	afx_msg void OnBnClickedTaskRemove();
	afx_msg void OnBnClickedTaskRemoveAll();
	afx_msg void OnBnClickedTaskProcess();
	
public:
	afx_msg void OnBnClickedTaskAdd();

protected:
	HICON m_hIcon;
	CEdit m_wndEdit[3];
	CFont m_fntEdit;
	CString m_strIniFileName;
	int nListIndex;

	DECLARE_MESSAGE_MAP()

public:
	CListBox m_ListBox;
	CDeuVectorView* p_View;
	void InsertListItem(const char *p_ItemName);
	void DelTaskItem(int nIndex);
};