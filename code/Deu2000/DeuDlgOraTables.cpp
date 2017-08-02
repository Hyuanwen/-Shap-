// DeuDlgOraTables.cpp : 实现文件

#include "stdafx.h"
#include "DeuDlgOraTables.h"

// CDeuDlgOraTables 对话框
IMPLEMENT_DYNAMIC(CDeuDlgOraTables, CDialog)
CDeuDlgOraTables::CDeuDlgOraTables(TranformType _ParentType, CWnd* pParent /*=NULL*/)
	: CDialog(CDeuDlgOraTables::IDD, pParent)
{
	_TType = _ParentType;
	switch (_ParentType)
	{
	case VECTOR:
		p_Parent_Vector = (CDeuVectorTranDlg*)pParent;
		break;
	case RASTER:
		p_Parent_Raster = (CDeuRasterTranDlg*)pParent;
		break;
	}

	IsHideChkbox = FALSE;
}

CDeuDlgOraTables::~CDeuDlgOraTables()
{
}

void CDeuDlgOraTables::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_CHECK1, m_chk_select);
	DDX_Control(pDX, IDC_CHECK2, m_chk_addtional);
}

BEGIN_MESSAGE_MAP(CDeuDlgOraTables, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CDeuDlgOraTables::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_CHECK1, &CDeuDlgOraTables::OnBnClickedCheck1)
END_MESSAGE_MAP()

// CDeuDlgOraTables 消息处理程序
BOOL CDeuDlgOraTables::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch (_TType)
	{
	case VECTOR:
		{
			if(p_Parent_Vector->IsAdditional == TRUE)
			{
				this->m_chk_addtional.SetCheck(1);
			}
			
			if(StatusAction == "In")
			{
				m_chk_addtional.ShowWindow(SW_SHOW);
			}
			else
			{
				m_chk_addtional.ShowWindow(SW_HIDE);
			}
		}
		break;
	case RASTER:
		m_chk_addtional.ShowWindow(SW_HIDE);
		break;
	}

	m_list.InsertColumn(0, "");
	
	DWORD dwStyle = m_list.GetExtendedStyle();
	if(!IsHideChkbox)
	{
		dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES;
		m_list.SetColumnWidth(0, 20);
	}
	else
	{
		m_chk_select.ShowWindow(SW_HIDE);
		dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		m_list.SetColumnWidth(0, 0);
	}

	m_list.SetExtendedStyle(dwStyle);
	m_list.InsertColumn(1, "表名");
	m_list.SetColumnWidth(1, 300);
	
	_ConnectionPtr conn;
	conn.CreateInstance(__uuidof(Connection));

	//区分状态
	if(lstrcmp(StatusAction, "Out") == 0)
	{
		try
		{	
			HRESULT hr = conn->Open((_bstr_t)("Provider=oraoledb.oracle.1; Data Source="+m_oracle.strSID+";User Id="+m_oracle.strUser+"; Password="+m_oracle.strPwd+"; persist security info=false"), (_bstr_t)m_oracle.strUser, (_bstr_t)m_oracle.strPwd, adConnectUnspecified);
			if(FAILED(hr))
			{			
				MessageBox("连接失败!", "系统提示", MB_OK|MB_ICONEXCLAMATION);
				return FALSE;
			}
			
			strConn = "Provider=oraoledb.oracle.1; Data Source="+m_oracle.strSID+"; User Id="+m_oracle.strUser+"; Password="+m_oracle.strPwd+"; persist security info=false";
			//strConn = "Provider=MSDAORA; Data Source="+m_oracle.strSID+";User Id="+m_oracle.strUser+"; Password="+m_oracle.strPwd;

			_RecordsetPtr rst = conn->Execute("select * from tabs", NULL, adCmdText);

			rst->MoveFirst();
			int m = 0;
			CString strItem;
			while(!rst->_EOF)
			{
				m_list.InsertItem(m, NULL);
				strItem = rst->GetCollect("TABLE_NAME");
				m_list.SetItemText(m, 1, strItem);
				rst->MoveNext();
				m++;
			}

			rst->Close();
			conn->Close();
		}
		catch(_com_error e) 
		{ 				
			MessageBox("连接失败:\r\n    "+e.Description(), "系统提示", MB_OK|MB_ICONEXCLAMATION);
			//MessageBox(e.ErrorMessage(), "系统提示", MB_OK|MB_ICONEXCLAMATION);
			return FALSE;
		}
	}
	else if(lstrcmp(StatusAction, "In") == 0)
	{
		switch (_TType)
		{
		case VECTOR:
			{
				if((p_Parent_Vector->_TablesList.GetCount() > 0) && (p_Parent_Vector->_TablesList_selected.GetCount() > 0))
				{
					for(int n=0; n<p_Parent_Vector->_TablesList.GetCount(); n++)
					{
						m_list.InsertItem(n, NULL);
						m_list.SetItemText(n, 1, p_Parent_Vector->_TablesList.GetAt(n));
						for(int m=0; m<p_Parent_Vector->_TablesList_selected.GetCount(); m++)
						{
							if(p_Parent_Vector->_TablesList_selected.GetAt(m) == p_Parent_Vector->_TablesList.GetAt(n))
							{
								m_list.SetCheck(n);
							}
						}
					}
				}
				else if((p_Parent_Vector->_TablesList.GetCount() > 0) && (p_Parent_Vector->_TablesList_selected.GetCount() == 0))
				{
					for(int n=0; n<p_Parent_Vector->_TablesList.GetCount(); n++)
					{
						m_list.InsertItem(n, NULL);
						m_list.SetItemText(n, 1, p_Parent_Vector->_TablesList.GetAt(n));
					}
				}
				else if((p_Parent_Vector->_TablesList.GetCount() == 0) && (p_Parent_Vector->_TablesList_selected.GetCount() > 0))
				{
					for(int m=0; m<p_Parent_Vector->_TablesList_selected.GetCount(); m++)
					{
						m_list.InsertItem(m, NULL);
						m_list.SetItemText(m, 1, p_Parent_Vector->_TablesList_selected.GetAt(m));
						m_list.SetCheck(m);
					}
				}
			}
			break;
		case RASTER:
			{		
				/*if((p_Parent_Raster->_TablesList.GetCount() > 0) 
					&& (p_Parent_Raster->_TablesList_selected.GetCount() > 0))
				{
					for(int n=0; n<p_Parent_Raster->_TablesList.GetCount(); n++)
					{
						m_list.InsertItem(n, NULL);
						m_list.SetItemText(n, 1, p_Parent_Raster->_TablesList.GetAt(n));
						for(int m=0; m<p_Parent_Raster->_TablesList_selected.GetCount(); m++)
						{
							if(p_Parent_Raster->_TablesList_selected.GetAt(m) == p_Parent_Raster->_TablesList.GetAt(n))
								m_list.SetCheck(n);
						}
					}
				}
				else if((p_Parent_Raster->_TablesList.GetCount() > 0) 
					&& (p_Parent_Raster->_TablesList_selected.GetCount() == 0))
				{
					for(int n=0; n<p_Parent_Raster->_TablesList.GetCount(); n++)
					{
						m_list.InsertItem(n, NULL);
						m_list.SetItemText(n, 1, p_Parent_Raster->_TablesList.GetAt(n));
					}
				}
				else if((p_Parent_Raster->_TablesList.GetCount() == 0) 
					&& (p_Parent_Raster->_TablesList_selected.GetCount() > 0))
				{
					for(int m=0; m<p_Parent_Raster->_TablesList_selected.GetCount(); m++)
					{
						m_list.InsertItem(m, NULL);
						m_list.SetItemText(m, 1, p_Parent_Raster->_TablesList_selected.GetAt(m));
						m_list.SetCheck(m);
					}
				}*/
			}
			break;
		}
	}

	return TRUE;
}

