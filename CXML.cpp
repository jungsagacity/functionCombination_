#include "CXML.H"
#include "CStringProcess.H"
#include "CPatentStruct.H"
#include "xmill/CXMILL.h"
#include <iostream>
using namespace std;

/*
	方法	：	Create
	功能	：	创建xml文件，格式化专利信息，包括中国、美国和欧洲的专利
	参数	：	{string txtFile}输入的待处理的txt文件，包括路径和名称, 文件名包括时间、数据库名称和操作，如： "F:\\@_@cn@2012.5.21@databaseName@insert.txt
	返回	：	void
	
	作者	：	吴军
	修改	：	{2013.5.20} 第一次创建

*/
void CXML::Create(string txtFile)
{
	
	string xmlFile = txtFile;//生成的XML文件，包括路径和名称,初始化为txtFile
	int dotPos = 0;
	dotPos = txtFile.rfind('.', txtFile.npos);
	xmlFile.replace(dotPos+1, 3, "xml");//修改后缀名

	ifstream ifile;//txt文件流
	try
	{
		ifile.open(txtFile.c_str(),ios::in);
	}catch(...)
	{
		CXML::m_iStatus = CXMLStatus::CREATE_FAILED;//打开txt文件失败，则标识创建xml文件失败
		return;
	}
	
	 
	int slashPos	= txtFile.find("@_@", 0)+3;// 指示的是'@_@'的末地址
	if( slashPos == txtFile.npos)
	{
		return;
	}
	string txtFileName = txtFile.substr(slashPos, dotPos-slashPos);	
	vector<string> sqlInfo = CStringProcess::split(txtFileName, "@");//获取更新时间、更新数据库、操作行为 {0:专利国别，1:更新时间，2：更新的数据库，3：操作行为}
	
	string country = sqlInfo.at(0);	
	string date = sqlInfo.at(1);
	string database = sqlInfo.at(2);
	string action = sqlInfo.at(3).substr(0,-3);


    TiXmlDocument *myDocument = new TiXmlDocument();//创建一个XML的文档对象
    
    TiXmlElement *databaseElement = new TiXmlElement("DATABASE"); //创建一个根元素<DATABASE>并连接。
	databaseElement->SetAttribute("name",database.c_str());
	myDocument->LinkEndChild(databaseElement);	

	TiXmlElement *dateElement = new TiXmlElement("DATE");//创建一个根元素<DATE>并连接。
	databaseElement->LinkEndChild(dateElement);	
	TiXmlText *dateContent = new TiXmlText(date.c_str());
	dateElement->LinkEndChild(dateContent);

	TiXmlElement *sqlElement = new TiXmlElement("ACTION");//创建一个根元素<ACTION>并连接。
	databaseElement->LinkEndChild(sqlElement);
	TiXmlText *sqlContent = new TiXmlText(action.c_str());
	sqlElement->LinkEndChild(sqlContent);	

	TiXmlElement *patents = new TiXmlElement("PATENTS");//创建一个根元素<PATENTS>并连接。
	databaseElement->LinkEndChild(patents);
	
	

	//根据数据的国别实例化一个专利数据结构变量
	CPatentStruct *ps;
	if( !country.compare("cn"))
	{
		ps = new CPatentStruct('C');
	}else
	{
		ps = new CPatentStruct('A');	
	}


	try
    {
        string lineContent;//存放txt文件中的每一行
		while(getline(ifile,lineContent))//读取txt文件的每一行
		{
			TiXmlElement *PatentElement = new TiXmlElement("PATENTELEMENT");//保存每一条专利信息
			patents->LinkEndChild(PatentElement);

			vector<string> patentInfo = CStringProcess::split(lineContent,"\t","");//对每行进行分割，形成专利详细信息
			vector<string>::iterator it = patentInfo.begin(), end = patentInfo.end();
			
			for(int i=0;it != end,i<40;i++)
			{				
				TiXmlElement *PatentItem = new TiXmlElement(ps->patentStruct.at(i).c_str());
				PatentElement->LinkEndChild(PatentItem);
				TiXmlText *PatentItemContent = new TiXmlText((*it).c_str());
				PatentItem->LinkEndChild(PatentItemContent);
				it++;
				
			}		
		}
    }
    catch (...)
    {
		CXML::m_iStatus = CXMLStatus::CREATE_FAILED;//读取txt文件失败
		return ;
    }
	try
	{
		myDocument->SaveFile(xmlFile.c_str());//保存到xml文件
	}catch(...)
	{
		CXML::m_iStatus = CXMLStatus::CREATE_FAILED;//创建xml文件失败
		return;
	}
	

	CXML::m_iStatus = CXMLStatus::CREATE_SUCCESS;//创建xml命令执行成功
	CXML::m_strDesFileName.createFile = xmlFile;
    return ;

}



