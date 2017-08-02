#ifndef _DEUFUNCTION_H_
#define _DEUFUNCTION_H_

#pragma once


#include <list>
#include <atlstr.h>
#include "Node.h"
CString GetCurrentDir();

CNode* getNodeFromName(std::list<CNode *> n, CString name);//根据标签名称取结点 曹欣

CString getNodeName(std::list<CNode *> n, CString name);//用来取结点名称的通用方法 曹欣


void AfxSelectDirDlg(/*char Dir[256]*/char * Dir);

void SelectDirDlg(const CString& strSelectDir, char* szDir);

BOOL IsExistDirectory(const string& strPath);

template<class T>
T getListItem(std::list<T> l,int i)
{
	std::list<T>::iterator it;

	int count = 0;
	for(it = l.begin(); it != l.end(); it++,count++)
	{
		if(count == i)
			return (T)*it;
	}

	return T(NULL);
}


//这个宏用来获得一个条件函数，该条件判断 ( 类的成员 ) 和给定的值是否相等
#define IFFUNC(val) template<class T,class K>\
class IFFunctor_##val\
{\
public:\
	IFFunctor_##val(K s):m_s(s)\
{}\
	bool operator ()(T a)\
{\
	return (a != NULL)&&(a->val == m_s);\
}\
private:\
	K m_s;\
} ;\


//这个宏用来获得一个条件函数，该条件判断 （CS中node的data） 和给定的值是否相等
#define IFFUNC_2(val) template<class T,class K>\
class IFFunctor2_##val\
{\
public:\
	IFFunctor2_##val(K s):m_s(s)\
{}\
	bool operator ()(T a)\
{\
	return (a != NULL)&&(a->val.m_strData == m_s);\
}\
private:\
	K m_s;\
} ;\



//CString 转Int,Float
#define TTOI(str) _ttoi((LPCTSTR)str)
#define TSTOF(str) _tstof((LPCTSTR)str)


class CDeuFunction
{
public:
	CDeuFunction(void);
public:
	~CDeuFunction(void);
};

//根据图幅号算西南角点
void CalculateWS(const char * tf, double & w ,double & s);

int letter2num(const char l);

void GetDetalXY( int iScaleCode , double & detalX , double & detalY );

#endif