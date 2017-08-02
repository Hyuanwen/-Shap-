// DeuCommCPDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "DeuDlgCommCP.h"
#include "DeuDlgCp.h"
#include "DeuDlgDataSrc.h"
#include "DeuTranslate.h"
#include "DeuDlgCpList.h"
#include "SetTransParams.h"

// CDeuDlgCommCP �Ի���
IMPLEMENT_DYNAMIC(CDeuDlgCommCP, CDialog)
CDeuDlgCommCP::CDeuDlgCommCP(TranformType __Type, CWnd* pParent /*=NULL*/)
		     : CDialog(CDeuDlgCommCP::IDD, pParent)
{
	if(__Type == VECTOR)
	{
		m_strModel = sz_TranModel_Vector[0];
	}
	else
	{
		m_strModel = sz_TranModel_Raster[0];
	}

	_Type = __Type;
	m_7param = new double[40];
	m_Invpara = new double[40];

	m_x = NULL;
	m_y = NULL;
	m_z = NULL;
	m_x2 = NULL;
	m_y2 = NULL;
	m_z2 = NULL;
	m_res_x = NULL;
	m_res_y = NULL;
	m_res_z = NULL;
	m_res = NULL;

	m_install = FALSE;
	ori_x = _T("");
	ori_y = _T("");
	ori_z = _T("");
	des_x = _T("");
	des_y = _T("");
	des_z = _T("");
	lbt = 0;
	m_strControlPath = _T("");
	IsInputParams = FALSE;
}

CDeuDlgCommCP::~CDeuDlgCommCP()
{
	delete[] m_x;
	delete[] m_y;
	delete[] m_z;
	delete[] m_x2;
	delete[] m_y2;
	delete[] m_z2;
	delete[] m_res_x;
	delete[] m_res_y;
	delete[] m_res_z;
	delete[] m_res;
	delete[] m_7param;   //�߲���Ҳ�ɽв���
	delete[] m_Invpara;  //�����

	for(int i = 0; i <_controlPointPairs._controlPointPair.GetCount(); i++)
	{
		delete _controlPointPairs._controlPointPair.GetAt(i);
	}

	_controlPointPairs._controlPointPair.RemoveAll();
}

void CDeuDlgCommCP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CONTROL_PT, m_List);
	DDX_Control(pDX, IDC_EDIT_SRC, m_Edit_Src);
	DDX_Control(pDX, IDC_EDIT_DEST, m_Edit_Dest);
}

BEGIN_MESSAGE_MAP(CDeuDlgCommCP, CDialog)
	ON_COMMAND(ID_IMPORT, OnImportData)
	ON_COMMAND(ID_EXPORT, OnExportData)
	ON_COMMAND(ID_DELROW,OnDelRow)
	ON_COMMAND(ID_DEL_ALL,OnDelAll)
	ON_COMMAND(ID_CREATE_CP,OnCreateData)
	ON_BN_CLICKED(IDC_BTN_CREATE_CP, &CDeuDlgCommCP::OnCreateData)
	ON_BN_CLICKED(IDC_BTN_IMPORT_CP, &CDeuDlgCommCP::OnImportData)
	ON_BN_CLICKED(IDC_BTN_EXPORT_CP, &CDeuDlgCommCP::OnExportData)
	ON_BN_CLICKED(IDC_BTN_REMOVE, &CDeuDlgCommCP::OnDelAll)
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CONTROL_PT, &CDeuDlgCommCP::OnNMRClickListControlPt)
	ON_EN_SETFOCUS(IDC_EDIT_SRC, &CDeuDlgCommCP::OnEnSetfocusEditSrc)
	ON_EN_SETFOCUS(IDC_EDIT_DEST, &CDeuDlgCommCP::OnEnSetfocusEditDest)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONTROL_PT, &CDeuDlgCommCP::OnNMDblclkListControlPt)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CONTROL_PT, &CDeuDlgCommCP::OnLvnKeydownListControlPt)
	//ON_NOTIFY(WM_HOTKEY, IDC_LIST_CONTROL_PT, &CDeuDlgCommCP::OnListHotKey)
	ON_WM_CLOSE()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CONTROL_PT, &CDeuDlgCommCP::OnLvnColumnclickListControlPt)
	ON_BN_CLICKED(IDC_BTN_INSTALL, &CDeuDlgCommCP::OnBnClickedButtonInstall)
	ON_BN_CLICKED(IDC_OUT_PUT_PARA, &CDeuDlgCommCP::OnBnClickedOutPutPara)
	ON_BN_CLICKED(IDC_BTN_GRID, &CDeuDlgCommCP::OnBnClickedBtnGrid)
	ON_BN_CLICKED(IDC_BTN_INPUTPARAM, &CDeuDlgCommCP::OnBnClickedBtnInputparam)
END_MESSAGE_MAP()

// CDeuDlgCommCP ��Ϣ�������
void CDeuDlgCommCP::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rct,rctwnd, relRct;

	//�ؼ�����Ӧ
	CStatic* p_pt	   = (CStatic*)GetDlgItem(IDC_STATIC_PT);
	CStatic* p_src	   = (CStatic*)GetDlgItem(IDC_STATIC_SRC);
	CStatic* p_dest	   = (CStatic*)GetDlgItem(IDC_STATIC_DEST);
	CEdit* p_edit_src  = (CEdit*)GetDlgItem(IDC_EDIT_SRC);
	CEdit* p_edit_dest = (CEdit*)GetDlgItem(IDC_EDIT_DEST);
	CButton* p_btn_cp  = (CButton*)GetDlgItem(IDC_BTN_CREATE_CP);
	CListCtrl* p_list  = (CListCtrl*)GetDlgItem(IDC_LIST_CONTROL_PT);

	if(p_pt->GetSafeHwnd())
	{
		int nMiddle = 0, nWidth=0, offset_x=0;

		this->GetClientRect(&rct);
		p_pt->MoveWindow(&rct);
		ClientToScreen(&rct);
		
		this->GetWindowRect(&rctwnd);
		nMiddle = rctwnd.Width()/2;

//----------------------- ��߿ؼ� -----------------------------------

		//Դ����ϵLabel
		p_src->GetWindowRect(&relRct);
		nWidth = relRct.Width();
		relRct.left = rctwnd.left+30;
		relRct.right = relRct.left+nWidth;
		offset_x = relRct.right;
		ScreenToClient(&relRct);
		p_src->MoveWindow(&relRct);
	
		/*
		p_btn_cp->GetWindowRect(&relRct);
		nWidth = relRct.Width();
		relRct.left = rctwnd.left+30;
		relRct.right = relRct.left+nWidth;
		ScreenToClient(&relRct);
		p_btn_cp->MoveWindow(&relRct);
		*/

		p_list->GetWindowRect(&relRct);
		nWidth = relRct.Width();
		relRct.left = rctwnd.left+30;
		relRct.right = rctwnd.right -20;
		ScreenToClient(&relRct);
		p_list->MoveWindow(&relRct);

		//�ؼ�
		p_edit_src->GetWindowRect(&relRct);
		relRct.left = offset_x;
		relRct.right = relRct.left+nMiddle-90;
		ScreenToClient(&relRct);
		p_edit_src->MoveWindow(&relRct);
		
//----------------------- �ұ߿ؼ� -----------------------------------

		//Ŀ������ϵ Label
		p_dest->GetWindowRect(&relRct);
		nWidth = relRct.Width();
		relRct.left = rctwnd.left+nMiddle+20;
		relRct.right = relRct.left+nWidth;
		offset_x = relRct.right;
		ScreenToClient(&relRct);
		p_dest->MoveWindow(&relRct);

		//�ؼ�
		p_edit_dest->GetWindowRect(&relRct);
		nWidth = relRct.Width();
		relRct.left = offset_x;
		relRct.right = rct.right-20;
		ScreenToClient(&relRct);
		p_edit_dest->MoveWindow(&relRct);
	}
}

