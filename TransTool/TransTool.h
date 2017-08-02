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

	//先调用SetTransPara设置转换参数，再使用转换函数TransDot
public:
	//pdSrcX pdSrcY pdSrcZ 控制点源坐标点串
	//pdDesX pdDesY pdDesZ 控制点目标坐标点串
	//lDotNum 点对个数
	bool SetTransPara(double* pdSrcX, double* pdSrcY, double* pdSrcZ,
		              double* pdDesX, double *pdDesY, double *pdDesZ, long lDotNum);

	bool TransDot(double dSrcX, double dSrcY, double dSrcZ,
		          double &dDesX, double &dDesY, double &dDesZ);

private:
	double *pTransPra;
};
#endif


