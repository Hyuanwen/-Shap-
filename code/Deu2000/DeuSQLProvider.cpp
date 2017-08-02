#include "StdAfx.h"
#include "DeuSQLProvider.h"
#include "DeuGlobal.h"
using namespace std;



/*
======================================================   
����:	�ڹ��캯���м�����ݿ�,������������ʼ������
����:   2010-10-27
======================================================
*/
CDeuSQLProvider::CDeuSQLProvider()
{
	//��ʼ��ʱ������ͻ��������Ƿ���ڣ����������ʼ���������ݽ�ȥ
	m_db.open(szDbName, szDbPwd);

	CString m_strSql;
	char szGuid[38];
	char m_szTime[20];

	//1. ��顰deu_usergroup�� ��
	if(!m_db.tableExists("deu_usergroup"))
	{
		m_db.execDML("CREATE TABLE [deu_usergroup] ([usergroup_id] VARCHAR2(50), [usergroup_name] text, usergroup_sl_explorer VARCHAR2(50), usergroup_sg_explorer VARCHAR2(50), usergroup_db_explorer VARCHAR2(50), usergroup_sl_conversion VARCHAR2(20), usergroup_sg_conversion VARCHAR2(20), usergroup_db_conversion VARCHAR2(20), usergroup_createtime VARCHAR2(50))");
	}	

	CDeuSQLite3Query m_query;
	m_query = m_db.execQuery("select * from deu_usergroup where usergroup_name = '��������Ա'");
	if(m_query.eof())
	{
		lstrcpy(szGuid, newGUID());
		
		this->GetTime(m_szTime);
		
		m_strSql.Format("insert into deu_usergroup(usergroup_id, usergroup_name, usergroup_sl_explorer, usergroup_sg_explorer, usergroup_db_explorer, usergroup_sl_conversion,usergroup_sg_conversion,usergroup_db_conversion,usergroup_createtime) values('%s','��������Ա', '��', '��', '��', '��', '��', '��','%s')", szGuid, m_szTime);
		m_db.execDML(m_strSql);

	}
	else
	{
		lstrcpy(szGuid, m_query.fieldValue("usergroup_id"));
		
	}


	//2. ��顰deu_users�� ��
	if(!m_db.tableExists("deu_users"))
	{
		m_db.execDML("CREATE TABLE [deu_users] ([users_id] VARCHAR2(50), [usersgroup_id] text, users_name VARCHAR2(50), users_passwd VARCHAR2(50), users_encryptpwd VARCHAR2(50), users_createtime VARCHAR2(50))");
	}
	else
	{
		//3. ����������
		CDeuSQLite3Query m_query;
		
		m_query = m_db.execQuery("select * from deu_users");
		if(m_query.eof())
		{
			/* md5���ܴ� */			
			char szmd5[33];
			m_md5.TargetStr("123456");
			lstrcpy(szmd5, m_md5.GetDigestKey());

			/* Guid */
			char szUserGuid[38];
			lstrcpy(szUserGuid, newGUID());	
			
			this->GetTime(m_szTime);
			m_strSql.Format("insert into deu_users(users_id, usersgroup_id, users_name, users_passwd, users_encryptpwd, users_createtime) values('%s', '%s', 'sa', '123456', '%s', '%s')", szUserGuid, szGuid, szmd5, m_szTime);
			m_db.execDML(m_strSql);
		}
	}


}

CDeuSQLProvider::~CDeuSQLProvider(void)
{
	m_db.close();
}




/*
=============================================   
����:	��ȡ�����û�����
����:	2010-11-1	add by hushichen
=============================================
*/
CDeuSQLite3Query CDeuSQLProvider::GetUsersQueryObject()
{
	return m_db.execQuery("select * from deu_users order by users_createtime desc");
}




/*
=============================================   
����:	��ȡָ���û�����Ϣ
����:	2010-10-27	add by hushichen
=============================================
*/
void CDeuSQLProvider::GetUserGroupIdByName(CString strName, CString *p_strId)
{
	CDeuSQLite3Query m_query;
	m_query = m_db.execQuery("select * from deu_usergroup where usergroup_name = '"+strName+"'");

	if(!m_query.eof())
	{
		p_strId->Format(m_query.fieldValue("usergroup_id"));
	}
}




