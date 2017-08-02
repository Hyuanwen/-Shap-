// DeuDlgTreeTask.cpp : ʵ���ļ�
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
// CDeuDlgTreeTask �Ի���

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


// CDeuDlgTreeTask ��Ϣ�������


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

	hRoot1 = m_Tree.InsertItem (_T("��Ŀ"), TVI_ROOT);
	

	//ʸ��
	VEC(CPropertyPage*)::iterator itVec;
	
	hVecParent = m_Tree.InsertItem (_T("ʸ��"), hRoot1);	

	//for (itVec = vecVecPage.begin();itVec != vecVecPage.end();itVec++)
	//{
	//	HTREEITEM  hItem1;
	//	hItem1=m_Tree.InsertItem(_T("ʸ��ת��"), hVecParent);
	//	(*itVec)->m_psp.dwFlags |= PSP_USETITLE; 
	//	(*itVec)->m_psp.pszTitle = "ʸ��ת��"; 


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

		
		m_strLabel.Format("ʸ��ת�� %d", n);
		m_Tree.InsertItem(m_strLabel, hVecParent);

	}

	m_Tree.Expand(hVecParent,TVE_EXPAND );

	//դ��


	VEC(CPropertyPage*)::iterator itRaster;
	hRasterParent = m_Tree.InsertItem (_T("դ��"), hRoot1);	
	
	
	/*for (itRaster = vecRasterPage.begin();itRaster != vecRasterPage.end();itRaster++)
	{
		HTREEITEM hItem2 = m_Tree.InsertItem ("դ��ת��", hRasterParent);

		(*itRaster)->m_psp.dwFlags |= PSP_USETITLE; 
		(*itRaster)->m_psp.pszTitle = "դ��ת��"; 

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

		m_strLabel.Format("դ��ת�� %d", n);
		m_Tree.InsertItem(m_strLabel, hRasterParent);
	}
	m_Tree.Expand(hRasterParent,TVE_EXPAND );

	m_Tree.Expand(hRoot1,TVE_EXPAND );

	return 0;
}


// CDLGTreeCtrl ��Ϣ�������

void  CDeuDlgTreeTask::OnSize(UINT nType, int cx, int cy) ///�д�������������
{
	CDialog::OnSize(nType,cx,cy);
	if (m_Tree.m_hWnd!=NULL)
	{
		m_Tree.SetWindowPos (NULL,nBorder, nBorder, cx-2*nBorder, cy-2*nBorder,SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


void CDeuDlgTreeTask::OnTvnSelectedChangepage(NMHDR *pNMHDR, LRESULT *pResult)
{



	//ѡ��ť��ͬʱҪ�������Ժ�����ת��ҳ��
	POINT  mPoint;
	GetCursorPos(&mPoint);

	TVHITTESTINFO hitInfo;
	hitInfo.pt=mPoint;

	HTREEITEM  hSelItem=m_Tree.GetSelectedItem();


	//��ʾ��Ӧ������
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
		/* ʸ������ */
		if( pData->type == VEC_TASK )
		{
			CDeuDataTransform * pTrans = ( CDeuDataTransform * ) pData->p1;
			pTask = pTrans->m_deuTask;
 
			strName			 =	pTask->TaskName;//��������
			strStatus		 =	pTask->TaskStatus;//����״̬			
			currentTable	 =	pTask->CurTable;//��ǰ������
			filePathName	 =	pTask->PathName;//�ļ�·����
			inDriver		 =	pTask->Driver;//����
			srcolEllip		 =	pTask->SrcEllip;//Դ����
			Incoordtype		 =	pTask->InCoordType;//������������			
			inCentre_long	 =	pTask->InCentr_long;//����������
			out_filePathName =	pTask->out_PathName;//���·��
			out_driver		 =	pTask->out_Driver;			//�������
			destEllip		 =	pTask->DestEllip;			//Ŀ������
			OutCoordType	 =	pTask->OutCoordType;		//�����������			
            outCentr_long	 =	pTask->OutCentr_long;      //�������������			
			pTask			 =	NULL;

		}

		/* դ������ */
		else /*(pData->type==TIF_TASK)*/
		{

			CDeuRasterTrans * pRasTans=(CDeuRasterTrans*)pData->p1;
			pTask			=	pRasTans->m_deuTask;
			strName			=	pTask->TaskName;//��������
			strStatus		=	pTask->TaskStatus;//����״̬			
			currentTable	=	pTask->CurTable;//��ǰ������
			filePathName	=	pTask->PathName;//�ļ�·����
			inDriver		=	pTask->Driver;//����
			srcolEllip		=	pTask->SrcEllip;//Դ����
			Incoordtype		=	pTask->InCoordType;//������������			
			inCentre_long	=	pTask->InCentr_long;//����������
			out_filePathName=	pTask->out_PathName;//���·��
			out_driver		=	pTask->out_Driver;//�������
			destEllip		=	pTask->DestEllip;//Ŀ������
			OutCoordType	=	pTask->OutCoordType;//�����������			
			outCentr_long	=	pTask->OutCentr_long;      //�������������			
			pTask=NULL;

		}
			//0
			CBCGPProp *pProty=new CBCGPProp(CString(L"��������") ,(_variant_t)strName, CString(L"The name is the simple description of the task.") );
			pProty->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty);
			//1		
			switch(_tstoi(strStatus))
			{
				case 0:
					strStatus=L"δ��ʼ";
					break;
				case 1:
					strStatus=L"ִ����";
					break;
				case 2:
					strStatus=L"���";
					break;
				default:break;
			}
			CBCGPProp *pProty1=new CBCGPProp( CString(L"����״̬"),(_variant_t)strStatus,CString (L"The statues of the task be on."));
			pProty1->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty1);
			//2
			CBCGPProp *pProty2=new CBCGPProp( CString(L"��ǰ������"),(_variant_t)currentTable,CString (L"This name is the table that user is using ."));
			pProty2->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty2);
			//3	
			CBCGPProp *pProty3=new CBCGPProp( CString(L"�ļ�·��"),(_variant_t)filePathName,CString (L"The name is path that the file has be saved."));
			pProty3->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty3);			
			//4
			CBCGPProp *pProty4=new CBCGPProp( CString(L"��������"),(_variant_t)out_driver,CString(L"The name is a kind of driver of the corresponding file."));
			pProty4->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty4);
			//5
			CBCGPProp *pProty5=new CBCGPProp( CString(L"Դ����"),(_variant_t)srcolEllip,CString(L"The name is a source elliptic."));
			pProty5->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty5);
			//6	
			switch(Incoordtype)//������������
			{
			case 0:
				strIncoordtype=L"δ֪";
				break;
			case 1:
				strIncoordtype=L"���";
				break;
			case 2:
				strIncoordtype=L"�ռ�ֱ��";
				break;
			case 3:
				strIncoordtype=L"ƽ��";
				break;
			default:break;		
			}
			CBCGPProp *pProty6=new CBCGPProp( CString(L"������������"),(_variant_t)strIncoordtype,CString(L"This is the type of coordinate."));
			pProty6->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty6);
			//7
			CBCGPProp *pProty7=new CBCGPProp( CString(L"����������"),(_variant_t)inCentre_long,CString(L"The name is the center of long."));
			pProty7->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty7);
			//8
			CBCGPProp *pProty8=new CBCGPProp( CString(L"���·��"),(_variant_t)out_filePathName,CString(L"This is a path of output."));
			pProty8->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty8);
			//9
			CBCGPProp *pProty9=new CBCGPProp( CString(L"�������"),(_variant_t)out_driver,CString(L"The name is a kind of driver of the corresponding  file be output."));
			pProty9->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty9);
			//10
			CBCGPProp *pProty10=new CBCGPProp( CString(L"Ŀ������"),(_variant_t)destEllip,CString(L"The name is the destination  elliptic."));
			pProty10->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty10);
			//11
			switch(OutCoordType)//�����������
			{
			case 0:
				strOutCoordType=L"δ֪";
				break;
			case 1:
				strOutCoordType=L"���";
				break;
			case 2:
				strOutCoordType=L"�ռ�ֱ��";
				break;
			case 3:
				strOutCoordType=L"ƽ��";
				break;
			default:break;				
			}
			CBCGPProp *pProty11=new CBCGPProp( CString(L"�����������"),(_variant_t)strOutCoordType,CString(L"The name is the output coordinate type."));
			pProty11->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty11);
			//12
			CBCGPProp *pProty12=new CBCGPProp( CString(L"�������������"),(_variant_t)outCentr_long,CString(L"The name is the output center long ."));
			pProty12->AllowEdit(FALSE);
			pPropage->m_PropList.AddProperty(pProty12);			
		


		/*
			��Ӧҳ���л�����
		*/

		CDeuDialog* pPage = NULL;
		pPage = (CDeuDialog*)pData->p1;
		
		//�л���ѡ��ҳ
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

	//AfxMessageBox(TXT);//ȡ�����������ֵ
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


