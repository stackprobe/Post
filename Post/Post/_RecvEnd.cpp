#include "all.h"

static __int64 RecvFinalSize;

static void CheckReqContentLength(__int64 size)
{
	if(GetReqContentLengthMax() < size) // ? ���N�G�X�g Body �傫�߂���I
	{
		//ErrorRes(); // ���N�G�X�g���M�O�ɉ������Đؒf�����Ⴄ����_��
		error();
	}
}

static int PCS_Resized;

static int ParseChunkSize(void) // ret: ? ��M����
{
	PCS_Resized = 0;

	FILE *fp = fileOpen(RECV_FILE, "rb");
	fileSeek(fp, SEEK_SET, RecvFinalSize);

	memFree(readLine(fp)); // CR-LF // ParseHeader() �� CR-LF �ǂݖ߂��I
	char *chunkLine = n2x(readLine(fp)); // CHUNK_SIZE + ( ';' + CHUNK_EXTENSION ) + CR-LF

	{
		char *p = strchr(chunkLine, ';');

		if(p)
			*p = '\0'; // CHUNK_EXTENSION �̔r��
	}

	__int64 chunkSize = hex2i64_x(chunkLine);

	int retval = 0;
	__int64 endPos = -1;

	// CHUNK_TRAILER ��ǂ�ł��Ȃ��BXXX

	// HACK
	// Chunked-Body �̍Ō�� CR-LF ���� CHUNK_TRAILER ���P�o�C�g�ł���M����ƁA
	// ���� if(!feof(fp)) �ɓ����Ă��܂��A�������J�n���Ă��܂��B

	if(!feof(fp)) // ? �`�����N�T�C�Y��M����
	{
		endPos = getSeekPos(fp);

		if(1 <= chunkSize) // ? �`�����N�܂�����
		{
			errorCase(chunkSize < 0);
			errorCase(I64_TOO_BIG - RecvFinalSize < chunkSize); // ? overflow
			CheckReqContentLength(RecvFinalSize + chunkSize);
			writeLine(RECVFINALSIZE_FILE, xcout("%I64d", RecvFinalSize + chunkSize));
		}
		else // ? �`�����N�I��
			retval = 1;
	}
	fileClose(fp);

	if(endPos != -1) // �`�����N�T�C�Y�������폜
	{
		errorCase(endPos < RecvFinalSize); // 2bs

		if(retval) // ? �`�����N�I��
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

	if(getFileSize(RECV_FILE) < RecvFinalSize) // ? ��M����
		return 0;

	if(!existFile(CHUNKEDMODE_FILE)) // ? ��`�����N -> ��M����
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
