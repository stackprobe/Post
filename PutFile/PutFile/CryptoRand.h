#include <wincrypt.h>
#pragma comment(lib, "ADVAPI32")

void getCryptoBlock_MS(uchar *buffer, int size);

int getCryptoByte(void);
uint getCrypto32(void);
