// CRijndael.cpp: implementation of the CRijndael class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "CRijndael.h"
#include <afxmt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const long MaxSize=1048576;//定义最大的读取文件的缓冲区大小
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/////////////////////////////////
byte power3[255]=
{1, 3, 5, 15, 17, 51, 85, 255, 26, 46, 114, 150, 161, 248, 19, 53, 95, 225,
56, 72, 216, 115, 149, 164, 247, 2, 6, 10, 30, 34, 102, 170, 229, 52, 92,
228, 55, 89, 235, 38, 106, 190, 217, 112, 144, 171, 230, 49, 83, 245, 4, 12,
20, 60, 68, 204, 79, 209, 104, 184, 211, 110, 178, 205, 76, 212, 103, 169,
224, 59, 77, 215, 98, 166, 241, 8, 24, 40, 120, 136, 131, 158, 185, 208, 107,
189, 220, 127, 129, 152, 179, 206, 73, 219, 118, 154, 181, 196, 87, 249, 16,
48, 80, 240, 11, 29, 39, 105, 187, 214, 97, 163, 254, 25, 43, 125, 135, 146,
173, 236, 47, 113, 147, 174, 233, 32, 96, 160, 251, 22, 58, 78, 210, 109,
183, 194, 93, 231, 50, 86, 250, 21, 63, 65, 195, 94, 226, 61, 71, 201, 64,
192, 91, 237, 44, 116, 156, 191, 218, 117, 159, 186, 213, 100, 172, 239, 42,
126, 130, 157, 188, 223, 122, 142, 137, 128, 155, 182, 193, 88, 232, 35, 101,
175, 234, 37, 111, 177, 200, 67, 197, 84, 252, 31, 33, 99, 165, 244, 7, 9,
27, 45, 119, 153, 176, 203, 70, 202, 69, 207, 74, 222, 121, 139, 134, 145,
168, 227, 62, 66, 198, 81, 243, 14, 18, 54, 90, 238, 41, 123, 141, 140, 143,
138, 133, 148, 167, 242, 13, 23, 57, 75, 221, 124, 132, 151, 162, 253, 28,
36, 108, 180, 199, 82, 246};

byte log3[256]=
{0, 0, 25, 1, 50, 2, 26, 198, 75, 199, 27, 104, 51, 238, 223, 3, 100, 4, 224,
14, 52, 141, 129, 239, 76, 113, 8, 200, 248, 105, 28, 193, 125, 194, 29, 181,
249, 185, 39, 106, 77, 228, 166, 114, 154, 201, 9, 120, 101, 47, 138, 5, 33,
15, 225, 36, 18, 240, 130, 69, 53, 147, 218, 142, 150, 143, 219, 189, 54,
208, 206, 148, 19, 92, 210, 241, 64, 70, 131, 56, 102, 221, 253, 48, 191, 6,
139, 98, 179, 37, 226, 152, 34, 136, 145, 16, 126, 110, 72, 195, 163, 182,
30, 66, 58, 107, 40, 84, 250, 133, 61, 186, 43, 121, 10, 21, 155, 159, 94,
202, 78, 212, 172, 229, 243, 115, 167, 87, 175, 88, 168, 80, 244, 234, 214,
116, 79, 174, 233, 213, 231, 230, 173, 232, 44, 215, 117, 122, 235, 22, 11,
245, 89, 203, 95, 176, 156, 169, 81, 160, 127, 12, 246, 111, 23, 196, 73,
236, 216, 67, 31, 45, 164, 118, 123, 183, 204, 187, 62, 90, 251, 96,177,
134, 59, 82, 161, 108, 170, 85, 41, 157, 151, 178, 135, 144, 97, 190,220,
252, 188, 149, 207, 205, 55, 63, 91, 209, 83, 57, 132, 60, 65, 162, 109,71,
20, 42, 158, 93, 86, 242, 211, 171, 68, 17, 146, 217, 35, 32, 46, 137,180,
124, 184, 38, 119, 153, 227, 165, 103, 74, 237, 222, 197, 49, 254, 24,13,
99, 140, 128, 192, 247, 112, 7};

