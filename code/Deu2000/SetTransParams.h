#pragma once
#include "afxwin.h"

struct _Params
{
	CString		strXSrc;
	CString		strYSrc;
	CString		strZSrc;
	CString		strX0Src;
	CString		strY0Src;
	CString		strZ0Src;
	CString		strKSrc;
};

// CSetTransParams 对话框
class CSetTransParams : public CDialog
{
	DECLARE_DYNAMIC(CSetTransParams)

public:
	CSetTransParams(bool IsVector, bool IsBursa, _Params params, _Params invparams, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetTransParams();

// 对话框数据
	enum { IDD = IDD_DLG_SETPARAMS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	void GetTransParams(double* params);
	void GetTransInvParams(double* params);
	
private:
	void InitParams(_Params params, _Params invParams);

private:
	double m_Ed_X_Src;
	double m_Ed_Y_Src;
	double m_Ed_Z_Src;
	double m_Ed_XO_Src;
	double m_Ed_YO_Src;
	double m_Ed_ZO_Src;
	double m_Ed_K_Src;
	double m_Ed_X_Des;
	double m_Ed_Y_Des;
	double m_Ed_Z_Des;
	double m_Ed_XO_Des;
	double m_Ed_YO_Des;
	double m_Ed_ZO_Des;
	double m_Ed_K_Des;

	bool	m_IsVector;
	bool	m_IsBursa;
	_Params	m_params;
	_Params	m_invparams;	
};
