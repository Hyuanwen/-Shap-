/////////////////////////////////////////////////////////////////////
//
//     项目: 德毅智慧转换软件
//
//     作者：   hushichen
//
//     描述:	矢量投影操作窗口类
//
//     版本:	V1.0
//	   CopyRight 2010-2011 ljdy Corporation All Rights Reserved
//
/////////////////////////////////////////////////////////////////////

#pragma once
#include "resource.h"
#include "DeuDlgCommCP.h"
#include "afxwin.h"

class CDeuVectorProjectTranDlg : public CDialog
{
	DECLARE_DYNCREATE(CDeuVectorProjectTranDlg)

public:
	CDeuVectorProjectTranDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CDeuVectorProjectTranDlg();
	enum { IDD = IDD_DLG_TASK };

//#ifdef _DEBUG
//	virtual void AssertValid() const;
//#ifndef _WIN32_WCE
//	virtual void Dump(CDumpContext& dc) const;
//#endif
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedBtnInput();
	afx_msg void OnBnClickedBtnOutput();
	void OnCoordinateInput();
	void OnCoordinateOutput();
	DECLARE_MESSAGE_MAP()

public:
	void LoadExistData(CString m_str[6]);
	void TranFinish(const char* strTimeMsg);	//转换结束
	void ShowStatusPanel(CString str);
	BOOL CheckControl();
	BOOL CheckCoord();
	void DisableAllController();
	void EnbleAllController();
	void InitTransFormat();

public:
	CDeuDlgCommCP m_Controlpoint_Dlg;
	CComboBox m_ComboInput;
	CComboBox m_ComboOutput;
	CComboBox m_ComboTranModel;
	CComboBox m_ComboReCollect;
	CComboBox m_ComboTransfer;
	CEdit m_edit_InputFile;
	CEdit m_edit_OutputFile;
	CEdit m_edit_InCoord;
	CEdit m_edit_OutCoord;	
	CButton m_Annotation;
	CString strGuid;

	//文件
	CStringArray _FilsList;
	CStringArray _FilsList_selected;
	CStringArray _TablesList;
	CStringArray _TablesList_selected;
	CString strLastPath;

	//记录数据库的连接信息
	CString strDBSid_Src, strDBUser_Src, strDBPwd_Src;
	CString strDBSid_Dest, strDBUser_Dest, strDBPwd_Dest;
	
	int iModel;
	CXTPProgressCtrl m_Progress;
	BOOL IsAdditional;
	
private:
//	virtual void OnInitialUpdate(); 
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCbnSelchangeComboTranmodel();
	afx_msg void OnCbnSelchangeComboInput();
	afx_msg void OnCbnSelchangeComboOutput();	
	void ClearCache(BOOL IsOut=FALSE);
	afx_msg LRESULT OnProgressStep(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
public:
	afx_msg void OnBnClickedButton1();	
	afx_msg void OnBnClickedRadio1();

	//add by chenyong 2013-11-25
	IWorkspacePtr					m_pSrcWS;
	IWorkspacePtr					m_pDesWS;
	IWorkspacePtr	GetSrcWorkspace() const;
	IWorkspacePtr	GetDesWorkspace() const;

	vector<STR_SDEINFO>	GetSelVec() const;
	vector<STR_SDEINFO>				m_vecSelect;
};



