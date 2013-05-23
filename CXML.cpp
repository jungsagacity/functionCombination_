#include "CXML.H"
#include "CStringProcess.H"
#include "CPatentStruct.H"
#include "xmill/CXMILL.h"
#include <iostream>
using namespace std;

/*
	����	��	Create
	����	��	����xml�ļ�����ʽ��ר����Ϣ�������й���������ŷ�޵�ר��
	����	��	{string txtFile}����Ĵ������txt�ļ�������·��������, �ļ�������ʱ�䡢���ݿ����ƺͲ������磺 "F:\\@_@cn@2012.5.21@databaseName@insert.txt
	����	��	void
	
	����	��	���
	�޸�	��	{2013.5.20} ��һ�δ���

*/
void CXML::Create(string txtFile)
{
	
	string xmlFile = txtFile;//���ɵ�XML�ļ�������·��������,��ʼ��ΪtxtFile
	int dotPos = 0;
	dotPos = txtFile.rfind('.', txtFile.npos);
	xmlFile.replace(dotPos+1, 3, "xml");//�޸ĺ�׺��

	ifstream ifile;//txt�ļ���
	try
	{
		ifile.open(txtFile.c_str(),ios::in);
	}catch(...)
	{
		CXML::m_iStatus = CXMLStatus::CREATE_FAILED;//��txt�ļ�ʧ�ܣ����ʶ����xml�ļ�ʧ��
		return;
	}
	
	 
	int slashPos	= txtFile.find("@_@", 0)+3;// ָʾ����'@_@'��ĩ��ַ
	if( slashPos == txtFile.npos)
	{
		return;
	}
	string txtFileName = txtFile.substr(slashPos, dotPos-slashPos);	
	vector<string> sqlInfo = CStringProcess::split(txtFileName, "@");//��ȡ����ʱ�䡢�������ݿ⡢������Ϊ {0:ר������1:����ʱ�䣬2�����µ����ݿ⣬3��������Ϊ}
	
	string country = sqlInfo.at(0);	
	string date = sqlInfo.at(1);
	string database = sqlInfo.at(2);
	string action = sqlInfo.at(3).substr(0,-3);


    TiXmlDocument *myDocument = new TiXmlDocument();//����һ��XML���ĵ�����
    
    TiXmlElement *databaseElement = new TiXmlElement("DATABASE"); //����һ����Ԫ��<DATABASE>�����ӡ�
	databaseElement->SetAttribute("name",database.c_str());
	myDocument->LinkEndChild(databaseElement);	

	TiXmlElement *dateElement = new TiXmlElement("DATE");//����һ����Ԫ��<DATE>�����ӡ�
	databaseElement->LinkEndChild(dateElement);	
	TiXmlText *dateContent = new TiXmlText(date.c_str());
	dateElement->LinkEndChild(dateContent);

	TiXmlElement *sqlElement = new TiXmlElement("ACTION");//����һ����Ԫ��<ACTION>�����ӡ�
	databaseElement->LinkEndChild(sqlElement);
	TiXmlText *sqlContent = new TiXmlText(action.c_str());
	sqlElement->LinkEndChild(sqlContent);	

	TiXmlElement *patents = new TiXmlElement("PATENTS");//����һ����Ԫ��<PATENTS>�����ӡ�
	databaseElement->LinkEndChild(patents);
	
	

	//�������ݵĹ���ʵ����һ��ר�����ݽṹ����
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
        string lineContent;//���txt�ļ��е�ÿһ��
		while(getline(ifile,lineContent))//��ȡtxt�ļ���ÿһ��
		{
			TiXmlElement *PatentElement = new TiXmlElement("PATENTELEMENT");//����ÿһ��ר����Ϣ
			patents->LinkEndChild(PatentElement);

			vector<string> patentInfo = CStringProcess::split(lineContent,"\t","");//��ÿ�н��зָ�γ�ר����ϸ��Ϣ
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
		CXML::m_iStatus = CXMLStatus::CREATE_FAILED;//��ȡtxt�ļ�ʧ��
		return ;
    }
	try
	{
		myDocument->SaveFile(xmlFile.c_str());//���浽xml�ļ�
	}catch(...)
	{
		CXML::m_iStatus = CXMLStatus::CREATE_FAILED;//����xml�ļ�ʧ��
		return;
	}
	

	CXML::m_iStatus = CXMLStatus::CREATE_SUCCESS;//����xml����ִ�гɹ�
	CXML::m_strDesFileName.createFile = xmlFile;
    return ;

}



