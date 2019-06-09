#include "all.h"

int BatchMode;
int SilentMode;

void termination(int errorlevel)
{
	_fcloseall();

	if(RemoveSendFileAtTermination)
	{
		LOGPOS();
		remove(SendFileFullPath);
	}
	exit(errorlevel);
}
void error2(char *source, int lineno, char *function, char *message)
{
	{
		static int passed;

		if(passed)
			exit(2);

		passed = 1;
	}

	cout("POST.ERROR %s %d %s\n", source, lineno, function);

	if(message)
		cout("reason: %s\n", message);

	HTT_Disconnect();
	/*
	{
		char *text = xcout(
			"<html>\n"
			"<head>\n"
			"<title>エラーが発生しました</title>\n"
			"</head>\n"
			"<body>\n"
			"<h1>[Post]エラー @ %s %d %s<hr/>\n"
			"<a href=\"/\">ここをクリックするとホームページに戻ります</a></h1>"
			"</body>\n"
			"</html>\n"
			,source
			,lineno
			,function
			);
		WriteResponseHtmlFile(text);
		memFree(text);
	}
	*/

	termination(1);
}
void ErrorRes2(char *source, int lineno, char *function)
{
	char *text = xcout(
		"<html>\n"
		"<head>\n"
		"<title>エラーが発生しました</title>\n"
		"</head>\n"
		"<body style=\"font-family: Meiryo, Arial; font-size: large;\">\n"
		"[Post]エラー @ %s %d %s<hr/>\n"
		"<a href=\"/\">ここをクリックするとホームページに戻ります</a>"
		"</body>\n"
		"</html>\n"
		,source
		,lineno
		,function
		);
	WriteResponseHtmlFile(text);
	memFree(text);

	termination(2);
}
void ErrorRes_417(void)
{
	//errorCase(!SendFileFullPath); // この場合、切断(HTT_Disconnect)が効かないので敢えて続行ということだと思う。@ 2018.2.19
	if(!SendFileFullPath)
	{
		LOGPOS();
		return;
	}
	errorCase(!ResponseModeFileFullPath);

	FILE *fp = fileOpen(SendFileFullPath, "wb");

	writeToken(fp, "HTTP/1.1 417 Green Tea" CRLF);
	writeToken(fp, "Server: htt" CRLF);
	writeToken(fp, "Connection: close" CRLF);
	writeToken(fp, CRLF);

	fileClose(fp);

	createFile(ResponseModeFileFullPath);

	termination(2);
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

char *getArg(int index)
{
	errorCase(index < 0 || __argc - ArgIndex <= index);
	return __argv[ArgIndex + index];
}
char *nextArg(void)
{
	char *arg = getArg(0);

	ArgIndex++;
	return arg;
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