byte SBox[16][16] = 
	{{0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76},
	{0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0},
	{0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15},
	{0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75}, 
	{0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84},
	{0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf},
	{0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8},
	{0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2},
	{0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73},
	{0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb},
	{0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79},
	{0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08},
	{0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a},
	{0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e},
	{0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf},
	{0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16} 
	};//s-盒

byte InvSBox[16][16]= 
	{{0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb},
	{0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb},
	{0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e},
	{0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25},
	{0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92},
	{0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84},
	{0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06},
	{0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b},
	{0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73},
	{0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e},
	{0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b},
	{0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4},
	{0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f},
	{0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef},
	{0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61},
	{0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d},
	};//逆s-盒

byte Rc[31] = 
{ 0x00, 0x01,0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 
0xfa, 0xef, 0xc5,0x91};
////////////////////////////////

CRijndael::CRijndael()//type=true时为加密文件,type=false时为加密字符串
{
	int i;
	for(i=0;i<4;i++)//置空
	{
		key[i]=NULL;
		w[i]=NULL;
	}
	SourceFileName=NULL;
	TargetFileName=NULL;
	save=""; //modified by wujun 2013.4.26   --original: [ save=_T(""); ]
	State=NULL;
	ErrorMessage="";
}

CRijndael::~CRijndael()
{
	for(int i=0;i<4;i++)//释放原有的内存并置空
	{
		if(key[i]!=NULL)
		{
			delete key[i];
			key[i]=NULL;
		}
		if(w[i]!=NULL)
		{
			delete w[i];
			w[i]=NULL;
		}
	}
	save=("");

	//comment by wujun 2013.4.26  ocurr the error " _CrtIsValidHeapPointer(pUserData)" mainly by memmory allocation and realse
	//SetFileName function has already realsed the memory which SourceFileName and TargetFileName point to.
	if(SourceFileName!=NULL)//释放存放文件路径的内存
		delete []SourceFileName;
	if(TargetFileName!=NULL)//释放存放文件路径的内存  --modified by wujun 2013.4.26 --original :[if(SourceFileName!=NULL)]
		delete []TargetFileName;
}



void CRijndael::SetNrNk(int keySize)
{
	this->keySize=keySize;
	if(keySize=16)  
	{  
		Nk=4;    //4*4字节，128位密钥，10轮加密  
		Nr=10;  
	}  
	else if(keySize=24)  
	{  
		Nk=6;    //6*4字节，192位密钥，12轮加密  
		Nr=12;  
	}  
	else if(keySize=48)  
	{  
		Nk=8;    //8*4字节，256位密钥，14轮加密  
		Nr=14;  
	}  
}
bool CRijndael::SetKey(CString m_key)
{
	CString temp;
	int len,count;
	temp=m_key;
	len=m_key.GetLength();
	if(len==0)//长度为0时直接返回
		return 0;
	if(len>keySize)//长度超过规定长度
	{
		m_key=temp;
//		MessageBox("所给的密钥长度超过规定!","警告",MB_OK|MB_ICONWARNING);
	}
	else
		if(len<keySize)//长度不足规定长度
		{
			count=keySize/len-1;//计算进行多少次的密钥直接复制到临时密钥的末尾
			m_keytemp=m_key;
			for(len=0;len<count;len++)
			{
				temp.Format("%s%s",m_keytemp,m_key);
				m_keytemp=temp;
			}
			count=keySize-m_keytemp.GetLength();
			
			if(count!=0)//进行count次的密钥直接复制后还未达到规定长度
			{
				temp.Format("%s%s",m_keytemp,m_key.Left(count));
				m_keytemp=temp;				
			}
		}
	
	for(int i=0;i<4;i++)//释放原有的内存并置空
	{		
		if(key[i]!=NULL)
		{
			delete key[i];
			key[i]=NULL;
		}
		if(w[i]!=NULL)
		{
			delete w[i];
			w[i]=NULL;
		}
	}
	for(int i=0;i<4;i++)
	{
		key[i]=new byte[Nk];
		if(key[i]==NULL)
		{
			ErrorMessage=ErrorMessage+"\n分配内存空间出错!内存空间不足,请稍候运行本程序!";
			return false;
		}		
	}
	for(int i=0;i<4;i++)
	{
		w[i]=new byte[4*(Nr+1)]; 
		if(w[i]==NULL)
		{
			ErrorMessage=ErrorMessage+"\n分配内存空间出错!内存空间不足,请稍候运行本程序!";
			return false;
		}
	}
	for(int i=0;i<4;i++)//获得密钥
		for(int j=0;j<Nk;j++)
			key[i][j]=m_keytemp.GetAt(Nk*i+j);
    KeyExpansion();//密钥扩展
	return true;
}

