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

autoList<char *> *tokenize(char *line, char *delimiters)
{
	autoList<char *> *tokens = new autoList<char *>();
	autoList<char> *token = new autoList<char>();

	for(char *p = line; *p; p++)
	{
		char *d;

		for(d = delimiters; *d; d++)
			if(*d == *p)
				break;

		if(*d)
		{
			token->AddElement('\0');
			tokens->AddElement(token->UnbindBuffer());
		}
		else
			token->AddElement(*p);
	}
	token->AddElement('\0');
	tokens->AddElement(token->UnbindBuffer());

	delete token;
	return tokens;
}
autoList<char *> *resTokenize(char *line, char *delimiters)
{
	autoList<char *> *tokens = tokenize(line, delimiters);

	for(int index = 0; index < tokens->GetCount(); index++)
	{
		char *token = tokens->GetElement(index);

//		toRangeToken(token, '\x20', '\x7e'); // ascii
		toRangeToken(token, '\x20', '\xfc'); // sjis

		trim(token, ' ');

		if(!*token) // ? == "" -> 除去
		{
			memFree(token);
			tokens->DesertElement(index);
			index--;
		}
	}
	return tokens;
}
autoList<char *> *resTokenize_xc(char *line, char *delimiters)
{
	autoList<char *> *out = resTokenize(line, delimiters);
	memFree(line);
	return out;
}
char *untokenize(autoList<char *> *tokens, char *separator)
{
	autoList<char> *buffer = new autoList<char>();

	for(int index = 0; index < tokens->GetCount(); index++)
	{
		char *token = tokens->GetElement(index);

		if(index)
			buffer->AddElements(separator, strlen(separator));

		buffer->AddElements(token, strlen(token));
	}
	buffer->AddElement('\0');
	char *line = buffer->UnbindBuffer();
	delete buffer;
	return line;
}
char *untokenize_xc(autoList<char *> *tokens, char *separator)
{
	char *out = untokenize(tokens, separator);
	releaseList(tokens, (void (*)(char *))memFree);
	return out;
}

#define CB_MINSIZE 16

static uchar CB_Buff[CB_MINSIZE];

void copyBlock(void *dest, void *src, int size) // 20140622_debug
{
	if(dest == src)
		return;

	if(size == 0)
		return;

	if((uchar *)dest + size <= src || (uchar *)src + size <= dest) // ? 重複ナシ
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

char *findMbsChar(char *line, int chr)
{
	for(char *p = line; *p; mbcInc(p))
		if(*p == chr)
			return p;

	return NULL; // not found
}
char *findMbsLastChar(char *line, int chr)
{
	errorCase(chr == '\0');

	char *p = findMbsChar(line, chr);

	if(p)
	{
		for(; ; )
		{
			char *tmp = findMbsChar(p + 1, chr);

			if(!tmp)
				break;

			p = tmp;
		}
	}
	return p;
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

	for(char *p = str; *p; )
	{
		if(!(ignoreCase ? _strnicmp : strncmp)(p, srcPtn, srcPtnLen)) // ? srcPtn 発見
		{
			buff->AddElements(destPtn, destPtnLen);
			p += srcPtnLen;
		}
		else if(isMbc(p))
		{
			buff->AddElement(p[0]);
			buff->AddElement(p[1]);
			p += 2;
		}
		else
		{
			buff->AddElement(*p);
			p++;
		}
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

char *addToken(char *buffer, char *token)
{
	char *newBuffer = xcout("%s%s", buffer, token);
	memFree(buffer);
	return newBuffer;
}
char *addToken_x(char *buffer, char *token)
{
	char *newBuffer = addToken(buffer, token);
	memFree(token);
	return newBuffer;
}
char *addChar(char *buffer, int chr)
{
	char *newBuffer = xcout("%s%c", buffer, chr);
	memFree(buffer);
	return newBuffer;
}

void toRangeToken(char *str, int minchr, int maxchr)
{
	for(char *p = str; *p; p++)
	{
		m_range(*p, minchr, maxchr);
	}
}
char *toJToken(char *str, int minchr, int maxchr)
{
	char *buffer = strx("");

	for(char *p = str; *p; p++)
	{
		if(isJChar(p))
		{
			buffer = addChar(buffer, p[0]);
			buffer = addChar(buffer, p[1]);
			p++;
		}
		else
		{
			int chr = *p;
			m_range(chr, minchr, maxchr);
			buffer = addChar(buffer, chr);
		}
	}
	return buffer;
}
char *toJToken_x(char *str, int minchr, int maxchr)
{
	char *ret = toJToken(str, minchr, maxchr);
	memFree(str);
	return ret;
}
