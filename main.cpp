#include "CXML.h"



int main(int argc, char* argv[])
{

	clock_t start,end;
	clock_t start1,end1;
	start1 = clock();
	start = clock();
	

	
	string src = "f:\\@_@cn@2012.3.5@chinapatent@insert.txt";//待处理的文件	
	string desfilename;

	CXML *xml = new CXML();
	xml->Create(src);//生成xml文件

	desfilename = xml->GetDesFileName().createFile;
	//xml->Parser(desfilename);//解析xml文件

	//desfilename = xml->GetDesFileName().createFile;
	//xml->AESEncrypt(desfilename, "123456", 16);//加密文件

	//desfilename = xml->GetDesFileName().encryptFile;
	//xml->AESDencrypt(desfilename, "123456", 16);//解密文件

	//desfilename = xml->GetDesFileName().dencryptFile;
	xml->Compress(xml->GetDesFileName().createFile);//压缩文件

	desfilename = xml->GetDesFileName().compressFile;
	xml->Uncompress(desfilename);//压缩文件

	end = clock();
	cout<<"xml文件生成时间 :\t"<<(end-start)<<endl;
	


}