bool CRijndael::SetFileName(CString SFileName,CString TFileName)//设置加密与解密用的文件的路径
{
	int i,j;
	SourceFileName=new char[(SFileName.GetLength()+1)*sizeof(char)];
	if(SourceFileName==NULL)
	{
		ErrorMessage=ErrorMessage+"\n分配内存空间出错!内存空间不足,请稍候运行本程序!";
		SourceFileName=NULL;
		return false;
	}
	TargetFileName=new char[(TFileName.GetLength()+1)*sizeof(char)];
	if(SourceFileName==NULL)
	{
		ErrorMessage=ErrorMessage+"\n分配内存空间出错!内存空间不足,请稍候运行本程序!";
		delete []SourceFileName;
		SourceFileName=NULL;
		TargetFileName=NULL;
		return false;
	}
	for(i=0;i<SFileName.GetLength();i++)
		SourceFileName[i]=SFileName.GetAt(i);
	SourceFileName[i]='\0';
	for(i=0;i<TFileName.GetLength();i++)
		TargetFileName[i]=TFileName.GetAt(i);
	TargetFileName[i]='\0';
	/////////////打开文件//////////////
	i=Source.Open(SourceFileName,CFile::modeRead|CFile::shareDenyRead);
	j=Target.Open(TargetFileName,CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone);
	if(i==0||j==0)//打开文件失败,释放内存及已打开的关闭文件
	{
		if(i==0)
		{
			ErrorMessage=ErrorMessage+"\n打开\""+SFileName+"\"文件失败!请确认所给的路径时候是否正确!";
			delete []SourceFileName;
		}
		else
			Source.Close();
		if(j==0)
		{
			ErrorMessage=ErrorMessage+"\n打开\""+TFileName+"\"文件失败!请确认所给的路径时候是否正确!";
			delete []TargetFileName;
		}
		else
			Target.Close();
		return false;		
	}
	delete []SourceFileName;//释放内存
	SourceFileName = NULL;
	delete []TargetFileName;//释放内存
	TargetFileName=NULL;
	return true;
}



void CRijndael::SubBytes()//字节代替变换
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			State[i][j]=SBox[(State[i][j]>>4)&0x0F][State[i][j]&0x0F];
}

void CRijndael::ShiftRows()//循环移位
{
///////////////////实现方法一,枚举方法////////////////
	byte temp;
	temp=State[0][1];
	State[0][1]=State[1][1];
	State[1][1]=State[2][1];
	State[2][1]=State[3][1];
	State[3][1]=temp;

	temp=State[0][2];
	State[0][2]=State[2][2];
	State[2][2]=temp;
	temp=State[1][2];
	State[1][2]=State[3][2];
	State[3][2]=temp;

	temp=State[3][3];
	State[3][3]=State[2][3];
	State[2][3]=State[1][3];
	State[1][3]=State[0][3];
	State[0][3]=temp;
/*实现方法二,数学方法
	byte temp[3];
	int i,j,k;
	for(j=1;j<4;j++)
    {
        for(k=0;k<j;k++)
			temp[k]=State[k][j];
		for(;k<4;k++)
		    State[k-j][j]=State[k][j];
		k=4-j;
		for(i=0;i<j;i++)
			State[k++][j]=temp[i];
	}
*/
}

