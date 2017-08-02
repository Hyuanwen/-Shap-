#pragma once
#include <vector>
#include "Node.h"

class CDeuTaskCache
{
public:
	CDeuTaskCache();
public:
	~CDeuTaskCache();

//���л���Ա
public:
	CString type;											  //����
	CString TaskName;										  //��������
	CString TaskStatus;										  //����״̬
	CString CurTable;										  //��ǰ�����ı�
	
	CString PathName;										  //�ļ�·�������ݿ�����
	CString Driver;                                           //��������
	CString SrcEllip;                                         //Դ����
	SHORT	InCoordType;                                      //������������
	double	InCentr_long;									  //����������

	CString out_PathName;                                     //���·��
	CString out_Driver;                                       //�������
	CString DestEllip;                                        //Ŀ������
	SHORT	OutCoordType;                                     //�����������
	double	OutCentr_long;									  //����������
	
	std::vector<CString> TableList;							  //��ļ���
	int		iModel;

public:
	CNode* GetNode();  										  //�������л�����
	//�����л� void MakeObj(CNode *);

//�����л���Ա
public:
	LONGLONG	hWnd;
	double *	Param;
	double *	InvParam;
	long		nPara; 
};