// ReadShapeDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <CString>
#include <vector>
#include <iostream>
#include <string>
#include "ogrsf_frmts.h"
//#include "DeuTranslate.h"
//#include "DeuDef.h"
#include "COMDEF.H"
#include "ShapeData.h"
#include "TransTool.h"
#include "afxwin.h"
#include <fstream>
//#include "deuTransFile.h"
//#include "deuTransApDef.h"
//#include "DeuFunction.h"
#define MAX_TransNum      1000000000

// CReadShapeDlg 对话框
class CReadShapeDlg : public CDialog
{
// 构造
public:
	CReadShapeDlg(CWnd* pParent = NULL);	// 标准构造函数
	void readShape(CString inFileName,CString outFileName);
	void TransLate(double oldX, double oldY, double oldZ,
		           double &newX, double &newY, double &newZ);
	void ViewShape(CString fileName);
	CString infilename; 
	CString outfilename; 

// 对话框数据
	enum { IDD = IDD_READSHAPE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg void OnBnClickedSelect();
	CListCtrl m_ShapeList;
	CListCtrl m_TranShapeList;
	std::vector<ShapeData> m_value;
	std::vector<ShapeData> m_TransValue;

	std::vector<ShapeData> vetNewShape;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	
private:
	unsigned long							m_all_fea_count;	//总要素个数
	unsigned long							m_fea_done;			//已经处理要素个数
	unsigned long							m_fea_null_count;	//空要素个数
	unsigned long							m_fea_create_count;	//成功创建要素个数
	unsigned long							m_fea_fail_count;	//创建失败的要素个数

	unsigned long							m_geo_point_count;	//点类型个数
	unsigned long							m_geo_line_count;	//线类型个数
	unsigned long							m_geo_polygon_count;//面类型个数
	unsigned long							m_geo_multi_point_count;	//多点类型个数
	unsigned long							m_geo_multi_line_count;		//多线类型个数
	unsigned long							m_geo_multi_polygon_count;	//多面类型个数
	unsigned long							m_geo_null_count;			//空类型个数

	unsigned long							m_error_count;				//错误
	unsigned long							m_geo_ori_error_count;		//原始geometry错误
	unsigned long							m_geo_done;					//已处理的非空geometry个数
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	// 输出路径
	CEdit m_edit_OutputFile;
	OGRwkbGeometryType Newtype;
};
