#pragma once

#include "afxcmn.h"
#include <string>
#include <vector>
using namespace std;

// CSdeSelect 对话框
class CSdeSelect : public CDialog
{
	DECLARE_DYNAMIC(CSdeSelect)

public:
	CSdeSelect(const vector<STR_SDEINFO> vecAll, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSdeSelect();

	// 对话框数据
	enum { IDD = IDD_DLG_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	void InitShowData(/*const vector<STR_SDEINFO>& vecRaster*/);

private:
	CListCtrl											m_ListShow;
	vector<STR_SDEINFO>									m_vecSelectItem;
	vector<STR_SDEINFO>									m_vecAll;
	
public:
	vector<STR_SDEINFO> GetSelectItem() const;
};
