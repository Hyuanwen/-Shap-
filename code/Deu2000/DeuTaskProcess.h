///////////////////////////////////////////////////////////////////////////
//     ��Ŀ:	 �����ǻ�ת�����	
//	   ����:	 ������㴦���� (������ͼ��ʾ����դ��ʸ����ת������)
//
//     ���ߣ�		����
//     �޸��ߣ�		Hushichen�ع�
//     ��Ҫ������	---
//     �汾:		---
//     �޸�:		---
//	   CopyRight 2010 ljdy Corporation All Rights Reserved
//////////////////////////////////////////////////////////////////////////
#pragma once

class CDeuTaskCache;
class CNode;
class CDeuVectorTranDlg;
class CDeuRasterTranDlg;
class CDeuVectorProjectTranDlg;
class CDeuRasterProjectTranDlg;
class CDeuEllipse;
class CDeuUnits;
class CDeuCoordType;
class CDeuSpatialReference;
class CSevenParams;
class CDeuConnPool;
class CDeuDatabase;

#import "..\..\dll\MapWinGIS.ocx" raw_interfaces_only,   raw_native_types,    named_guids/* , rename_namespace("MapWinGIS") */
//#include "DeuViewView.h"
//#include "DeuToolIdetify.h"

#include "DeuCoordinateSystem.h"
#include "DeuDMap.h"
using namespace std;
using namespace DeuCS;
#include <string>

extern BOOL	g_ThreadFinished; 
class CDeuTaskProcess
{
public:
	CDeuTaskProcess();
	~CDeuTaskProcess(void);

public:
	CString TaskName;		//��������
	CString TaskStatus;		//����״̬

public:
	std::vector<CString>* GetTabListInDB(CString strConn);

	//add by chenyong 2013-01-10
	void Task_Calculate7Param(SHORT aMode,
		SHORT CtrlPtCoordType,
		SHORT UnitType,
		const CDeuEllipse& pSrcEllip,
		const CDeuEllipse& pDestEllip,
		int iCount,
		double *x,
		double *y ,
		double *z,
		double *x2,
		double *y2,
		double *z2,
		double *residual_x,
		double *residual_y,
		double *residual_z,
		double *residual,
		double *_7param
		);

	/* ʸ���ۺϲ�������(�Ĳ������߲���..etc) */
	void Task_VectorCalculate7Param(SHORT aMode,
		SHORT CtrlPtCoordType,
		SHORT UnitType,
		const CDeuEllipse& pSrcEllip,
		const CDeuEllipse& pDestEllip,
		int iCount,
		double *x,
		double *y ,
		double *z,
		double *x2,
		double *y2,
		double *z2,
		double *residual_x,
		double *residual_y,
		double *residual_z,
		double *residual,
		double *_param,
		double *_inv_param,
		ULONG  *np	);

	/*  դ���ۺϲ�������(�Ĳ������߲���..etc) */
	void Task_RasterCalculate7Param(SHORT aMode,
		SHORT CtrlPtCoordType,
		SHORT UnitType,
		const CDeuEllipse& pSrcEllip,
		const CDeuEllipse& pDestEllip,
		int iCount,
		double *x,
		double *y ,
		double *z,
		double *x2,
		double *y2,
		double *z2,
		double *residual_x,
		double *residual_y,
		double *residual_z,
		double *residual,
		double *_7param,
		double *_inv_param,
		ULONG*	npara);

	/* ��ȡ��λ */
	CDeuUnits  GetUnit(SHORT InUnitType,SHORT OutUnitType);

	/* ��ȡ�߲��� */
	CSevenParams GetSevenParam(double *_7param);

	/* ��ȡ�ռ�ο����� */
	CDeuSpatialReference GetSRS(CoordinateType _CoordinateType, CString strName);

	/* ��ȡ����ϵ���� ���� */
	CDeuCoordType  GetCoordType(SHORT SrcType,SHORT DestType,SHORT CtrlPtType );
	CDeuEllipse GetDeuEllipse(CoordinateType CT,  const CString& strEllipseName);

	//�������ֲ��Ҷ�Ӧ����ϵ����
	__COORDTYPE FindCoordindateType(CString strEllipseName);
	CoordinateType FindCoordinateType(CString strEllipseName);

	char* FindCoordType(CString strEllipseName);
	char* FindCustomCoordType(CString strEllipseName);
	void InitConnPool(CString strConn);

	BOOL Task_VectorTransForm(CDeuVectorTranDlg* pVecDlg);
	BOOL Task_RasterTransForm(CDeuRasterTranDlg * pRasterDlg);
	BOOL Task_RasterTransFormDEM(CDeuRasterTranDlg * pRasterDlg);
	BOOL Task_VectorProjectTransForm(CDeuVectorProjectTranDlg * pProjectDlg);
	BOOL Task_RasterProjectTransForm(CDeuRasterProjectTranDlg * pProjectDlg);

	void UpdateTaskList(std::list<CDeuTaskCache*> *vecTask);//new or modify all tasks in file
	void UpdateTask(CDeuTaskCache* Task);                   //new or modify a task in file
	void RemoveTask(CString TaskName);                      //remove a task from file
	void UpdateEllipseList(std::list<CNode*> lisEllipse);

	//add by chenyong 2013-10-15 for ArcSDE
	string GetPrjFullPathByName(const CString& strEllipseName);
	
public:	
	//��ͼ
	void	ShowView(BSTR pathString, CDeuDMap* p_map);	//��ʾ��ͼ��������
	void    ZoomIn(CDeuDMap* p_map);                    //�Ŵ�

	/* ��С */
	void    ZoomOut(CDeuDMap* p_map);

	/* ���� */
	void    Pan(CDeuDMap* p_map);

	/* ǰһ��ͼ */
	void    ZoomToPrev(CDeuDMap* p_map);

	/* ��һ��ͼ */
	void    ZoomToNext(CDeuDMap* p_map);

	/* ȫ����ͼ */
	void    ZoomToMaxVisibleExtents(CDeuDMap* p_map);

	/* ��ָ�� */
	void    None(CDeuDMap* p_map);

	/* ѡ��Ҫ�� */
	void    SelectFeatures(CDeuDMap* p_map);

	/* ȥ��������ʾ */
	void    RemoveSelections(CDeuDMap* p_map);

	/* �Ƴ���ǰ��ͼ������ͼ�� */
	void    RemoveAllLayers(CDeuDMap* p_map);

	/* ww��Χ���� */
	VEC(MapWinGIS::IExtentsPtr) m_arrExtents;

	/* ��⵱ǰ��ǩ�Ƿ�Ϊ��ͼҳ */
	BOOL CheckMap();
};
