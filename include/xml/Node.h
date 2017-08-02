#pragma once
#include <vector>
#include <list>
#include "Markup.h"
using namespace std;

class CNode
{
public:
	CNode(void);
public:
	~CNode(void);
public:
	CNode	* parent;
	list<CNode*> _sub_nodes;
	CString data;
	CString ele_name;
	CString tag_name;
	void DestroySubNodes();

public:
	CNode	*Clone();
};

#if 0
//CEllipsoid54
class CEllipsoid54:public CNode
{
public:
	CEllipsoid54()
	{
		name = L"ellipsoidbeijing54";
		//ellip_name
		CNode* _ellip_name;
		_ellip_name=new CNode;
		_ellip_name->name=L"Ellip_Name";
		_ellip_name->data="";
		_sub_nodes.push_back(_ellip_name);
		//Major
		CNode* _major;
		_major= new CNode;
		_major->name= L"Major";
		_major->data="";
		_sub_nodes.push_back(_major);
		CNode* _minor;
		_minor= new CNode;
		_minor->name=L"Minor";
		_minor->data="";
		_sub_nodes.push_back(_minor);
		//Flatening
		CNode*  _flatening;
		_flatening= new CNode;
		_flatening->name=L"Flatening";
		_flatening->data="";
		_sub_nodes.push_back(_flatening);
		//Prj_Name
		CNode* _prj_Name;
		_prj_Name= new CNode;
		_prj_Name->name=L"Prj_Name";
		_prj_Name->data="";
		_sub_nodes.push_back(_prj_Name);
		//Prj_Type
		CNode* _prj_Type;
		_prj_Type= new CNode;
		_prj_Type->name=L"Prj_Type";
		_prj_Type->data="";
		_sub_nodes.push_back(_prj_Type);
		//Centr_long
		CNode* _centr_long;
		_centr_long= new CNode;
		_centr_long->name=L"Centr_long";
		_centr_long->data="";
		_sub_nodes.push_back(_centr_long);
		//We
		CNode* _we;
		_we= new CNode;
		_we->name=L"We";
		_we->data="";
		_sub_nodes.push_back(_we);
		//Orininal_Lat
		CNode* _orininal_lat;
		_orininal_lat= new CNode;
		_orininal_lat->name=L"Orininal_Lat";
		_orininal_lat->data="";
		_sub_nodes.push_back(_orininal_lat);
		//Ns
		CNode* _ns;
		_ns= new CNode;
		_ns->name=L"Ns";
		_ns->data="";
		_sub_nodes.push_back(_ns);
		//False_N
		CNode* _false_N;
		_false_N= new CNode;
		_false_N->name=L"False_N";
		_false_N->data="";
		_sub_nodes.push_back(_false_N);
		//False_E
		CNode* _false_E;
		_false_E= new CNode;
		_false_E->name=L"False_E";
		_false_E->data="";
		_sub_nodes.push_back(_false_E);
		//BL_sacle
		CNode* _bl_sacle;
		_bl_sacle= new CNode;
		_bl_sacle->name=L"BL_sacle";
		_bl_sacle->data="";
		_sub_nodes.push_back(_bl_sacle);
		//S_Lat
		CNode* _s_Lat;
		_s_Lat= new CNode;
		_s_Lat->name=L"S_Lat";
		_s_Lat->data="";
		_sub_nodes.push_back(_s_Lat);
		//N_Lat
		CNode* _n_Lat;
		_n_Lat= new CNode;
		_n_Lat->name=L"N_Lat";
		_n_Lat->data="";
		_sub_nodes.push_back(_n_Lat);
	}
};
//CEllipsoid80
class CEllipsoid80:public CNode
{
public:
	CEllipsoid80()
	{
		name = L"ellipsoidxian80";
		//ellip_name
		CNode* _ellip_name;
		_ellip_name=new CNode;
		_ellip_name->name=L"Ellip_Name";
		_ellip_name->data="";
		_sub_nodes.push_back(_ellip_name);
		//Major
		CNode* _major;
		_major= new CNode;
		_major->name= L"Major";
		_major->data="";
		_sub_nodes.push_back(_major);
		CNode* _minor;
		_minor= new CNode;
		_minor->name=L"Minor";
		_minor->data="";
		_sub_nodes.push_back(_minor);
		//Flatening
		CNode*  _flatening;
		_flatening= new CNode;
		_flatening->name=L"Flatening";
		_flatening->data="";
		_sub_nodes.push_back(_flatening);
		//Prj_Name
		CNode* _prj_Name;
		_prj_Name= new CNode;
		_prj_Name->name=L"Prj_Name";
		_prj_Name->data="";
		_sub_nodes.push_back(_prj_Name);
		//Prj_Type
		CNode* _prj_Type;
		_prj_Type= new CNode;
		_prj_Type->name=L"Prj_Type";
		_prj_Type->data="";
		_sub_nodes.push_back(_prj_Type);
		//Centr_long
		CNode* _centr_long;
		_centr_long= new CNode;
		_centr_long->name=L"Centr_long";
		_centr_long->data="";
		_sub_nodes.push_back(_centr_long);
		//We
		CNode* _we;
		_we= new CNode;
		_we->name=L"We";
		_we->data="";
		_sub_nodes.push_back(_we);
		//Orininal_Lat
		CNode* _orininal_lat;
		_orininal_lat= new CNode;
		_orininal_lat->name=L"Orininal_Lat";
		_orininal_lat->data="";
		_sub_nodes.push_back(_orininal_lat);
		//Ns
		CNode* _ns;
		_ns= new CNode;
		_ns->name=L"Ns";
		_ns->data="";
		_sub_nodes.push_back(_ns);
		//False_N
		CNode* _false_N;
		_false_N= new CNode;
		_false_N->name=L"False_N";
		_false_N->data="";
		_sub_nodes.push_back(_false_N);
		//False_E
		CNode* _false_E;
		_false_E= new CNode;
		_false_E->name=L"False_E";
		_false_E->data="";
		_sub_nodes.push_back(_false_E);
		//BL_sacle
		CNode* _bl_sacle;
		_bl_sacle= new CNode;
		_bl_sacle->name=L"BL_sacle";
		_bl_sacle->data="";
		_sub_nodes.push_back(_bl_sacle);
		//S_Lat
		CNode* _s_Lat;
		_s_Lat= new CNode;
		_s_Lat->name=L"S_Lat";
		_s_Lat->data="";
		_sub_nodes.push_back(_s_Lat);
		//N_Lat
		CNode* _n_Lat;
		_n_Lat= new CNode;
		_n_Lat->name=L"N_Lat";
		_n_Lat->data="";
		_sub_nodes.push_back(_n_Lat);
	}
};
//CEllipsoid2000
class CEllipsoid2000:public CNode
{
public:
	CEllipsoid2000()
	{
		name = "ellipsoidcgs2000";
		//ellip_name
		CNode* _ellip_name;
		_ellip_name=new CNode;
		_ellip_name->name=L"Ellip_Name";
		_ellip_name->data="";
		_sub_nodes.push_back(_ellip_name);
		//Major
		CNode* _major;
		_major= new CNode;
		_major->name= L"Major";
		_major->data="";
		_sub_nodes.push_back(_major);
		CNode* _minor;
		_minor= new CNode;
		_minor->name=L"Minor";
		_minor->data="";
		_sub_nodes.push_back(_minor);
		//Flatening
		CNode*  _flatening;
		_flatening= new CNode;
		_flatening->name=L"Flatening";
		_flatening->data="";
		_sub_nodes.push_back(_flatening);
		//Prj_Name
		CNode* _prj_Name;
		_prj_Name= new CNode;
		_prj_Name->name=L"Prj_Name";
		_prj_Name->data="";
		_sub_nodes.push_back(_prj_Name);
		//Prj_Type
		CNode* _prj_Type;
		_prj_Type= new CNode;
		_prj_Type->name=L"Prj_Type";
		_prj_Type->data="";
		_sub_nodes.push_back(_prj_Type);
		//Centr_long
		CNode* _centr_long;
		_centr_long= new CNode;
		_centr_long->name=L"Centr_long";
		_centr_long->data="";
		_sub_nodes.push_back(_centr_long);
		//We
		CNode* _we;
		_we= new CNode;
		_we->name=L"We";
		_we->data="";
		_sub_nodes.push_back(_we);
		//Orininal_Lat
		CNode* _orininal_lat;
		_orininal_lat= new CNode;
		_orininal_lat->name=L"Orininal_Lat";
		_orininal_lat->data="";
		_sub_nodes.push_back(_orininal_lat);
		//Ns
		CNode* _ns;
		_ns= new CNode;
		_ns->name=L"Ns";
		_ns->data="";
		_sub_nodes.push_back(_ns);
		//False_N
		CNode* _false_N;
		_false_N= new CNode;
		_false_N->name=L"False_N";
		_false_N->data="";
		_sub_nodes.push_back(_false_N);
		//False_E
		CNode* _false_E;
		_false_E= new CNode;
		_false_E->name=L"False_E";
		_false_E->data="";
		_sub_nodes.push_back(_false_E);
		//BL_sacle
		CNode* _bl_sacle;
		_bl_sacle= new CNode;
		_bl_sacle->name=L"BL_sacle";
		_bl_sacle->data="";
		_sub_nodes.push_back(_bl_sacle);
		//S_Lat
		CNode* _s_Lat;
		_s_Lat= new CNode;
		_s_Lat->name=L"S_Lat";
		_s_Lat->data="";
		_sub_nodes.push_back(_s_Lat);
		//N_Lat
		CNode* _n_Lat;
		_n_Lat= new CNode;
		_n_Lat->name=L"N_Lat";
		_n_Lat->data="";
		_sub_nodes.push_back(_n_Lat);
	}
};
class CEllipsoids_ :public CNode
{
public:
	CEllipsoids_()
	{
		name=L"ellipsoids";
		CEllipsoid54 * sub_node1;		
		sub_node1 = new CEllipsoid54;	   
		_sub_nodes.push_back(sub_node1);

		CEllipsoid80 * sub_node2;		
		sub_node2 = new CEllipsoid80;	   
		_sub_nodes.push_back(sub_node2);

		CEllipsoid2000 * sub_node3;		
		sub_node3 = new CEllipsoid2000;	   
		_sub_nodes.push_back(sub_node3);	

	}
};
class CDY :public CNode
{
public:
	CDY()
	{
		name=L"dy";
		CEllipsoids_ * sub_node1;		
		sub_node1 = new CEllipsoids_;	   
		_sub_nodes.push_back(sub_node1);

	}
};

class CUnits:public CNode
{
public:
	CUnits()
	{
		name = L"Units";
	}
};
#endif

class CXmlOperate
{
public:
	CNode* m_node;
public:

	void LoadFileold(CString FileName);

	void LoadFile(CString FileName);//╪стьнд╪Ч

	void LoadNode(CNode* node);
	
	void fill(CNode* node);

	void query(CString NodeName,CNode* Node);
	
	void add(CNode* node);
	
	void _delete(CString id);
	
	void New(CString filename);

	void CreateFile(CString strFileName,CNode *Node);
	
	void Save();

	void  flush();

private:
	CMarkup xml;
	CString m_filename;
};