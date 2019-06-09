#include "all.h"

char *strx(char *line)
{
	return strcpy((char *)memAlloc(strlen(line) + 1), line);
}
char *strr(char *line)
{
	return (char *)memRealloc(line, strlen(line) + 1);
}
void strz(char *&buffer, char *line)
{
	memFree(buffer);
	buffer = strx(line);
}
char *n2x(char *str)
{
	if(!str)
		str = strx("");

	return str;
}

#define CB_MINSIZE 16

static uchar CB_Buff[CB_MINSIZE];

void copyBlock(void *dest, void *src, int size) // 20140622_debug
{
	if(dest == src)
		return;

	if(size == 0)
		return;

	if((uchar *)dest + size <= src || (uchar *)src + size <= dest) // ? d•¡ƒiƒV
	{
		memcpy(dest, src, size);
	}
	else if(size <= CB_MINSIZE)
	{
		memcpy(CB_Buff, src, size);
		memcpy(dest, CB_Buff, size);
	}
	else
	{
		int half = size / 2;

		if(dest < src)
			copyBlock(dest, src, half);

		copyBlock((uchar *)dest + half, (uchar *)src + half, size - half);

		if(src < dest)
			copyBlock(dest, src, half);
	}
}
void copyLine(char *dest, char *src)
{
	copyBlock(dest, src, strlen(src) + 1);
}

void trimLead(char *line, int chr)
{
	char *p;

	for(p = line; *p; p++)
		if(*p != chr)
			break;

	copyLine(line, p);
}
void trimTrail(char *line, int chr)
{
	char *p;

	for(p = strchr(line, '\0'); line < p; p--)
		if(p[-1] != chr)
			break;

	*p = '\0';
}
void trimEdge(char *line, int chr)
{
	trimLead(line, chr);
	trimTrail(line, chr);
}
void trimSequ(char *line, int delimChr)
{
	/*
		debug segv @ 2016.4.7
	*/

	char *n = line;

	errorCase(delimChr == '\0');

	while(n = strchr(n, delimChr))
	{
		n++;

		if(*n == delimChr)
		{
			char *f = n;

			do
			{
				f++;
			}
			while(*f == delimChr);

			while(*f)
			{
				if(*f == delimChr)
					while(f[1] == delimChr)
						f++;

				*n++ = *f++;
			}
			*n = '\0';
			break;
		}
	}
}
void trim(char *line, int chr)
{
	trimEdge(line, chr);
	trimSequ(line, chr);
}

void replaceMbsChar(char *line, int chr1, int chr2)
{
	for(char *p = line; *p; mbcInc(p))
		if(*p == chr1)
			*p = chr2;
}
void escapeYen(char *line)
{
	replaceMbsChar(line, '\\', '/');
}
void unescapeYen(char *line)
{
	replaceMbsChar(line, '/', '\\');
}
char *replace(char *str, char *srcPtn, char *destPtn, int ignoreCase) // ret: strr(str)
{
	autoList<char> *buff = new autoList<char>();

	int srcPtnLen = strlen(srcPtn);
	int destPtnLen = strlen(destPtn);

	errorCase(srcPtnLen < 1);

	for(char *p = str; *p; p++)
	{
		if(!(ignoreCase ? _strnicmp : strncmp)(p, srcPtn, srcPtnLen)) // ? srcPtn ”­Œ©
		{
			buff->AddElements(destPtn, destPtnLen);
			p += srcPtnLen - 1;
		}
		else
			buff->AddElement(*p);
	}
	memFree(str);

	buff->AddElement('\0');
	char *out = buff->UnbindBuffer();
	delete buff;
	return out;
}

int toLower(int chr)
{
	if('A' <= chr && chr <= 'Z')
	{
		chr += 'a' - 'A';
	}
	return chr;
}
int mbs_stricmp(char *str1, char *str2, int num)
{
	int onMbc = 0;

	for(int index = 0; index < num; index++)
	{
		int chr1 = str1[index];
		int chr2 = str2[index];

		if(!chr1 && !chr2)
			break;

		if(onMbc)
		{
			onMbc = 0;
		}
		else if(isMbc1(chr1))
		{
			onMbc = 1;
		}
		else
		{
			chr1 = toLower(chr1);
			chr2 = toLower(chr2);
		}

		if(chr1 != chr2)
		{
			return chr1 - chr2;
		}
	}
	return 0;
}
int mbs_stristart(char *str, char *ptn)
{
	return mbs_stricmp(str, ptn, strlen(ptn));
}
char *mbs_stristr(char *str, char *ptn)
{
	for(char *p = str; *p; mbcInc(p))
		if(!mbs_stristart(p, ptn))
			return p;

	return NULL; // not found
}

int my_strncmp(char *str1, char *str2, int num)
{
	for(int index = 0; index < num; index++)
	{
		if(str1[index] != str2[index]) return (int)str1[index] - (int)str2[index];
		if(str1[index] == '\0') break;
	}
	return 0;
}
int strstart(char *str, char *ptn)
{
	return my_strncmp(str, ptn, strlen(ptn));
}

char *addToken(char *buffer, char *token)
{
	char *newBuffer = xcout("%s%s", buffer, token);
	memFree(buffer);
	return newBuffer;
}

void toRangeToken(char *token, int minchr, int maxchr, int subchr)
{
	for(char *p = token; *p; p++)
		if(m_isRange(*p, minchr, maxchr) == 0)
			*p = subchr;
}
void toAsciiToken(char *token)
{
	toRangeToken(token, '\x20', '\x7e', '\x20'); // '\t' etc. -> ' '
}
void to09AZazToken(char *token)
{
	for(char *p = token; *p; p++)
	{
		if(
			'0' <= *p && *p <= '9' ||
			'A' <= *p && *p <= 'Z' ||
			'a' <= *p && *p <= 'z' ||
			*p == '-' ||
			*p == '_'
			)
		{}
		else
			*p = '$';
	}
}
