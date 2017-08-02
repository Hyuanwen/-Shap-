
#include "stdafx.h"
#include "DeuPanelTask.h"
#include "DeuVectorView.h"
#include "DeuRasterView.h"

// CDeuPanelTask
IMPLEMENT_DYNAMIC(CDeuPanelTask, CWnd)
CDeuPanelTask::CDeuPanelTask()
{
	nVecIndex = 0;
	nRasterIndex = 0;
}

CDeuPanelTask::~CDeuPanelTask()
{
}

BEGIN_MESSAGE_MAP(CDeuPanelTask, CWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_MESSAGE(WM_TASK_VECTOR, OnInsertVectorNode)
	ON_MESSAGE(WM_TASK_RASTER, OnInsertRasterNode)
	ON_NOTIFY(NM_CLICK, IDC_TREETASK, &CDeuPanelTask::OnNMClickTree1)
END_MESSAGE_MAP()

// CDeuPanelTask ��Ϣ�������
int CDeuPanelTask::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	if (m_wndSolutionView.GetSafeHwnd() == 0)
	{
		if (!m_wndSolutionView.Create(WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS, CRect(0,0,0,0), this,  IDC_TREETASK)) //0xFF
		{
			TRACE0( "Unable to create tree control.\n" );
			return 0;
		}

		if (!CreateImageList(m_ilSolutionView, IDB_TREEIMG))
		{
			return 0;
		}
			
		m_wndSolutionView.SetImageList(&m_ilSolutionView, TVSIL_NORMAL);

		// add the parent item, make it bold
		htiParent = m_wndSolutionView.InsertItem(_T("ת������"), 1, 1, TVI_ROOT);
		m_wndSolutionView.SetItemState (htiParent, TVIS_BOLD, TVIS_BOLD);

		htiVector = m_wndSolutionView.InsertItem(_T("ʸ��ת��"), 2, 2, htiParent);
		m_wndSolutionView.Expand(htiVector, TVE_EXPAND);
		
		htiRaster = m_wndSolutionView.InsertItem(_T("դ��ת��"), 3, 3, htiParent);
		m_wndSolutionView.Expand(htiRaster, TVE_EXPAND);

		m_wndSolutionView.Expand(htiParent, TVE_EXPAND);
	}

	return 0;
}

void CDeuPanelTask::OnSetFocus(CWnd* pOldWnd)
{
	//CWnd::OnSetFocus(pOldWnd);
	m_wndSolutionView.SetFocus();
}

void CDeuPanelTask::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	int nTop = 0;
	if (m_wndSolutionView.GetSafeHwnd())
	{
		m_wndSolutionView.MoveWindow(0, nTop, cx, cy - nTop);
		m_wndSolutionView.Invalidate(FALSE);
	}
}

//����ʸ���ڵ�
LRESULT CDeuPanelTask::OnInsertVectorNode(WPARAM wParam, LPARAM lParam)
{
	CString strName("ʸ��ת��");
	strName.Format("ʸ��ת��%d", (nVecIndex+1));	
	_TreeVectorList.Add(m_wndSolutionView.InsertItem(strName, 4, 4, htiVector));
	nVecIndex++; //����������
	m_wndSolutionView.Invalidate(FALSE);
	m_wndSolutionView.Expand(htiVector, TVE_EXPAND);

	this->KeepIndex(VECTOR);

	return 0;
}

//����դ��ڵ�
LRESULT CDeuPanelTask::OnInsertRasterNode(WPARAM wParam, LPARAM lParam)
{
	CString strName("դ��ת��");
	strName.Format("դ��ת��%d", nRasterIndex+1);
	_TreeRasterList.Add(m_wndSolutionView.InsertItem(strName, 4, 4, htiRaster));
	nRasterIndex++; //����������	
	m_wndSolutionView.Invalidate(FALSE);
	m_wndSolutionView.Expand(htiRaster, TVE_EXPAND);
	
	this->KeepIndex(RASTER);

	return 0;
}

//ɾ����Ӧ�ڵ�
void CDeuPanelTask::OnDeleteNode(TranformType _TranType, int nIndex)
{
	switch(_TranType)
	{
	case RASTER:
		m_wndSolutionView.DeleteItem(_TreeRasterList.GetAt(nIndex));
		_TreeRasterList.RemoveAt(nIndex);
		this->KeepIndex(RASTER);
		break;

	case VECTOR:
		m_wndSolutionView.DeleteItem(_TreeVectorList.GetAt(nIndex));
		_TreeVectorList.RemoveAt(nIndex);
		this->KeepIndex(VECTOR);
		break;
	}
}

/*
	���ĵ���¼����ֹ��ؼ���Ϣӳ��
	
		������������ָ����Doc
*/
void CDeuPanelTask::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	HTREEITEM     hItem;
	DWORD         dwpos = GetMessagePos();   
	TVHITTESTINFO ht = {0};  

	ht.pt.x = GET_X_LPARAM(dwpos);
	ht.pt.y = GET_Y_LPARAM(dwpos);
	::MapWindowPoints(HWND_DESKTOP,pNMHDR->hwndFrom, &ht.pt, 1); //����Ļ����ת���ɿؼ�����
	TreeView_HitTest(pNMHDR->hwndFrom, &ht);				     //ȷ�����������һ��
	
	if((ht.hItem != htiParent) && (ht.hItem != htiVector)  && (ht.hItem != htiRaster))
	{
		CString m_NodeName;
		m_NodeName = m_wndSolutionView.GetItemText(ht.hItem);
		
		//��ȡ���ڵ�
		hItem = m_wndSolutionView.GetParentItem(ht.hItem);
		if(hItem == htiRaster)
		{
			//���ݽڵ������ҵ���Ӧ�ӿ��
			DWORD d = m_wndSolutionView.GetItemData(ht.hItem);
			if(_ViewRasterList.GetCount() > 0)
			{
				((CDeuRasterView*)_ViewRasterList.GetAt(d))->ActiveParentFrm();
			}		
		}
		else if(hItem == htiVector)
		{				
			//���ݽڵ������ҵ���Ӧ�ӿ��
			DWORD d = m_wndSolutionView.GetItemData(ht.hItem);
			if(_ViewVectorList.GetCount() > 0)
			{
				((CDeuVectorView*)_ViewVectorList.GetAt(d))->ActiveParentFrm();
			}
		}
	}
}

/*
	ά�����ڵ������˳����CArray ����һ��
*/
void CDeuPanelTask::KeepIndex(TranformType _TranType)
{	
	switch(_TranType)
	{
	case RASTER:
		//ά������
		for(int k=0; k<_TreeRasterList.GetCount(); k++)
		{		
			m_wndSolutionView.SetItemData(_TreeRasterList.GetAt(k), k);
		}
		break;
	case VECTOR:
		//ά������
		for(int k=0; k<_TreeVectorList.GetCount(); k++)
		{		
			m_wndSolutionView.SetItemData(_TreeVectorList.GetAt(k), k);
		}
		break;
	}
}