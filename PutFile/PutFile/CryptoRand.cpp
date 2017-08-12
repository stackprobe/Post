#include "all.h"

void createKeyContainer(void)
{
	HCRYPTPROV hp;

	if(CryptAcquireContext(&hp, 0, 0, PROV_RSA_FULL, CRYPT_NEWKEYSET)) // エラー無視
		CryptReleaseContext(hp, 0);
}
void deleteKeyContainer(void)
{
	HCRYPTPROV hp;

	CryptAcquireContext(&hp, 0, 0, PROV_RSA_FULL, CRYPT_DELETEKEYSET); // エラー無視
}
void getCryptoBlock_MS(uchar *buffer, int size)
{
#if 1 // やっぱりちゃんとしよう... @ 2017.7.4
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
#else
#if 1 // 多分ファイル一覧のシャッフルにしか使ってないから、暗号論的な乱数は求めていないはず。-> 適当に初期化して返す。
	cout("GCB_MS-P.1\n");
	uint64 n = (uint64)GetTickCount();
	uint64 t = (uint64)time(NULL);
	uint p = (uint)buffer;
	int index;

	cout("n=%016x\n", n);
	cout("t=%016x\n", t);
	cout("p=%08x\n", p);

	index = 0;

	for(int c = 0; c < 8; c++)
		buffer[index++] = (n >> (c * 8)) & 0xff;

	for(int c = 0; c < 8; c++)
		buffer[index++] = (t >> (c * 8)) & 0xff;

	for(int c = 0; c < 4; c++)
		buffer[index++] = (p >> (c * 8)) & 0xff;

	/*
	for(int c = 0; c < 16; c++)
		buffer[index++] = "0123456789abcdef"[(n >> (c * 4)) & 0x0f];
		*/

	cout("GCB_MS-P.2\n");

	for(int index = 0; index < size; index++)
		cout("%02x", buffer[index]);

	cout("\n");
	cout("GCB_MS-P.3\n");
#else // old
	HCRYPTPROV hp;

	if(!CryptAcquireContext(&hp, 0, 0, PROV_RSA_FULL, 0) &&
		(GetLastError() != NTE_BAD_KEYSET ||
		!CryptAcquireContext(&hp, 0, 0, PROV_RSA_FULL, CRYPT_NEWKEYSET)))
		error();

	if(!CryptGenRandom(hp, size, buffer))
	{
		CryptReleaseContext(hp, 0);
		error();
	}
	CryptReleaseContext(hp, 0);
#if 0
// test
cout("mscr: ");
for(int c = 0; c < size; c++)
	cout("%02x", buffer[c]);
cout("\n");
#endif
#endif
#endif
}

#if 0

#define BUFFERSIZE 65 // == プロセスで必要なバイト数

int getCryptoByte(void)
{
	static uchar buffer[BUFFERSIZE];
	static uint index;

	errorCase(BUFFERSIZE <= index);

	if(!index)
		getCryptoBlock_MS(buffer, BUFFERSIZE);

	return buffer[index++];
}

#else

//#define SEEDSIZE 20
//#define SEEDSIZE 300
#define SEEDSIZE 4096
#define BUFFERSIZE 64 // == sha512 hash size

static void GetCryptoBlock(uchar *buffer)
{
	static sha512_t *ctx;

	sha512_evacuate();

	if(!ctx)
	{
		uchar seed[SEEDSIZE];

		getCryptoBlock_MS(seed, SEEDSIZE);

		ctx = sha512_create();
		sha512_update(ctx, seed, SEEDSIZE);
		sha512_makeHash(ctx);
	}
	else
	{
		static uint counter;
		sha512_t *ictx = sha512_copy(ctx);

		sha512_update(ictx, &counter, sizeof(counter));
		sha512_makeHash(ictx);

		counter++;

		if(!counter) // ? カンスト
		{
			sha512_release(ctx);
			ctx = ictx;
		}
		else
			sha512_release(ictx);
	}
	memcpy(buffer, sha512_hash, BUFFERSIZE);
	sha512_unevacuate();
}
int getCryptoByte(void)
{
	static uchar buffer[BUFFERSIZE];
	static uint index = BUFFERSIZE;

	if(BUFFERSIZE <= index)
	{
		GetCryptoBlock(buffer);
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

#endif

char *makePw(int radix, int len) // radix: 1 - 62
{
	char *pw = (char *)memAlloc(len + 1);
	int modulo = 256 - 256 % radix;

	for(int index = 0; index < len; index++)
	{
		int chr;
		do {
			chr = getCryptoByte();
		}
		while(modulo <= chr);
		chr %= radix;

		if(36 <= chr)
			chr += 'A' - 36;
		else if(10 <= chr)
			chr += 'a' - 10;
		else
			chr += '0';

		pw[index] = chr;
	}
	pw[len] = '\0';
	return pw;
}
