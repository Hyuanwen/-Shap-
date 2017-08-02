// DeuDlgTreeTask.cpp : 实现文件
//

#include "stdafx.h"
#include "Deu2000.h"
#include "DeuDlgTreeTask.h"
#include "DeuTask.h"
#include "DeuDataTransForm.h"
#include "DeuDef.h"
#include "DeuRasterTrans.h"
#include "DeuCtrlTab.h"

#define  nBorder 1
// CDeuDlgTreeTask 对话框

IMPLEMENT_DYNAMIC(CDeuDlgTreeTask, CDialog)

CDeuDlgTreeTask::CDeuDlgTreeTask(CWnd* pParent /*=NULL*/)
	: CDialog(CDeuDlgTreeTask::IDD, pParent)
{

}

CDeuDlgTreeTask::~CDeuDlgTreeTask()
{
	VEC_IT(TreeData*) it = m_vecTreeData.begin();
	for ( ; it != m_vecTreeData.end() ; it++)
	{
		delete (*it);
	}
	 
	delete m_Tree;
}

void CDeuDlgTreeTask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeuDlgTreeTask, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED,IDC_WNDTREE,&CDeuDlgTreeTask::OnTvnSelectedChangepage)
    ON_MESSAGE(WM_TASKREN_FINISHED,OnRenTskFinished)
END_MESSAGE_MAP()


// CDeuDlgTreeTask 消息处理程序


BOOL CDeuDlgTreeTask::OnInitDialog()
{
	CRect rect;
	rect.SetRectEmpty();

	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
		TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_Tree.Create (dwViewStyle, rect, this, IDC_WNDTREE))
	{
		TRACE0("Failed to create workspace view\n");//fail to create
		return -1; 
	}

	//////////////////////////////////////////////////////////////////////////

	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	VEC(CPropertyPage*) &vecVecPage = pDeuData->vecVectorTrans;
	VEC(CPropertyPage*) &vecRasterPage = pDeuData->vecRasterTrans;

	//////////////////////////////////////////////////////////////////////////

	hRoot1 = m_Tree.InsertItem (_T("项目"), TVI_ROOT);
	

	//矢量
	VEC(CPropertyPage*)::iterator itVec;
	
	hVecParent = m_Tree.InsertItem (_T("矢量"), hRoot1);	

	//for (itVec = vecVecPage.begin();itVec != vecVecPage.end();itVec++)
	//{
	//	HTREEITEM  hItem1;
	//	hItem1=m_Tree.InsertItem(_T("矢量转换"), hVecParent);
	//	(*itVec)->m_psp.dwFlags |= PSP_USETITLE; 
	//	(*itVec)->m_psp.pszTitle = "矢量转换"; 


	//	TreeData  * taskofsl=new TreeData;
	//	taskofsl->type = VEC_TASK;
	//	taskofsl->p1 =*itVec; 
	//	
	//	m_Tree.SetItemData(hItem1,(DWORD_PTR)taskofsl);
	//	m_vecTreeData.push_back(taskofsl);
	//}
	CString m_strLabel;
	for(int n=0; n<DEUMAINFRM.m_deuData->vecVector.GetCount(); n++)
	{
		//CDeuDialog* p_deudialog = (CDeuDialog*)DEUMAINFRM.m_deuData->vecVector.GetAt(n);
		//p_tree.InsertItem(strLabel, DEUMAINFRM.m_wndProject.m_dlgTreeTask.hRasterParent);

		
		m_strLabel.Format("矢量转换 %d", n);
		m_Tree.InsertItem(m_strLabel, hVecParent);

	}

	m_Tree.Expand(hVecParent,TVE_EXPAND );

	//栅格


	VEC(CPropertyPage*)::iterator itRaster;
	hRasterParent = m_Tree.InsertItem (_T("栅格"), hRoot1);	
	
	
	/*for (itRaster = vecRasterPage.begin();itRaster != vecRasterPage.end();itRaster++)
	{
		HTREEITEM hItem2 = m_Tree.InsertItem ("栅格转换", hRasterParent);

		(*itRaster)->m_psp.dwFlags |= PSP_USETITLE; 
		(*itRaster)->m_psp.pszTitle = "栅格转换"; 

		TreeData *taskofSg = new TreeData;
		taskofSg->type=TIF_TASK;

		taskofSg->p1 = *itRaster;
		m_Tree.SetItemData(hItem2,(DWORD_PTR)taskofSg);
		m_vecTreeData.push_back(taskofSg);
	}*/


	for(int n=0; n<DEUMAINFRM.m_deuData->vecRaster.GetCount(); n++)
	{
		//CDeuDialog* p_deudialog = (CDeuDialog*)DEUMAINFRM.m_deuData->vecVector.GetAt(n);
		//p_tree.InsertItem(strLabel, DEUMAINFRM.m_wndProject.m_dlgTreeTask.hRasterParent);

		m_strLabel.Format("栅格转换 %d", n);
		m_Tree.InsertItem(m_strLabel, hRasterParent);
	}
	m_Tree.Expand(hRasterParent,TVE_EXPAND );

	m_Tree.Expand(hRoot1,TVE_EXPAND );

	return 0;
}