BOOL CDeuDlgCommCP::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_List.InsertColumn(0, _T("ԴX"), 80);	
	m_List.InsertColumn(1, _T("ԴY"), 80);
	m_List.InsertColumn(2, _T("ԴZ"), 80);

	m_List.InsertColumn(3, _T("Ŀ��X"), 80);
	m_List.InsertColumn(4, _T("Ŀ��Y"), 80);
	m_List.InsertColumn(5, _T("Ŀ��Z"), 80);
	
	m_List.InsertColumn(6, _T("�в�X"), 80);
	m_List.InsertColumn(7, _T("�в�Y"), 80);
	m_List.InsertColumn(8, _T("�в�Z"), 80);

	m_List.InsertColumn(9, _T("�в�"), 80);

	//���ÿ�
	int n = m_List.GetHeaderCtrl()->GetItemCount();
	while(n >= 0)
	{
		m_List.SetColumnWidth(n, 80);
		n--;
	}

	DWORD dwStyle = m_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;  //LVS_EX_GRIDLINES
	m_List.SetExtendedStyle(dwStyle);

	m_bmp_import.LoadBitmap(IDB_IMPORT);
	m_bmp_save.LoadBitmap(IDB_SAVE);
	m_bmp_del.LoadBitmap(IDB_DEL);
	m_menu.LoadMenu(IDR_MENU_LIST_PT);
	m_menu.GetSubMenu(0)->SetMenuItemBitmaps(1, MF_BYPOSITION, &m_bmp_import, &m_bmp_import);
	m_menu.GetSubMenu(0)->SetMenuItemBitmaps(2, MF_BYPOSITION, &m_bmp_save, &m_bmp_save);
	m_menu.GetSubMenu(0)->SetMenuItemBitmaps(3, MF_BYPOSITION, &m_bmp_del, &m_bmp_del);

	return TRUE;
}

void CDeuDlgCommCP::OnNMRClickListControlPt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	
	CPoint m_pt;
	GetCursorPos(&m_pt);
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, m_pt.x, m_pt.y, this);
}

void CDeuDlgCommCP::OnEnSetfocusEditSrc()
{
	CDeuDlgDataSrc m_DataSrcDlg;
	m_DataSrcDlg.DoModal();

	CEdit* p_edit_src = (CEdit*)GetDlgItem(IDC_EDIT_SRC);
	if(!m_DataSrcDlg.m_strSelectItem.IsEmpty())
	{
		p_edit_src->SetWindowText(m_DataSrcDlg.m_strSelectItem);
	}
}

void CDeuDlgCommCP::OnEnSetfocusEditDest()
{
	CDeuDlgDataSrc m_DataSrcDlg;
	m_DataSrcDlg.DoModal();
	
	CEdit* p_edit_dest = (CEdit*)GetDlgItem(IDC_EDIT_DEST);
	if(!m_DataSrcDlg.m_strSelectItem.IsEmpty())
	{
		p_edit_dest->SetWindowText(m_DataSrcDlg.m_strSelectItem);
	}
}

void CDeuDlgCommCP::OnImportData()
{
	CFileDialog m_FileDlg(true,"ControlPoint", "*.cp",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, "ControlPoint(*.cp)|*.cp|Excel(*.xlsx)|*.xlsx||",NULL);
	m_FileDlg.m_ofn.lpstrTitle = _T("ѡ����Ƶ��ļ�");
	if(m_FileDlg.DoModal() == IDOK)
	{
		m_strControlPath = m_FileDlg.GetPathName();

		CString                   strPath;
		CString                   strText;

		ClearDataPackage();

		//��Ҫ���ļ����ֽ��н����ж���ѡ���cp�ļ�����xlsx�ļ�
		strPath = m_FileDlg.GetPathName();
		int i = strPath.ReverseFind('.');
		strText = strPath.Right(strPath.GetLength()-1-i);

		if (strText == _T("xlsx"))
		{
			GetControlPointByExcel(strPath);

			//ReLoadList();
			CalcResidual();

			this->UpdateData(FALSE);
		}
		else if (strText == _T("cp"))
		{
			if (!m_XmlCP.LoadFile(m_FileDlg.GetPathName()))
			{
				AfxMessageBox("���ؿ��Ƶ��ļ�ʧ��!");
				return;
			}
			m_XmlCP.GetControlPoint(&_controlPointPairs);
			//ReLoadList();		
			CalcResidual();

			this->UpdateData(FALSE);
		}		
		else
		{
			AfxMessageBox("��֧�ֵĿ��Ƶ��ļ���ʽ����!");
			return;
		}
	}

	return;
}

