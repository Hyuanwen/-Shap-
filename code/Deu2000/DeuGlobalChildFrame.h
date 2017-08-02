/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     描述:	主要用来多文档框架下，子框架的公共属性的定义的父类
//     作者：	hushichen
//     修改者：	----
//     主要函数：
//     版本: 
//     修改: 
//     CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////

#pragma once

class CDeuGlobalChildFrame:public CMDIChildWnd
{
public:
	CDeuGlobalChildFrame();
	~CDeuGlobalChildFrame();
	
	//子框架窗口属性
	char sz_ModuleType[10];

	//框架的流水号
	int m_nOrder;
};
