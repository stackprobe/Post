#include "all.h"

// sync > @ updateDiskSpace

uint64 lastDiskFree_User; // ���݂̃��[�U�[�����p�ł���f�B�X�N�̋󂫃o�C�g��
uint64 lastDiskFree;
uint64 lastDiskSize;

static void S_UpdateDiskSpace(char *dir)
{
	ULARGE_INTEGER a;
	ULARGE_INTEGER f;
	ULARGE_INTEGER t;

	/*
		�h���C�u�����݂��Ȃ� || �����o���Ă��Ȃ� || �f�B���N�g�������݂��Ȃ� -> ���s����B
	*/
	if (!(int)GetDiskFreeSpaceEx((LPCTSTR)dir, &a, &t, &f)) // ? ���s
	{
		error();
	}
	lastDiskFree_User = (uint64)a.LowPart | (uint64)a.HighPart << 32;
	lastDiskFree      = (uint64)f.LowPart | (uint64)f.HighPart << 32;
	lastDiskSize      = (uint64)t.LowPart | (uint64)t.HighPart << 32;
}
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
	S_UpdateDiskSpace(dir);
}

// < sync
