#pragma once

//-------------------------------------------------------------------------------------------------------------------------
//
// in  : double d 
// out : char *
// descrip : 将输入的double，转化为字符串输出,保留16位有效数字
//
//-------------------------------------------------------------------------------------------------------------------------
char* DoubleToString(double d);

// 仅仅支持ARC2格式下的浮点数转换
void  Scientific_notationtoDouble(string& strLine, double* pxy);

// 2012.9.14科学计数法转double
void  DoubletoScientific_notation(double d, string& strResult);
void  DoubletoScientific_notation2(double d, string& strResult, int a);

// 2012.9.18科学计数法转sdouble
void  SDoubletoScientific_notation(double d, string& strResult);

//string strFormt(char *pVal, char chVal);