void CDeuDlgCommCP::OnExportData()
{
	if(this->m_List.GetItemCount() <= 0)
	{
		AfxMessageBox("���ޱ�������.");
	}
	else
	{
		CFileDialog m_FileDlg(false,"ControlPoint", "*.cp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "ControlPoint(*.cp)",NULL);
		m_FileDlg.m_ofn.lpstrTitle = _T("������Ƶ��ļ�");
		if(m_FileDlg.DoModal() == IDOK)
		{
			CDeuXmlWriter m_XmlWirte;
			m_XmlWirte.BuildControlPointXml(m_FileDlg.GetPathName(),&_controlPointPairs);
		}
	}
}

//ɾ������
void CDeuDlgCommCP::OnDelAll()
{
	m_List.DeleteAllItems();
	while(_controlPointPairs._controlPointPair.GetCount() > 0)
	{
		delete _controlPointPairs._controlPointPair.GetAt(0);
		_controlPointPairs._controlPointPair.RemoveAt(0);
	}
}

//ɾ��ָ����
void CDeuDlgCommCP::OnDelRow()
{
	int n = m_List.GetSelectionMark();
	m_List.DeleteItem(n);
	delete _controlPointPairs._controlPointPair.GetAt(n);
	_controlPointPairs._controlPointPair.RemoveAt(n);
}

void CDeuDlgCommCP::OnCreateData()
{
	/*
	CDeuDlgCp m_Dlg;

	if(m_Dlg.DoModal() == IDOK)
	{
		p_ControlPointPair pControlPointPair = new ControlPointPair;
		pControlPointPair->X_SRC = m_Dlg.m_X_SRC;
		pControlPointPair->Y_SRC = m_Dlg.m_Y_SRC;
		pControlPointPair->Z_SRC = m_Dlg.m_Z_SRC;

		pControlPointPair->X_DEST = m_Dlg.m_X_DEST;
		pControlPointPair->Y_DEST = m_Dlg.m_Y_DEST;
		pControlPointPair->Z_DEST = m_Dlg.m_Z_DEST;

		_controlPointPairs._controlPointPair.Add(pControlPointPair);
		this->ReLoadList();
	}
	*/

	CDeuDlgCpList m_Dlg;
	if (m_Dlg.DoModal() == IDOK)
	{
		//���ж�ԭ�е��б����Ƿ����ֵ
		if ( _controlPointPairs._controlPointPair.GetCount() > 0 ) 
		{
			if ( MessageBox(_T("ԭ�б����Ѵ��ڲ��ֿ��Ƶ��Ƿ񱣴棿"), NULL, MB_YESNO) == IDYES )
			{
				for (int i = 0; i < m_Dlg.m_ControlPoint.GetStructNum(); i++)
				{
					p_ControlPointPair pControlPointPair = new ControlPointPair;
					pControlPointPair->X_SRC.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->des_x);
                    pControlPointPair->Y_SRC.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->des_y);
					pControlPointPair->Z_SRC.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->des_z);
					
					pControlPointPair->X_DEST.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->res_x);
					pControlPointPair->Y_DEST.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->res_y);
					pControlPointPair->Z_DEST.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->res_z);

					_controlPointPairs._controlPointPair.Add(pControlPointPair);

					ReLoadList();
				}
			}
			else   
			{
				//���ԭ�����б���Ϣ
				ClearDataPackage();

				for (int i = 0; i < m_Dlg.m_ControlPoint.GetStructNum(); i++)
				{
					p_ControlPointPair pControlPointPair = new ControlPointPair;
					pControlPointPair->X_SRC.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->des_x);
					pControlPointPair->Y_SRC.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->des_y);
					pControlPointPair->Z_SRC.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->des_z);

					pControlPointPair->X_DEST.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->res_x);
					pControlPointPair->Y_DEST.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->res_y);
					pControlPointPair->Z_DEST.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->res_z);

					_controlPointPairs._controlPointPair.Add(pControlPointPair);

					ReLoadList();
				}
			}
		}
		else
		{
			for (int i = 0; i < m_Dlg.m_ControlPoint.GetStructNum(); i++)
			{
				p_ControlPointPair pControlPointPair = new ControlPointPair;
				pControlPointPair->X_SRC.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->des_x);
				pControlPointPair->Y_SRC.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->des_y);
				pControlPointPair->Z_SRC.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->des_z);

				pControlPointPair->X_DEST.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->res_x);
				pControlPointPair->Y_DEST.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->res_y);
				pControlPointPair->Z_DEST.Format(_T("%s"), m_Dlg.m_ControlPoint.GetAt(i)->res_z);

				_controlPointPairs._controlPointPair.Add(pControlPointPair);

				ReLoadList();
			}
		}
		//�ٴ��ж��Ƿ��б��д����㹻�Ŀ��Ƶ㣬����еĻ�����ʾ�Ƿ���Ҫ���м���
		//ͨ�����Ƶ����ת������ ������Ҫ4���� ��Ȼ��ͬ�ļ��㷽��������Ҫ�����ٿ��Ƶ������ͬ ����������ʱд��4��
		if (_controlPointPairs._controlPointPair.GetCount() >= 4) 
		{
			if ( MessageBox(_T("ԭ�б��п��Ƶ�������������Ҫ��,�Ƿ����¼���ת��������"), NULL, MB_YESNO) == IDYES )
			{
				CalcResidual();
			}
		}
	}
}

//˫��List Item
void CDeuDlgCommCP::OnNMDblclkListControlPt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if(pNMItemActivate->iItem != -1)
	{
		CDeuDlgCp m_Dlg;
		m_Dlg.IsUpdate = TRUE;
		m_Dlg.m_X_SRC = m_List.GetItemText(pNMItemActivate->iItem, 0);
		m_Dlg.m_Y_SRC = m_List.GetItemText(pNMItemActivate->iItem, 1);
		m_Dlg.m_Z_SRC = m_List.GetItemText(pNMItemActivate->iItem, 2);

		m_Dlg.m_X_DEST = m_List.GetItemText(pNMItemActivate->iItem, 3);
		m_Dlg.m_Y_DEST = m_List.GetItemText(pNMItemActivate->iItem, 4);
		m_Dlg.m_Z_DEST = m_List.GetItemText(pNMItemActivate->iItem, 5);
		
		if(m_Dlg.DoModal() == IDOK)
		{
			_controlPointPairs._controlPointPair.GetAt(pNMItemActivate->iItem)->X_SRC = m_Dlg.m_X_SRC;
			_controlPointPairs._controlPointPair.GetAt(pNMItemActivate->iItem)->Y_SRC = m_Dlg.m_Y_SRC;
			_controlPointPairs._controlPointPair.GetAt(pNMItemActivate->iItem)->Z_SRC = m_Dlg.m_Z_SRC;

			_controlPointPairs._controlPointPair.GetAt(pNMItemActivate->iItem)->X_DEST = m_Dlg.m_X_DEST;
			_controlPointPairs._controlPointPair.GetAt(pNMItemActivate->iItem)->Y_DEST = m_Dlg.m_Y_DEST;
			_controlPointPairs._controlPointPair.GetAt(pNMItemActivate->iItem)->Z_DEST = m_Dlg.m_Z_DEST;

			this->ReLoadList();
		}
	}

	*pResult = 0;
}

