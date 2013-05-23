#ifndef CXML_H
#define CXML_H
#include "stdafx.h"

#include <iostream>
#include <sstream>

#include <fstream>
#include <string>
#include <vector>
#include <afxmt.h>
#include "tinyXML/tinyxml.h"
#include "AES/CRijndael.h"



using namespace std;

 
//处理XML过程中生成的文件名
typedef struct
{
	string createFile;		//由txt生成的xml文件的文件名
	string parserFile;		//xml解析后生成的txt文件的文件名
	string encryptFile;		//加密后生成的文件名
	string dencryptFile;	//解密后生成的文件
	string compressFile;	//压缩后生成的文件名
	string uncompressFile;	//解压后生成的文件名
}strDesFileName;

/*
	类名	：	CXML
	功能	：	处理XML文件，包括文件的生成、解析、压缩、解压缩
	作者	：	吴军
	修改	：	{2013.5.20 第一次创建}

*/
class CXML
{
private:
	int m_iStatus;//对XML文件处理的状态
	string m_szResFile;//所处理的加密文件文件名	
	strDesFileName m_strDesFileName;//中间生成的文件名

public:
	void Create(string txtFile);//由TXT文件创建XML文件
	void Parser(string xmlFile);//创建XML文件
	void Compress(string xmlFile);//压缩XML文件
	void Uncompress(string xmlFile);//解压缩XML文件
	void AESEncrypt(string xmlFile, string key, int keySize=16);//加密XML文件
	void AESDencrypt(string sFile, string key, int keySize=16);//解密XML文件
	int GetStatus();//返回处理状态
	strDesFileName GetDesFileName();//返回生成的文件名；

	
};


/*
	类名	：	CXMLStatus
	功能	：	描述XML处理状态信息
	作者	：	吴军
	修改	：	{2013.5.20 第一次创建}

*/

class CXMLStatus
{
public:
	static const  int CREATE_SUCCESS		= 1;	//创建XML文件成功
	static const  int CREATE_FAILED			= 2;	//创建XML文件失败
	static const  int PARSER_SUCCESS		= 3;	//解析XML文件成功
	static const  int PARSER_FAILED			= 4;	//解析XML文件失败
	static const  int COMPRESS_SUCCESS		= 5;	//压缩XML文件成功
	static const  int COMPRESS_FAILED		= 6;	//压缩XML文件失败
	static const  int UNCOMPRESS_SUCCESS	= 7;	//解压XML文件成功
	static const  int UNCOMPRESS_FAILED		= 8;	//解压XML文件失败
	static const  int ENCRYPT_SUCCESS		= 9;	//加密XML文件成功
	static const  int ENCRYPT_FAILED		= 10;	//加密XML文件失败
	static const  int DENCRYPT_SUCCESS		= 11;	//解密XML文件成功
	static const  int DENCRYPT_FAILED		= 12;	//解密XML文件失败

};

#endif