/*
	����	��	Parser
	����	��	����xml�ļ�
	����	��	{string xmlFile}����Ĵ������xml�ļ�
	����	��	void
	
	����	��	���
	�޸�	��	{2013.5.20} ��һ�δ���

*/
void CXML::Parser(string xmlFile)
{
	string txtFile = xmlFile;//���ɵ�XML�ļ�������·��������,��ʼ��ΪtxtFile
	int dotPos = 0;
	dotPos = txtFile.rfind('.', txtFile.npos);
	txtFile.replace(dotPos+1, 3, "txt");//�޸ĺ�׺��

	
	ofstream ofile;//��xml�ļ��н����������д��txt�ļ�
	try
	{		
		ofile.open(txtFile.c_str());
	}catch(...)
	{
		CXML::m_iStatus = CXMLStatus::PARSER_FAILED;//����txt�ļ�ʧ��
		return;
	}


	 TiXmlDocument *myDocument = new TiXmlDocument();//����һ��XML���ĵ�����
	 try
	 {
		myDocument->LoadFile(xmlFile.c_str(),TIXML_DEFAULT_ENCODING) ;
	 }catch(...)
	 {
		CXML::m_iStatus = CXMLStatus::PARSER_FAILED;//����xml�ļ�ʧ��
		return;
	 }

	 TiXmlElement *databaseElement = myDocument->RootElement();//<DATABASE> ���ڵ�
	 
	 TiXmlElement *patents = databaseElement->FirstChildElement()->NextSiblingElement()->NextSiblingElement();//<PATENTS> �ڵ�
	 TiXmlElement *patentElement = patents->FirstChildElement();//<PATENTELEMENT> �ڵ�
	 while(patentElement)
	 {
		TiXmlElement* item = patentElement->FirstChildElement();  //���ĳ��ר���ĸ����ֶ�ֵ
		while(item)
		{			
			const char * text = item->GetText();
			if(!text)//����ֶ���ϢΪ�գ�������"\t"
			{
				ofile<<"\t";//����ڵ�û���κ����ݣ�ֱ������text�������κ��жϵĻ����ᵼ��д�ļ�������Ϊtextָ����ǵ�ַ0x0,ϵͳ�޷���ȡ�õ�ַָ�������
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
	CXML::m_iStatus = CXMLStatus::PARSER_SUCCESS;//����xml�ļ�ʧ��
	CXML::m_strDesFileName.parserFile = txtFile;	
	return;

}


/*
	����	��	AESEncrypt
	����	��	����xml�ļ�
	����	��	{string sFile}����Ĵ������xml�ļ�
			{int keySize} ��Կ���ȣ���ȡ16��24��48��Ĭ��Ϊ16
	����	��	void
	
	����	��	���
	�޸�	��	{2013.5.20} ��һ�δ���

*/
void CXML::AESEncrypt(string sFile, string key, int keySize)
{
	
	CRijndael encrypt; 
	encrypt.SetNrNk(keySize);//������Կ����	
	CString ckey=key.c_str();
    encrypt.SetKey(ckey);//������Կ
	

	int dotPos = 0;
	dotPos = sFile.rfind('.', sFile.npos);
	string encryptFile = sFile;
	encryptFile.replace(dotPos+1, 3, "aes");//�޸ĺ�׺��Ϊaes	
	encrypt.SetFileName(sFile.c_str(),encryptFile.c_str());//���ü��ܺ��ļ���

	try
	{
		encrypt.EncrypFile();//���ܹ��̷�װ
	}catch(...)
	{
		CXML::m_iStatus = CXMLStatus::ENCRYPT_FAILED;//����ʧ��
		return;
	}

	CXML::m_iStatus = CXMLStatus::ENCRYPT_SUCCESS;//���ܳɹ�
	CXML::m_strDesFileName.encryptFile = encryptFile;
	return;
	

}


/*
	����	��	AESDencrypt
	����	��	����aes�ļ�������xmi�ļ�
	����	��	{string sFile}����Ĵ������aes�ļ�
			{int keySize} ��Կ���ȣ���ȡ16��24��48��Ĭ��Ϊ16
	����	��	void
	
	����	��	���
	�޸�	��	{2013.5.20} ��һ�δ���

*/
void CXML::AESDencrypt(string sFile, string key, int keySize)
{
	
	CRijndael dencrypt; 
	dencrypt.SetNrNk(keySize);//������Կ����	
	CString ckey=key.c_str();
    dencrypt.SetKey(ckey);//������Կ
	

	int dotPos = 0;
	dotPos = sFile.rfind('.', sFile.npos);
	string dencryptFile = sFile;
	dencryptFile.replace(dotPos+1, 3, "xmi");//�޸ĺ�׺��Ϊxmi	
	dencrypt.SetFileName(sFile.c_str(),dencryptFile.c_str());//���ü��ܺ��ļ���

	try
	{
		dencrypt.DecrypFile();//���ܹ��̷�װ
	}catch(...)
	{
		CXML::m_iStatus = CXMLStatus::DENCRYPT_FAILED;//����ʧ��
		return;
	}

	CXML::m_iStatus = CXMLStatus::DENCRYPT_SUCCESS;//���ܳɹ�
	CXML::m_strDesFileName.dencryptFile = dencryptFile;
	return;
	

}

/*
	����	��	Compress
	����	��	ѹ��xml�ļ����ļ���Ҫ��.xml��Ϊ��׺��������xmi�ļ���
	����	��	{string xmlFile}����Ĵ������xml�ļ�
			
	����	��	void
	
	����	��	���
	�޸�	��	{2013.5.20} ��һ�δ���

*/
void CXML::Compress(string xmlFile)
{	
	const char *fileTemp = xmlFile.c_str();
	int len = strlen(fileTemp);
	if( len == 0 )
	{
		CXML::m_iStatus = CXMLStatus::COMPRESS_FAILED;//ѹ��ʧ��
		return;
	}
	
	char * fileName = new char[len];
	strcpy(fileName, fileTemp);
	HandleSingleFile(fileName,0);//0:ѹ��

	string xmiFile = xmlFile;//���ɵ�XML�ļ�������·��������,��ʼ��ΪtxtFile
	int dotPos = 0;
	dotPos = xmiFile.rfind('.', xmiFile.npos);
	xmiFile.replace(dotPos+1, 3, "xmi");//�޸ĺ�׺��

	CXML::m_iStatus = CXMLStatus::COMPRESS_SUCCESS;//ѹ���ɹ�
	CXML::m_strDesFileName.compressFile = xmiFile;
	return;
}


/*
	����	��	Uncompress
	����	��	��ѹ��xmi�ļ����ļ���Ҫ��.xmi��Ϊ��׺��������xml�ļ���
	����	��	{string xmiFile}����Ĵ������aes�ļ�
			
	����	��	void
	
	����	��	���
	�޸�	��	{2013.5.20} ��һ�δ���

*/
void CXML::Uncompress(string xmiFile)
{	
	const char *fileTemp = xmiFile.c_str();
	int len = strlen(fileTemp);
	if( len == 0 )
	{
		CXML::m_iStatus = CXMLStatus::UNCOMPRESS_FAILED;//ѹ��ʧ��
		return;
	}
	
	char * fileName = new char[len];
	strcpy(fileName, fileTemp);
	HandleSingleFile(fileName,1);//1:ѹ��

	string xmlFile = xmiFile;//���ɵ�XML�ļ�������·��������,��ʼ��ΪtxtFile
	int dotPos = 0;
	dotPos = xmlFile.rfind('.', xmlFile.npos);
	xmlFile.replace(dotPos+1, 3, "xml");//�޸ĺ�׺��

	CXML::m_iStatus = CXMLStatus::UNCOMPRESS_SUCCESS;//ѹ���ɹ�
	CXML::m_strDesFileName.uncompressFile = xmlFile;
	return;
}

/*
	����	��	GetDesFile
	����	��	�������ɵ��ļ���
	����	��	
	����	��	{desFileName} ���ɵ��ļ����ṹ��
	
	����	��	���
	�޸�	��	{2013.5.20} ��һ�δ���

*/
strDesFileName CXML::GetDesFileName()
{	
	return CXML::m_strDesFileName;
}


/*
	����	��	GetStatus
	����	��	����XML�ļ�����״̬
	����	��	
	����	��	{int} XML�ļ�����״̬
	
	����	��	���
	�޸�	��	{2013.5.20} ��һ�δ���

*/
int CXML::GetStatus()
{	
	return CXML::m_iStatus;
}
