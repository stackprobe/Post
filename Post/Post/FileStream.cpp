#include "all.h"

FILE *rfopen(char *file, char *mode)
{
	for(int retry = 0; ; retry++)
	{
		// fopen() は引数に問題が無くても、稀に失敗することがある。
		// 適当に間隔を空けて何度かリトライする。
		FILE *fp = fopen(file, mode); // file == "" のとき NULL を返す。

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

		// sync > @ HTT_rfopen_CheckDisease

		{
			DWORD lastError = GetLastError();

			if(lastError == ERROR_VIRUS_INFECTED || lastError == ERROR_VIRUS_DELETED)
			{
				LOGPOS();
				cout("file: \"%s\"\n", file);
				cout("mode: \"%s\"\n", mode);
				cout("lastError: %d\n", (int)lastError);
				return NULL;
			}
		}

		// < sync

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
	errorCase(fclose(fp)); // ? 失敗
}

__int64 getSeekPos(FILE *fp)
{
	__int64 pos = _ftelli64(fp);
	errorCase(pos < 0); // ? 失敗
	return pos;
}
__int64 getFileSize(FILE *fp) // シーク位置を移動することに注意
{
	errorCase(_fseeki64(fp, 0I64, SEEK_END)); // ? 失敗
	__int64 size = _ftelli64(fp);
	errorCase(size < 0); // ? 失敗 || 大きすぎる。
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

	errorCase(_chsize_s(fh, size)); // ? 失敗

	fileClose(fp);
}

int lastReadChar;

int readChar(FILE *fp)
{
	int chr = fgetc(fp);

	errorCase(chr == EOF && ferror(fp)); // ? 失敗
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

	if(!line)
		line = strx("");

	return line;
}

void writeChar(FILE *fp, int chr)
{
	errorCase(fputc(chr, fp) == EOF); // ? 失敗
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

void fileSeek(FILE *fp, int origin, __int64 offset) // origin, offset の並びは fseek() と逆
{
	errorCase(_fseeki64(fp, offset, origin)); // ? 失敗
}
void fileRead(FILE *fp, void *block, int size)
{
	if(size)
	{
		errorCase(fread(block, 1, size, fp) != size); // ? 失敗 || size バイト読み込む前に EOF に到達
		errorCase(ferror(fp));
	}
}
void fileWrite(FILE *fp, void *block, int size)
{
	if(size)
	{
		errorCase(fwrite(block, 1, size, fp) != size); // ? 失敗
		errorCase(ferror(fp));
	}
}
