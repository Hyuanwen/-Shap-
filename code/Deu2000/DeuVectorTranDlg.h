/////////////////////////////////////////////////////////////////////
//
//     ��Ŀ: �����ǻ�ת�����
//
//     ���ߣ�   hushichen
//
//     ����:	դ��ת������������
//
//     �汾:	V1.0
//	   CopyRight 2010-2011 ljdy Corporation All Rights Reserved
//
/////////////////////////////////////////////////////////////////////

#pragma once
#include "resource.h"
#include "DeuDlgCommCP.h"
#include "afxwin.h"

class CDeuVectorTranDlg : public CDialog
{
	DECLARE_DYNCREATE(CDeuVectorTranDlg)

public:
	CDeuVectorTranDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDeuVectorTranDlg();
	enum { IDD = IDD_DLG_TASK };

//#ifdef _DEBUG
//	virtual void AssertValid() const;
//#ifndef _WIN32_WCE
//	virtual void Dump(CDumpContext& dc) const;
//#endif
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedBtnInput();
	afx_msg void OnBnClickedBtnOutput();
	void OnCoordinateInput();
	void OnCoordinateOutput();
	DECLARE_MESSAGE_MAP()

public:
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void LoadExistData(CString m_str[10]);
	
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

	//�ļ�
	CStringArray _FilsList;
	CStringArray _FilsList_selected;
	CStringArray _TablesList;
	CStringArray _TablesList_selected;
	CString strLastPath;

	//��¼���ݿ��������Ϣ
	CString strDBSid_Src, strDBUser_Src, strDBPwd_Src;
	CString strDBSid_Dest, strDBUser_Dest, strDBPwd_Dest;
	void TranFinish(const char* strTimeMsg);	//ת������
	void ShowStatusPanel(CString str);
	int iModel;
	BOOL CheckControl();
	BOOL CheckCoord();
	CXTPProgressCtrl m_Progress;

	void DisableAllController();
	void EnbleAllController();
	
	BOOL IsAdditional;

	void SetTransModel(const CString& strTransModel);

	//add by chenyong 2013-4-3 ��ʼ��ת���ļ���ʽ��
	void InitTransFormat();

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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();

//add by chenyong 2013-10-9 for ArcSDE

	IWorkspacePtr						m_pSrcWS;
	IWorkspacePtr						m_pDesWS;
	IWorkspacePtr	  GetSrcWorkspace() const;
	IWorkspacePtr	  GetDesWorkspace() const;

	vector<STR_SDEINFO>		GetSelVec() const;
	vector<STR_SDEINFO>					m_vecSelect;
};