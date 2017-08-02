#pragma once

#ifndef DEU_TRANS__H
#define DEU_TRANS__H
//#include "TransToolDef.h"

#ifdef DLL_FILE_LIB
#define DLL_TRANS_H2D_H_ _declspec(dllimport)
#else
#define DLL_TRANS_H2D_H_ _declspec(dllexport)  
#endif

class DLL_TRANS_H2D_H_ CTransTool
{
public:
	CTransTool(void);
	~CTransTool(void);

	//�ȵ���SetTransPara����ת����������ʹ��ת������TransDot
public:
	//pdSrcX pdSrcY pdSrcZ ���Ƶ�Դ����㴮
	//pdDesX pdDesY pdDesZ ���Ƶ�Ŀ������㴮
	//lDotNum ��Ը���
	bool SetTransPara(double* pdSrcX, double* pdSrcY, double* pdSrcZ,
		              double* pdDesX, double *pdDesY, double *pdDesZ, long lDotNum);

	bool TransDot(double dSrcX, double dSrcY, double dSrcZ,
		          double &dDesX, double &dDesY, double &dDesZ);

private:
	double *pTransPra;
};
#endif