// CDLGTreeCtrl 消息处理程序

void  CDeuDlgTreeTask::OnSize(UINT nType, int cx, int cy) ///有错？？？？？？？
{
	CDialog::OnSize(nType,cx,cy);
	if (m_Tree.m_hWnd!=NULL)
	{
		m_Tree.SetWindowPos (NULL,nBorder, nBorder, cx-2*nBorder, cy-2*nBorder,SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


void CDeuDlgTreeTask::OnTvnSelectedChangepage(NMHDR *pNMHDR, LRESULT *pResult)
{



	//选择按钮的同时要给出属性和数据转换页面
	POINT  mPoint;
	GetCursorPos(&mPoint);

	TVHITTESTINFO hitInfo;
	hitInfo.pt=mPoint;

	HTREEITEM  hSelItem=m_Tree.GetSelectedItem();


	//显示相应的属性
	TreeData  *pData = NULL;
	pData = ( TreeData * )m_Tree.GetItemData(hSelItem);

	pPropage->m_PropList.RemoveAll();
	CDeuTask * pTask = NULL;

	CString strName;
	CString strStatus;
	CString currentTable;
	CString filePathName;
	CString inDriver;
	CString srcolEllip;

	SHORT Incoordtype;
	CString strIncoordtype;
	double inCentre_long;
	CString out_filePathName;
	CString out_driver;
	CString destEllip;
	SHORT OutCoordType;
	CString strOutCoordType;
	double  outCentr_long; 

	if (pData)
	{    
		/* 矢量任务 */
		if( pData->type == VEC_TASK )
		{
			CDeuDataTransform * pTrans = ( CDeuDataTransform * ) pData->p1;
			pTask = pTrans->m_deuTask;
 
			strName			 =	pTask->TaskName;//任务名称
			strStatus		 =	pTask->TaskStatus;//任务状态			
			currentTable	 =	pTask->CurTable;//当前操作表
			filePathName	 =	pTask->PathName;//文件路径名
			inDriver		 =	pTask->Driver;//驱动
			srcolEllip		 =	pTask->SrcEllip;//源椭球
			Incoordtype		 =	pTask->InCoordType;//输入坐标类型			
			inCentre_long	 =	pTask->InCentr_long;//中央子午线
			out_filePathName =	pTask->out_PathName;//输出路径
			out_driver		 =	pTask->out_Driver;			//输出驱动
			destEllip		 =	pTask->DestEllip;			//目标椭球
			OutCoordType	 =	pTask->OutCoordType;		//输出坐标类型			
            outCentr_long	 =	pTask->OutCentr_long;      //输出中央子午线			
			pTask			 =	NULL;

		}

		/* 栅格任务 */
		else /*(pData->type==TIF_TASK)*/
		{

			CDeuRasterTrans * pRasTans=(CDeuRasterTrans*)pData->p1;
			pTask			=	pRasTans->m_deuTask;
			strName			=	pTask->TaskName;//任务名称
			strStatus		=	pTask->TaskStatus;//任务状态			
			currentTable	=	pTask->CurTable;//当前操作表
			filePathName	=	pTask->PathName;//文件路径名
			inDriver		=	pTask->Driver;//驱动
			srcolEllip		=	pTask->SrcEllip;//源椭球
			Incoordtype		=	pTask->InCoordType;//输入坐标类型			
			inCentre_long	=	pTask->InCentr_long;//中央子午线
			out_filePathName=	pTask->out_PathName;//输出路径
			out_driver		=	pTask->out_Driver;//输出驱动
			destEllip		=	pTask->DestEllip;//目标椭球
			OutCoordType	=	pTask->OutCoordType;//输出坐标类型			
			outCentr_long	=	pTask->OutCentr_long;      //输出中央子午线			
			pTask=NULL;

		}
			//0
			CBCGPProp *pProty=new CBCGPProp(CString(L"任务名称") ,(_variant_t)strName, CString(L"The name is the simple description of the task.") );
			pProty->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty);
			//1		
			switch(_tstoi(strStatus))
			{
				case 0:
					strStatus=L"未开始";
					break;
				case 1:
					strStatus=L"执行中";
					break;
				case 2:
					strStatus=L"完成";
					break;
				default:break;
			}
			CBCGPProp *pProty1=new CBCGPProp( CString(L"任务状态"),(_variant_t)strStatus,CString (L"The statues of the task be on."));
			pProty1->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty1);
			//2
			CBCGPProp *pProty2=new CBCGPProp( CString(L"当前操作表"),(_variant_t)currentTable,CString (L"This name is the table that user is using ."));
			pProty2->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty2);
			//3	
			CBCGPProp *pProty3=new CBCGPProp( CString(L"文件路径"),(_variant_t)filePathName,CString (L"The name is path that the file has be saved."));
			pProty3->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty3);			
			//4
			CBCGPProp *pProty4=new CBCGPProp( CString(L"输入驱动"),(_variant_t)out_driver,CString(L"The name is a kind of driver of the corresponding file."));
			pProty4->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty4);
			//5
			CBCGPProp *pProty5=new CBCGPProp( CString(L"源椭球"),(_variant_t)srcolEllip,CString(L"The name is a source elliptic."));
			pProty5->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty5);
			//6	
			switch(Incoordtype)//输入坐标类型
			{
			case 0:
				strIncoordtype=L"未知";
				break;
			case 1:
				strIncoordtype=L"大地";
				break;
			case 2:
				strIncoordtype=L"空间直角";
				break;
			case 3:
				strIncoordtype=L"平面";
				break;
			default:break;		
			}
			CBCGPProp *pProty6=new CBCGPProp( CString(L"输入坐标类型"),(_variant_t)strIncoordtype,CString(L"This is the type of coordinate."));
			pProty6->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty6);
			//7
			CBCGPProp *pProty7=new CBCGPProp( CString(L"中央子午线"),(_variant_t)inCentre_long,CString(L"The name is the center of long."));
			pProty7->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty7);
			//8
			CBCGPProp *pProty8=new CBCGPProp( CString(L"输出路径"),(_variant_t)out_filePathName,CString(L"This is a path of output."));
			pProty8->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty8);
			//9
			CBCGPProp *pProty9=new CBCGPProp( CString(L"输出驱动"),(_variant_t)out_driver,CString(L"The name is a kind of driver of the corresponding  file be output."));
			pProty9->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty9);
			//10
			CBCGPProp *pProty10=new CBCGPProp( CString(L"目标椭球"),(_variant_t)destEllip,CString(L"The name is the destination  elliptic."));
			pProty10->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty10);
			//11
			switch(OutCoordType)//输出坐标类型
			{
			case 0:
				strOutCoordType=L"未知";
				break;
			case 1:
				strOutCoordType=L"大地";
				break;
			case 2:
				strOutCoordType=L"空间直角";
				break;
			case 3:
				strOutCoordType=L"平面";
				break;
			default:break;				
			}
			CBCGPProp *pProty11=new CBCGPProp( CString(L"输出坐标类型"),(_variant_t)strOutCoordType,CString(L"The name is the output coordinate type."));
			pProty11->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty11);
			//12
			CBCGPProp *pProty12=new CBCGPProp( CString(L"输出中央子午线"),(_variant_t)outCentr_long,CString(L"The name is the output center long ."));
			pProty12->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty12);			
		


		/*
			对应页面切换过程
		*/

		CDeuDialog* pPage = NULL;
		pPage = (CDeuDialog*)pData->p1;
		
		//切换到选择页
		CMainFrame &MainFrm = *(CMainFrame*) AfxGetMainWnd();
		CDeu2000View &pView = *(CDeu2000View*)MainFrm.GetActiveView();

		if( pData->type == VEC_TASK )
		{
			for(int i=0; i<DEUMAINFRM.m_deuData->vecVector.GetCount(); i++)
			{
				if(pPage == DEUMAINFRM.m_deuData->vecVector.GetAt(i))
				{
					pView.m_DlgContainer.m_DeuTab.SetActiveTab(pPage->GlobalIndex);
				}
			}
		}
		else
		{
			for(int i=0; i<DEUMAINFRM.m_deuData->vecRaster.GetCount(); i++)
			{
				if(pPage == DEUMAINFRM.m_deuData->vecRaster.GetAt(i))
				{
					pView.m_DlgContainer.m_DeuTab.SetActiveTab(pPage->GlobalIndex);
				}
			}
		}
		
		
		

	}
	else   return;



}

LRESULT CDeuDlgTreeTask::OnRenTskFinished(WPARAM ,LPARAM )////you went i 
{
	LRESULT result = Default(); 

	HTREEITEM hSelItem=m_Tree.GetSelectedItem();
	CString TXT;
	TXT=m_Tree.GetItemText(hSelItem);

	//AfxMessageBox(TXT);//取到了命名后的值
	TreeData  *pData = NULL;
	pData = ( TreeData * )m_Tree.GetItemData(hSelItem);

	pPropage->m_PropList.RemoveAll();
	CDeuTask * pTask = NULL;

 if(pData!=NULL)
  
  {	
	  if( pData->type == VEC_TASK )
		{

			CDeuDataTransform * pTrans = ( CDeuDataTransform * ) pData->p1;
			pTask = pTrans->m_deuTask;
		    pTask->TaskName=TXT;
			
		}
		else
		{
			CDeuRasterTrans * pRasTans=(CDeuRasterTrans*)pData->p1;
			pTask=pRasTans->m_deuTask;
			pTask->TaskName=TXT;
			
		}
  }    

	return result;
}

void CDeuDlgTreeTask::DeleteNode(HTREEITEM item)
{
	this->m_Tree.DeleteItem(item);
}


