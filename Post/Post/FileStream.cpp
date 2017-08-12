#include "all.h"

FILE *rfopen(char *file, char *mode)
{
	for(int retry = 0; ; retry++)
	{
		// fopen() ‚Íˆø”‚É–â‘è‚ª–³‚­‚Ä‚àA‹H‚É¸”s‚·‚é‚±‚Æ‚ª‚ ‚éB
		// “K“–‚ÉŠÔŠu‚ğ‹ó‚¯‚Ä‰½“x‚©ƒŠƒgƒ‰ƒC‚·‚éB
		FILE *fp = fopen(file, mode); // file == "" ‚Ì‚Æ‚« NULL ‚ğ•Ô‚·B

		if(fp != NULL)
		{
			if(retry)
				cout("File opened at %u-th retrial.\n", retry);

			return fp;
		}
		if(retry == 20)
		{
			cout("Can not open file \"%s\" as \"%s\" mode.\n", file, mode);
			return NULL;
		}
		Sleep(100);
	}
}
FILE *fileOpen(char *file, char *mode)
{
	FILE *fp = rfopen(file, mode);

	errorCase(!fp);
	return fp;
}
void fileClose(FILE *fp)
{
	errorCase(fclose(fp)); // ? ¸”s
}

__int64 getSeekPos(FILE *fp)
{
	__int64 pos = _ftelli64(fp);
	errorCase(pos < 0); // ? ¸”s
	return pos;
}
__int64 getFileSize(FILE *fp) // ƒV[ƒNˆÊ’u‚ğˆÚ“®‚·‚é‚±‚Æ‚É’ˆÓ
{
	errorCase(_fseeki64(fp, 0I64, SEEK_END)); // ? ¸”s
	__int64 size = _ftelli64(fp);
	errorCase(size < 0); // ? ¸”s || ‘å‚«‚·‚¬‚éB
	return size;
}
__int64 getFileSize(char *file)
{
	FILE *fp = fileOpen(file, "rb");
	__int64 size = getFileSize(fp);
	fileClose(fp);
	return size;
}
void setFileSize(char *file, __int64 size)
{
	FILE *fp = fileOpen(file, "ab");
	int fh = _fileno(fp);

	errorCase(_chsize_s(fh, size)); // ? ¸”s

	fileClose(fp);
}

int lastReadChar;

int readChar(FILE *fp)
{
	int chr = fgetc(fp);

	errorCase(chr == EOF && ferror(fp)); // ? ¸”s
	return lastReadChar = chr;
}
char *readLine(FILE *fp, int lenmax)
{
	autoList<char> *buffer = new autoList<char>();

	for(; ; )
	{
		int chr = readChar(fp);

		if(chr == '\r')
			continue;

		if(chr == '\n')
			break;

		if(chr == EOF)
		{
			if(!buffer->GetCount())
			{
				delete buffer;
				return NULL;
			}
			break;
		}
		errorCase(lenmax <= buffer->GetCount());
		buffer->AddElement(chr);
	}
	buffer->AddElement('\0');
	char *line = buffer->UnbindBuffer();
	delete buffer;
	return line;
}
char *readLine(char *file, int lenmax)
{
	FILE *fp = fileOpen(file, "rt");
	char *line = readLine(fp, lenmax);
	fileClose(fp);
	return line;
}

void writeChar(FILE *fp, int chr)
{
	errorCase(fputc(chr, fp) == EOF); // ? ¸”s
}
void writeToken(FILE *fp, char *token)
{
	for(char *p = token; *p; p++)
	{
		writeChar(fp, *p);
	}
}
void writeToken_x(FILE *fp, char *token)
{
	writeToken(fp, token);
	memFree(token);
}
void writeToken(char *file, char *token)
{
	FILE *fp = fileOpen(file, "wt");
	writeToken(fp, token);
	fileClose(fp);
}
void writeLine(FILE *fp, char *line)
{
	writeToken(fp, line);
	writeChar(fp, '\n');
}
void writeLine_x(FILE *fp, char *line)
{
	writeLine(fp, line);
	memFree(line);
}
void writeLine(char *file, char *line)
{
	FILE *fp = fileOpen(file, "wt");
	writeLine(fp, line);
	fileClose(fp);
}
void writeLine_cx(char *file, char *line)
{
	writeLine(file, line);
	memFree(line);
}

void fileSeek(FILE *fp, int origin, __int64 offset) // origin, offset ‚Ì•À‚Ñ‚Í fseek() ‚Æ‹t
{
	errorCase(_fseeki64(fp, offset, origin)); // ? ¸”s
}
void fileRead(FILE *fp, void *block, int size)
{
	if(size)
	{
		errorCase(fread(block, 1, size, fp) != size); // ? ¸”s || size ƒoƒCƒg“Ç‚İ‚Ş‘O‚É EOF ‚É“’B
		errorCase(ferror(fp));
	}
}
void fileWrite(FILE *fp, void *block, int size)
{
	if(size)
	{
		errorCase(fwrite(block, 1, size, fp) != size); // ? ¸”s
		errorCase(ferror(fp));
	}
}

int fileReadMax(FILE *fp, void *block, int size)
{
	if(size)
	{
		int retval = fread(block, 1, size, fp);
		errorCase(retval < 0 || size < retval);
		errorCase(ferror(fp));
		return retval;
	}
	return 0;
}
