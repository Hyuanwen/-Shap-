#include "StdAfx.h"
#include "DeuReadFile.h"


DeuReadFile::DeuReadFile(const char * szfn)
{
	ifstream infile(szfn);
	//ifstream infile("E:\\��д\\���Խ��\\���Ȳ���\\Config.ini");
	//ifstream infile("Config.ini");
    //Ĭ�������ģʽ,����ģʽ(�����ƻ�ԭ������)��: ofstream outfile   ("d:\\bbb.txt",ios_base::app)
    //ofstream outfile("d:\\bbb.txt");  
    string sline;//ÿһ��
    string s1,s2,s3,s4,s5,s6;
    /*vector<string> vec1,vec2;*/
    while(getline(infile,sline))
    {
        istringstream sin(sline);
        sin>>s1>>s2>>s3>>s4>>s5>>s6;
        vec1.push_back(s1);
        vec2.push_back(s2);
		vec3.push_back(s3);
		vec4.push_back(s4);
		vec5.push_back(s5);
		vec6.push_back(s6);


    }
}

DeuReadFile::~DeuReadFile(void)
{
}
