#include "CXML.h"



int main(int argc, char* argv[])
{

	clock_t start,end;
	clock_t start1,end1;
	start1 = clock();
	start = clock();
	

	
	string src = "f:\\@_@cn@2012.3.5@chinapatent@insert.txt";//��������ļ�	
	string desfilename;

	CXML *xml = new CXML();
	xml->Create(src);//����xml�ļ�

	desfilename = xml->GetDesFileName().createFile;
	//xml->Parser(desfilename);//����xml�ļ�

	//desfilename = xml->GetDesFileName().createFile;
	//xml->AESEncrypt(desfilename, "123456", 16);//�����ļ�

	//desfilename = xml->GetDesFileName().encryptFile;
	//xml->AESDencrypt(desfilename, "123456", 16);//�����ļ�

	//desfilename = xml->GetDesFileName().dencryptFile;
	xml->Compress(xml->GetDesFileName().createFile);//ѹ���ļ�

	desfilename = xml->GetDesFileName().compressFile;
	xml->Uncompress(desfilename);//ѹ���ļ�

	end = clock();
	cout<<"xml�ļ�����ʱ�� :\t"<<(end-start)<<endl;
	


}