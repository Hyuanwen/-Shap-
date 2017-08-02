#include "StdAfx.h"
#include "StringFunction.h"
#include <math.h>

//-------------------------------------------------------------------------------------------------------------------------
//
// in  : double d 
// out : char *
// descrip : �������double��ת��Ϊ�ַ������,����16λ��Ч����
//
//-------------------------------------------------------------------------------------------------------------------------
char* DoubleToString(double d)
{
	double d0 = d;
	int    decimal = 0;
	int    sign = 0;
	char*  buffer = NULL;
	int    precision = 16;  //����16λ��Ч����

	// ��˫���ȸ�������ת��Ϊ�ַ���
	buffer = _ecvt(d0, precision, &decimal, &sign);

	// ����С����
	char * result = new char[32];
	char * p_res = result;
	char * p_buf = buffer;

	//if (sign > 0)
	//{
	//	*p_res++ = '-';
	//}

	// alter by chenyong 2013-5-13 ����С������
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

	//ȥ��ĩβ��0
	p_res--;
	while (*p_res == '0')
	{
		*p_res-- = 0;
	}

	return result;
}

// ����֧��ARC2��ʽ�µĸ�����ת��
void Scientific_notationtoDouble(string& strLine, double* pxy) 
{
	int       iE = 0;     //�ҵ�"E"���ַ��е�λ��
	string    strMiType;  //��ÿ�ѧ�������������Ƕ���
    string    strMi;
	string    strdoule;   
	double    tmpdouble = 0;
	int       iMi = 0;

	unsigned int loc = strLine.find("E", 0);
	strMiType = strLine.at(loc+1);				  //E��һλ������������ + ���� -
    strMi = strLine.substr(loc+2,strLine.size()); //E����λ�����Ϊ������ֵ
    strdoule = strLine.substr(0, loc);
    tmpdouble = atof(strdoule.c_str());
	iMi = atol(strMi.c_str());

	//�����󷵻ص�double
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

// 2012.9.14��ѧ������תdouble
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

	//ת��֮����Ҫ���л��ݴ��� ��֤ E+����E-��������λ����2����
	unsigned int loc = tmpstr.find("E");
	strMi = tmpstr.substr(loc+2, tmpstr.size()-1);
	str1 = tmpstr.at(loc);
	str3 = tmpstr.at(loc+1);
	str2 = tmpstr.substr(0, loc);
	iMi = atol(strMi.c_str());

	//Ȼ��ת����2����
	if (0 < iMi < 10)
	{
		sprintf(chMi, "0%d", iMi);
	}
	else
	{
		sprintf(chMi, "%d", iMi);
	}

	//�ж�Eǰ���ַ����Ƿ�������㳤��Ҫ�� ������9λ
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

// 2012.9.18��ѧ������תsdouble  by liujun
// 2012.10.26  ��дby������
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

	//ת��֮����Ҫ���л��ݴ��� ��֤ E+����E-��������λ����2����
	unsigned int loc = tmpstr.find("E");
	strMi = tmpstr.substr(loc+2, tmpstr.size()-1);
	str1 = tmpstr.at(loc);
	str3 = tmpstr.at(loc+1);
	str2 = tmpstr.substr(0, loc);
	iMi = atol(strMi.c_str());

	//Ȼ��ת����2����
	if (0 < iMi < 10)
	{
		sprintf(chMi, "0%d", iMi);
	}
	else
	{
		sprintf(chMi, "%d", iMi);
	}

	//�ж�Eǰ���ַ����Ƿ�������㳤��Ҫ�� ������9λ
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