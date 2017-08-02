#pragma once
#include <vector>
#include "Node.h"

class CDeuTaskCache
{
public:
	CDeuTaskCache();
public:
	~CDeuTaskCache();

//序列化成员
public:
	CString type;											  //类型
	CString TaskName;										  //任务名称
	CString TaskStatus;										  //任务状态
	CString CurTable;										  //当前操作的表
	
	CString PathName;										  //文件路径或数据库连接
	CString Driver;                                           //输入驱动
	CString SrcEllip;                                         //源椭球
	SHORT	InCoordType;                                      //输入坐标类型
	double	InCentr_long;									  //中央子午线

	CString out_PathName;                                     //输出路径
	CString out_Driver;                                       //输出驱动
	CString DestEllip;                                        //目标椭球
	SHORT	OutCoordType;                                     //输出坐标类型
	double	OutCentr_long;									  //中央子午线
	
	std::vector<CString> TableList;							  //表的集合
	int		iModel;

public:
	CNode* GetNode();  										  //生成序列化对象
	//反序列化 void MakeObj(CNode *);

//非序列化成员
public:
	LONGLONG	hWnd;
	double *	Param;
	double *	InvParam;
	long		nPara; 
};