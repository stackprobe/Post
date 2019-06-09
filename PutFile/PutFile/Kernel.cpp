#include "all.h"

uint64 lastDiskFree;
uint64 lastDiskFree_real;
uint64 lastDiskSize;

void updateDiskSpace(int drive)
{
	ULARGE_INTEGER a;
	ULARGE_INTEGER f;
	ULARGE_INTEGER t;

	errorCase(
		(drive < 'A' || 'Z' < drive) &&
		(drive < 'a' || 'z' < drive)
		);

	char dir[] = {
		drive,
		':',
		'\\',
		'\0',
	};

	/*
		�h���C�u�����݂��Ȃ� || �����o���Ă��Ȃ� -> ���s����B
	*/
	errorCase(!GetDiskFreeSpaceEx((LPCTSTR)dir, &a, &t, &f)); // ? ���s

	lastDiskFree      = (uint64)a.LowPart | (uint64)a.HighPart << 32;
	lastDiskFree_real = (uint64)f.LowPart | (uint64)f.HighPart << 32;
	lastDiskSize      = (uint64)t.LowPart | (uint64)t.HighPart << 32;
}