byte CRijndael::Multi(byte a,byte b)//二元域上的乘法运算
{
	if(a&&b)
		return power3[(log3[a]+log3[b])%255];
	else
		return 0;
}

void CRijndael::MixColumns()//列混合变换
{
	byte stemp[4];
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
			stemp[j]=State[i][j];
		State[i][0]=Multi(0x02,stemp[0])^(Multi(0x03,stemp[1]))^stemp[2]^stemp[3];
		State[i][1]=stemp[0]^Multi(0x02,stemp[1])^(Multi(0x03,stemp[2]))^stemp[3];
		State[i][2]=stemp[0]^stemp[1]^Multi(0x02,stemp[2])^(Multi(0x03,stemp[3]));
		State[i][3]=Multi(0x03,stemp[0])^stemp[1]^stemp[2]^Multi(0x02,stemp[3]);
	}
}

void CRijndael::AddRoundKey()//圈密钥加法变换
{
	int i,j,k=round*4;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		State[i][j]=State[i][j]^w[i][k+j];//State[i][j]=State[i][j];//modified by wujun 2013.4.26 --original [State[i][j]=State[i][j]^w[i][k+j];]
}

void CRijndael::KeyExpansion()//密钥扩展
{
	byte temp[4],tp;
	int i,j,x;
	for(i=0;i<Nk;i++)//生成前Nk个字
	{
		w[0][i]=key[0][i];
		w[1][i]=key[1][i];
		w[2][i]=key[2][i];
		w[3][i]=key[3][i];
	}
	while(i<4*(Nr+1))//生成后几个字
	{
		for(j=0;j<4;j++)
			temp[j]=w[j][i-1];
		if(i%Nk==0)
		{
			tp=temp[0];
			temp[0]=temp[1];
			temp[1]=temp[2];
			temp[2]=temp[3];
			temp[3]=tp;
			for(j=0;j<4;j++)
				temp[j]=SBox[(temp[j]>>4)&0x0F][temp[j]&0x0F];
			x=Rc[i/Nk];
			temp[0]=temp[0]^Rc[i/Nk];
		}
		else
			if(Nk>6&&(i%Nk==4))
				for(j=0;j<4;j++)
					temp[j]=SBox[(temp[j]>>4)&0x0F][temp[j]&0x0F];
		for(j=0;j<4;j++)
			w[j][i]=(w[j][i-Nk])^temp[j];		
		i++;
	}
	for(int k=0;k<=Nr;k++)//实现密钥的每16个字节为一个矩阵的矩阵转置(对字符串加密/解密有影响)
		for(i=0;i<3;i++)
		{
			x=4*k;
			for(j=i+1;j<4;j++)
			{
				tp=w[i][x+j];
				w[i][x+j]=w[j][x+i];
				w[j][x+i]=tp;
			}
		}
	
}

void CRijndael::InvShiftRows()//循环右移函数(0000000000)
{
///////////////////实现方法一,枚举方法////////////////
	byte temp;
	temp=State[3][1];
	State[3][1]=State[2][1];
	State[2][1]=State[1][1];
	State[1][1]=State[0][1];
	State[0][1]=temp;

	temp=State[2][2];
	State[2][2]=State[0][2];
	State[0][2]=temp;
	temp=State[3][2];
	State[3][2]=State[1][2];
	State[1][2]=temp;

	temp=State[0][3];
	State[0][3]=State[1][3];
	State[1][3]=State[2][3];
	State[2][3]=State[3][3];
	State[3][3]=temp;
/*实现方法二,数学方法
	byte temp[3];
	int i,j,k;
	for(j=1;j<4;j++)
	{
		i=4-j;
		for(k=0;k<j;k++)//取出前面的元素
			temp[k]=State[i++][j];
		for(i=3-j;i>=0;i--)//移位
			State[i+j][j]=State[i][j];
		for(k=0;k<j;k++)//放回取出的元素
			State[k][j]=temp[k];
	}
*/
}

