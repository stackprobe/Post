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

static int PCS_Resized;

static int ParseChunkSize(void) // ret: ? 受信完了
{
	PCS_Resized = 0;

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

	// CHUNK_TRAILER を読んでいない。XXX

	// HACK
	// Chunked-Body の最後の CR-LF 又は CHUNK_TRAILER を１バイトでも受信すると、
	// 下の if(!feof(fp)) に入ってしまい、応答を開始してしまう。

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

		PCS_Resized = 1;
	}
	return retval;
}
int IsRecvEnded(void)
{
	int resizedCount = 0;

restart:
	RecvFinalSize = s2i64_x(n2x(readLine(RECVFINALSIZE_FILE)));

	if(getFileSize(RECV_FILE) < RecvFinalSize) // ? 受信未完
		return 0;

	if(!existFile(CHUNKEDMODE_FILE)) // ? 非チャンク -> 受信完了
		return 1;

	if(ParseChunkSize())
		return 1;

	if(PCS_Resized)
	{
		resizedCount++;

		if(2 <= resizedCount)
			cout("[Chunk]IRE_resizedCount: %d\n", resizedCount);

		goto restart;
	}
	return 0;
}