//ʹ��delete��ɾ������
void CDeuDlgCommCP::OnLvnKeydownListControlPt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	
	if(pLVKeyDow->wVKey == VK_DELETE)
	{
		int n = m_List.GetSelectionMark();
		m_List.DeleteItem(n);
		_controlPointPairs._controlPointPair.RemoveAt(n);
	}

	*pResult = 0;
}

//��սṹ������
void CDeuDlgCommCP::ClearDataPackage()
{
	while(_controlPointPairs._controlPointPair.GetCount() > 0)
	{
		delete _controlPointPairs._controlPointPair.GetAt(0);
		_controlPointPairs._controlPointPair.RemoveAt(0);
	}
}

//���¼������ݵ��б�
void CDeuDlgCommCP::ReLoadList()
{
	m_List.DeleteAllItems();
	for(int n=0; n<_controlPointPairs._controlPointPair.GetCount(); n++)
	{
		m_List.InsertItem(n, NULL);
// 		m_List.SetItemText(n, 0, ((p_ControlPointPair)_controlPointPairs._controlPointPair.GetAt(n))->X_SRC);
// 		m_List.SetItemText(n, 1, ((p_ControlPointPair)_controlPointPairs._controlPointPair.GetAt(n))->Y_SRC);
// 		m_List.SetItemText(n, 2, ((p_ControlPointPair)_controlPointPairs._controlPointPair.GetAt(n))->Z_SRC);
// 
// 		m_List.SetItemText(n, 3, ((p_ControlPointPair)_controlPointPairs._controlPointPair.GetAt(n))->X_DEST);
// 		m_List.SetItemText(n, 4, ((p_ControlPointPair)_controlPointPairs._controlPointPair.GetAt(n))->Y_DEST);
// 		m_List.SetItemText(n, 5, ((p_ControlPointPair)_controlPointPairs._controlPointPair.GetAt(n))->Z_DEST);

		m_List.SetItemText(n, 0, _T("********"));
		m_List.SetItemText(n, 1, _T("********"));
		m_List.SetItemText(n, 2, _T("********"));

		m_List.SetItemText(n, 3, _T("********"));
		m_List.SetItemText(n, 4, _T("********"));
		m_List.SetItemText(n, 5, _T("********"));

		m_List.SetItemText(n, 6, ((p_ControlPointPair)_controlPointPairs._controlPointPair.GetAt(n))->X_Residual);
		m_List.SetItemText(n, 7, ((p_ControlPointPair)_controlPointPairs._controlPointPair.GetAt(n))->Y_Residual);
		m_List.SetItemText(n, 8, ((p_ControlPointPair)_controlPointPairs._controlPointPair.GetAt(n))->Z_Residual);

		m_List.SetItemText(n, 9, ((p_ControlPointPair)_controlPointPairs._controlPointPair.GetAt(n))->Total_Residual);
	}
}

//����в�
void CDeuDlgCommCP::CalcResidual()
{
	int nCount = _controlPointPairs._controlPointPair.GetCount();

	if(m_x) delete m_x;
	if(m_y) delete m_y;
	if(m_z) delete m_z;

	if(m_x2) delete m_x2;
	if(m_y2) delete m_y2;
	if(m_z2) delete m_z2;

	if(m_res_x) delete m_res_x;
	if(m_res_y) delete m_res_y;
	if(m_res_z) delete m_res_z;
	if(m_res)   delete m_res;

	m_x = new double[nCount];
	m_y = new double[nCount];
	m_z = new double[nCount];

	m_x2 = new double[nCount];
	m_y2 = new double[nCount];
	m_z2 = new double[nCount];

	m_res_x = new double[nCount];
	m_res_y = new double[nCount];
	m_res_z = new double[nCount];
	m_res	= new double[nCount];

	CString m_Src, m_Dest;
	m_Edit_Src.GetWindowText(m_Src);
	m_Edit_Dest.GetWindowText(m_Dest);

	if (m_Src.IsEmpty() || m_Dest.IsEmpty())
	{
		MessageBox(_T("��ѡ������ϵ����"));
		return;
	}
	
	//1. �ҵ�����ϵת��������
	__COORDTYPE _type_src = m_TaskProcess.FindCoordindateType(m_Src);
	__COORDTYPE _type_dest = m_TaskProcess.FindCoordindateType(m_Dest);

	//2. �ҵ�����ϵ������ָ�� alter by chenyong 2013-01-10
	CDeuEllipse pSrcEllipse = m_TaskProcess.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, m_Src);
	CDeuEllipse pDestEllipse = m_TaskProcess.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, m_Dest);

	for(int n=0; n<nCount; n++)
	{
		m_x[n] = _tstof(_controlPointPairs._controlPointPair.GetAt(n)->X_SRC);
		m_y[n] = _tstof(_controlPointPairs._controlPointPair.GetAt(n)->Y_SRC);
		m_z[n] = _tstof(_controlPointPairs._controlPointPair.GetAt(n)->Z_SRC);

		m_x2[n] = _tstof(_controlPointPairs._controlPointPair.GetAt(n)->X_DEST);
		m_y2[n] = _tstof(_controlPointPairs._controlPointPair.GetAt(n)->Y_DEST);
		m_z2[n] = _tstof(_controlPointPairs._controlPointPair.GetAt(n)->Z_DEST);

		m_res_x[n] = -1;
		m_res_y[n] = -1;
		m_res_z[n] = -1;

		m_res[n] = -1;
	}

	int iModel = -1;
	if( m_strModel == "����ɯת��ģ��")
	{		
		iModel=MODEL_BURSA;
	}
	else if(m_strModel == "��ά�߲���ת��ģ��")
	{		
		iModel=MODEL_D2P7;
	}
	else if (m_strModel == "��ά�߲���ת��ģ��")
	{	
		iModel=MODEL_D3P7;
	}
	else if (m_strModel == "ƽ���Ĳ���ת��ģ��")
	{		
		iModel=MODEL_D2P4;
	}
	else if (m_strModel == "����ת��ģ��")
	{
		iModel=MODEL_GRID;
	}
	else if(m_strModel == "����ת��ģ��")
	{		
		iModel=MOD_AFFINE;
	}
	else if(m_strModel == "һ�׶���ʽת��ģ��")
	{		
		iModel=MOD_POLYNOMIAL1;
	}
	else if (m_strModel == "���׶���ʽת��ģ��")
	{	
		iModel=MOD_POLYNOMIAL2;
	}
	else if (m_strModel == "���׶���ʽת��ģ��")
	{		
		iModel=MOD_POLYNOMIAL3; 
	}
	else if (m_strModel == "�Ľ׶���ʽת��ģ��")
	{		
		iModel=MOD_POLYNOMIAL4;
	}
	else if (m_strModel == "����ת��ģ��ȫͼ��ƽ�Ʒ�")
	{		
		iModel=MODEL_TRANS_ALL_AFFINE;
	}
	else if (m_strModel == "����ת��ģ��ȫͼ��ƽ�Ʒ�")
	{		
		iModel=MODEL_GRID;
	}
	else if(m_strModel == "����ת��ģ��ȫͼ��ƽ�Ʒ�")
	{
		iModel=MODEL_TRANS_ALL_GRID;
	}

	switch(_Type)
	{
	case VECTOR:
		{
			m_TaskProcess.Task_Calculate7Param(iModel, 
				_type_src,
				_type_src,
				pSrcEllipse,
				pDestEllipse,
				nCount,
				m_x,
				m_y,
				m_z,
				m_x2,
				m_y2,
				m_z2,
				m_res_x,
				m_res_y,
				m_res_z,
				m_res,
				m_7param);
		}
		break;
	case RASTER:
		{
			ULONG nParam = 0;
			m_TaskProcess.Task_RasterCalculate7Param(iModel,
				_type_src,
				_type_src,
				pSrcEllipse,
				pDestEllipse,
				nCount,
				m_x,
				m_y,
				m_z,
				m_x2,
				m_y2,
				m_z2,
				m_res_x,
				m_res_y,
				m_res_z,
				m_res,
				m_7param,
				m_Invpara,
				&nParam);
		}
		break;
	default:
		break;
	}

	m_imodel=iModel;

	for(int n=0; n<nCount; n++)
	{
		_controlPointPairs._controlPointPair.GetAt(n)->X_Residual.Format("%.8f", m_res_x[n]);
		_controlPointPairs._controlPointPair.GetAt(n)->Y_Residual.Format("%.8f", m_res_y[n]);
		_controlPointPairs._controlPointPair.GetAt(n)->Z_Residual.Format("%.8f", m_res_z[n]);

		_controlPointPairs._controlPointPair.GetAt(n)->Total_Residual.Format("%.8f", m_res[n]);
	}

	this->ReLoadList();

	return ;
}

