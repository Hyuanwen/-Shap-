/////////////////////////////////////////////////////////////////////
//   ��Ŀ:   �����ǻ�����ת�����
//   ���ߣ�  hushichen
//   �޸��ߣ�
//   ����:	 �����Լ���sqlite ���Ϸ�װ������
//   �汾:	 1.0
/////////////////////////////////////////////////////////////////////

#pragma once

#include <objbase.h>
#include <stdio.h>

#include "md5.h"
#include "DeuSQLite3.h"

#define szDbName "deuDB.dll"
#define szDbPwd "123456"



class CDeuSQLProvider
{
public:
	CDeuSQLProvider();
	~CDeuSQLProvider(void);
	

private:	
	CDeuSQLite3DB m_db;
	CMd5 m_md5;

	bool ExcuteSQL(CString strSQL);

public:
	/* �û������������ */
	CDeuSQLite3Query GetUsersQueryObject();		//��ȡ�û����ѯ����
	void GetUser(CString strName, CString strPwd, CStringArray* p_Array);
	void GetUser(CString strName, CStringArray* p_Array);

	bool CreateUser(CString strName, CString strPwd, CString strUserGroup);
	bool UpdateUser(CString strSrcName, CString strNewName, CString strPwd, CString strUserGroupId);
	bool DeleteUser(CString strName);

	bool CheckUserExist(CString strName);

	/*--------�û������������------*/

	//��ȡ�û����ѯ����
	CDeuSQLite3Query GetGroupQueryObject();
	CDeuSQLite3Query GetUserGroup(CString strId);
	BOOL DelUserGroupByName(CString strName);
	
	/* �����û������ж��Ƿ���� */
	BOOL GetUserGroupByName(CString strName);
	
	/* �����û�������ȡ�û�����Ϣ */
	void GetUserGroupByName(CString strName, CStringArray *p_array);
	
	/* �����û�������ȡ�û�id */
	void GetUserGroupIdByName(CString strName, CString *p_strId);

	/* ���û�����ȡ�û���ID  */
	void FromUserGetGroupId(char* m_cName, CString* p_strId);

	
	int CreateUserGroup(CString strName,  CString IsSl_E, CString IsSg_E, CString IsDb_E, CString IsSl_C, CString IsSg_C, CString IsDb_C);
	BOOL UpdateUserGroup(CString strName, CString IsSl_E, CString IsSg_E, CString IsDb_E, CString IsSl_C, CString IsSg_C, CString IsDb_C);
	BOOL DeleteUserGroup(CString strId);

	/* ��ȡ yyyy-mm-dd hh:mm:ss ��ʽʱ�䴮*/
	void GetTime(char *szTime);

	/* �ú�������ΪĳЩ���ⳡ��ʹ���ṩ */
	void Open();
	void Close();

};	