/*
	方法	：	Parser
	功能	：	解析xml文件
	参数	：	{string xmlFile}输入的待处理的xml文件
	返回	：	void
	
	作者	：	吴军
	修改	：	{2013.5.20} 第一次创建

*/
void CXML::Parser(string xmlFile)
{
	string txtFile = xmlFile;//生成的XML文件，包括路径和名称,初始化为txtFile
	int dotPos = 0;
	dotPos = txtFile.rfind('.', txtFile.npos);
	txtFile.replace(dotPos+1, 3, "txt");//修改后缀名

	
	ofstream ofile;//将xml文件中解析后的内容写进txt文件
	try
	{		
		ofile.open(txtFile.c_str());
	}catch(...)
	{
		CXML::m_iStatus = CXMLStatus::PARSER_FAILED;//创建txt文件失败
		return;
	}


	 TiXmlDocument *myDocument = new TiXmlDocument();//创建一个XML的文档对象
	 try
	 {
		myDocument->LoadFile(xmlFile.c_str(),TIXML_DEFAULT_ENCODING) ;
	 }catch(...)
	 {
		CXML::m_iStatus = CXMLStatus::PARSER_FAILED;//加载xml文件失败
		return;
	 }

	 TiXmlElement *databaseElement = myDocument->RootElement();//<DATABASE> 根节点
	 
	 TiXmlElement *patents = databaseElement->FirstChildElement()->NextSiblingElement()->NextSiblingElement();//<PATENTS> 节点
	 TiXmlElement *patentElement = patents->FirstChildElement();//<PATENTELEMENT> 节点
	 while(patentElement)
	 {
		TiXmlElement* item = patentElement->FirstChildElement();  //获得某条专利的各个字段值
		while(item)
		{			
			const char * text = item->GetText();
			if(!text)//如果字段信息为空，则输入"\t"
			{
				ofile<<"\t";//如果节点没有任何内容，直接输入text而不做任何判断的话，会导致写文件错误，因为text指向的是地址0x0,系统无法读取该地址指向的内容
			}else
			{
				ofile<< text << "\t";
			}		
			
			item = item->NextSiblingElement();
		}
		ofile<< "\n";		 
		patentElement = patentElement->NextSiblingElement();
	 }

	ofile.close();
	CXML::m_iStatus = CXMLStatus::PARSER_SUCCESS;//加载xml文件失败
	CXML::m_strDesFileName.parserFile = txtFile;	
	return;

}


/*
	方法	：	AESEncrypt
	功能	：	加密xml文件
	参数	：	{string sFile}输入的待处理的xml文件
			{int keySize} 密钥长度，可取16，24，48，默认为16
	返回	：	void
	
	作者	：	吴军
	修改	：	{2013.5.20} 第一次创建

*/
void CXML::AESEncrypt(string sFile, string key, int keySize)
{
	
	CRijndael encrypt; 
	encrypt.SetNrNk(keySize);//设置密钥轮数	
	CString ckey=key.c_str();
    encrypt.SetKey(ckey);//设置密钥
	

	int dotPos = 0;
	dotPos = sFile.rfind('.', sFile.npos);
	string encryptFile = sFile;
	encryptFile.replace(dotPos+1, 3, "aes");//修改后缀名为aes	
	encrypt.SetFileName(sFile.c_str(),encryptFile.c_str());//设置加密后文件名

	try
	{
		encrypt.EncrypFile();//加密过程封装
	}catch(...)
	{
		CXML::m_iStatus = CXMLStatus::ENCRYPT_FAILED;//加密失败
		return;
	}

	CXML::m_iStatus = CXMLStatus::ENCRYPT_SUCCESS;//加密成功
	CXML::m_strDesFileName.encryptFile = encryptFile;
	return;
	

}