//void CDeuDlgCommCP::OnListHotKey(WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}

//BOOL CDeuDlgCommCP::PreTranslateMessage(MSG* pMsg)
//{
//	if   (pMsg-> message  ==  WM_KEYDOWN 
//		&& pMsg-> hwnd == m_List.GetSafeHwnd()
//		&&pMsg-> wParam  ==  'C'   
//		&& (GetKeyState(VK_CONTROL)&0x8000)) 
//	{
//		CString source;
//		source = "131 533 64564 4646";
//		HGLOBAL clipbuffer;
//		char * buffer;
//		EmptyClipboard();
//		clipbuffer = GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT,sizeof(1024));//
//		buffer = (char*)GlobalLock(clipbuffer);
//		strcpy(buffer, LPCSTR(source));
//		SetClipboardData(CF_TEXT,clipbuffer);
//		GlobalUnlock(clipbuffer);
//		CloseClipboard();
//
//	}
//
//	return CDialog::PreTranslateMessage(pMsg);
//}

void CDeuDlgCommCP::OnClose()
{
	delete[] m_x;
	delete[] m_y;
	delete[] m_z;
	delete[] m_x2;
	delete[] m_y2;
	delete[] m_z2;
	delete[] m_res_x;
	delete[] m_res_y;
	delete[] m_res_z;
	delete[] m_res;
	delete[] m_7param;  //�߲���Ҳ�ɽв���
	delete[] m_Invpara; //�����

	while(_controlPointPairs._controlPointPair.GetCount()>0)
	{
		delete _controlPointPairs._controlPointPair.GetAt(0);
	}

	_controlPointPairs._controlPointPair.RemoveAll();

	CDialog::OnClose();
}

void CDeuDlgCommCP::DisableAllController()
{
	CButton* p_btn1 = (CButton*)GetDlgItem(IDC_BTN_IMPORT_CP);
	CButton* p_btn2 = (CButton*)GetDlgItem(IDC_BTN_EXPORT_CP);
	CButton* p_btn3 = (CButton*)GetDlgItem(IDC_BTN_CREATE_CP);
	CButton* p_btn4 = (CButton*)GetDlgItem(IDC_BTN_REMOVE);
	CButton* p_btn5 = (CButton*)GetDlgItem(IDC_BTN_INSTALL);
	CButton* p_btn6 = (CButton*)GetDlgItem(IDC_OUT_PUT_PARA);		

	p_btn1->EnableWindow(FALSE);
	p_btn2->EnableWindow(FALSE);
	p_btn3->EnableWindow(FALSE);
	p_btn4->EnableWindow(FALSE);
	p_btn5->EnableWindow(FALSE);
	m_List.EnableWindow(FALSE);
	m_Edit_Src.EnableWindow(FALSE);
	m_Edit_Dest.EnableWindow(FALSE);
	p_btn6->EnableWindow(FALSE);

	CButton* p_grid = (CButton*)GetDlgItem(IDC_BTN_GRID);
	p_grid->EnableWindow(FALSE);

	CButton* p_param = (CButton*)GetDlgItem(IDC_BTN_INPUTPARAM);
	p_param->EnableWindow(FALSE);
}

void CDeuDlgCommCP::EnbleAllController()
{
	CButton* p_btn1 = (CButton*)GetDlgItem(IDC_BTN_IMPORT_CP);
	CButton* p_btn2 = (CButton*)GetDlgItem(IDC_BTN_EXPORT_CP);
	CButton* p_btn3 = (CButton*)GetDlgItem(IDC_BTN_CREATE_CP);
	CButton* p_btn4 = (CButton*)GetDlgItem(IDC_BTN_REMOVE);
	CButton* p_btn5 = (CButton*)GetDlgItem(IDC_BTN_INSTALL);
	CButton* p_btn6 = (CButton*)GetDlgItem(IDC_OUT_PUT_PARA);		
	p_btn1->EnableWindow(TRUE);
	p_btn2->EnableWindow(TRUE);
	p_btn3->EnableWindow(TRUE);
	p_btn4->EnableWindow(TRUE);
	p_btn5->EnableWindow(TRUE);
	m_List.EnableWindow(TRUE);
	//m_Edit_Src.EnableWindow(TRUE);
	//m_Edit_Dest.EnableWindow(TRUE);
	p_btn6->EnableWindow(TRUE);

	CButton* p_grid = (CButton*)GetDlgItem(IDC_BTN_GRID);
	p_grid->EnableWindow(TRUE);

	CButton* p_param = (CButton*)GetDlgItem(IDC_BTN_INPUTPARAM);
	p_param->EnableWindow(TRUE);
}

