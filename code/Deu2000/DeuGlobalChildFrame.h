/////////////////////////////////////////////////////////////////////
//     ��Ŀ:	�����ǻ�ת�����
//     ����:	��Ҫ�������ĵ�����£��ӿ�ܵĹ������ԵĶ���ĸ���
//     ���ߣ�	hushichen
//     �޸��ߣ�	----
//     ��Ҫ������
//     �汾: 
//     �޸�: 
//     CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////

#pragma once

class CDeuGlobalChildFrame:public CMDIChildWnd
{
public:
	CDeuGlobalChildFrame();
	~CDeuGlobalChildFrame();
	
	//�ӿ�ܴ�������
	char sz_ModuleType[10];

	//��ܵ���ˮ��
	int m_nOrder;
};
