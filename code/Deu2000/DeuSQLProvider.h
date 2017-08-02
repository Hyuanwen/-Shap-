/////////////////////////////////////////////////////////////////////
//   项目:   德毅智慧坐标转换软件
//   作者：  hushichen
//   修改者：
//   描述:	 德毅自加密sqlite 向上封装访问类
//   版本:	 1.0
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
	/* 用户组操作函数集 */
	CDeuSQLite3Query GetUsersQueryObject();		//获取用户组查询对象
	void GetUser(CString strName, CString strPwd, CStringArray* p_Array);
	void GetUser(CString strName, CStringArray* p_Array);

	bool CreateUser(CString strName, CString strPwd, CString strUserGroup);
	bool UpdateUser(CString strSrcName, CString strNewName, CString strPwd, CString strUserGroupId);
	bool DeleteUser(CString strName);

	bool CheckUserExist(CString strName);

	/*--------用户组操作函数集------*/

	//获取用户组查询对象
	CDeuSQLite3Query GetGroupQueryObject();
	CDeuSQLite3Query GetUserGroup(CString strId);
	BOOL DelUserGroupByName(CString strName);
	
	/* 根据用户组名判断是否存在 */
	BOOL GetUserGroupByName(CString strName);
	
	/* 根据用户组名获取用户组信息 */
	void GetUserGroupByName(CString strName, CStringArray *p_array);
	
	/* 根据用户组名获取用户id */
	void GetUserGroupIdByName(CString strName, CString *p_strId);

	/* 从用户表处获取用户组ID  */
	void FromUserGetGroupId(char* m_cName, CString* p_strId);

	
	int CreateUserGroup(CString strName,  CString IsSl_E, CString IsSg_E, CString IsDb_E, CString IsSl_C, CString IsSg_C, CString IsDb_C);
	BOOL UpdateUserGroup(CString strName, CString IsSl_E, CString IsSg_E, CString IsDb_E, CString IsSl_C, CString IsSg_C, CString IsDb_C);
	BOOL DeleteUserGroup(CString strId);

	/* 获取 yyyy-mm-dd hh:mm:ss 格式时间串*/
	void GetTime(char *szTime);

	/* 该函数仅仅为某些特殊场合使用提供 */
	void Open();
	void Close();

};	


