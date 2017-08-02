#include "StdAfx.h"
#include "GridParameter.h"
#include "GridTranslate.h"

CGridTranslate::CGridTranslate(void)
{
}

CGridTranslate::~CGridTranslate(void)
{
}

HRESULT CGridTranslate::InitGridTranslate(std::string strFileName)
{
	m_GridParameter.InitGridParameter(strFileName);

	return S_OK;
}

HRESULT CGridTranslate::CalculateOffset(std::string strSheetNum, double x, double y, double * dx, double * dy)
{
	GridParameter                 GridFormat;
	GridParameter                 SheetGridFormat;
	HRESULT                       Hre;

	//获得格网改正量
	m_GridParameter.GetParameterBySheet(strSheetNum, &GridFormat);
	if (GridFormat.DB_DB == 0 
		&& GridFormat.DB_DN == 0 
		&& GridFormat.DB_XB == 0
		&& GridFormat.DB_XN == 0
		&& GridFormat.DL_DB == 0
		&& GridFormat.DL_DN == 0
		&& GridFormat.DL_XB == 0
		&& GridFormat.DL_XN == 0)
	{
		*dx = 0;
		*dy = 0;
		return S_FALSE;
	}

    //获得图幅4个角点的坐标信息
	Hre = CalculateCoordsByFrame(strSheetNum, &SheetGridFormat);
	if (Hre != S_OK)
	{
		//没有正常获得信息返回失败
		*dx = 0;
		*dy = 0;
		return S_FALSE;
	}

	//计算该点改正量，双线性内插法

	double detalL = SheetGridFormat.DL_DN - SheetGridFormat.DL_XN;

	double detalB = SheetGridFormat.DB_DB - SheetGridFormat.DB_DN;

	*dx = (( SheetGridFormat.DL_DN - y ) / detalL ) * (( SheetGridFormat.DB_DB - x ) / detalB ) *  GridFormat.DB_XN  +

		((SheetGridFormat.DL_DN - y ) / detalL ) * (( x - SheetGridFormat.DB_XN ) / detalB ) * GridFormat.DB_XB +

		((y - SheetGridFormat.DL_XN) / detalL ) * (( x - SheetGridFormat.DB_XN ) / detalB ) * GridFormat.DB_DB +

		((y - SheetGridFormat.DL_XN) / detalL ) * (( SheetGridFormat.DB_XB - x ) / detalB ) * GridFormat.DB_DN;

	//单位是秒

	*dy = (( SheetGridFormat.DL_DN - y ) / detalL ) * (( SheetGridFormat.DB_DB - x ) / detalB ) *  GridFormat.DL_XN  +

		((SheetGridFormat.DL_DN - y ) / detalL ) * (( x - SheetGridFormat.DB_XN ) / detalB ) * GridFormat.DL_XB +

		((y - SheetGridFormat.DL_XN) / detalL ) * (( x - SheetGridFormat.DB_XN ) / detalB ) * GridFormat.DL_DB +

		((y - SheetGridFormat.DL_XN) / detalL ) * (( SheetGridFormat.DB_XB - x ) / detalB ) * GridFormat.DL_DN;//单位是秒

	//转化为°

	*dx /= 3600.0 ;

	*dy /= 3600.0 ;

	return S_OK;
}

//通过图幅号获得图幅范围的角点坐标值
HRESULT CGridTranslate::CalculateCoordsByFrame(std::string strSheetNum, GridParameter * pGridFormat)
{
	std::string                   strA;
	std::string                   strB;
	std::string                   strC;
	std::string                   strD;
	std::string                   strScaleCode;

	double                        la = 0;
	double                        lb = 0;
	double                        lc = 0;
	double                        ld = 0;
	double                        detalX = 0;
	double                        detalY = 0;

	strA = strSheetNum.substr(0, 1);       
	strB = strSheetNum.substr(1, 2);
	strScaleCode = strSheetNum.substr(3, 1);
	strC = strSheetNum.substr(4, 3);
	strD = strSheetNum.substr(7, 3);

	la = letter2num(strA.c_str());
	lb = atoi(strB.c_str());
	lc = atoi(strC.c_str());
	ld = atoi(strD.c_str());
	int iScaleCode = letter2num(strScaleCode.c_str());
	GetDetalXY(iScaleCode, &detalY, &detalX);

	pGridFormat->DL_XN = ( lb - 31 ) * 6 + ( ld - 1 ) * detalY;
	pGridFormat->DB_XN = ( la - 1 ) * 4 + ( 4 / detalX - lc ) * detalX;

	pGridFormat->DB_XB = pGridFormat->DB_XN + detalX;
	pGridFormat->DL_XB = pGridFormat->DL_XN;

	pGridFormat->DB_DB = pGridFormat->DB_XN + detalX;
	pGridFormat->DL_DB = pGridFormat->DL_XN + detalY;

	pGridFormat->DB_DN = pGridFormat->DB_XN;
	pGridFormat->DL_DN = pGridFormat->DL_XN + detalY;

	return S_OK;
}

//通过经纬度坐标计算图幅号
HRESULT CGridTranslate::CalculateFrameByPoint(double x, double y, std::string strScalecode, std::string * pstrFrame)
{
	int                           a = 0; 
	int                           b = 0;
	int                           c = 0;
	int                           d = 0;
	double                        dx = 0;
	double                        dy = 0;
	std::string                   strA;
	char                          chFrame[32] = {0};

	a = (int)( x / 4 ) + 1;
	b = (int)( y / 6 ) + 31;

	//根据比例尺获得图幅缩放量
	GetDetalXY(letter2num(strScalecode), &dx, &dy);

	c = 4 / dy - (int)(  fmod( x , 4 ) / dy ) ;
	d = (int)( fmod(y , 6) /dx) + 1 ;

	num2letter(a, &strA);

	sprintf(chFrame, "%s%02d%s%03d%03d", strA.c_str(), b, strScalecode.c_str(), c, d) ;

    * pstrFrame = chFrame;

	return S_OK;
}


HRESULT CGridTranslate::GetDetalXY(int iScaleCode , double * detalX, double * detalY)
{
	*detalX = LatLongDiff[iScaleCode - 1][0];

	*detalY = LatLongDiff[iScaleCode - 1][1];

	return S_OK;
}

int CGridTranslate::letter2num(std::string strl)
{
	std::string strletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int iLength = strletter.length();

	for (int i = 0; i < /*strletter.length()*/iLength; i++)
	{
		if(strl == strletter.substr(i, 1))
		{
			return i+1;
		}
	}

	return -1;
}

HRESULT CGridTranslate::num2letter(int n, std::string * pstrScaleCode)
{
	std::string strletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	if (n <= 0 || n >26)
	{
		return S_FALSE;
	}

    * pstrScaleCode = strletter.substr(n-1,1);

	return S_OK;
}