/*
	方法	：	AESDencrypt
	功能	：	解密aes文件，生成xmi文件
	参数	：	{string sFile}输入的待处理的aes文件
			{int keySize} 密钥长度，可取16，24，48，默认为16
	返回	：	void
	
	作者	：	吴军
	修改	：	{2013.5.20} 第一次创建

*/
void CXML::AESDencrypt(string sFile, string key, int keySize)
{
	
	CRijndael dencrypt; 
	dencrypt.SetNrNk(keySize);//设置密钥轮数	
	CString ckey=key.c_str();
    dencrypt.SetKey(ckey);//设置密钥
	

	int dotPos = 0;
	dotPos = sFile.rfind('.', sFile.npos);
	string dencryptFile = sFile;
	dencryptFile.replace(dotPos+1, 3, "xmi");//修改后缀名为xmi	
	dencrypt.SetFileName(sFile.c_str(),dencryptFile.c_str());//设置加密后文件名

	try
	{
		dencrypt.DecrypFile();//解密过程封装
	}catch(...)
	{
		CXML::m_iStatus = CXMLStatus::DENCRYPT_FAILED;//加密失败
		return;
	}

	CXML::m_iStatus = CXMLStatus::DENCRYPT_SUCCESS;//加密成功
	CXML::m_strDesFileName.dencryptFile = dencryptFile;
	return;
	

}

/*
	方法	：	Compress
	功能	：	压缩xml文件（文件需要以.xml做为后缀），生成xmi文件，
	参数	：	{string xmlFile}输入的待处理的xml文件
			
	返回	：	void
	
	作者	：	吴军
	修改	：	{2013.5.20} 第一次创建

*/
void CXML::Compress(string xmlFile)
{	
	const char *fileTemp = xmlFile.c_str();
	int len = strlen(fileTemp);
	if( len == 0 )
	{
		CXML::m_iStatus = CXMLStatus::COMPRESS_FAILED;//压缩失败
		return;
	}
	
	char * fileName = new char[len];
	strcpy(fileName, fileTemp);
	HandleSingleFile(fileName,0);//0:压缩

	string xmiFile = xmlFile;//生成的XML文件，包括路径和名称,初始化为txtFile
	int dotPos = 0;
	dotPos = xmiFile.rfind('.', xmiFile.npos);
	xmiFile.replace(dotPos+1, 3, "xmi");//修改后缀名

	CXML::m_iStatus = CXMLStatus::COMPRESS_SUCCESS;//压缩成功
	CXML::m_strDesFileName.compressFile = xmiFile;
	return;
}


/*
	方法	：	Uncompress
	功能	：	解压缩xmi文件（文件需要以.xmi做为后缀），生成xml文件，
	参数	：	{string xmiFile}输入的待处理的aes文件
			
	返回	：	void
	
	作者	：	吴军
	修改	：	{2013.5.20} 第一次创建

*/
void CXML::Uncompress(string xmiFile)
{	
	const char *fileTemp = xmiFile.c_str();
	int len = strlen(fileTemp);
	if( len == 0 )
	{
		CXML::m_iStatus = CXMLStatus::UNCOMPRESS_FAILED;//压缩失败
		return;
	}
	
	char * fileName = new char[len];
	strcpy(fileName, fileTemp);
	HandleSingleFile(fileName,1);//1:压缩

	string xmlFile = xmiFile;//生成的XML文件，包括路径和名称,初始化为txtFile
	int dotPos = 0;
	dotPos = xmlFile.rfind('.', xmlFile.npos);
	xmlFile.replace(dotPos+1, 3, "xml");//修改后缀名

	CXML::m_iStatus = CXMLStatus::UNCOMPRESS_SUCCESS;//压缩成功
	CXML::m_strDesFileName.uncompressFile = xmlFile;
	return;
}

/*
	方法	：	GetDesFile
	功能	：	返回生成的文件名
	参数	：	
	返回	：	{desFileName} 生成的文件名结构体
	
	作者	：	吴军
	修改	：	{2013.5.20} 第一次创建

*/
strDesFileName CXML::GetDesFileName()
{	
	return CXML::m_strDesFileName;
}


/*
	方法	：	GetStatus
	功能	：	返回XML文件处理状态
	参数	：	
	返回	：	{int} XML文件处理状态
	
	作者	：	吴军
	修改	：	{2013.5.20} 第一次创建

*/
int CXML::GetStatus()
{	
	return CXML::m_iStatus;
}
