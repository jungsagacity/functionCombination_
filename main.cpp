#include <iostream>
#include <sstream>
#include "tinyXML/tinyxml.h"
#include "AES/stdafx.h"
#include "AES/CRijndael.h"
#include <afxmt.h>
#include "xmill/Main.hpp"
using namespace std;


int main(int argc, char* argv[])
{


	const char* demoStart =
		"<?xml version=\"1.0\"  standalone='no' >\n"
		"<!-- Our to do list data -->"
		"<ToDo>\n"
		"<!-- Do I need a secure PDA? -->\n"
		"<Item priority=\"1\" distance='close'> Go to the <bold>Toy store!</bold></Item>"
		"<Item priority=\"2\" distance='none'> Do bills   </Item>"
		"<Item priority=\"2\" distance='far &amp; back'> Look for Evil Dinosaurs! </Item>"
		"<jun>12</jun>"
		"</ToDo>";


		//--------------------------------------------------------------------------------------
		// Write to a file and read it back, to check file I/O.

		TiXmlDocument doc( "d:\\1.xml" );
		doc.Parse( demoStart );

		if ( doc.Error() )
		{
			printf( "Error in %s: %s\n", doc.Value(), doc.ErrorDesc() );
			exit( 1 );
		}
		doc.SaveFile();
		




	//切记不能用同一个实例进行加密和解密
	CRijndael aes_en;
	CRijndael aes_den;

    int keysize=16;  //16,24,48字节，密钥长度
	aes_en.SetNrNk(keysize);
	aes_den.SetNrNk(keysize);

	CString m_key="12345678";
    aes_en.SetKey(m_key);
	aes_den.SetKey(m_key);
//加密
    CString SFileName="D:\\1.xml";
	CString TFileName="D:\\2.xml";
    aes_en.SetFileName(SFileName,TFileName);
	aes_en.EncrypFile();

	//解密
	CString _SFileName="D:\\2.xml";
	CString _TFileName="D:\\3.xml";
    aes_den.SetFileName(_SFileName,_TFileName);
	aes_den.DecrypFile();


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
      // An error occurred
   {
      return -1;
   }

   //HandleSingleFile("D:\\3_1.xml",0);//0:压缩
   HandleSingleFile("D:\\3_1.xmi",1);//0:压缩

	return 0;
}