/*
=============================================   
����:	��ȡָ���û�����Ϣ
����:	2010-10-27	add by hushichen
=============================================
*/
void CDeuSQLProvider::FromUserGetGroupId(char* m_cName, CString* p_strId)
{
	char m_szSQl[100] = "select * from deu_users where users_name = '";
	strcat(m_szSQl, m_cName);
	strcat(m_szSQl, "'");

	CDeuSQLite3Query m_query;
	m_query = m_db.execQuery(m_szSQl);

	if(!m_query.eof())
	{
		if(m_query.fieldValue("usersgroup_id") != NULL)
			p_strId->Format(m_query.fieldValue("usersgroup_id"));
		else
			p_strId->Format("");
	}
}








/*
=============================================   
����:	��ȡָ���û�����Ϣ
����:	strName	�û���
		strPwd	�û�����

����:	CStringArray �û���Ϣ����
����:	2010-10-27	add by hushichen
��ע��	�ú���Ϊ��½ʹ��
=============================================
*/
void CDeuSQLProvider::GetUser(CString strName, CString strPwd, CStringArray* p_Array)
{
	m_md5.TargetStr(strPwd);
	
	CString m_strSQL;
	m_strSQL.Format("select * from deu_users where users_name='%s' and users_encryptpwd='%s'", strName, m_md5.GetDigestKey());	

	CDeuSQLite3Query m_query;
	m_query = m_db.execQuery(m_strSQL);

	CStringArray m_Array;
	if(!m_query.eof()){		

		CString m_username, m_userid, m_usergroup;

		m_username	= m_query.getStringField("users_name");
		m_userid	= m_query.getStringField("users_id");
		m_usergroup = m_query.getStringField("usersgroup_id");

		p_Array->Add(m_userid);
		p_Array->Add(m_username);
		p_Array->Add(m_usergroup);
	}

}



/*
=============================================   
����:	��ȡָ���û�����Ϣ
����:	strName	�û���
����:	CStringArray �û���Ϣ����
����:	2010-10-27	add by hushichen
=============================================
*/
void CDeuSQLProvider::GetUser(CString strName, CStringArray* p_Array)
{
	CString m_strSQL;
	m_strSQL.Format("select * from deu_users where users_name='%s'", strName);	

	CDeuSQLite3Query m_query;
	m_query = m_db.execQuery(m_strSQL);

	CStringArray m_Array;
	if(!m_query.eof())
	{
		CString m_username, m_userpwd, m_usergroup, m_strTmp;

		m_username	= m_query.getStringField("users_name");
		m_userpwd	= m_query.getStringField("users_passwd");
		m_usergroup = m_query.getStringField("usersgroup_id");
		
		p_Array->Add(m_username);
		p_Array->Add(m_userpwd);
		p_Array->Add(m_usergroup);
		
		/*
		
		m_db.execQuery("select * from deu_usergroup where user_id in ("+m_userid+")");
		*/

	}

}



/*
=============================================   
����:	�����û�
����:	strName	�û���
		strPwd	�û�����
		strUserGroup �û�����Ϣ
����:	��TRUE ��FALSE
����:	2010-10-27	add by hushichen
=============================================
*/
bool CDeuSQLProvider::CreateUser(CString strName, CString strPwd, CString strUserGroup)
{
	/* Guid */			
	char szGuid[38];
	lstrcpy(szGuid, newGUID());

	char sztime[20];
	this->GetTime(sztime);

	/* �������� */
	m_md5.TargetStr(strPwd);

	CString m_strSql;
	m_strSql.Format("insert into deu_users(users_id, usersgroup_id, users_name, users_passwd, users_encryptpwd, users_createtime) values('%s','%s','%s','%s','%s','%s')", szGuid, strUserGroup, strName, strPwd, m_md5.GetDigestKey(), sztime);

	return ExcuteSQL(m_strSql);

}


