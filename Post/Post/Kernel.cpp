#include "all.h"

// sync > @ updateDiskSpace

uint64 lastDiskFree_User; // このプロセスが使用出来る空き領域サイズ
uint64 lastDiskFree;
uint64 lastDiskSize;

static void S_UpdateDiskSpace(char *dir)
{
	ULARGE_INTEGER a;
	ULARGE_INTEGER f;
	ULARGE_INTEGER t;

	/*
		ドライブが存在しない || 準備出来ていない || ディレクトリが存在しない -> 失敗する。
	*/
	if (!(int)GetDiskFreeSpaceEx((LPCTSTR)dir, &a, &t, &f)) // ? 失敗
	{
		error();
	}
	lastDiskFree_User = (uint64)a.LowPart | (uint64)a.HighPart << 32;
	lastDiskFree      = (uint64)f.LowPart | (uint64)f.HighPart << 32;
	lastDiskSize      = (uint64)t.LowPart | (uint64)t.HighPart << 32;
}
/*
	ドライブが存在しない || 準備出来ていない -> error();
*/
void updateDiskSpace(int drive)
{
	char dir[4];

	errorCase(!isalpha(drive));

	dir[0] = drive;
	dir[1] = ':';
	dir[2] = '\\';
	dir[3] = '\0';

	S_UpdateDiskSpace(dir);
}
void updateDiskSpace_Dir(char *dir)
{
#if 0 // zantei
	return S_UpdateDiskSpace(dir);
#else
	int drive;

	errorCase(!*dir); // 2bs

	if(dir[1] == ':')
	{
		drive = dir[0];
	}
	else
	{
		dir = getCwd();
		drive = dir[0];
		memFree(dir);
	}
	return updateDiskSpace(drive);
#endif
}

// < sync
