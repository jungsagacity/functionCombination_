#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "tinyXML/tinyxml.h"
#include "AES/stdafx.h"
#include "AES/CRijndael.h"
#include <afxmt.h>
#include "xmill/Main.hpp"
using namespace std;

vector<string> split(const string& src, string delimit, string null_subst="")
{
	if(src.empty() || delimit.empty())
	{
		throw "split or delimit empty.";
	}

	vector<string> v;
	int delimit_len = delimit.size();
	long index = -1, last_search_position = 0;

	while((index = src.find( delimit, last_search_position )) != string::npos)
	{
		if( index == last_search_position )
		{
			v.push_back(null_subst);
		}else
		{
			string substring = src.substr(last_search_position, index - last_search_position);
			v.push_back(substring);			
		}

		last_search_position = index + delimit_len;

	}

	string last_substring = src.substr(last_search_position);

	v.push_back( last_substring.empty() ? null_subst : last_substring);

	return v;
}

bool CreateXmlFile(string& txtFileName, string& xmlFileName)
{//����xml�ļ�,szFilePathΪ�ļ������·��,�������ɹ�����true,����false
    
	ifstream ifile;
	ifile.open(txtFileName.c_str(),ios::in);

	//����һ��XML���ĵ�����
    TiXmlDocument *myDocument = new TiXmlDocument();
    //����һ����Ԫ�ز����ӡ�
    TiXmlElement *databaseElement = new TiXmlElement("database"); 
	databaseElement->SetAttribute("name","chinapatent");
	myDocument->LinkEndChild(databaseElement);	

	TiXmlElement *dateElement = new TiXmlElement("date");
	databaseElement->LinkEndChild(dateElement);	
	TiXmlText *dateContent = new TiXmlText("2013.5.11");
	dateElement->LinkEndChild(dateContent);

	TiXmlElement *sqlElement = new TiXmlElement("SQL");
	databaseElement->LinkEndChild(sqlElement);
	TiXmlText *sqlContent = new TiXmlText("insert");
	sqlElement->LinkEndChild(sqlContent);

	TiXmlElement *tableElement = new TiXmlElement("tableName");
	databaseElement->LinkEndChild(tableElement);
	tableElement->SetAttribute("name","computer");

	try
    {
        string lineContent;
		//while(getline(ifile,lineContent))
		//{
		//	
		//	vector<string> patentInfo = split(lineContent,"\t","");
		//	vector<string>::iterator it = patentInfo.begin(), end = patentInfo.end();
		//	TiXmlElement *PatentElement = new TiXmlElement("patentElement");
		//	RootElement->LinkEndChild(PatentElement);
		//	while(it != end)
		//	{				
		//		TiXmlElement *PatentItem = new TiXmlElement("item");
		//		PatentElement->LinkEndChild(PatentItem);
		//		TiXmlText *PatentItemContent = new TiXmlText((*it).c_str());
		//		PatentItem->LinkEndChild(PatentItemContent);
		//		it++;
		//		
		//	}		
		//}
		while(getline(ifile,lineContent))
		{			
			TiXmlElement *PatentElement = new TiXmlElement("patentElement");
			TiXmlText *PatentItemContent = new TiXmlText(lineContent.c_str());
			
			PatentElement->LinkEndChild(PatentItemContent);
			tableElement->LinkEndChild(PatentElement);
				
		}
		myDocument->SaveFile(xmlFileName.c_str());//���浽�ļ�

    }
    catch (string& e)
    {
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{


	//const char* demoStart =
	//	"<?xml version=\"1.0\"  standalone='no' >\n"
	//	"<!-- Our to do list data -->"
	//	"<ToDo>\n"
	//	"<!-- Do I need a secure PDA? -->\n"
	//	"<Item priority=\"1\" distance='close'> Go to the <bold>Toy store!</bold></Item>"
	//	"<Item priority=\"2\" distance='none'> Do bills   </Item>"
	//	"<Item priority=\"2\" distance='far &amp; back'> Look for Evil Dinosaurs! </Item>"
	//	"<jun>12</jun>"
	//	"</ToDo>";


	//	//--------------------------------------------------------------------------------------
	//	// Write to a file and read it back, to check file I/O.

	//	TiXmlDocument doc( "d:\\1.xml" );
	//	doc.Parse( demoStart );

	//	if ( doc.Error() )
	//	{
	//		printf( "Error in %s: %s\n", doc.Value(), doc.ErrorDesc() );
	//		exit( 1 );
	//	}
	//	doc.SaveFile();
	//	

	//����xml�ĵ�
	string src = "f:\\patentTest.txt";
	string des = "f:\\patentTest.xml";
	CreateXmlFile(src,des);

	//ѹ��xml�ĵ�
	try
	{

		globallabeldict.Init(); // Initialized the label dictionary
		FSMInit();
		char *pathptr="//#";
		pathexprman.AddNewVPathExpr(pathptr,pathptr+strlen(pathptr));
		pathptr="/";
		pathexprman.AddNewVPathExpr(pathptr,pathptr+strlen(pathptr));
		globallabeldict.FinishedPredefinedLabels();
		pathexprman.InitWhitespaceHandling();

	}
	catch(XMillException *)     
	{
      return -1;
	}
	HandleSingleFile("f:\\patentTest.xml",0);//0:ѹ��


	
	//�мǲ�����ͬһ��ʵ�����м��ܺͽ���
	CRijndael aes_en;
	CRijndael aes_den;
    int keysize=16;  //16,24,48�ֽڣ���Կ����
	aes_en.SetNrNk(keysize);
	aes_den.SetNrNk(keysize);
	CString m_key="12345678";
    aes_en.SetKey(m_key);
	aes_den.SetKey(m_key);

	////����
    CString SFileName="f:\\patentTest.xmi";
	CString TFileName="f:\\patentTest.aes";
    aes_en.SetFileName(SFileName,TFileName);
	aes_en.EncrypFile();




	////����
	CString _SFileName="f:\\patentTest.aes";
	CString _TFileName="f:\\patentTest_.xmi";
    aes_den.SetFileName(_SFileName,_TFileName);
	aes_den.DecrypFile();
	
	//��ѹ��
	HandleSingleFile("f:\\patentTest_.xmi",1);//1:��ѹ��



	return 0;
}