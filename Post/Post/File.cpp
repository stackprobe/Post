#include "all.h"

int existPath(char *path)
{
	return !m_isEmpty(path) && !_access(path, 0);
}
int existFile(char *file)
{
	return existPath(file) && !(GetFileAttributes(file) & FILE_ATTRIBUTE_DIRECTORY);
}
int existDir(char *dir)
{
	return existPath(dir) && GetFileAttributes(dir) & FILE_ATTRIBUTE_DIRECTORY;
}

void trimPath(char *path)
{
	escapeYen(path);
	trimSequ(path, '/');
	unescapeYen(path);
}
char *combine(char *dir, char *file)
{
	if(dir[0] && dir[1] == ':' && dir[2] == '\0')
	{
		static char buff[] = "?:.";

		buff[0] = dir[0];
		dir = buff;
	}
	char *dirFile = xcout("%s\\%s", dir, file);

	trimPath(dirFile);
	return dirFile;
}
char *combine_cx(char *dir, char *file)
{
	char *out = combine(dir, file);
	memFree(file);
	return out;
}
char *combine_xc(char *dir, char *file)
{
	char *out = combine(dir, file);
	memFree(dir);
	return out;
}
char *getDir(char *path)
{
	path = strx(path);
	escapeYen(path);
	char *p = strrchr(path, '/');

	if(p)
	{
		*p = '\0';
		unescapeYen(path);

		// ? ルートディレクトリ
		if(
			path[0] &&
			path[1] == ':' &&
			path[2] == '\0'
			)
		{
			path[2] = '\\';
			path[3] = '\0';
		}
	}
	else
		strz(path, ".");

	return path;
}
char *getDir_x(char *path)
{
	char *out = getDir(path);
	memFree(path);
	return out;
}
char *getLocalPath(char *path)
{
	path = strx(path);
	escapeYen(path);
	char *p = strrchr(path, '/');

	if(p)
	{
		p = strx(p + 1);
		memFree(path);
		path = p;
	}
	return path;
}
char *getLocalPath_x(char *path)
{
	char *out = getLocalPath(path);
	memFree(path);
	return out;
}

void setCwd(char *dir)
{
	errorCase(m_isEmpty(dir));
	errorCase(_chdir(dir)); // ? 失敗
}
void setCwd_x(char *dir)
{
	setCwd(dir);
	memFree(dir);
}
char *getCwd(void)
{
	char *dirBuff = _getcwd(NULL, 0);
	errorCase(m_isEmpty(dirBuff));
	char *dir = strx(dirBuff);
	free(dirBuff);
	return dir;
}
static oneObject(autoList<char *>, new autoList<char *>(), GetCwdStack)

void addCwd(char *dir)
{
	GetCwdStack()->AddElement(getCwd());
	setCwd(dir);
}
void addCwd_x(char *dir)
{
	addCwd(dir);
	memFree(dir);
}
void unaddCwd(void)
{
	setCwd_x(GetCwdStack()->UnaddElement());
}

// sync > @ My_mkdir

