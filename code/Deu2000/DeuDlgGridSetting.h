#pragma once
#include "resource.h"

// CDeuDlgGridSetting �Ի���

class CDeuDlgGridSetting : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgGridSetting)

public:
	CDeuDlgGridSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgGridSetting();

	// �Ի�������
	enum { IDD =IDD_DLG_GRIDSETTING  };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboProName();
	afx_msg void OnCbnSelchangeComboFx();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	//�����ŵĹ�������
	//BSTR m_ProId;
	//BSTR m_pwd;
	//BSTR m_Fx;
	//BSTR m_ProName;

	CString   mt_ProId;
	CString   mt_pwd;
	CString   mt_Fx;
	CString   mt_ProName;
	CComboBox m_cbProname;
	CComboBox m_cbFx;
	
//public:
	//��һЩ������ʼ���Ĺ���...
	//int	InitGridSetting( /*out*/BSTR  &ProName ,/*out*/BSTR  &ProId , /*out*/BSTR  &pwd , /*out*/BSTR  &Fx );
};
