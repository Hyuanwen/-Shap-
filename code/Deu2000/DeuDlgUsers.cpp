// DeuUsersDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "DeuDlgUsers.h"
#include "DeuSQLProvider.h"
#include "DeuDlgUsersOpera.h"

// CDeuDlgUsers �Ի���
IMPLEMENT_DYNAMIC(CDeuDlgUsers, CXTResizeDialog)
CDeuDlgUsers::CDeuDlgUsers(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CDeuDlgUsers::IDD, pParent)
{
}

CDeuDlgUsers::~CDeuDlgUsers()
{
}

void CDeuDlgUsers::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UROLE_SRC, m_ListUser);
}

BEGIN_MESSAGE_MAP(CDeuDlgUsers, CXTResizeDialog)
	ON_BN_CLICKED(IDC_BTN_USER_CLOSE, &CDeuDlgUsers::OnBnClickedBtnUserclose)
	ON_BN_CLICKED(IDC_BTN_USERS_CREATE, &CDeuDlgUsers::OnBnClickedBtnUsersCreate)
	ON_BN_CLICKED(IDC_BTN_USERS_DEL, &CDeuDlgUsers::OnBnClickedBtnUsersDel)
	ON_BN_CLICKED(IDC_BTN_USERS_UPDATE, &CDeuDlgUsers::OnBnClickedBtnUsersUpdate)
END_MESSAGE_MAP()

// CDeuDlgUsers ��Ϣ�������
BOOL CDeuDlgUsers::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	this->m_ListUser.InsertColumn(0, "�û���");
	this->m_ListUser.SetColumnWidth(0, 80);

	this->m_ListUser.InsertColumn(1, "�����û���");
	this->m_ListUser.SetColumnWidth(1, 80);

	this->m_ListUser.InsertColumn(2, "դ�����");
	this->m_ListUser.SetColumnWidth(2, 80);

	this->m_ListUser.InsertColumn(3, "ʸ�����");
	this->m_ListUser.SetColumnWidth(3, 80);

	this->m_ListUser.InsertColumn(4, "���ݿ����");
	this->m_ListUser.SetColumnWidth(4, 80);

	this->m_ListUser.InsertColumn(5, "դ��ת��");
	this->m_ListUser.SetColumnWidth(5, 80);

	this->m_ListUser.InsertColumn(6, "ʸ��ת��");
	this->m_ListUser.SetColumnWidth(6, 80);

	this->m_ListUser.InsertColumn(7, "���ݿ�ת��");
	this->m_ListUser.SetColumnWidth(7, 80);

	this->SetResize(IDC_LIST_UROLE_SRC, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);

	//����CListCtrl��ʽ
	DWORD dwStyle = this->m_ListUser.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	this->m_ListUser.SetExtendedStyle(dwStyle);
	
	LoadAllUser();

	return TRUE;
}

/*
=======================================================
����:			���������û���Ϣ
�����߼�:		��ȡ�������û���Ϣ��Ȼ���
				ÿ����Ϣ�û���Ȩ�޽��н�����ϣ�
				�����ʾ��Ȩ��������

����:			2010-11-2
=======================================================
*/
void CDeuDlgUsers::LoadAllUser()
{	

	m_ListUser.DeleteAllItems();

	/* ��ʼ����ɫ���� */
	CDeuSQLite3Query m_query;
	CDeuSQLProvider m_SqlProvider;
	m_query = m_SqlProvider.GetUsersQueryObject();

	int n=0;	
	CStringArray m_array;
	while(!m_query.eof())
	{
		m_array.RemoveAll();
		this->PowerMerge(m_query.fieldValue("usersgroup_id"), &m_array);

		m_ListUser.InsertItem(n, "");
		if(m_array.GetCount() > 0)
		{
			m_ListUser.SetItemText(n, 1, m_array.GetAt(0));	//�û�����

			m_ListUser.SetItemText(n, 2, m_array.GetAt(2)); //դ�����
			m_ListUser.SetItemText(n, 3, m_array.GetAt(1)); //ʸ�����
			m_ListUser.SetItemText(n, 4, m_array.GetAt(3)); //���ݿ����
			m_ListUser.SetItemText(n, 5, m_array.GetAt(5)); //դ��ת��
			m_ListUser.SetItemText(n, 6, m_array.GetAt(4)); //ʸ��ת��
			m_ListUser.SetItemText(n, 7, m_array.GetAt(6)); //���ݿ�ת��
		}

		m_ListUser.SetItemText(n, 0, m_query.fieldValue("users_name"));

		m_query.nextRow();
		n++;
	}
}

