#include "all.h"

static __int64 RecvFinalSize;

static void CheckReqContentLength(__int64 size)
{
	if(GetReqContentLengthMax() < size) // ? リクエスト Body 大き過ぎる！
	{
		//ErrorRes(); // リクエスト送信前に応答して切断しちゃうからダメ
		error();
	}
}
static int ParseChunkSize(void) // ret: ? 受信完了
{
	FILE *fp = fileOpen(RECV_FILE, "rb");
	fileSeek(fp, SEEK_SET, RecvFinalSize);

	memFree(readLine(fp)); // CR-LF // ParseHeader() で CR-LF 読み戻し！
	char *chunkLine = n2x(readLine(fp)); // CHUNK_SIZE + ( ';' + CHUNK_EXTENSION ) + CR-LF

	{
		char *p = strchr(chunkLine, ';');

		if(p)
			*p = '\0'; // CHUNK_EXTENSION の排除
	}
	__int64 chunkSize = hex2i64_x(chunkLine);

	int retval = 0;
	__int64 endPos = -1;

	if(!feof(fp)) // ? チャンクサイズ受信完了
	{
		endPos = getSeekPos(fp);

		if(1 <= chunkSize) // ? チャンクまだ続く
		{
			errorCase(chunkSize < 0);
			errorCase(I64_TOO_BIG - RecvFinalSize < chunkSize); // ? overflow
			CheckReqContentLength(RecvFinalSize + chunkSize);
			writeLine(RECVFINALSIZE_FILE, xcout("%I64d", RecvFinalSize + chunkSize));
		}
		else // ? チャンク終了
			retval = 1;
	}
	fileClose(fp);

	if(endPos != -1) // チャンクサイズ部分を削除
	{
		errorCase(endPos < RecvFinalSize); // 2bs

		if(retval) // ? チャンク終了
			setFileSize(RECV_FILE, RecvFinalSize);
		else
			DeleteFileDataPart(RECV_FILE, RecvFinalSize, endPos - RecvFinalSize);
	}
	return retval;
}
int IsRecvEnded(void)
{
	RecvFinalSize = s2i64_x(n2x(readLine(RECVFINALSIZE_FILE)));

	if(getFileSize(RECV_FILE) < RecvFinalSize) // ? 受信未完
		return 0;

	if(!existFile(CHUNKEDMODE_FILE)) // ? 非チャンク -> 受信完了
		return 1;

	return ParseChunkSize();
}
