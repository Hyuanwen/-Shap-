// ReadShape.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReadShapeApp:
// �йش����ʵ�֣������ ReadShape.cpp
//

class CReadShapeApp : public CWinApp
{
public:
	CReadShapeApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReadShapeApp theApp;