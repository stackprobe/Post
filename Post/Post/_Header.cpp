#include "all.h"

typedef struct Field_st
{
	char *Name;
	char *Value;
}
Field_t;

static char *Header;
static autoList<Field_t *> *Fields;

static void CheckReqContentLength(__int64 size)
{
	if(GetReqContentLengthMax() < size) // ? リクエスト Body 大き過ぎる！
	{
		//ErrorRes(); // リクエスト送信前に応答して切断しちゃうからダメ
		error();
	}
}
static void MakeHeaderFile(void)
{
	FILE *fp = fileOpen(HEADER_FILE, "wt");

	writeLine(fp, Header);

	for(int index = 0; index < Fields->GetCount(); index++)
	{
		Field_t *i = Fields->GetElement(index);

		if(!_stricmp(i->Name, "Content-Length"))
		{
			__int64 size = s2i64(i->Value);
			errorCase(size < 0);
			errorCase(I64_TOO_BIG < size); // ? overflow
			CheckReqContentLength(size);
			writeLine_cx(RECVFINALSIZE_FILE, xcout("%I64d", size));
		}
		else if(!_stricmp(i->Name, "Transfer-Encoding") && !_stricmp(i->Value, "chunked"))
		{
			createFile(CHUNKEDMODE_FILE);
		}
		writeLine_x(fp, xcout("%s:%s", i->Name, i->Value));
	}
	fileClose(fp);

	if(existFile(CHUNKEDMODE_FILE))
		createFile(RECVFINALSIZE_FILE); // to '0'

	errorCase(!existFile(RECVFINALSIZE_FILE));
}
int ParseHeader(void)
{
	if(existFile(HEADER_FILE))
		return 1;

	FILE *fp = fileOpen(RECV_FILE, "rb");
	int retval = 0;
	__int64 headerEndPos = -1;

	Header = readLine(fp);

	if(!Header)
		goto endfunc;

	TrimHeaderToken(Header);

	Fields = new autoList<Field_t *>();

	for(; ; )
	{
		char *line = readLine(fp);

		if(!line)
			break;

		if(!*line)
		{
			memFree(line);
			break;
		}
		if(*line <= ' ')
		{
			TrimHeaderToken(line);
			Field_t *i = Fields->GetLastElement();
			i->Value = addToken(i->Value, line);
		}
		else
		{
			char *p = strchr(line, ':');

			if(p)
			{
				*p = '\0';
				p++;

				Field_t *i = nb(Field_t);
				i->Name = strx(line);
				i->Value = strx(p);

				TrimHeaderToken(i->Name);
				TrimHeaderToken(i->Value);

				Fields->AddElement(i);
			}
		}
		memFree(line);
	}
	if(!feof(fp)) // ? 読み込み完了
	{
		headerEndPos = getSeekPos(fp);
		MakeHeaderFile();
		retval = 1;
	}
endfunc:
	fileClose(fp);

	if(headerEndPos != -1)
	{
		if(existFile(CHUNKEDMODE_FILE))
		{
			errorCase(headerEndPos < 2); // 2bs
			headerEndPos -= 2;
		}
		DeleteFileDataPart(RECV_FILE, 0, headerEndPos); // ヘッダ部分を削除
	}
	errorCase(!retval && 512000 < getFileSize(RECV_FILE)); // ? ヘッダが大きすぎる。
	return retval;
}