void CRijndael::InvSubBytes()//利用逆S盒InvSBox实现逆字节代替变换
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			State[i][j]=InvSBox[(State[i][j]>>4)&0x0F][State[i][j]&0x0F];
}

void CRijndael::InvMixColumns()
{
	int i,j;
	byte stemp[4];
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			stemp[j]=State[i][j];
		State[i][0]=Multi(0x0e,stemp[0])^Multi(0x0b,stemp[1])^Multi(0x0d,stemp[2])^Multi(0x09,stemp[3]);
		State[i][1]=Multi(0x09,stemp[0])^Multi(0x0e,stemp[1])^Multi(0x0b,stemp[2])^Multi(0x0d,stemp[3]);
		State[i][2]=Multi(0x0d,stemp[0])^Multi(0x09,stemp[1])^Multi(0x0e,stemp[2])^Multi(0x0b,stemp[3]);
		State[i][3]=Multi(0x0b,stemp[0])^Multi(0x0d,stemp[1])^Multi(0x09,stemp[2])^Multi(0x0e,stemp[3]);
	}
}

void CRijndael::Encryption()//加密
{
	int j,k=0;
	round=0;
	AddRoundKey();
	round=round+1;
	for(j=1;j<Nr;j++)
	{
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey();
		round=round+1;
	}
	SubBytes();
	ShiftRows();
	AddRoundKey();
}

void CRijndael::Decryption()//解密
{
	int j,k=0;
	round=Nr;
	AddRoundKey();
	round=round-1;
	for(j=Nr-1;j>0;j--)
	{
		InvShiftRows();
		InvSubBytes();
		AddRoundKey();
		round=round-1;
		InvMixColumns();
	}
	InvShiftRows();
	InvSubBytes();
	AddRoundKey();
}

bool CRijndael::EncrypFile()
{
	long i,j,k,len,count,size;
	int remain;
	byte *temp,(*in_stream)[4][4];
	State=NULL;
	Cur_Round=0;
	/////////////获取文件名//////////////
	len=Source.GetLength();//取得文件长度(字节)
	if(len%16==0)//计算总的加密轮数
		Total_Round=len/16;
	else
		Total_Round=len/16+1;
	
	remain=len;//计算不够用于加密的字节数
	while(remain>=16)
	{
		if(remain>=MaxSize)
			size=MaxSize;
		else
			size=remain-remain%16;
		len=size/16;
		in_stream=new byte[len][4][4];//设置读入缓冲区
		count=remain/size;//计算读取文件的次数
		while((in_stream==NULL)&&(size>16))//循环计算可得到的最大缓冲区
		{
			size=size/2;
			if(size%16!=0)
				size=size+(16-size%16);	
			if(size<16)//若可得的最大缓冲区小于16个字节时，为错误情形
			{
				ErrorMessage=ErrorMessage+"\n内存空间不足!";
				Source.Close();
				Target.Close();
				return false;
			}
			len=size/16;
			count=remain/size;//计算读取文件的次数
			in_stream=new byte[len][4][4];//设置读入缓冲区
		}
		for(i=0;i<count;i++)
		{
			try
			{
				Source.Read(in_stream,size);//从明文文件中读入size个字节内容到缓冲区
			}
			catch(...)//读入文件失败
			{
				ErrorMessage=ErrorMessage+"\n读入文件失败!";
				delete []in_stream;
				Source.Close();
				Target.Close();
				return false;
			}
			for(j=0;j<len;j++)
			{
				State=&(in_stream[j][0]);
				Encryption();//调用加密函数
				Cur_Round++;//当前轮数加1
			}
			try
			{
				Target.Write(in_stream,size);//将缓冲区的size个字节内容写入到密文文件中
			}
			catch(...)//写入文件失败
			{
				ErrorMessage=ErrorMessage+"\n写入文件失败!";
				delete []in_stream;
				Source.Close();
				Target.Close();
				return false;
			}
		}			
		remain=remain-size*count;//计算未处理的文件大小
		if(remain<16&&remain>0)
		{
			Target.Seek(-(16-remain),CFile::current);//当前指针后移(相对于当前位置)remain=2
			temp=new byte[remain];
			if(temp==NULL)
			{
				ErrorMessage=ErrorMessage+"\n读入文件失败!";
				delete []in_stream;
				Source.Close();
				Target.Close();
				return false;
			}
			byte *p=NULL;
			p=&(State[0][0]);
			try
			{
				Source.Read(temp,remain);
			}
			catch(...)//读入文件失败
			{
				ErrorMessage=ErrorMessage+"\n读入文件失败!";
				delete []temp;
				delete []in_stream;
				Source.Close();
				Target.Close();
				return false;
			}
			k=0;
			for(j=remain;j<16;j++,k++)
				*(p+k)=*(p+j);//k=16-remain
			for(j=0;j<remain;j++,k++)
				*(p+k)=temp[j];
			Encryption();//调用加密函数
			Cur_Round++;//当前轮数加1
			try
			{
				Target.Write(State,16);
			}
			catch(...)//写入文件失败
			{
				ErrorMessage=ErrorMessage+"\n写入文件失败!";					
				delete []temp;
				delete []in_stream;
				Source.Close();
				Target.Close();
				return false;
			}
			delete []temp;
			remain=0;
		}
		delete []in_stream;
		}
	Source.Close();
	Target.Close();
	for(i=0;i<4;i++)//释放密钥的内存并置空
	{
		delete key[i];
		key[i]=NULL;
		delete w[i];
		w[i]=NULL;
	}
	return true;
}

