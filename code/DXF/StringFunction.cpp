#include "StdAfx.h"
#include "StringFunction.h"
#include <math.h>

//-------------------------------------------------------------------------------------------------------------------------
//
// in  : double d 
// out : char *
// descrip : 将输入的double，转化为字符串输出,保留16位有效数字
//
//-------------------------------------------------------------------------------------------------------------------------
char* DoubleToString(double d)
{
	double d0 = d;
	int    decimal = 0;
	int    sign = 0;
	char*  buffer = NULL;
	int    precision = 16;  //保留16位有效数字

	// 将双精度浮点型数转换为字符串
	buffer = _ecvt(d0, precision, &decimal, &sign);

	// 插入小数点
	char * result = new char[32];
	char * p_res = result;
	char * p_buf = buffer;

	//if (sign > 0)
	//{
	//	*p_res++ = '-';
	//}

	// alter by chenyong 2013-5-13 增加小数处理
	if (decimal > 0)
	{
		if (d < 0)
		{
			*p_res++ = '-';
		}
		for(int i=0 ; i<17 ; i++)
		{
			if(i == decimal)
			{
				*p_res++ = '.';
			}
			else
			{
				*p_res++ = *p_buf++;
			}
		}	

	}
	else
	{
		if (d > 0)
		{
			for (int i = decimal -2; i < 17 + decimal; i++)
			{
				if (i < 0)
				{
					if (i == decimal -1)
					{
						*p_res++ = '.';
					}
					else
					{
						*p_res++ = '0';
					}
				}
				else
				{
					*p_res++ = *p_buf++;
				}
			}
		}
		else
		{
			for (int i = decimal -3; i < 17 + decimal; i++)
			{
				if (i < 0)
				{
					if (i == decimal -3)
					{
						*p_res++ = '-';
					}
					else if (i == decimal -1)
					{
						*p_res++ = '.';
					}
					else
					{
						*p_res++ = '0';
					}
				}
				else
				{
					*p_res++ = *p_buf++;
				}
			}
		}

	}
	
	/*for(int i=0 ; i<17 ; i++)
	{
		if(i== decimal)
		{
			*p_res++ = '.';
		}
		else
		{
			*p_res++ = *p_buf++;
		}
	}*/
	// end by chenyong 2013-5-13

	*p_res = '\0';

	//去掉末尾的0
	p_res--;
	while (*p_res == '0')
	{
		*p_res-- = 0;
	}

	return result;
}

// 仅仅支持ARC2格式下的浮点数转换
void Scientific_notationtoDouble(string& strLine, double* pxy) 
{
	int       iE = 0;     //找到"E"在字符中的位置
	string    strMiType;  //获得科学计数法的幂数是多少
    string    strMi;
	string    strdoule;   
	double    tmpdouble = 0;
	int       iMi = 0;

	unsigned int loc = strLine.find("E", 0);
	strMiType = strLine.at(loc+1);				  //E后一位是幂数的类型 + 还是 -
    strMi = strLine.substr(loc+2,strLine.size()); //E后两位到最后为幂数的值
    strdoule = strLine.substr(0, loc);
    tmpdouble = atof(strdoule.c_str());
	iMi = atol(strMi.c_str());

	//获得最后返回的double
    if (strMiType == "+")
    {
		for (int i = 0; i < iMi; i++)
		{
			tmpdouble = tmpdouble * 10;
		}

        * pxy = tmpdouble;
    } 
    else if (strMiType == "-")
    {
		for (int i = 0; i < iMi; i++)
		{
			tmpdouble = tmpdouble / 10;
		}

		 * pxy = tmpdouble;
    }
    else
	{
		* pxy = 0;
	}
}

// 2012.9.14科学计数法转double
void DoubletoScientific_notation(double d, string& strResult)
{
	char                               result[20];
	char                               chMi[5];
	string                             tmpstr;
	string                             strMi;
	string                             str1;
	string                             str2;
	string                             str3;
	int                                iMi = 0;

	sprintf(result, "%E", d);     
	tmpstr = (string)result;

	//转换之后需要进行换幂处理 保证 E+或者E-后面是两位数的2次幂
	unsigned int loc = tmpstr.find("E");
	strMi = tmpstr.substr(loc+2, tmpstr.size()-1);
	str1 = tmpstr.at(loc);
	str3 = tmpstr.at(loc+1);
	str2 = tmpstr.substr(0, loc);
	iMi = atol(strMi.c_str());

	//然后转换成2次幂
	if (0 < iMi < 10)
	{
		sprintf(chMi, "0%d", iMi);
	}
	else
	{
		sprintf(chMi, "%d", iMi);
	}

	//判断E前的字符串是否可以满足长度要求 必须是9位
	int i = 0;
	i = str2.size();
	if (i < 9)  
	{
		for (int l = 0; l < 9 - i; l ++)
		{
			str2 = str2 + "0";
		}
	}
	else if (i > 9)
	{
		str2 = str2.substr(0,8);    
	}

	strResult = str2 + str1 + str3 + (string)chMi;

	return;
}

