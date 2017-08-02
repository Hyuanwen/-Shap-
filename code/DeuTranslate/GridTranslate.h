#include "GridParameter.h"

#pragma once

const double LatLongDiff[8][2] = {
	{6,4},
	{3,2},
	{1.5,1},
	{1.0/2.0,1.0/3.0},
	{1.0/4.0,1.0/6.0},
	{1.0/8.0,1.0/12.0},
	{1.0/16.0,1.0/24.0},
	{1.0/32.0,1.0/48.0},
};

class CGridTranslate
{
public:
	CGridTranslate(void);
	~CGridTranslate(void);

public:
	//��ʼ����������
	HRESULT InitGridTranslate(std::string strFileName);
	
	//����ͼ���Ż��ͼ����Χ�Ľǵ�����
	HRESULT CalculateOffset(std::string strSheetNum, double x, double y, double * dx, double * dy);
	
	//���������ö�Ӧ��ͼ����
	HRESULT CalculateFrameByPoint(double x, double y, std::string strScalecode, std::string * pstrFrame);

private:
	HRESULT CalculateCoordsByFrame(std::string, GridParameter * pGridFormat);
	HRESULT GetDetalXY(int iScaleCode, double * detalX, double * detalY);
	int     letter2num(std::string strl);
	HRESULT num2letter(int n, std::string * strScaleCode);

private:
	CGridParameter                m_GridParameter;
};
