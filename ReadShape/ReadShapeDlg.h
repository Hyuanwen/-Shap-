// ReadShapeDlg.h : ͷ�ļ�
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

// CReadShapeDlg �Ի���
class CReadShapeDlg : public CDialog
{
// ����
public:
	CReadShapeDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void readShape(CString inFileName,CString outFileName);
	void TransLate(double oldX, double oldY, double oldZ,
		           double &newX, double &newY, double &newZ);
	void ViewShape(CString fileName);
	CString infilename; 
	CString outfilename; 

// �Ի�������
	enum { IDD = IDD_READSHAPE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	unsigned long							m_all_fea_count;	//��Ҫ�ظ���
	unsigned long							m_fea_done;			//�Ѿ�����Ҫ�ظ���
	unsigned long							m_fea_null_count;	//��Ҫ�ظ���
	unsigned long							m_fea_create_count;	//�ɹ�����Ҫ�ظ���
	unsigned long							m_fea_fail_count;	//����ʧ�ܵ�Ҫ�ظ���

	unsigned long							m_geo_point_count;	//�����͸���
	unsigned long							m_geo_line_count;	//�����͸���
	unsigned long							m_geo_polygon_count;//�����͸���
	unsigned long							m_geo_multi_point_count;	//������͸���
	unsigned long							m_geo_multi_line_count;		//�������͸���
	unsigned long							m_geo_multi_polygon_count;	//�������͸���
	unsigned long							m_geo_null_count;			//�����͸���

	unsigned long							m_error_count;				//����
	unsigned long							m_geo_ori_error_count;		//ԭʼgeometry����
	unsigned long							m_geo_done;					//�Ѵ���ķǿ�geometry����
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	// ���·��
	CEdit m_edit_OutputFile;
	OGRwkbGeometryType Newtype;
};