/* 
	1. Ȩ�޺ϲ�����  
	2. ��ȡ��Ȩ�Ľ�������
*/
void CDeuDlgUsers::PowerMerge(CString strGroupId, CStringArray *p_array)
{
	CDeuSQLite3Query m_query;
	CDeuSQLProvider m_SqlProvider;
	
	if(strGroupId.Find(",", 0) == -1)
	{
		m_query = m_SqlProvider.GetUserGroup("'"+strGroupId+"'");
	}
	else
	{
		CString m_strTmp, _m_strTmp;
		int _index = 0;
		int  _start = 0;
		while(_index != -1)
		{
			_index = strGroupId.Find(",",_index);
			
			if(_index != -1)
			{
				_m_strTmp = strGroupId.Mid(_start, _index-_start);
				_start = _index+1;
				_index++;
			}
			else
			{
				_m_strTmp = strGroupId.Mid(_start);
			}

			m_strTmp  += "'"+_m_strTmp+"',";
 		}
		m_strTmp.TrimRight(",");		

		m_query = m_SqlProvider.GetUserGroup(m_strTmp);
	}
		
	while(!m_query.eof())
	{
		if(p_array->GetCount() == 0)
		{
			p_array->Add(m_query.fieldValue("usergroup_name"));
			p_array->Add(m_query.fieldValue("usergroup_sl_explorer"));
			p_array->Add(m_query.fieldValue("usergroup_sg_explorer"));
			p_array->Add(m_query.fieldValue("usergroup_db_explorer"));
			p_array->Add(m_query.fieldValue("usergroup_sl_conversion"));
			p_array->Add(m_query.fieldValue("usergroup_sg_conversion"));
			p_array->Add(m_query.fieldValue("usergroup_db_conversion"));
			//TRACE("%s\n%s\n%s\n%s\n%s\n%s\n", p_array->GetAt(1),p_array->GetAt(2),p_array->GetAt(3), p_array->GetAt(4), p_array->GetAt(5), p_array->GetAt(6));
		}
		else
		{
			CString m_strT;

			//�ϲ��û�����
			m_strT.Format("%s", m_query.getStringField("usergroup_name"));
			p_array->SetAt(0, p_array->GetAt(0)+","+m_strT);

			//�ϲ�ʸ�����Ȩ��
			m_strT.Format("%s", m_query.getStringField("usergroup_sl_explorer"));
			if((p_array->GetAt(1) == "��") && m_strT == "��")
			{
				p_array->SetAt(1, "��");
			}
			//TRACE("%s  %s\n", p_array->GetAt(1), m_query.fieldValue("usergroup_sl_explorer"));

			//�ϲ�դ�����Ȩ��
			m_strT.Format("%s", m_query.getStringField("usergroup_sg_explorer"));
			if((p_array->GetAt(2) == "��") && m_strT == "��")
			{
				p_array->SetAt(2, "��");
			}
			//TRACE("%s  %s\n", p_array->GetAt(2), m_query.fieldValue("usergroup_sg_explorer"));

			//�ϲ����ݿ����Ȩ��
			m_strT.Format("%s", m_query.getStringField("usergroup_db_explorer"));
			if((p_array->GetAt(3) == "��") && m_strT == "��")
			{
				p_array->SetAt(3, "��");
			}
			//TRACE("%s  %s\n", p_array->GetAt(3), m_query.fieldValue("usergroup_db_explorer"));

			//�ϲ�ʸ��ת��Ȩ��
			m_strT.Format("%s", m_query.getStringField("usergroup_sl_conversion"));
			if((p_array->GetAt(4) == "��") && m_strT == "��")
			{
				p_array->SetAt(4, "��");
			}
			//TRACE("%s  %s\n", p_array->GetAt(4), m_query.fieldValue("usergroup_sl_conversion"));

			//�ϲ�դ��ת��Ȩ��
			m_strT.Format("%s", m_query.getStringField("usergroup_sg_conversion"));
			if((p_array->GetAt(5) == "��") && m_strT == "��")
			{
				p_array->SetAt(5, "��");
			}
			//TRACE("%s  %s\n", p_array->GetAt(5), m_query.fieldValue("usergroup_sg_conversion"));

			//�ϲ����ݿ�ת��Ȩ��
			m_strT.Format("%s", m_query.getStringField("usergroup_db_conversion"));
			if((p_array->GetAt(6) == "��") && (m_strT == "��"))
			{
				p_array->SetAt(6, "��");
			}			
			//TRACE("%s  %s\n", p_array->GetAt(6), m_query.fieldValue("usergroup_db_conversion"));
		}	

		m_query.nextRow();
	}
}

void CDeuDlgUsers::OnBnClickedBtnUserclose()
{
	this->OnOK();
}

/*
	�����û�
*/
void CDeuDlgUsers::OnBnClickedBtnUsersCreate()
{
	CDeuDlgUsersOpera m_DlgUsersOpera(NULL, 1);
	if(m_DlgUsersOpera.DoModal() == IDOK)
	{
		LoadAllUser();
	}
}

/*
	ɾ���û�
*/
void CDeuDlgUsers::OnBnClickedBtnUsersDel()
{
	if(this->m_ListUser.GetSelectedCount() == 0)	
	{
		this->MessageBox("��ѡ��Ҫɾ�����û�", "ϵͳ��ʾ", MB_OK|MB_ICONINFORMATION);
	}
	else
	{
		if(IDYES == MessageBox("ȷ��ɾ�����˻���", "ϵͳ��ʾ", MB_YESNO|MB_ICONQUESTION))
		{
			int n = m_ListUser.GetSelectionMark();
			CDeuSQLProvider m_SqlProvider;
			m_SqlProvider.DeleteUser(m_ListUser.GetItemText(n, 0));
			this->LoadAllUser();
		}
	}
}

/*
	�޸��û�
*/
void CDeuDlgUsers::OnBnClickedBtnUsersUpdate()
{
	if(this->m_ListUser.GetSelectedCount() == 0)	
	{
		this->MessageBox("��ѡ���޸ĵ��û�", "ϵͳ��ʾ", MB_OK|MB_ICONINFORMATION);
	}
	else
	{
		int n = m_ListUser.GetSelectionMark();
		CString m_strName;
		m_strName = m_ListUser.GetItemText(n, 0);

		CDeuDlgUsersOpera m_DlgUserOpera(NULL, 2);
		m_DlgUserOpera.m_strCurName = m_strName;
		if(m_DlgUserOpera.DoModal() == IDOK)
		{
			LoadAllUser();
		}
	}
}