bool CRijndael::DecrypFile()
{
	long i,j,k=0,len,count,size;
	int remain;
	byte *temp=NULL,*s=NULL,(*in_stream)[4][4];
	State=NULL;
	Cur_Round=0;
	/////////////获取文件名//////////////
	len=Source.GetLength();//取得文件长度(字节)		
	if(len%16==0)//计算总的解密轮数
		Total_Round=len/16;
	else
		Total_Round=len/16+1;
	
	remain=len;
	if(remain%16!=0)
	{
		k=16+remain%16;
		remain=remain-k;
	}
	while(remain>=16)
	{
		if(remain>=MaxSize)
			size=MaxSize;
		else
			size=remain;
		len=size/16;
		in_stream=new byte[len][4][4];//设置读入缓冲区
		count=remain/size;//计算读取文件的次数
		while((in_stream==NULL)&&(size>16))//循环计算可得到的最大缓冲区
		{
			size=size/2;
			if(size%16!=0)
				size=size+(16-size%16);	
			if(size<16)//若可得的最大缓冲区小于16个字节时，为错误情形
			{
				ErrorMessage=ErrorMessage+"\n内存空间不足!";
				Source.Close();
				Target.Close();
				return false;
			}
			len=size/16;
			count=remain/size;//计算读取文件的次数
			in_stream=new byte[len][4][4];//设置读入缓冲区
		}
		for(i=0;i<count;i++)
		{
			try
			{
				Source.Read(in_stream,size);//从明文文件中读入size个字节内容到缓冲区
			}
			catch(...)//读入文件失败
			{
				ErrorMessage=ErrorMessage+"\n读入文件失败!";
				delete []in_stream;
				Source.Close();
				Target.Close();
				return false;
			}
			for(j=0;j<len;j++)
			{
				State=&(in_stream[j][0]);
				Decryption();//调用解密函数
				Cur_Round++;//当前轮数加1
			}
			try
			{
				Target.Write(in_stream,size);//将缓冲区的size个字节内容写入到密文文件中
			}
			catch(...)//写入文件失败
			{
				ErrorMessage=ErrorMessage+"\n写入文件失败!";
				delete []in_stream;
				Source.Close();
				Target.Close();
				return false;
			}
		}			
		remain=remain-size*count;//计算未处理的文件大小
		delete []in_stream;
	}
	if(k!=0)
	{
		remain=k-16;
		s=new byte[remain];//取出remain个字节
		if(s==NULL)//分配内存失败
		{
			ErrorMessage=ErrorMessage+"\n内存空间不足!";
			Source.Close();
			Target.Close();
			return false;
		}
		temp=new byte[remain];//取出remain个字节
		if(temp==NULL)//分配内存失败
		{
			ErrorMessage=ErrorMessage+"\n内存空间不足!";
			Source.Close();
			Target.Close();
			return false;			
		}
		byte in[4][4];
		try
		{
			Source.Read(s,remain);//跳过remain个字节
			Source.Read(in,16);//做最后一轮解密
		}
		catch(...)//读入文件失败
		{
			ErrorMessage=ErrorMessage+"\n读入文件失败!";
			Source.Close();
			Target.Close();
			delete []s;
			delete []temp;
			return false;
		}
		State=in;
		Decryption();//调用解密函数	
		
		Cur_Round++;//当前轮数加1
		
		byte *p=NULL;
		p=&(State[0][0]);			
		for(i=0,j=16-remain;j<16;j++)
			temp[i++]=*(p+j);
		for(i=15-remain,j=15;i>=0;i--,j--)
			*(p+j)=*(p+i);				
		for(j=0;j<remain;j++)
			*(p+j)=s[j];	
		Decryption();//调用解密函数
		
		Cur_Round++;//当前轮数加1
		try
		{
			Target.Write(State,16);
			Target.Write(temp,remain);
		}
		catch(...)//写入文件失败
		{
			ErrorMessage=ErrorMessage+"\n写入文件失败!";
			delete []s;
			delete []temp;
			Source.Close();
			Target.Close();
			return false;
		}
		delete []s;
		delete []temp;
	}
	Source.Close();
	Target.Close();
	for(i=0;i<4;i++)//释放密钥的内存并置空
	{
		delete key[i];
		key[i]=NULL;
		delete w[i];
		w[i]=NULL;
	}
	return true;
}