void DoubletoScientific_notation2(double d, string& strResult, int a)
{

	double				bef=abs(d);
	char                result[20];
	char                chMi[5];
	string              str1;
	string              str2;
	int					aft =0;

	if (bef >= 10)
	{
		str1="+";
	} 
	else
	{
        str1="-";
	}

	while(bef>=10 || (bef<1&&bef!=0))
	{
		if (bef>=10)
		{
			bef=bef/10;
			aft++;
		} 
		else
		{
			bef=bef*10;
			aft--;
		}
	}    
	sprintf(result,"%.14f",bef);
	str2  = (string)result;

	int i = str2.size();
	if (i < a+1)  
	{
		for (int l = 0; l < a+1 - i; l ++)
		{
			str2 = str2 + "0";
		}
	}
	else if (i > a+1)
	{
		str2 = str2.substr(0,a);    
	}
	if (0 < aft < 10)
	{
		sprintf(chMi, "0%d", aft);
	}
	else
	{
		sprintf(chMi, "%d", aft);
	}

	strResult=str2+"E"+str1+(string)chMi;

	return;
}

// 2012.9.18科学计数法转sdouble  by liujun
// 2012.10.26  改写by潘万坤
void SDoubletoScientific_notation(double d, string & strResult)
{
	/*
	char                               result[20];
	char                               chMi[5];
	string                             tmpstr;
	string                             strMi;
	string                             str1;
	string                             str2;
	string                             str3;
	int                                iMi = 0;

	sprintf(result, "%E", d);     
	tmpstr = (string)result;

	//转换之后需要进行换幂处理 保证 E+或者E-后面是两位数的2次幂
	unsigned int loc = tmpstr.find("E");
	strMi = tmpstr.substr(loc+2, tmpstr.size()-1);
	str1 = tmpstr.at(loc);
	str3 = tmpstr.at(loc+1);
	str2 = tmpstr.substr(0, loc);
	iMi = atol(strMi.c_str());

	//然后转换成2次幂
	if (0 < iMi < 10)
	{
		sprintf(chMi, "0%d", iMi);
	}
	else
	{
		sprintf(chMi, "%d", iMi);
	}

	//判断E前的字符串是否可以满足长度要求 必须是9位
	int i = 0;
	i = str2.size();
	if ( i < 16 )
	{
		for (int l = 0; l < 16 - i; l ++)
		{
			str2 = str2 + "0";
		}
	}
	else if ( i > 16 )
	{
		str2 = str2.substr(0, 15);
	}

	strResult = str2 + str1 + str3 + (string)chMi;*/

	double					bef=abs(d);
	char                    result[20];
	char                    chMi[5];
	string                  str1;
	string                  str2;
	int						aft =0;

	if (bef >= 10)
	{
		str1="+";
	} 
	else
	{
		str1="-";
	}
	while(bef >= 10 || (bef<1&&bef!=0))
	{
		if (bef>=10)
		{
			bef=bef/10;
			aft++;
		} 
		else
		{
			bef=bef*10;
			aft--;
		}
	}

	sprintf(result,"%.14f",bef);
	str2=(string)result;
	if (0 < aft < 10)
	{
		sprintf(chMi, "0%d", aft);
	}
	else
	{
		sprintf(chMi, "%d", aft);
	}

	strResult=str2+"E"+str1+(string)chMi;

	return;
}

//string strFormt(char *pVal, char chVal)
//{
//	string str(pVal);
//	int    iLen = 0;
//	int	   index = 0;
//
//	index = str.find_first_of('.');
//	iLen = str.length();
//	for (int i = index + 5; i < iLen; i++)
//	{
//		str[i] = chVal;
//	}
//
//	return str;
//}