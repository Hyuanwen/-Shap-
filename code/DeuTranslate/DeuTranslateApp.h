// DeuTranslate.h : DeuTranslate DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDeuTranslateApp
// �йش���ʵ�ֵ���Ϣ������� DeuTranslate.cpp
//

class CDeuTranslateApp : public CWinApp
{
public:
	CDeuTranslateApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
