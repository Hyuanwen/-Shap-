/////////////////////////////////////////////////////////////////////
//     ��Ŀ:	�����ǻ�ת�����
//     ���ߣ�	hushichen
//     ����:	Tab����
//     �汾:v1.0
//
//		CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
#pragma once

#include "Resource.h"
#include "deuctrltab.h"

#include "DeuData.h"


class CDeuDlgContainer : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDeuDlgContainer)

public:
	CDeuDlgContainer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgContainer();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDeuCtrlTab m_DeuTab;
	virtual BOOL OnInitDialog();

	afx_msg void OnSize(UINT nType, int cx, int cy);


	void InitExistTask();


	//����tab�麯��

	/* ��ת */
	void AddTabForSingle();
	void DelTabForSingle(int _Index);

	/* ��ת */
	void AddTabForBatRechange();
	void DelTabForBatRechange(int _Index);


	/* ��ͼ */
	void AddTabForView();
	void DelTabForView(int _Index);


	/* ʸ�� */
	void AddTabForVector(TreeData* p_treedata);
	void DelTabForVector(int _Index);

	//������tab�Ӵ��ڵ�ȫ������ֵ
	void ResetTabOrder();

	//����ʸ���������Ӵ��ڵ���������ֵ
	void ResetVectorAyOrder();

	//����դ���������Ӵ��ڵ���������ֵ
	void ResetRasterAyOrder();
	

	/* դ�� */
	void AddTabForRaster(TreeData* p_treedata);
	void DelTabForRaster(int _Index);

	//һ�����������ݣ����¼��ؿؼ���������
	void ResetTree();

	

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