int CRijndael::GetCurPos()
{
	return Cur_Round*100/Total_Round;
}

//void	 CRjndael::OnChangeKey(CString m_key,int i) 
//{
//	// TODO: If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialog::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//	
//	// TODO: Add your control notification handler code here
//	CString	m_keylen;
//	CString	m_kltype;
//	CString temp;
//	int k,r;
//	switch(i)
//	{
//	case 0:m_kltype.Format("128位");m_keylen.Format("16");k=4;r=10;break;
//    case 1:m_kltype.Format("192位");m_keylen.Format("24");k=6;r=12;break;
//	case 2:m_kltype.Format("256位");m_keylen.Format("32");k=8;r=14;break;
//	}
//  
//	int len,count;
//	temp=m_key;
//	len=m_key.GetLength();
//	if(len==0)//长度为0时直接返回
//		return;
//	if(len>atoi(m_keylen))//长度超过规定长度
//	{
//		m_key=temp;
//		MessageBox("所给的密钥长度超过规定!","警告",MB_OK|MB_ICONWARNING);
//	}
//	else
//		if(len<atoi(m_keylen))//长度不足规定长度
//		{
//			count=atoi(m_keylen)/len-1;//计算进行多少次的密钥直接复制到临时密钥的末尾
//			m_keytemp=m_key;
//			for(len=0;len<count;len++)
//			{
//				temp.Format("%s%s",m_keytemp,m_key);
//				m_keytemp=temp;
//			}
//			count=atoi(m_keylen)-m_keytemp.GetLength();
//			
//			if(count!=0)//进行count次的密钥直接复制后还未达到规定长度
//			{
//				temp.Format("%s%s",m_keytemp,m_key.Left(count));
//				m_keytemp=temp;				
//			}
//		}
//		_m_key=m_keytemp;
//	SetVariable(k,r,m_key);	
//}