#pragma once

#include "resource.h"
#include "afxwin.h"

// CRasterSetting �Ի���
class CRasterSetting : public CDialog
{
	DECLARE_DYNAMIC(CRasterSetting)

public:
	CRasterSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRasterSetting();

	// �Ի�������
	enum { IDD = IDD_DLG_RASTERSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnCbnSelchangeCombo1();

public:
	long m_SizeX;		//���
	long m_SizeY;		//�߶�
	double m_PixX;		//��Ԫ���
	double m_PixY;		//��Ԫ�߶�
	BOOL m_bSpecialFrame;
	double m_dbLeft;	//��
	double m_dbTop;		//��

	// ��׼�ַ�
	bool m_bStandardFrame;

	// �Ǳ�׼�ַ�
	bool m_bNonStandardFrame;
	
	// ͼ����
	CString m_strFrameNo;

	CComboBox m_cbUnit;
	double m_dbBottom;
	double m_dbRight;
};
