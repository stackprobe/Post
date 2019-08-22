#include "all.h"

FILE *rfopen(char *file, char *mode)
{
	for(int retry = 0; ; retry++)
	{
		// fopen() ÇÕà¯êîÇ…ñ‚ëËÇ™ñ≥Ç≠ÇƒÇ‡ÅAãHÇ…é∏îsÇ∑ÇÈÇ±Ç∆Ç™Ç†ÇÈÅB
		// ìKìñÇ…ä‘äuÇãÛÇØÇƒâΩìxÇ©ÉäÉgÉâÉCÇ∑ÇÈÅB
		FILE *fp = fopen(file, mode); // file == "" ÇÃÇ∆Ç´ NULL Çï‘Ç∑ÅB

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

		// sync > @ HTT_rfopen_ForceCreateRecvFile

#define RFOPEN_FORCE_CREATE_FILE "Recv.httdat"

		if(mode[0] == 'r' && !strcmp(file, RFOPEN_FORCE_CREATE_FILE))
		{
			DWORD lastError = GetLastError();

			cout("fopen RecvFile LastError: %d\n", (int)lastError);

			if(lastError == ERROR_VIRUS_INFECTED || lastError == ERROR_VIRUS_DELETED || _access(RFOPEN_FORCE_CREATE_FILE, 0))
			{
				LOGPOS();

				file = RFOPEN_FORCE_CREATE_FILE ".2";
				writeLine(file,
					"                " "                " "                " "                "
					"                " "                " "                " "                "
					"                " "                " "                " "                "
					"                " "                " "                " "                " // SP x 256
					);
			}
		}

#undef RFOPEN_FORCE_CREATE_FILE

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
	errorCase(fclose(fp)); // ? é∏îs
}

__int64 getSeekPos(FILE *fp)
{
	__int64 pos = _ftelli64(fp);
	errorCase(pos < 0); // ? é∏îs
	return pos;
}
__int64 getFileSize(FILE *fp) // ÉVÅ[ÉNà íuÇà⁄ìÆÇ∑ÇÈÇ±Ç∆Ç…íçà”
{
	errorCase(_fseeki64(fp, 0I64, SEEK_END)); // ? é∏îs
	__int64 size = _ftelli64(fp);
	errorCase(size < 0); // ? é∏îs || ëÂÇ´Ç∑Ç¨ÇÈÅB
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

	errorCase(_chsize_s(fh, size)); // ? é∏îs

	fileClose(fp);
}

int lastReadChar;

int readChar(FILE *fp)
{
	int chr = fgetc(fp);

	errorCase(chr == EOF && ferror(fp)); // ? é∏îs
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
	errorCase(fputc(chr, fp) == EOF); // ? é∏îs
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

void fileSeek(FILE *fp, int origin, __int64 offset) // origin, offset ÇÃï¿Ç—ÇÕ fseek() Ç∆ãt
{
	errorCase(_fseeki64(fp, offset, origin)); // ? é∏îs
}
void fileRead(FILE *fp, void *block, int size)
{
	if(size)
	{
		errorCase(fread(block, 1, size, fp) != size); // ? é∏îs || size ÉoÉCÉgì«Ç›çûÇﬁëOÇ… EOF Ç…ìûíB
		errorCase(ferror(fp));
	}
}
void fileWrite(FILE *fp, void *block, int size)
{
	if(size)
	{
		errorCase(fwrite(block, 1, size, fp) != size); // ? é∏îs
		errorCase(ferror(fp));
	}
}
