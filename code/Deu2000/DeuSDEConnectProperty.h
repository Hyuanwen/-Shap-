#pragma once
#include "afxwin.h"


// CDeuSDEConnectProperty �Ի���

class CDeuSDEConnectProperty : public CDialog
{
	DECLARE_DYNAMIC(CDeuSDEConnectProperty)

public:
	CDeuSDEConnectProperty(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuSDEConnectProperty();

// �Ի�������
	enum { IDD = IDD_DLG_CONNECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedOk();


	IWorkspacePtr GetWorkspace() const;


private:

	void GetSDEInfo();

	void InitCtrls();
	
private:
	CEdit m_edit_server;
	CEdit m_edit_service;
	CEdit m_edit_database;
	CEdit m_edit_username;
	CEdit m_edit_password;
	CEdit m_edit_version;

	CString					strServer;
	CString					strInstance;
	CString					strDatabase;
	CString					strUsername;
	CString					strPassword;
	CString					strVersion;


	IWorkspacePtr				m_Workspace;


	CButton m_checkbox_version;
	STR_SDE_PARAM			m_param;
public:
	afx_msg void OnBnClickedBtnConnect();
	CString					GetConnString() const;

	//add by chenyong 2013-12-3 ����Ĭ�ϵ�ArcSDE������Ϣ
	void			SetParam(STR_SDE_PARAM param);
	STR_SDE_PARAM	GetParam();
};


