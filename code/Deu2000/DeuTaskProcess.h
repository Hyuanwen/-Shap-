///////////////////////////////////////////////////////////////////////////
//     项目:	 德毅智慧转换软件	
//	   描述:	 坐标计算处理类 (包含视图显示处理，栅格，矢量的转换计算)
//
//     作者：		戴峰
//     修改者：		Hushichen重构
//     主要函数：	---
//     版本:		---
//     修改:		---
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
	CString TaskName;		//任务名称
	CString TaskStatus;		//任务状态

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

	/* 矢量综合参数计算(四参数，七参数..etc) */
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

	/*  栅格综合参数计算(四参数，七参数..etc) */
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

	/* 获取单位 */
	CDeuUnits  GetUnit(SHORT InUnitType,SHORT OutUnitType);

	/* 获取七参数 */
	CSevenParams GetSevenParam(double *_7param);

	/* 获取空间参考对象 */
	CDeuSpatialReference GetSRS(CoordinateType _CoordinateType, CString strName);

	/* 获取坐标系类型 重载 */
	CDeuCoordType  GetCoordType(SHORT SrcType,SHORT DestType,SHORT CtrlPtType );
	CDeuEllipse GetDeuEllipse(CoordinateType CT,  const CString& strEllipseName);

	//根据名字查找对应坐标系类型
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
	//视图
	void	ShowView(BSTR pathString, CDeuDMap* p_map);	//显示视图（曹欣）
	void    ZoomIn(CDeuDMap* p_map);                    //放大

	/* 缩小 */
	void    ZoomOut(CDeuDMap* p_map);

	/* 漫游 */
	void    Pan(CDeuDMap* p_map);

	/* 前一视图 */
	void    ZoomToPrev(CDeuDMap* p_map);

	/* 后一视图 */
	void    ZoomToNext(CDeuDMap* p_map);

	/* 全景视图 */
	void    ZoomToMaxVisibleExtents(CDeuDMap* p_map);

	/* 空指针 */
	void    None(CDeuDMap* p_map);

	/* 选择要素 */
	void    SelectFeatures(CDeuDMap* p_map);

	/* 去掉高亮显示 */
	void    RemoveSelections(CDeuDMap* p_map);

	/* 移除当前地图下所有图层 */
	void    RemoveAllLayers(CDeuDMap* p_map);

	/* ww范围数组 */
	VEC(MapWinGIS::IExtentsPtr) m_arrExtents;

	/* 检测当前标签是否为视图页 */
	BOOL CheckMap();
};
