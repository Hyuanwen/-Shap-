#pragma once

//-------------------------------------------------------------------------------------------------------------------------
//
// in  : double d 
// out : char *
// descrip : �������double��ת��Ϊ�ַ������,����16λ��Ч����
//
//-------------------------------------------------------------------------------------------------------------------------
char* DoubleToString(double d);

// ����֧��ARC2��ʽ�µĸ�����ת��
void  Scientific_notationtoDouble(string& strLine, double* pxy);

// 2012.9.14��ѧ������תdouble
void  DoubletoScientific_notation(double d, string& strResult);
void  DoubletoScientific_notation2(double d, string& strResult, int a);

// 2012.9.18��ѧ������תsdouble
void  SDoubletoScientific_notation(double d, string& strResult);

//string strFormt(char *pVal, char chVal);