void CDeuDlgOraTables::OnBnClickedBtnOk()
{
	if(lstrcmp(StatusAction, "In") == 0)
	{
		if(m_chk_addtional.GetCheck())
		{
			p_Parent_Vector->IsAdditional = TRUE;
		}
		else
		{
			p_Parent_Vector->IsAdditional = FALSE;
		}

		SaveSelectFiles();
	}
	this->OnOK();
}

void CDeuDlgOraTables::OnBnClickedCheck1()
{
	int n = m_list.GetItemCount();
	if(m_chk_select.GetCheck())
	{
		while(n >= 0)
		{
			m_list.SetCheck(n, 1);
			n--;
		}
	}
	else
	{
		while(n >= 0)
		{
			m_list.SetCheck(n, 0);
			n--;
		}
	}
}

//保存已经选中的文件
void CDeuDlgOraTables::SaveSelectFiles()
{
	if(!IsHideChkbox)
	{
		switch (_TType)
		{
		case VECTOR:
			{
				p_Parent_Vector->_TablesList_selected.RemoveAll();
			}
			break;
		case RASTER:
			{
				p_Parent_Raster->_TablesList_selected.RemoveAll();
			}
			break;
		}

		CString m_str;
		for(int n =0; n<m_list.GetItemCount(); n++)
		{
			if(m_list.GetCheck(n))
			{
				m_str = m_list.GetItemText(n, 1);
				switch (_TType)
				{
				case VECTOR:
					{
						p_Parent_Vector->_TablesList_selected.Add(m_str);
					}
					break;
				case RASTER:
					{					
						p_Parent_Raster->_TablesList_selected.Add(m_str);
					}
					break;
				}
			}
		}
	}
}
