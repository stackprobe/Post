#include "all.h"

int BatchMode;
int SilentMode;

void termination(int errorlevel)
{
	cout("exitcode: %d\n", errorlevel);
	exit(errorlevel);
}
void error2(char *source, int lineno, char *function, char *message)
{
	{
		static int once;

		if(once)
			exit(2);

		once = 1;
	}

	cout("PUTFILE.ERROR %s %d %s\n", source, lineno, function);

	if(message)
		cout("reason: %s\n", message);

	// app >

	LOGPOS();
	if(SendFileFullPath)
	{
		LOGPOS();

		{
			char *text = xcout(
				"<html>\n"
				"<head>\n"
				"<title>エラーが発生しました</title>\n"
				"</head>\n"
				"<body style=\"font-family: Meiryo, Arial; font-size: large;\">\n"
				"[PutFile]エラー @ %s %d %s<hr/>"
				"%s<hr/>"
				"<a href=\"/\">ここをクリックするとホームページに戻ります</a>"
				"</body>\n"
				"</html>\n"
				,source
				,lineno
				,function
				,message ? message : "エラーが発生しました。"
				);
			WriteResponseHtmlFile(text);
			memFree(text);
		}
	}
	LOGPOS();

	// < app

	termination(1);
}

// sync > @ cout

void cout(char *format, ...)
{
	va_list marker;

	va_start(marker, format);

	if(!strcmp(format, "%s"))
	{
		coutLongText(va_arg(marker, char *));
	}
	else if(!strcmp(format, "%s\n"))
	{
		coutLongText(va_arg(marker, char *));
		coutLongText("\n");
	}
	else
		coutLongText_x(vxcout(format, marker));

	va_end(marker);
}
char *xcout(char *format, ...)
{
	char *ret;
	va_list marker;

	va_start(marker, format);
	ret = vxcout(format, marker);
	va_end(marker);

	return ret;
}
char *vxcout(char *format, va_list marker)
{
	char *buffer;

	for(int size = strlen(format) + 100; ; size *= 2)
	{
		int ret;

#define MARGIN 10

		buffer = (char *)memAlloc(size + MARGIN * 2);
		ret = _vsnprintf(buffer, size + MARGIN, format, marker);

#undef MARGIN

		if(0 <= ret && ret <= size)
			break;

		memFree(buffer);
		errorCase(128 * 1024 * 1024 < size); // ANTI OVER-FLOW
	}
	return strr(buffer);
}
void coutLongText(char *text)
{
	char format[6]; // max: "%.99s"
	char *p;
	char *q;
	uint d;

	for(p = text; *p; p = q)
	{
#define PRINT_LMT 98

		for(q = p; *q && (uint)q - (uint)p < PRINT_LMT; q += _ismbblead(*q) ? 2 : 1)
		{}

#undef PRINT_LMT

		d = (uint)q - (uint)p;

		errorCase(sprintf(format, "%%.%us", d) < 0);
		errorCase(printf(format, p) != d);
	}
}
void coutLongText_x(char *text)
{
	coutLongText(text);
	memFree(text);
}

// < sync

static int ArgIndex = 1;

int argIs(char *spell)
{
	if(ArgIndex < __argc)
	{
		if(!_stricmp(__argv[ArgIndex], spell))
		{
			ArgIndex++;
			return 1;
		}
	}
	return 0;
}

char *getSelfFile(void)
{
	static char *fileBuff;

	if(!fileBuff)
	{
		const int BUFFSIZE = 1000;
		const int MARGINSIZE = 10;

		fileBuff = (char *)memAlloc(BUFFSIZE + MARGINSIZE);
		errorCase(!GetModuleFileName(NULL, fileBuff, BUFFSIZE)); // ? 失敗
	}
	return fileBuff;
}
char *getSelfDir(void)
{
	static char *dirBuff;

	if(!dirBuff)
		dirBuff = getDir(getSelfFile());

	return dirBuff;
}