void CDeuDlgCommCP::OnLvnColumnclickListControlPt(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//char index[10];
	//sprintf(index, "%d", pNMLV->iSubItem);	
	//AfxMessageBox(index);

	*pResult = 0;
}

//��ת��ʱ����ĳЩ�ض��ĸ�ʽ��Ҫ�������� yzg
void CDeuDlgCommCP::OnBnClickedButtonInstall()
{
	//����EXCEL���õĶԻ���
	CDeuDlgExcel   DlgExcel;

    DlgExcel.src_x = ori_x;
	DlgExcel.src_y = ori_y;
	DlgExcel.src_z = ori_z;

	DlgExcel.des_x = des_x;
	DlgExcel.des_y = des_y;
	DlgExcel.des_z = des_z;

	DlgExcel.lbt = lbt;

	if (DlgExcel.DoModal() == IDOK)
	{
		//��Ҫ�жϷ��ص���Ϣ�Ƿ���Ч XY Դ��Ŀ���ж������� Z����û�� ��ͷ����λ�ñ�����ֵ
		if (DlgExcel.src_x.empty() 
		 || DlgExcel.src_y.empty()
		 || DlgExcel.des_x.empty()
		 || DlgExcel.des_y.empty()
		 || DlgExcel.lbt < 0)
		{
			AfxMessageBox("EXCEL������Ϣ������,����������!");
			m_install = FALSE;
		    return;
		}

		m_format.sType = ExcelFormatType::LETTER ;
		m_format.pColFormat = &m_ColumnFormat;
		m_format._ColumnHeader.ColumnHeaderRow = DlgExcel.lbt; //��ͷ������
		lbt = DlgExcel.lbt;

		if(m_format._ColumnHeader.ColumnHeaderRow > 0)
		{
			m_format._ColumnHeader.haveColumnHeader = true;
		}
		else
		{
			m_format._ColumnHeader.haveColumnHeader = false;
		}

		ori_x = DlgExcel.src_x;
		m_ColumnFormat.oriX =  (char*)ori_x.c_str() ;	 //ԴX������

		ori_y = DlgExcel.src_y;
		m_ColumnFormat.oriY =  (char*)ori_y.c_str() ;	 //ԴY������

		if (DlgExcel.src_z.empty())
		{
			ori_z = _T("");
			m_ColumnFormat.oriZ = NULL;
		}
		else
		{
			ori_z = DlgExcel.src_z;
			m_ColumnFormat.oriZ =  (char*)ori_z.c_str() ;//ԴZ������
		}

		des_x = DlgExcel.des_x;
		m_ColumnFormat.desX =  (char*)des_x.c_str() ;	 //ԴX������

		des_y = DlgExcel.des_y;
		m_ColumnFormat.desY =  (char*)des_y.c_str() ;	 //ԴY������

		if (DlgExcel.des_z.empty())
		{
			des_z = _T("");
			m_ColumnFormat.desZ = NULL;
		}
		else
		{
			des_z = DlgExcel.des_z;
			m_ColumnFormat.desZ =  (char*)des_z.c_str() ;//ԴZ������
		}

		m_t_format.byref = & m_format ;
		m_install = TRUE;
	}
	else
	{
		m_install = FALSE;
	}

	return;
}

void CDeuDlgCommCP::OnBnClickedOutPutPara()
{
	if(this->m_List.GetItemCount() <= 0)
	{
		AfxMessageBox("���ޱ�������.");
		return;
	}

	int  nParaCount = 7;
	if (m_imodel == MODEL_D2P4)
	{
		nParaCount=4;
	}

	CFileDialog _FILEDlg(FALSE,"txt","�߲���.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.txt",NULL,0,TRUE);
	CString     FilePathName;
	if (_FILEDlg.DoModal() == IDOK)
	{
		FilePathName = _FILEDlg.GetPathName();
		FILE *_PFile = fopen(FilePathName.GetBuffer(),"w");
		CString OutPara =_T("");
		if (nParaCount==7)
		{
			/*for (int i=0;i<3;i++)
			{
				OutPara.Format(_T("����%d(��λΪ��)��%f"),i+1,*(m_7param+i));
				fwrite(OutPara,OutPara.GetLength(),1,_PFile);
				fwrite(("\t\n"),2,1,_PFile);
			}
			for (int i=3;i<6;i++)
			{
				OutPara.Format(_T("����%d(��λΪ����)��%f"),i+1,*(m_7param+i));
				fwrite(OutPara,OutPara.GetLength(),1,_PFile);
				fwrite(("\t\n"),2,1,_PFile);
			}
			OutPara.Format(_T("����%d(��λΪ����ϵ��)��%f"),7,*(m_7param+6));
			fwrite(OutPara,OutPara.GetLength(),1,_PFile);
			fwrite(("\t\n"),2,1,_PFile);*/

			//add by chenyong 2014-3-11
			OutPara.Format(_T("Xƽ��:%f\nYƽ��:%f\nZƽ��:%f\nX��ת:%f\nY��ת:%f\nZ��ת:%f\n����ϵ��:%f"),
				*(m_7param), *(m_7param+1), *(m_7param+2), *(m_7param+3), *(m_7param+4), *(m_7param+5), *(m_7param+6));
			
			fwrite(OutPara, OutPara.GetLength(), 1, _PFile);
		}
		else if (nParaCount==4)
		{
			/*for (int i=0;i<2;i++)
			{
				OutPara.Format(_T("����%d(��λΪ��)��%f"),i+1,*(m_7param+i));
				fwrite(OutPara,OutPara.GetLength(),1,_PFile);
				fwrite(("\t\n"),2,1,_PFile);
			}
			for (int i=2;i<4;i++)
			{
				OutPara.Format(_T("����%d(��λΪ����)��%f"),i+1,*(m_7param+i));
				fwrite(OutPara,OutPara.GetLength(),1,_PFile);
				fwrite(("\t\n"),2,1,_PFile);
			}*/

			//add by chenyong 2015-3-17
			OutPara.Format(_T("Xƽ��:%f\nYƽ��:%f\nX��ת:%f\nY��ת:%f"),
				*(m_7param), *(m_7param+1), *(m_7param+2), *(m_7param+3));

			fwrite(OutPara, OutPara.GetLength(), 1, _PFile);
		}

		fclose(_PFile);
	}
}

void CDeuDlgCommCP::OnBnClickedBtnGrid()
{
	CFileDialog m_FileDlg(true,"GridParameter", "*.xml",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, "GridParameter(*.xml)|*.xml||",NULL);
	m_FileDlg.m_ofn.lpstrTitle = _T("ѡ����������ļ�");

	CString FilePathName;
	if (m_FileDlg.DoModal() == IDOK)
	{
		FilePathName = m_FileDlg.GetPathName();
	}

	m_GridParameter = FilePathName;
}

