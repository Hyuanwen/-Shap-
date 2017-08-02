#pragma once
#include "resource.h"
#include "afxwin.h"

// CDeuAddProjectedDlg �Ի���

class CDeuAddProjectedDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeuAddProjectedDlg)

public:
	CDeuAddProjectedDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuAddProjectedDlg();

// �Ի�������
	enum { IDD = IDD_DLG_ADD_PROJECTED };

public: 
	double m_pdA[4];
	double m_pdB[4];
	double m_pdK[4];

	void  SetSRS2(CString szFilePath);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CComboBox m_ctlProjectType;
	CString m_szName;
	double m_dFalseEasting;
	double m_dFalseNorthing;
	double m_dCentralMeridia;
	CComboBox m_ctlCoordinateName;
	double m_dA;
	double m_dB;
	double m_dK;
	afx_msg void OnCbnSelchangeComboCoordinateName();
	CEdit m_ctlA;
	CEdit m_ctlB;
	CEdit m_ctlK;
};
