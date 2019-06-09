#include "all.h"

void getCryptoBlock_MS(uchar *buffer, int size)
{
	HCRYPTPROV hp;

	if(!CryptAcquireContext(&hp, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		cout("CSP Error, LastError=%08x\n", GetLastError());
		error();
	}
	if(!CryptGenRandom(hp, size, buffer))
	{
		CryptReleaseContext(hp, 0);
		error();
	}
	CryptReleaseContext(hp, 0);
}

#define BUFFERSIZE 65536

int getCryptoByte(void)
{
	static uchar buffer[BUFFERSIZE];
	static uint index = BUFFERSIZE;

	if(index == BUFFERSIZE)
	{
		getCryptoBlock_MS(buffer, BUFFERSIZE);
		index = 0;
	}
	return buffer[index++];
}
uint getCrypto32(void)
{
	return
		((uint)getCryptoByte() << 24) |
		((uint)getCryptoByte() << 16) |
		((uint)getCryptoByte() <<  8) |
		((uint)getCryptoByte() <<  0);
}
