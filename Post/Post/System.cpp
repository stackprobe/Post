#include "all.h"

int BatchMode;
int SilentMode;

static oneObject(autoList<void (*)(void)>, new autoList<void (*)(void)>(), GetFinalizers)

void addFinalizer(void (*func)(void))
{
	GetFinalizers()->AddElement(func);
}
void (*unaddFinalizer(void))(void)
{
	return GetFinalizers()->UnaddElement();
}

void termination(int errorlevel)
{
	while(GetFinalizers()->GetCount())
	{
		GetFinalizers()->UnaddElement()();
	}
	if(RemoveSendFileAtTermination)
	{
		LOGPOS();
		_fcloseall();
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
			"<title>�G���[���������܂���</title>\n"
			"</head>\n"
			"<body>\n"
			"<h1>[Post]�G���[ @ %s %d %s<hr/>\n"
			"<a href=\"/\">�������N���b�N����ƃz�[���y�[�W�ɖ߂�܂�</a></h1>"
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
		"<title>�G���[���������܂���</title>\n"
		"</head>\n"
		"<body style=\"font-family: Meiryo, Arial; font-size: large;\">\n"
		"[Post]�G���[ @ %s %d %s<hr/>\n"
		"<a href=\"/\">�������N���b�N����ƃz�[���y�[�W�ɖ߂�܂�</a>"
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
	//errorCase(!SendFileFullPath); // ���̏ꍇ�A�ؒf(HTT_Disconnect)�������Ȃ��̂Ŋ����đ��s�Ƃ������Ƃ��Ǝv���B@ 2018.2.19
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

void cout(char *format, ...)
{
	if(SilentMode)
		return;

	va_list marker;

	va_start(marker, format);
	errorCase(vprintf(format, marker) < 0);
	va_end(marker);
}
char *xcout(char *format, ...)
{
	char *buffer;
	int size;
	va_list marker;

	va_start(marker, format);

	for(size = strlen(format) + 128; ; size *= 2)
	{
		buffer = (char *)memAlloc(size + 20);
		int retval = _vsnprintf(buffer, size + 10, format, marker);
		buffer[size + 10] = '\0'; // �����I�ɕ���B

		if(0 <= retval && retval <= size)
			break;

		memFree(buffer);
		errorCase(128 * 1024 * 1024 < size); // anti-overflow
	}
	va_end(marker);

	return buffer;
}

static int ArgIndex = 1;

int hasArgs(int count)
{
	return count <= __argc - ArgIndex;
}
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
int getArgIndex(void)
{
	return ArgIndex;
}
void setArgIndex(int index)
{
	errorCase(index < 0 || __argc < index); // index == __argc �͑S���ǂݏI��������
	ArgIndex = index;
}

char *getSelfFile(void)
{
	static char *fileBuff;

	if(!fileBuff)
	{
		const int BUFFSIZE = 1000;
		const int MARGINSIZE = 10;

		fileBuff = (char *)memAlloc(BUFFSIZE + MARGINSIZE);
		errorCase(!GetModuleFileName(NULL, fileBuff, BUFFSIZE)); // ? ���s
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

#if 0 // �p�~ @ 2017.4.18
char *getTempRtDir(void)
{
#if 1
	return HomeDir;
#else
	static char *dir;
	
	if(!dir)
	{
		dir = getenv("TMP");

		if(!dir)
			dir = getenv("TEMP");

		errorCase(!dir);
		errorCase(!existDir(dir));
		dir = getFullPath(dir, getSelfDir()); // TMP, TEMP �̓t���p�X���Ǝv�����ǁA�O�̂��߁B���� dir �����̂��߁B
	}
	return dir;
#endif
}
char *makeTempPath(char *suffix)
{
	for(; ; )
	{
		char *pw = makePw36();
		char *path = combine_cx(getTempRtDir(), xcout("%s%s", pw, suffix));
		memFree(pw);

		if(!existPath(path))
			return path;

		memFree(path);
	}
}
char *makeTempFile(char *suffix)
{
	char *out = makeTempPath(suffix);
	createFile(out);
	return out;
}
char *makeTempDir(char *suffix)
{
	char *out = makeTempPath(suffix);
	createDir(out);
	return out;
}
#endif

double now(void)
{
	return clock() / (double)CLOCKS_PER_SEC;
}
char *getTimeStamp(time_t t) // t: 0 == ������
{
	static char timeStamp[25];
	char *p;

	if(!t)
		t = time(NULL);

	p = ctime(&t); // "Wed Jan 02 02:03:55 1980\n"

	if(!p) // ? invalid t
		p = "Thu Jan 01 00:00:00 1970";

	memcpy(timeStamp, p, 24);
	return timeStamp; // "Wed Jan 02 02:03:55 1980"
}
