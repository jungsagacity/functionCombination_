// Rijndael.h: interface for the Rijndael class.
//
//////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <afx.h>
typedef unsigned char byte;

class CRijndael
{
private:
	int Nk,Nr,round,keySize;
	CString m_keytemp;
	long Total_Round,Cur_Round;
	char *SourceFileName,*TargetFileName;
	CString source,*target,save;
	CFile Source,Target;
	byte (* State)[4],*w[4],*key[4];

public:
	CString ErrorMessage;
	CRijndael();
	virtual ~CRijndael();
	bool EncrypFile();
	bool DecrypFile();
	bool SetFileName(CString SFileName,CString TFileName);
	void SetNrNk(int keySize);
	bool SetKey(CString m_key);
	int GetCurPos();


private:
	void SubBytes();
	void ShiftRows();
	void MixColumns();
	byte Multi(byte a,byte b);
	void AddRoundKey();
	void KeyExpansion();
	void InvShiftRows();
	void InvSubBytes();
	void InvMixColumns();
	void Encryption();
	void Decryption();
};


