#include "all.h"

char *HomeDir;
char *SendFileFullPath;
int RemoveSendFileAtTermination;
char *ResponseModeFileFullPath;
char *UserProgram;

void HTT_Disconnect(void)
{
	LOGPOS();
	if(SendFileFullPath)
	{
		LOGPOS();
//		removeFile(SendFileFullPath); // オープンされていると削除出来ない！
		RemoveSendFileAtTermination = 1;
	}
	LOGPOS();
}
void DeleteFileDataPart(char *file, __int64 beginPos, __int64 delSize)
{
	errorCase(m_isEmpty(file));

	__int64 size = getFileSize(file);

	errorCase(beginPos < 0);
	errorCase(delSize < 0);
	errorCase(I64_TOO_BIG - beginPos < delSize); // 2bs
	errorCase(size < beginPos + delSize);

	if(delSize == 0)
		return;

	FILE *rfp = fileOpen(file, "rb");
	FILE *wfp = fileOpen(file, "r+b");

	fileSeek(rfp, SEEK_SET, beginPos + delSize);
	fileSeek(wfp, SEEK_SET, beginPos);

	const int bufferSize = 1000000;
	static void *buffer;

	if(!buffer)
		buffer = memAlloc(bufferSize);

	for(__int64 remain = size - (beginPos + delSize); 0 < remain; )
	{
		int rwSize = (int)m_min(remain, bufferSize);

		fileRead(rfp, buffer, rwSize);
		fileWrite(wfp, buffer, rwSize);

		remain -= rwSize;
	}
	fileClose(rfp);
	fileClose(wfp);

	setFileSize(file, size - delSize);
}
void TrimHeaderToken(char *token)
{
	toAsciiToken(token);
	trim(token, ' ');
}
void CheckDiskFree2(char *source, int lineno, char *function)
{
	char *cwd = getCwd();
	updateDiskSpace_Dir(cwd);
	memFree(cwd);

//	LOGPOS();
//	cout("LDF: %I64d\n", lastDiskFree_User);
//	cout("DFM: %I64d\n", DiskFreeMin);
	cout("LDF_DFM: %I64d_%I64d @ %s %d %s\n", lastDiskFree_User, DiskFreeMin, source, lineno, function);

//	errorCase(lastDiskFree_User < (uint64)DiskFreeMin); // old
	if(lastDiskFree_User < (uint64)DiskFreeMin)
	{
		ErrorRes(); // ディスクの空き領域が不足しています。
	}
}
void WriteResponseHtmlFile(char *text)
{
	//errorCase(!SendFileFullPath); // この場合、切断(HTT_Disconnect)が効かないので敢えて続行ということだと思う。@ 2018.2.19
	if(!SendFileFullPath)
	{
		LOGPOS();
		return;
	}
	errorCase(!ResponseModeFileFullPath);

	text = strx(text);
	text = replace(text, "\r", "");
	text = replace(text, "\n", "\r\n");

	int textLen = strlen(text);
	FILE *fp = fileOpen(SendFileFullPath, "wb");
	
	writeToken(fp, "HTTP/1.1 200 Happy Tea Time" CRLF);
	writeToken(fp, "Server: htt" CRLF);
	writeToken(fp, "Content-Type: text/html; charset=Shift_JIS" CRLF);
	writeToken_x(fp, xcout("Content-Length: %d" CRLF, textLen));
	writeToken(fp, "Connection: close" CRLF);
	writeToken(fp, CRLF);
	fileWrite(fp, text, textLen);

	fileClose(fp);
	memFree(text);

	createFile(ResponseModeFileFullPath); // add @ 2014.9.1
}
