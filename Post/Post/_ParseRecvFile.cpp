#include "all.h"

static char *Boundary;

static int ReadBoundary(FILE *fp)
{
	char *bTkn = readLine(fp);
	errorCase(!bTkn);
	TrimHeaderToken(bTkn);
	cout("Boundary: %s\n", bTkn);

	if(strstart(bTkn, "--")) // ? �}���`�p�[�g�ł͂Ȃ��B
	{
		LOGPOS();
		memFree(bTkn);
		return 0;
	}
	Boundary = strx("\r\n");
	Boundary = addToken(Boundary, bTkn);

	memFree(bTkn);
	return 1;
}
static char *GetValue(char *line, char *leader)
{
	char *p = mbs_stristr(line, leader);

	if(!p)
		return NULL;

	p += strlen(leader);
	char *q = strchr(p, '"');

	if(q)
		*q = '\0';

	return strx(p);
}

static char *PartName;
static char *PartFileName; // "" == �L�q����
static char *PartBodyFile;
static char *PartFileNameFile;

static void ReadPartHeader(FILE *fp)
{
	for(; ; )
	{
		char *line = readLine(fp);
		errorCase(!line);

		if(!*line) // ? �w�b�_�I��
		{
			memFree(line);
			break;
		}
//		TrimHeaderToken(line); // UTF-8

		if(!mbs_stristart(line, "Content-Disposition:"))
		{
			PartFileName = GetValue(line, "filename=\"");
			PartName = GetValue(line, "name=\"");
		}
		memFree(line);
	}
	if(!PartName) PartName = strx("");
	if(!PartFileName) PartFileName = strx("");

	TrimHeaderToken(PartName); // �t�@�C�����Ƃ��Ďg�p�B��� to09AZazToken()
//	TrimHeaderToken(PartFileName); // UTF-8

	cout("PartName: %s\n", PartName);
//	cout("PartFileName: %s\n", PartFileName);
}
static void ReadPartBody(FILE *rfp)
{
	LOGPOS();

	FILE *wfp = fileOpen(PartBodyFile, "wb");
//	errorCase(setvbuf(wfp, NULL, _IOFBF, 128000)); // ? ���s // old
	static autoList<uchar> *wBuff;

	if(!wBuff)
		wBuff = new autoList<uchar>(CopyBuffSize);

	for(__int64 rCount = 0; ; rCount++)
	{
		int chr = readChar(rfp);
		errorCase(chr == EOF);

		/*
			Boundary[0] �� Boundary + 1 �ȍ~�Ɋ܂܂�Ȃ����ƑO��
			<- �o�E���_��������̒��O�� "��r��n--" �� Boundary �Ɋ܂߂Ă���̂Ŗ�薳���B�܂� Boundary[0] == '��r'
		*/
		while(chr == Boundary[0])
		{
			for(char *p = Boundary + 1; ; p++)
			{
				if(*p == '\0')
					goto endPart;

				chr = readChar(rfp);
				errorCase(chr == EOF);

				if(chr != *p)
				{
					for(char *q = Boundary; q < p; q++)
//						writeChar(wfp, *q); // old
						wBuff->AddElement(*q);

					break;
				}
			}
		}
//		writeChar(wfp, chr); // old
		wBuff->AddElement(chr);

		if(CopyBuffSize < wBuff->GetCount())
		{
			cout("RPB_rCount: %I64d\n", rCount);

			CheckDiskFree();
			fileWrite(wfp, wBuff->ElementAt(0), wBuff->GetCount());
			CheckDiskFree();
			wBuff->Clear();
		}
	}
endPart:
	if(1 <= wBuff->GetCount())
	{
		CheckDiskFree();
		fileWrite(wfp, wBuff->ElementAt(0), wBuff->GetCount());
		CheckDiskFree();
		wBuff->Clear();
	}
	fileClose(wfp);

	LOGPOS();
}
static int ReadPartEnd(FILE *fp) // ret: ? �p��
{
	/*
		�p���̂Ƃ��� "��r��n"
		�I���̂Ƃ��� "--��r��n"
	*/
	return
		readChar(fp) == '\r' &&
		readChar(fp) == '\n';
}
static void PreCheckDiskFree(void)
{
	char *cwd = getCwd();
	updateDiskSpace(cwd[0]);
	cout("## %s\n", cwd);
	memFree(cwd);

	__int64 currDiskFree = (__int64)lastDiskFree_User;
	__int64 recvFileSize = getFileSize(RECV_FILE);
	__int64 destDiskFree = currDiskFree - recvFileSize;

	cout("## currDiskFree: %I64d\n", currDiskFree);
	cout("## recvFileSize: %I64d\n", recvFileSize);
	cout("## destDiskFree: %I64d\n", destDiskFree);
	cout("## DiskFreeMin : %I64d\n", DiskFreeMin);

	if(destDiskFree < DiskFreeMin)
	{
		ErrorRes(); // ��ƃf�B�X�N�̋󂫗̈悪����Ȃ��\���������B
	}
}
void ParseRecvFile(void)
{
	PreCheckDiskFree();
	CheckDiskFree();

	FILE *fp = fileOpen(RECV_FILE, "rb");
	errorCase(setvbuf(fp, NULL, _IOFBF, 128000)); // ? ���s

	errorCase(!ReadBoundary(fp)); // ? �}���`�p�[�g�ł͂Ȃ��B
	errorCase(512000 < strlen(Boundary)); // 2bs, ? �o�E���_�������񂪈ُ�ɒ����B

	for(int partnum = 0; ; partnum++)
	{
		ReadPartHeader(fp);

		to09AZazToken(PartName);
		errorCase(100 < strlen(PartName)); // �p�[�g������������B

		PartBodyFile = xcout("[%s].body.httdat", PartName);
		PartFileNameFile = xcout("[%s].filename.httdat", PartName);

		CheckDiskFree();
		ReadPartBody(fp);
		CheckDiskFree();

		if(*PartFileName)
		{
			writeToken(PartFileNameFile, PartFileName);
			CheckDiskFree();
		}
		memFree(PartName);
		memFree(PartFileName);
		memFree(PartBodyFile);
		memFree(PartFileNameFile);

		if(!ReadPartEnd(fp)) // ? �p�[�g��������
			break;

		errorCase(1000 < partnum); // overflow
	}
	fileClose(fp);
	createFile(RECV_FILE); // �ǂݏI������̂ŋ�ɂ���B
}
