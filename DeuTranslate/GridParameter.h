#include "TinyXml/tinyxml.h"

#pragma once


typedef struct GridParameter
{
	char                  szFrame[12];
	double                DB_XN;
	double	              DL_XN;
	double	              DB_XB;
	double	              DL_XB;
	double	              DB_DB;
	double	              DL_DB;
	double	              DB_DN;
	double	              DL_DN;
}GridParameter;


#define GRID_GridParameter "GridParameter"
#define GRID_Frame "FRame"
#define GRID_DB_XN "DB_XN"
#define GRID_DL_XN "DL_XN"
#define GRID_DB_XB "DB_XB"
#define GRID_DL_XB "DL_XB"
#define GRID_DB_DB "DB_DB"
#define GRID_DL_DB "DL_DB"
#define GRID_DB_DN "DB_DN"
#define GRID_DL_DN "DL_DN"

class CGridParameter
{
public:
	CGridParameter(void);
	CGridParameter(std::string strFileName);
	~CGridParameter(void);

public:
	//获得xml中格网参数的函数
	HRESULT InitGridParameter();
	HRESULT InitGridParameter(std::string strFileName);
	HRESULT GetParameterBySheet(std::string strSheetNum, GridParameter * pGridFormat);

	//生成存储格网改正量的文件并向中间插入一组格网参数的方法
	HRESULT GreatParameterXml(LPCSTR chPath, LPCSTR chName);
	HRESULT GreatParameterXml(std::string strPath, std::string strName);
	HRESULT InsertParameter(GridParameter GridFormat);

private:
	HRESULT GetGridParametersByXml(std::vector<GridParameter> * pGetGridParameterList);

private:
    TiXmlDocument                 m_ParameterXml;
	std::string                   m_strPath;
	std::vector<GridParameter>    m_ParameterList;
};

/*  Xml文件格式样例
<?xml version="1.0" encoding="UTF-8" ?>
<GridParameters>
    <GridParameter>
        <FRame>H51D001003</FRame>
        <DB_XN>-0.1861000000</DB_XN>
        <DL_XN>4.4850000000</DL_XN>
        <DB_XB>-0.1851000000</DB_XB>
        <DL_XB>4.5023000000</DL_XB>
        <DB_DB>-0.2042000000</DB_DB>
        <DL_DB>4.5027000000</DL_DB>
        <DB_DN>-0.2051000000</DB_DN>
        <DL_DN>4.4858000000</DL_DN>
    </GridParameter>
    <GridParameter>
        <FRame>H51D001004</FRame>
        <DB_XN>-0.2051000000</DB_XN>
        <DL_XN>4.4858000000</DL_XN>
        <DB_XB>-0.2042000000</DB_XB>
        <DL_XB>4.5027000000</DL_XB>
        <DB_DB>-0.2120000000</DB_DB>
        <DL_DB>4.4913000000</DL_DB>
        <DB_DN>-0.2134000000</DB_DN>
        <DL_DN>4.4805000000</DL_DN>
    </GridParameter>
</GridParameters>
*/