static void My_mkdir_WrLog(char *message)
{
	cout("%s\n", message);

#if 0
	{
		char *logFile = xcout("%s_MKDIR.log", getSelfFile());
		FILE *logFp;

		logFp = fileOpen(logFile, "at");
		writeLine(logFp, message);
		fileClose(logFp);

		memFree(logFile);
	}
#endif
}
static void My_mkdir_WrLog_x(char *message)
{
	My_mkdir_WrLog(message);
	memFree(message);
}
/*
	2019.2.18
	・WHTTR.exe(HTT_RPC)を起動する。
		WHTTR.exeがHTT.exeを起動する。このとき...
			WHTTR.exe起動時にWindowsDefenderのSmartScreenが表示されること。
			AntiWindowsDefenderSmartScreen()によってHTT.exeがWHTTR.exeによって読み込み・削除・書き出しされること。
	・WindowsDefenderのリアルタイム保護をオフにする。<-- 必須ではないかも。
	・デスクトップをロックして放置する。
	この手順で CreateDirectory, _mkdir が稀に失敗する。<-- 1分毎の空実行時の作業ディレクトリの作成。作成可能なはず。
	失敗した場合 MD で1回リトライすれば成功する模様。
	Sleepと5回のリトライは念の為。
*/
static int My_mkdir(char *dir) // ret: ? 失敗
{
#if 1
	if(CreateDirectory(dir, NULL) == 0) // ? 失敗
	{
		My_mkdir_WrLog_x(xcout("CreateDirectory() failed \"%s\" %u @ %I64d", dir, GetLastError(), time(NULL)));
		My_mkdir_WrLog("*1");

		for(int c = 0; ; c++)
		{
			Sleep(100);
			My_mkdir_WrLog("*2");

			if(existDir(dir))
				break;

			My_mkdir_WrLog("*3");

			if(5 <= c)
			{
				My_mkdir_WrLog("*3.5");
				return 1;
			}
			My_mkdir_WrLog("*4");
			Sleep(100);

			{
				char *command = xcout("MD \"%s\"", dir);
				system(command);
				memFree(command);
			}
		}
		My_mkdir_WrLog("*5");
	}
	return 0;
#elif 1
	if(CreateDirectory(dir, NULL) == 0) // ? 失敗
	{
		return 1;
	}
	return 0;
#else
	if(_mkdir(dir)) // ? 失敗
	{
		return 1;
	}
	return 0;
#endif
}

// < sync

void createFile(char *file)
{
	errorCase(m_isEmpty(file));
	fileClose(fileOpen(file, "wb"));
}
void createDir(char *dir)
{
	errorCase(m_isEmpty(dir));
	errorCase(My_mkdir(dir)); // ? 失敗
}

void removeFile(char *file)
{
	errorCase(m_isEmpty(file));
	remove(file);
}
void removeDir(char *dir)
{
	errorCase(m_isEmpty(dir));
	_rmdir(dir);
}
void clearDir(char *dir)
{
	autoList<char *> *paths = lss(dir);

	while(paths->GetCount())
	{
		char *path = paths->UnaddElement();

		remove(path);
		_rmdir(path);

		memFree(path);
	}
	delete paths;
}
void forceRemoveDir(char *dir)
{
	clearDir(dir);
	_rmdir(dir);
}

void fileMove(char *rFile, char *wFile)
{
	errorCase(rename(rFile, wFile)); // ? 失敗
}
void fileCopy(char *rFile, char *wFile)
{
	remove(wFile); // anti rFile == wFile

	FILE *rfp = fileOpen(rFile, "rb");
	FILE *wfp = fileOpen(wFile, "wb");

	__int64 rCount = getFileSize(rFile);

	const int buffSize = 1000000;
	uchar *buff = (uchar *)memAlloc(buffSize);

	while(0 < rCount)
	{
		int rSize = (int)m_min(rCount, buffSize);

		fileRead(rfp, buff, rSize);
		fileWrite(wfp, buff, rSize);

		rCount -= rSize;
	}
	memFree(buff);

	fileClose(rfp);
	fileClose(wfp);
}

char *getFullPath(char *path, char *baseDir)
{
	errorCase(m_isEmpty(path));
	errorCase(m_isEmpty(baseDir));

	addCwd(baseDir);
	path = _fullpath(NULL, path, 0);
	unaddCwd();

	char *retPath = strx(path);
	free(path);
	return retPath;
}
static char *GetExtPeriod(char *path)
{
	char *p = strrchr(path, '.');

	if(!p || findMbsChar(p + 1, '\\'))
		return NULL;

	return p;
}
char *getExt(char *path)
{
	char *p = GetExtPeriod(path);

	if(p)
		p++;
	else
		p = strchr(path, '\0');

	return p;
}
int removeExt(char *path) // ret: ? removed
{
	char *p = GetExtPeriod(path);

	if(p)
	{
		*p = '\0';
		return 1;
	}
	return 0;
}
char *addExt(char *path, char *ext)
{
	return addToken_x(path, xcout(".%s", ext));
}
