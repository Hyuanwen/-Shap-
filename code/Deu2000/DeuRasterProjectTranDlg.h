/////////////////////////////////////////////////////////////////////
//
//     项目: 德毅智慧转换软件
//     作者：   hushichen
//     描述:	栅格转换操作窗口容器类
//     版本:	V1.0
//	   CopyRight 2010-2011 ljdy Corporation All Rights Reserved
//
/////////////////////////////////////////////////////////////////////

#pragma once

#include "resource.h"
#include "DeuDlgCommCP.h"
#include "RasterSetting.h"

class CDeuRasterProjectTranDlg : public CDialog
{
	DECLARE_DYNCREATE(CDeuRasterProjectTranDlg)

public:
	CDeuRasterProjectTranDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CDeuRasterProjectTranDlg();
	enum { IDD = IDD_DLG_TASK };

//#ifdef _DEBUG
//	virtual void AssertValid() const;
//#ifndef _WIN32_WCE
//	virtual void Dump(CDumpContext& dc) const;
//#endif
//#endif

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnInput();
	afx_msg void OnBnClickedBtnOutput();
	afx_msg void OnCoordinateInput();
	afx_msg void OnCoordinateOutput();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnCbnSelchangeComboTranmodel();
	afx_msg void OnCbnSelchangeComboInput();
	afx_msg void OnCbnSelchangeComboOutput();
	afx_msg void OnCbnSelchangeComboRecollect();
	afx_msg void OnBnClickedBtnSetting();
	afx_msg void OnBnClickedRadioResample();
	afx_msg void OnBnClickedRadioTransfer();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	LRESULT OnTranformFinsh(WPARAM wParam, LPARAM lParam);
	LRESULT OnTranformFinshAll(WPARAM wParam, LPARAM lParam);
	LRESULT OnProgressStep(WPARAM wParam, LPARAM lParam);
	LRESULT OnLoadWait(WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	
	void ClearCache(BOOL IsOut=FALSE);

public:
	int iModel;
	int iReCollect;
	BOOL m_bResample;//TRUE = Resample FALSE = Transfer

	//文件
	CStringArray _FilsList;
	CStringArray _FilsList_selected;
	CStringArray _TablesList;
	CStringArray _TablesList_selected;

	CDeuDlgCommCP m_Controlpoint_Dlg;
	CComboBox m_ComboInput;
	CComboBox m_ComboOutput;
	CComboBox m_ComboTranModel;
	CComboBox m_ComboReCollect;
	CComboBox m_ComboTransfer;

	//判断是否在执行转换
	BOOL IsExcuting;
	CString strGuid;

	CEdit m_edit_InputFile;
	CEdit m_edit_OutputFile;
	CEdit m_edit_InCoord;
	CEdit m_edit_OutCoord;

	CString strLastPath;
	CString strDBSid_Src, strDBUser_Src, strDBPwd_Src;
	CString strDBSid_Dest, strDBUser_Dest, strDBPwd_Dest;

	CXTPProgressCtrl m_Progress;
	double StartTickTime,EndTickTime;
	CButton m_chk_dem;
	CRasterSetting m_dlgRasterSetting;

	BOOL m_bSpecified ;
	long m_lSizeX ;
	long m_lSizeY ;
	double m_dbPixX ;
	double m_dbPixY ;
	double m_dbLeft ;
	double m_dbTop ;

	IWorkspacePtr	     m_pSrcWS;
	IWorkspacePtr		 m_pDesWS;
	vector<STR_SDEINFO>	 m_vecSelect;

public:
	void LoadExistData(CString m_str[6]);
	BOOL CheckControl();
	void TranFinish(const char* strTimeMsg);
	void ShowStatusPanel(CString str);
	void EnbleAllController();
	void DisableAllController();
	BOOL CheckCoord(); //检查大地坐标是否存在
	void TranformOver();
	void InitTransFormat();
};