void CDeuDlgCommCP::SetSrcCoorType(const CString& strSrcCoorType)
{
	m_Edit_Src.SetWindowText(strSrcCoorType);
	UpdateData(FALSE);
}

void CDeuDlgCommCP::SetDesCoorType(const CString& strDesCoorType)
{
	m_Edit_Dest.SetWindowText(strDesCoorType);
	UpdateData(FALSE);
}

//֧�ּ���excel�б��еĿ��Ƶ����
HRESULT CDeuDlgCommCP::GetControlPointByExcel(CString strPath)
{
	_ApplicationPtr _App = NULL ;
	_WorkbookPtr    _book = NULL ;
	_WorksheetPtr   _sheet = NULL ;
	SheetsPtr       _sheets = NULL ;
	RangePtr        pThisRange = NULL ;
	_variant_t      vt;

	HRESULT hr = _App.CreateInstance("Excel.Application");
	if (FAILED(hr))
	{
		MessageBox("����Excel���ʵ��ʧ��!");
		return S_FALSE;
	}

	try
	{
		_book = _App->GetWorkbooks()->Open((LPCSTR)_bstr_t(strPath)) ;	
	}
	catch(...)
	{
		_App->Quit();
	}

	_sheets = _book->GetWorksheets() ;
	_sheet  = _sheets->GetItem((short)1);

	Excel::RangePtr _range;
	Excel::RangePtr _range_out;

	int _start_row = 1;  //��ʼ��

	char _ori_x_pos_lt[8];
	char _ori_y_pos_lt[8];
	char _ori_z_pos_lt[8];

	char _des_x_pos_lt[8];
	char _des_y_pos_lt[8];
	char _des_z_pos_lt[8];

	strcpy( _ori_x_pos_lt, "0");
	strcpy( _ori_y_pos_lt, "0");
	strcpy( _ori_z_pos_lt, "0");

	strcpy( _des_x_pos_lt, "0");
	strcpy( _des_y_pos_lt, "0");
	strcpy( _des_z_pos_lt, "0");

	char *_ori_x_Letter;
	char *_ori_y_Letter;
	char *_ori_z_Letter;

	char *_des_x_Letter;
	char *_des_y_Letter;
	char *_des_z_Letter;

	strcpy( _ori_x_pos_lt, _T("A"));
	strcpy( _ori_y_pos_lt, _T("B"));
	strcpy( _ori_z_pos_lt, _T("C"));

	strcpy( _des_x_pos_lt, _T("D"));
	strcpy( _des_y_pos_lt, _T("E"));
	strcpy( _des_z_pos_lt, _T("F"));

	long index = 0;
	long numSheet = _sheets->GetCount();

	for ( long iSheet = 1 ; iSheet <= numSheet ; iSheet++)
	{
		_sheet = _sheets->GetItem((short)iSheet);
		_range = _sheet->UsedRange;
		long numrow = _range->Rows->Count;
		char * szLog = new char[200];

		for (long irow = _start_row ; irow <= numrow ; irow++)
		{
			double ox;
			double oy;
			double oz;
			double dx;
			double dy;
			double dz;

			_variant_t tx;
			_variant_t des_tx;
			Excel::RangePtr _rx;

			try
			{
				_ori_x_Letter =  GetLetter( irow , _ori_x_pos_lt );
				if(_ori_x_Letter)
				{
					ox = GetDoubleCellVal(_sheet, _ori_x_Letter);
				}

				_ori_y_Letter =  GetLetter( irow , _ori_y_pos_lt );
				if(_ori_y_Letter)
				{
					oy = GetDoubleCellVal(_sheet, _ori_y_Letter);
				}

				_ori_z_Letter =  GetLetter( irow , _ori_z_pos_lt );
				if(_ori_z_Letter)
				{
					oz = GetDoubleCellVal(_sheet, _ori_z_Letter);
				}

				_des_x_Letter =  GetLetter( irow , _des_x_pos_lt );
				if(_des_x_Letter)
				{
					dx = GetDoubleCellVal(_sheet, _des_x_Letter);
				}

				_des_y_Letter =  GetLetter( irow , _des_y_pos_lt );
				if(_des_y_Letter)
				{
					dy = GetDoubleCellVal(_sheet, _des_y_Letter);
				}

				_des_z_Letter =  GetLetter( irow , _des_z_pos_lt );
				if(_des_z_Letter)
				{
					dz = GetDoubleCellVal(_sheet, _des_z_Letter);
				}

				if (ox == 0.00 || oy == 0.00 || dx == 0.00 || dy == 0.00)
				{
					continue;
				}

				//д��������
				p_ControlPointPair pControlPointPair = new ControlPointPair;

				pControlPointPair->X_SRC.Format(_T("%.15f"), ox);
				pControlPointPair->Y_SRC.Format(_T("%.15f"), oy);
				pControlPointPair->Z_SRC.Format(_T("%.15f"), oz);

				pControlPointPair->X_DEST.Format(_T("%.15f"), dx);
				pControlPointPair->Y_DEST.Format(_T("%.15f"), dy);
				pControlPointPair->Z_DEST.Format(_T("%.15f"), dz);

				_controlPointPairs._controlPointPair.Add(pControlPointPair);

			}
			catch(...)
			{
				char * szLine = new char[200];
				sprintf(szLine , "�������� SHEET = %d , ROW = %d " ,  iSheet , irow  );
			}
		}
	}

	delete _ori_x_Letter;
	delete _ori_y_Letter;
	delete _ori_z_Letter;

	delete _des_x_Letter;
	delete _des_y_Letter;
	delete _des_z_Letter;

	_book->Close();
	_App->Quit();

	return S_OK;
}

//�к��л��Letter
char * CDeuDlgCommCP::GetLetter( int iRow , char * szCol)
{
	if( strcmp( szCol , "0" ) == 0 )
	{
		return NULL;
	}

	char * Letter = new char[100];
	char * sz_r = new char[200];

	sz_r = itoa( iRow , sz_r ,10 );
	strcpy( Letter , szCol );
	strcat( Letter , sz_r );

	delete sz_r;

	return Letter;
}