/*
=============================================
����:	����ָ���û�����Ϣ
����:	strName	�û���
		strPwd	�û�����
		strUserGroup �û�����Ϣ

����:	��TRUE ��FALSE
����:	2010-10-27	add by hushichen
=============================================
*/
bool CDeuSQLProvider::UpdateUser(CString strSrcName, CString strNewName, CString strPwd, CString strUserGroupId)
{
	/* md5���ܴ� */			
	char szmd5pwd[33];
	m_md5.TargetStr(strPwd);
	lstrcpy(szmd5pwd, m_md5.GetDigestKey());

	CString m_strSql;
	m_strSql.Format("update deu_users set users_name='%s', users_passwd='%s', users_encryptpwd='%s', usersgroup_id='%s'  where users_name='%s'", strNewName, strPwd, szmd5pwd, strUserGroupId, strSrcName);

	return this->ExcuteSQL(m_strSql);
}



/*
=============================================
����:	ɾ���û�
����:	strName	�û���
		strPwd	�û�����

����:	��TRUE ��FALSE
����:	2010-10-27	add by hushichen
=============================================
*/
bool CDeuSQLProvider::DeleteUser(CString strName)
{
	CString m_strSql;
	m_strSql.Format("delete from deu_users where users_name='%s'", strName);	
	return this->ExcuteSQL(m_strSql);	
}




/*
=============================================   
����:	��ȡ�����û�������
����:	2010-11-1	add by hushichen
=============================================
*/
CDeuSQLite3Query CDeuSQLProvider::GetGroupQueryObject()
{ 
	return m_db.execQuery("select * from deu_usergroup order by usergroup_createtime asc");
}




/*
=============================================   
����:	�����û�
����:	��ȡ�û���ID��Ϣ			
����:	��ѯ����
����:	2010-10-27	add by hushichen
=============================================
*/
CDeuSQLite3Query CDeuSQLProvider::GetUserGroup(CString strId)
{
	CString  m_strSQL;
	m_strSQL.Format("select * from deu_usergroup where usergroup_id in (%s)", strId);
	return m_db.execQuery(m_strSQL);
}
	

/*
=============================================   
����:	�����û������ж��Ƿ����
����:	��ȡ�û�����
����:	������ڷ���TRUE,���򷵻�FALSE
����:	2010-11-2	add by hushichen
=============================================
*/
BOOL CDeuSQLProvider::GetUserGroupByName(CString strName)
{
	CString m_strSQL;
	m_strSQL.Format("select * from deu_usergroup where usergroup_name='%s'", strName);

	CDeuSQLite3Table m_query;
	m_query = m_db.getTable(m_strSQL);

	if(m_query.numRows() > 0) 
		return true;
	else 
		return false;
}


/*
=============================================   
����:	���û�������ȡ�û���Ȩ������
����:	��ȡ�û�����
����:	������ڷ���TRUE,���򷵻�FALSE
����:	2010-11-2	add by hushichen
=============================================
*/
void CDeuSQLProvider::GetUserGroupByName(CString strName, CStringArray *p_array)
{
	CString m_strSQL;
	m_strSQL.Format("select * from deu_usergroup where usergroup_name='%s'", strName);

	CDeuSQLite3Query m_query;
	m_query = m_db.execQuery(m_strSQL);
	
	if(!m_query.eof())
	{
		p_array->Add(m_query.fieldValue("usergroup_sl_explorer"));
		p_array->Add(m_query.fieldValue("usergroup_sg_explorer"));
		p_array->Add(m_query.fieldValue("usergroup_db_explorer"));
		p_array->Add(m_query.fieldValue("usergroup_sl_conversion"));
		p_array->Add(m_query.fieldValue("usergroup_sg_conversion"));
		p_array->Add(m_query.fieldValue("usergroup_db_conversion"));
	}
}




BOOL CDeuSQLProvider::DelUserGroupByName(CString strName)
{
	int m_nRet = m_db.execDML("delete from deu_usergroup where usergroup_name='"+strName+"'");
	if(m_nRet == 1) 
		return TRUE;
	else
		return FALSE;
}





