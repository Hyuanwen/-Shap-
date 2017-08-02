#pragma once

#include "resource.h"
#include "afxwin.h"

// CRasterSetting 对话框
class CRasterSetting : public CDialog
{
	DECLARE_DYNAMIC(CRasterSetting)

public:
	CRasterSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRasterSetting();

	// 对话框数据
	enum { IDD = IDD_DLG_RASTERSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnCbnSelchangeCombo1();

public:
	long m_SizeX;		//宽度
	long m_SizeY;		//高度
	double m_PixX;		//像元宽度
	double m_PixY;		//像元高度
	BOOL m_bSpecialFrame;
	double m_dbLeft;	//左
	double m_dbTop;		//上

	// 标准分幅
	bool m_bStandardFrame;

	// 非标准分幅
	bool m_bNonStandardFrame;
	
	// 图幅号
	CString m_strFrameNo;

	CComboBox m_cbUnit;
	double m_dbBottom;
	double m_dbRight;
};
