#include "all.h"

#define RTTE_LENMAX 1000

// ---- items ----

__int64 DiskFreeMin = 2000000000;
int CopyBuffSize = 20000000;

// ----

static int ConfLineNo;

static char *ReadConfLine(FILE *fp)
{
	for(; ; )
	{
		char *line = readLine(fp);

		errorCase_m(!line, "read eof @ config-file");

		ConfLineNo++;

		if(line[0] == '\0') // 空行
			continue;

		if(line[0] == ';') // コメント行
			continue;

		cout("confLine(%d): %s\n", ConfLineNo, line);
		return line;
	}
}
static int ToInt_x(char *line, int minval, int maxval)
{
	errorCase(maxval < minval);

	int value;

	if(!_stricmp(line, "IMAX"))
		value = IMAX;
	else
		value = atoi(line);

	errorCase_m(!m_isRange(value, minval, maxval), "out of range @ config-file");

	memFree(line);
	return value;
}

void LoadConfig(void)
{
	// ---- set default ----

	// none

	// ----

	LOGPOS();

	char *confFile = (char *)memAlloc(strlen(getSelfFile()) + 100);
	strcpy(confFile, getSelfFile());
	strcpy(strchr(confFile, '\0') - 3, "conf");

	if(existFile(confFile))
	{
		LOGPOS();

		FILE *fp = fileOpen(confFile, "rt");
		ConfLineNo = 0;

		// ---- read items ----

		DiskFreeMin = ToInt_x(ReadConfLine(fp), 1, IMAX);
		DiskFreeMin *= 1000000;

		CopyBuffSize = ToInt_x(ReadConfLine(fp), 1, 100);
		CopyBuffSize *= 1000000;

		// ----

		fileClose(fp);
	}
	memFree(confFile);

	cout("DiskFreeMin: %I64d\n", DiskFreeMin);
	cout("CopyBuffSize: %d\n", CopyBuffSize);
}

__int64 GetReqContentLengthMax(void)
{
	static __int64 ret = 9220000000000000001;
	static int retLoaded;

	if(!retLoaded)
	{
		char *clmFile = (char *)memAlloc(strlen(getSelfFile()) + 100);
		strcpy(clmFile, getSelfFile());
		strcpy(strchr(clmFile, '\0') - 7, "utFile.dat");

		if(existFile(clmFile))
		{
			FILE *fp = fileOpen(clmFile, "rb");

			memFree(readLine(fp)); // 1行目

			ret = _atoi64(readLine(fp)); // 2行目 == UploadDirSizeMax
			m_range(ret, 1, I64_TOO_BIG);

			fileClose(fp);

			cout("rclm_orig: %I64d\n", ret);

			// margin
			{
				uint64 tmp = ret;

				tmp += 1000000;
				tmp += tmp / 2;
				m_minim(tmp, I64_TOO_BIG);

				ret = (__int64)tmp;
			}
		}
		memFree(clmFile);
	}
	cout("ReqContentLengthMax: %I64d\n", ret);
	return ret;
}
