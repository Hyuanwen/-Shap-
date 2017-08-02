#include "StdAfx.h"
#include "Node.h"
#include "DeuGlobal.h"

CNode::CNode(void)
{
	ele_name = "noname";
}

CNode::~CNode(void)
{
	DestroySubNodes();
}

void CNode::DestroySubNodes()
{

	std::list<CNode*>::iterator it;
	for(it = _sub_nodes.begin();it!=_sub_nodes.end();it++)
	{
		CNode* p = *it;
		delete p;
	}

	return;
}

CNode *CNode::Clone()
{
	CNode *clone = new CNode;

	clone->parent = NULL ;

	clone->ele_name = this->ele_name;

	clone->tag_name = this->tag_name;

	clone->data = this->data;

	//////////////////////////////////////////////////////////////////////////
	//fill list
	
	LIST_IT(CNode*) it = this->_sub_nodes.begin();

	for (;it != this->_sub_nodes.end(); it++)
	{
		CNode * sub_clone = (*it)->Clone();

		clone->_sub_nodes.push_back(sub_clone);
	}
	
	return clone;

}


//////////////////////////////////////////////////////////////////////////

void CXmlOperate::LoadFile(CString FileName)
{
	m_filename=FileName;
	BOOL bLoad = false; 
	bLoad=xml.Load(m_filename); 
	xml.ResetMainPos();


	//bool res;
	//res=xml.FindElem();
	//res=xml.FindElem();

	return;
}

void CXmlOperate::LoadFileold(CString FileName)
{
	m_filename=FileName;
	BOOL bLoad = false; 
	bLoad=xml.Load(m_filename); 
	xml.ResetMainPos();

	xml.IntoElem();
	xml.FindElem();

	//bool res;
	//res=xml.FindElem();
	//res=xml.FindElem();

	return;
}

void CXmlOperate::CreateFile(CString strFileName,CNode *Node)
{
	m_filename=strFileName;
	BOOL bLoad = false; 
	bLoad=xml.Load(m_filename); 
	xml.ResetMainPos();

	xml.IntoElem();
	xml.FindElem();
	xml.RemoveElem();

	xml.ResetPos();

	//DeuXML头	
	//xml.AddElem(L"Deu","");
	//xml.AddAttrib(L"d",L"Deu");
	xml.IntoElem();
	
	add(Node);

	return;
}

void CXmlOperate::add(CNode* node)	//曹欣
{		
	//加自己
	xml.AddElem(node->tag_name,node->data);
	xml.AddAttrib("type",node->tag_name);
	xml.AddAttrib("name",node->ele_name);
	xml.IntoElem();
	//有子节点就添加
	CNode* sub_node;
	for (int i=0;i<node->_sub_nodes.size();i++)
	{
		sub_node=getListItem(node->_sub_nodes,i);
		add(sub_node);
	}		
	xml.OutOfElem();
	return;	
}

void CXmlOperate::LoadNode(CNode* node)
{
	xml.IntoElem(); 
	CString _attrib;
	CString _data;
	CString _TagName;
	while(xml.FindElem()==true)
	{

		_TagName = xml.GetTagName();
		_attrib=xml.GetAttrib("name");
		_data=xml.GetData();
		/*CNode* sub_node=new CNode;*/
		node->tag_name=_TagName;
		node->ele_name=_attrib;
		node->data=_data;


		fill(node);

	}
	xml.OutOfElem();
}

void CXmlOperate::fill(CNode* node)
{//前提指针指向这个node
	xml.IntoElem();
	CString _attrib;
	CString _data;
	CString _TagName;
	while(xml.FindElem()==true)
	{

		_TagName = xml.GetTagName();
		_attrib=xml.GetAttrib("name");
		_data=xml.GetData();
		CNode* sub_node=new CNode;
		sub_node->tag_name=_TagName;
		sub_node->ele_name=_attrib;
		sub_node->data=_data;
		node->_sub_nodes.push_back(sub_node);

		fill(sub_node);

	}

	xml.OutOfElem();
}

void CXmlOperate::query(CString NodeName,CNode* Node)
{		
	CString strID = ""; 
	CString strNAME = ""; 
	//xml.IntoElem(); 
	//xml.FindElem();
	//strID=xml.GetAttrib("d");
	xml.IntoElem();
	//获得自己
	if(xml.FindElem(NodeName)==false )
	{//找不到
		Node=NULL;
		return ;
	}
	strID=xml.GetAttrib("d");
	Node->data=xml.GetData();

	int _size=Node->_sub_nodes.size();
	for (int i=0;i<Node->_sub_nodes.size();i++)
	{
		CNode* p=getListItem(Node->_sub_nodes,i);

		query(p->ele_name,getListItem(Node->_sub_nodes,i));			
	}		
	xml.OutOfElem();
	strID=xml.GetAttrib("d");
	return;
}



void CXmlOperate::_delete(CString id)
{
	BOOL bLoad = false;
	BOOL bFind = false ;
	bLoad = xml.Load("C:\\myxml.xml"); 
	if (bLoad)
	{
		CString strID = ""; 
		xml.ResetMainPos();
		xml.FindElem("Angularunits");

		while (xml.FindChildElem("id")) 
		{ 
			strID = xml.GetChildData(); 
			if (strID== id) 
			{ 
				xml.RemoveChildElem(); 
				xml.Save("C:\\myxml.xml"); 
				break; 
			} 
		}
	}
	return;
}

void CXmlOperate::New(CString filename)
{
	m_filename=filename;
	CString doc="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
	xml.SetDoc(doc);
	xml.AddElem("dy");
	xml.IntoElem();
}

void CXmlOperate::Save()
{
	xml.Save(m_filename);
}

void  CXmlOperate::flush()
{
	xml.Save(m_filename);
}