double CDeuDlgCommCP::GetDoubleCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol)
{
	double dx = 0;
	_variant_t _tx;
	_variant_t _des_tx;

	Excel::RangePtr _rx;
	if(szRowCol == NULL)
	{
		return -1;
	}

	_rx = _sheet->GetRange(szRowCol);
	//_rx = _range->GetItem( _variant_t(irow) ,_variant_t(icol) );
	_tx = _rx->GetValue();

	if(_tx.vt != VT_R8)
	{
		_des_tx.ChangeType(VT_R8,&_tx);
	}
	else
	{
		_des_tx=_tx;
	}

	dx=(double)_des_tx;

	return dx;
}

void CDeuDlgCommCP::OnLoadControlData(const CString& strControlPath, const CString& strTransModel)
{
	CString                   strPath;
	CString                   strText;

	if (!strControlPath.IsEmpty())
	{	
		m_strControlPath = strControlPath;
		m_strModel = strTransModel;

		ClearDataPackage();

		//��Ҫ���ļ����ֽ��н����ж���ѡ���cp�ļ�����xlsx�ļ�
		strPath = strControlPath;
		int i = strPath.ReverseFind('.');
		strText = strPath.Right(strPath.GetLength()-1-i);
		if (strText == _T("xlsx"))
		{
			GetControlPointByExcel(strPath);

			CalcResidual();

			this->UpdateData(FALSE);
		}
		else if (strText == _T("cp"))
		{
			if (!m_XmlCP.LoadFile(strControlPath))
			{
				AfxMessageBox("���ؿ��Ƶ��ļ�ʧ��!");
				return;
			}
			m_XmlCP.GetControlPoint(&_controlPointPairs);

			CalcResidual();

			this->UpdateData(FALSE);
		}		
		else
		{
			AfxMessageBox("��֧�ֵĿ��Ƶ��ļ���ʽ����!");
			return;
		}
	}
}

void CDeuDlgCommCP::OnBnClickedBtnInputparam()
{
	bool			IsVector = true;
	bool			IsBrase = true;

	if (_Type == VECTOR)
	{
		IsVector = true;
	}
	else if (_Type == RASTER)
	{
		IsVector = false;
	}

	if (m_strModel == _T("ƽ���Ĳ���ת��ģ��"))
	{
		IsBrase = false;
	}
	else if (m_strModel == _T("����ɯת��ģ��") || m_strModel == _T("��ά�߲���ת��ģ��")
		|| m_strModel == _T("��ά�߲���ת��ģ��"))
	{
		IsBrase = true;
	}
	else
	{
		AfxMessageBox(_T("û����ת��ģ�Ͷ�Ӧ�Ĳ���"));
		return;
	}

	CString			strRate = GetStylesPath() + _T("\\Rate.ini");
	CString			strModel = _T("");
	CString			strTransType = _T("");

	::GetPrivateProfileString(_T("PARAMS"), _T("TYPE"), _T(""), strTransType.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
	::GetPrivateProfileString(_T("PARAMS"), _T("MODEL"), _T(""), strModel.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);

	CString			_strType;
	_strType.Format(_T("%d"), (long)_Type);
	_Params			params;
	_Params			InvParams;

	//�����ǰת�����ͼ�ģ�����ļ��м�¼��һ�£��򲻴���
	if (_strType.Trim() == strTransType.Trim() && m_strModel.Trim() == strModel.Trim())
	{
		::GetPrivateProfileString(_T("PARAMS"), _T("XSRC"), _T(""), params.strXSrc.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("YSRC"), _T(""), params.strYSrc.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("ZSRC"), _T(""), params.strZSrc.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("X0SRC"), _T(""), params.strX0Src.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("Y0SRC"), _T(""), params.strY0Src.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("Z0SRC"), _T(""), params.strZ0Src.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("KSRC"), _T(""), params.strKSrc.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);

		::GetPrivateProfileString(_T("PARAMS"), _T("XDES"), _T(""), InvParams.strXSrc.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("YDES"), _T(""), InvParams.strYSrc.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("ZDES"), _T(""), InvParams.strZSrc.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("X0DES"), _T(""), InvParams.strX0Src.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("Y0DES"), _T(""), InvParams.strY0Src.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("Z0DES"), _T(""), InvParams.strZ0Src.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("PARAMS"), _T("KDES"), _T(""), InvParams.strKSrc.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);

		//TransParams.InitParams(params, InvParams);
	}

	CSetTransParams  TransParams(IsVector, IsBrase, params, InvParams);
	if (TransParams.DoModal() == IDOK)
	{
		TransParams.GetTransParams(m_7param);
		TransParams.GetTransInvParams(m_Invpara);
		IsInputParams = TRUE;

		//д��¼
		::WritePrivateProfileString(_T("PARAMS"), _T("TYPE"), _strType, strRate);
		::WritePrivateProfileString(_T("PARAMS"), _T("MODEL"), m_strModel, strRate);

		CString			strFormat = _T("");
		double			temp = 0;
		if (IsBrase)
		{
			temp = m_7param[0];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("XSRC"), strFormat, strRate);

			temp = m_7param[1];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("YSRC"), strFormat, strRate);

			temp = m_7param[2];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("ZSRC"), strFormat, strRate);

			temp = m_7param[3];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("X0SRC"), strFormat, strRate);

			temp = m_7param[4];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("Y0SRC"), strFormat, strRate);

			temp = m_7param[5];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("Z0SRC"), strFormat, strRate);

			temp = m_7param[6];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("KSRC"), strFormat, strRate);

			//��
			temp = m_Invpara[0];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("XDES"), strFormat, strRate);

			temp = m_Invpara[1];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("YDES"), strFormat, strRate);

			temp = m_Invpara[2];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("ZDES"), strFormat, strRate);

			temp = m_Invpara[3];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("X0DES"), strFormat, strRate);

			temp = m_Invpara[4];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("Y0DES"), strFormat, strRate);

			temp = m_Invpara[5];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("Z0DES"), strFormat, strRate);

			temp = m_Invpara[6];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("KDES"), strFormat, strRate);
		}
		else
		{
			temp = m_7param[0];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("XSRC"), strFormat, strRate);

			temp = m_7param[1];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("YSRC"), strFormat, strRate);

			temp = m_7param[2];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("X0SRC"), strFormat, strRate);

			temp = m_7param[3];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("Y0SRC"), strFormat, strRate);


			temp = m_Invpara[0];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("XDES"), strFormat, strRate);

			temp = m_Invpara[1];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("YDES"), strFormat, strRate);

			temp = m_Invpara[2];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("X0DES"), strFormat, strRate);

			temp = m_Invpara[3];
			if (abs(temp) > 0.000001)
			{
				strFormat.Format(_T("%.06f"), temp);
			}
			else
			{
				strFormat = _T("");
			}

			::WritePrivateProfileString(_T("PARAMS"), _T("Y0DES"), strFormat, strRate);
		}
	}
}
