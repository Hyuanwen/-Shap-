#pragma once

#include "resource.h"
#include "AnimateStatic.h"

class CDeuDlgBackground : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgBackground)

public:
	CDeuDlgBackground(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgBackground();

	// 对话框数据
	enum { IDD = IDD_DLG_BACKGROUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CDeuAnimateStatic	m_staticGear;
};
