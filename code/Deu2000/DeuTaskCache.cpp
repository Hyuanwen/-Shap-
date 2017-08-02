#include "StdAfx.h"
#include "DeuTaskCache.h"
#include "ogrsf_frmts.h"

CDeuTaskCache::CDeuTaskCache():type("NOTYPE"),InCentr_long(0),OutCentr_long(0)
{
}

CDeuTaskCache::~CDeuTaskCache(void)
{
}

CNode* CDeuTaskCache::GetNode()
{
	CNode *node_task = new CNode;
	/*CNode *node_taskname = new CNode;*/
	
	CNode *node_in_path			=	new CNode;			//	输入路径
	CNode *node_out_path		=	new CNode;			//	输出路径	
	
	CNode *node_in_driver		=	new CNode;			//	输入驱动
	CNode *node_out_driver		=	new CNode;			//	输出驱动

	CNode *node_in_ellipse		=	new CNode;			//	输入椭球
	CNode *node_out_ellipse		=	new CNode;			//	输出椭球

	CNode *node_in_CoordType	=	new CNode;			//	输入坐标类型
	CNode *node_out_CoordType	=	new CNode;			//	输出坐标类型

	CNode *node_InCentr_long	=	new CNode;			//	输入中央子午线
	CNode *node_OutCentr_long	=	new CNode;			//	输出中央子午线

	CNode *node_type			=	new CNode;			//	类型 
	CNode *node_Status			=   new CNode;			//	状态
	CNode *node_CurTable        =   new CNode;			//	当前表
	CNode *node_List			= new CNode;			//	Table List

//////////////////////////////////////////////////////////////////////////
	node_task->tag_name = "CDeuTaskCache";
	node_task->ele_name = TaskName;

//////////////////////////////////////////////////////////////////////////
	node_in_path->tag_name	=	"IN_PATH"	;
	node_in_path->ele_name	=	"IN_PATH"	;
	node_in_path->data		=	PathName	;

//////////////////////////////////////////////////////////////////////////
	node_out_path->tag_name	=	"OUT_PATH"	;
	node_out_path->ele_name	=	"OUT_PATH"	;
	node_out_path->data		=	out_PathName;

//////////////////////////////////////////////////////////////////////////
	node_in_driver->tag_name=	"IN_DRIVER"	;
	node_in_driver->ele_name=	"IN_DRIVER"	;
	node_in_driver->data	=	Driver		;

//////////////////////////////////////////////////////////////////////////
	node_out_driver->tag_name=	"OUT_DRIVER";
	node_out_driver->ele_name=	"OUT_DRIVER";
	node_out_driver->data	 =	out_Driver;

//////////////////////////////////////////////////////////////////////////
	node_in_ellipse->tag_name=	"ELlIP_NAME";
	node_in_ellipse->ele_name=	"ELlIP_NAME";
	node_in_ellipse->data	 =	SrcEllip;

//////////////////////////////////////////////////////////////////////////
	node_out_ellipse->tag_name=	"OUT_ELLIP_NAME";
	node_out_ellipse->ele_name=	"OUT_ELLIP_NAME";
	node_out_ellipse->data	  =  DestEllip;

//////////////////////////////////////////////////////////////////////////
	node_in_CoordType->tag_name=	"COORDTYPE";
	node_in_CoordType->ele_name=	"COORDTYPE";
	CString strInCoordType;
	strInCoordType.Format(_T("%d"),InCoordType);
	node_in_CoordType->data	   =	strInCoordType;	

//////////////////////////////////////////////////////////////////////////
	node_out_CoordType->tag_name=	"Out_COORDTYPE";
	node_out_CoordType->ele_name=	"Out_COORDTYPE";
	CString strOutCoordType;
	strOutCoordType.Format(_T("%d"),OutCoordType);
	node_out_CoordType->data	=	strOutCoordType;	

//////////////////////////////////////////////////////////////////////////
	node_InCentr_long->tag_name	=	"InCentr_long";
	node_InCentr_long->ele_name	=	"InCentr_long";
	CString strInCentrLong;
	strInCentrLong.Format(_T("%.1f"),InCentr_long);
	node_InCentr_long->data		=	strInCentrLong;

//////////////////////////////////////////////////////////////////////////
	node_OutCentr_long->tag_name	=	"OutCentr_long";
	node_OutCentr_long->ele_name	=	"OutCentr_long";
	CString strOutCentrLong;
	strOutCentrLong.Format(_T("%.1f"),OutCentr_long);
	node_OutCentr_long->data		=	strOutCentrLong;

//////////////////////////////////////////////////////////////////////////
	node_type->tag_name = "Type";
	node_type->ele_name = "Type";
	node_type->data	= type;

	node_Status->tag_name = "Status";
	node_Status->ele_name = "Status";
	node_Status->data = TaskStatus;

	node_CurTable->tag_name = "CurTable";
	node_CurTable->ele_name = "CurTable";
	node_CurTable->data = CurTable;

	node_List->tag_name = "TableList";
	node_List->ele_name = "TableList";


	//////////////////////////////////////////////////////////////////////////
	//PUSH BACK
	//////////////////////////////////////////////////////////////////////////
	node_task->_sub_nodes.push_back(node_in_path);
	node_task->_sub_nodes.push_back(node_out_path);
	node_task->_sub_nodes.push_back(node_in_driver);
	node_task->_sub_nodes.push_back(node_out_driver);
	node_task->_sub_nodes.push_back(node_in_ellipse);
	node_task->_sub_nodes.push_back(node_out_ellipse);
	node_task->_sub_nodes.push_back(node_in_CoordType);
	node_task->_sub_nodes.push_back(node_out_CoordType);
	node_task->_sub_nodes.push_back(node_InCentr_long);
	node_task->_sub_nodes.push_back(node_OutCentr_long);
	node_task->_sub_nodes.push_back(node_type);
	node_task->_sub_nodes.push_back(node_Status);
	node_task->_sub_nodes.push_back(node_CurTable);
	node_task->_sub_nodes.push_back(node_List);

	int iCount = TableList.size();
	for (int i=0;i<iCount;i++)
	{
		CNode *node_tab = new CNode;

		node_tab->tag_name = "tab";
		node_tab->ele_name = "tab";
		
		node_tab->data = TableList[i];

		node_List->_sub_nodes.push_back(node_tab);
	}

	return node_task;
}