/*
=============================================   
����:	�����û�
����:	strName	�û���
		strPwd	�û�����
		strUserGroup �û�����Ϣ
����:	��TRUE ��FALSE
����:	2010-10-27	add by hushichen
=============================================
*/
int CDeuSQLProvider::CreateUserGroup(CString strName, CString IsSg_E , CString IsSl_E, CString IsDb_E, CString IsSl_C, CString IsSg_C, CString IsDb_C)
{
	char m_szTime[20];
	this->GetTime(m_szTime);

	/* Guid */			
	char szGuid[38];
	lstrcpy(szGuid, newGUID());

	CString m_strSql;
	CDeuSQLite3Query m_query;
	m_strSql.Format("select * from deu_usergroup where usergroup_name='%s'", strName);
	m_query = m_db.execQuery(m_strSql);
	if(m_query.eof())
	{
		m_strSql.Format("insert into deu_usergroup(usergroup_id, usergroup_name,usergroup_sl_explorer,usergroup_sg_explorer,usergroup_db_explorer,usergroup_sl_conversion,usergroup_sg_conversion,usergroup_db_conversion,usergroup_createtime) values('%s','%s','%s','%s','%s','%s','%s','%s','%s')", szGuid,strName, IsSl_E, IsSg_E, IsDb_E, IsSg_C, IsSl_C, IsDb_C, m_szTime);
		return ExcuteSQL(m_strSql);
	}
	else
	{
		return -1;
	}
	
}


/*
=============================================   
����:	����ָ���û�����Ϣ
����:	strName	�û���
		strPwd	�û�����
		strUserGroup �û�����Ϣ

����:	��TRUE ��FALSE
����:	2010-10-27	add by hushichen
=============================================
*/
BOOL CDeuSQLProvider::UpdateUserGroup(CString strName, CString IsSl_E, CString IsSg_E, CString IsDb_E, CString IsSl_C, CString IsSg_C, CString IsDb_C)
{
	CString m_strSql;
	m_strSql.Format("update deu_usergroup set usergroup_sl_explorer='%s', usergroup_sg_explorer='%s', usergroup_db_explorer='%s', usergroup_sl_conversion='%s',  usergroup_sg_conversion='%s', usergroup_db_conversion='%s' where usergroup_name='%s'", IsSl_E, IsSg_E, IsDb_E, IsSl_C, IsSg_C, IsDb_C, strName);
	return this->ExcuteSQL(m_strSql);
}
 


/*
=============================================   
����:	ɾ���û�
����:	strName	�û���
		strPwd	�û�����

����:	��TRUE ��FALSE
����:	2010-10-27	add by hushichen
=============================================
*/
BOOL CDeuSQLProvider::DeleteUserGroup(CString strId)
{
	return this->ExcuteSQL("delete from deu_usergroup where usergroup_id='"+strId+"'");
}








/*
=====================================================   
����:	��ȡϵͳ��ǰ"yyyy-mm-dd hh-ii-ss"��ʽ��ʱ��
����:	2010-10-27	add by hushichen
=====================================================
*/
void CDeuSQLProvider::GetTime(char *szTime)
{
	CTime m_time = CTime::GetCurrentTime();	
	CString m_strTime;
	m_strTime.Format("%d-%d-%d %d:%d:%d", m_time.GetYear(), m_time.GetMonth(), m_time.GetDay(), m_time.GetHour(), m_time.GetMinute(), m_time.GetSecond());	
	lstrcpy(szTime,(LPCSTR)m_strTime);
}


bool CDeuSQLProvider::ExcuteSQL(CString strSQL)
{
	int ret;
	m_db.execDML("begin transaction;");
	ret = m_db.execDML(strSQL);
	m_db.execDML("commit transaction;");

	if(ret == 1) return true;
	else return false;
}


//����sqlite���ʶ���
void CDeuSQLProvider::Open()
{
	m_db.open(szDbName, szDbPwd);
}


//�ر�sqlite���ʶ���
void CDeuSQLProvider::Close()
{
	m_db.close();
}



//����û����Ƿ����
bool CDeuSQLProvider::CheckUserExist(CString strName)
{
	CString m_strSQL;
	m_strSQL.Format("select * from deu_users where users_name='%s'", strName);	

	CDeuSQLite3Query m_query;
	m_query = m_db.execQuery(m_strSQL);

	if(!m_query.eof())
	{
		return true;
	}

	return false;
}