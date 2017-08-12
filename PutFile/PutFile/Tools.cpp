#include "all.h"

int getZero(void)
{
	return 0;
}
__int64 s2i64(char *line)
{
	__int64 result = 0;
	int sign = 1;

	for(char *p = line; *p; p++)
	{
		int digit = -1;

		if(*p == '-')
		{
			sign = -1;
		}
		else if(*p == '\x82') // "０" == { '\x82', '\x4f' }
		{
			p++;

			if(!*p)
				break;

			if('\x4f' <= *p && *p <= '\x58')
			{
				digit = *p - 0x4f;
			}
		}
		else if('0' <= *p && *p <= '9')
		{
			digit = *p - '0';
		}
		if(0 <= digit)
		{
			if((_I64_MAX - 9) / 10 < result)
				break;

			result *= 10;
			result += digit;
		}
	}
	return result * sign;
}
__int64 s2i64_x(char *line)
{
	__int64 value = s2i64(line);
	memFree(line);
	return value;
}
int s2i(char *line)
{
	__int64 value = s2i64(line);
	errorCase(value < -INT_MAX || INT_MAX < value);
	return (int)value;
}
int s2i_x(char *line)
{
	int value = s2i(line);
	memFree(line);
	return value;
}

int compInt(int a, int b)
{
	if(a < b) return -1;
	if(b < a) return 1;
	return 0;
}
int compI2D(i2D_t a, i2D_t b)
{
	int retval = compInt(a.X, b.X);

	if(!retval)
		retval = compInt(a.Y, b.Y);

	return retval;
}

int isHitKey(int key)
{
	int hit = 0;

	while(_kbhit())
	{
		cout("stdin %d\n", key);

		if(_getch() == key)
		{
			hit = 1;
		}
		cout("hit: %d\n", hit);
	}
	return hit;
}

void addValue(autoList<uchar> *block, uint64 value)
{
	block->AddElement(value >> 8 * 0 & 0xff);
	block->AddElement(value >> 8 * 1 & 0xff);
	block->AddElement(value >> 8 * 2 & 0xff);
	block->AddElement(value >> 8 * 3 & 0xff);
	block->AddElement(value >> 8 * 4 & 0xff);
	block->AddElement(value >> 8 * 5 & 0xff);
	block->AddElement(value >> 8 * 6 & 0xff);
	block->AddElement(value >> 8 * 7 & 0xff);
}
uint64 unaddValue64(autoList<uchar> *block)
{
	uint64 value = (uint64)block->UnaddElement() << 8 * 7;

	value |= (uint64)block->UnaddElement() << 8 * 6;
	value |= (uint64)block->UnaddElement() << 8 * 5;
	value |= (uint64)block->UnaddElement() << 8 * 4;
	value |= (uint64)block->UnaddElement() << 8 * 3;
	value |= (uint64)block->UnaddElement() << 8 * 2;
	value |= (uint64)block->UnaddElement() << 8 * 1;
	value |= (uint64)block->UnaddElement() << 8 * 0;

	return value;
}

char *incrementColumnDigits(char *column, char *digits) // ret: strr(column)
{
	char *p = strchr(column, '\0');
	char *enddp;

	errorCase(!digits[0]);
	enddp = strchr(digits, '\0') - 1;

	while(column < p)
	{
		int d = *--p;
		char *dp;

		dp = strchr(digits, d);

		if(!dp)
		{
			if(!p[1]) column = addChar(column, '~'); // column の最後に digits が無い -> column と digist のデリミタを付加
			break;
		}
		if(dp < enddp)
		{
			*p = dp[1];
			goto endfunc;
		}
		*p = digits[0];
	}
	column = addChar(column, digits[0]);

	for(p = strchr(column, '\0') - 1; column < p; p--)
		if(p[-1] != digits[0])
			break;

	*p = digits[1];

endfunc:
	return column;
}
char *incrementPathDigits(char *path, char *digits) // ret: strr(path)
{
	char *ext = strx(getExt(path));
	char *path2 = path;

	path = strx(path);
	removeExt(path);
	path = incrementColumnDigits(path, digits);
	path = addExt(path, ext);

	memFree(ext);
	memFree(path2);
	return path;
}
char *incrementColumn(char *column)
{
	return incrementColumnDigits(column, DIGITS);
}
char *incrementPath(char *path)
{
	return incrementPathDigits(path, DIGITS);
}
char *toCreatablePath(char *path, int faultCountMax) // ret: strr(path)
{
	if(existPath(path))
	{
		{
			char *ext = strx(getExtWithDot(path));

			removeExt(path);
			path = addToken(path, "~0");
			path = addToken(path, ext);

			memFree(ext);
		}

		int faultCount = 0;

		while(existPath(path))
		{
			errorCase_m(faultCountMax <= faultCount, "同じ名前のファイル大杉");
			faultCount++;

			path = incrementPath(path);
		}
	}
	return path;
}

char *getDateTimeStamp(time_t t)
{
	char *stamp;

	if(t == 0i64)
		t = time(NULL);

	stamp = ctime(&t); // "Wed Jan 02 02:03:55 1980\n"

	if(!stamp) // ? 不正な t
		stamp = "Thu Jan 01 00:00:00 1970\n";

	stamp = strx(stamp);
	stamp[24] = '\0';

	return stamp; // "Wed Jan 02 02:03:55 1980"
}
char *thousandComma(char *line) // ret: strr(line)
{
	autoList<char> *buffer = new autoList<char>(line, strlen(line));

	buffer->Reverse(); // 逆転

	for(int index = 3; index < buffer->GetCount(); index += 4)
	{
		buffer->InsertElement(index, ',');
	}
	buffer->Reverse(); // 復元

	buffer->AddElement('\0');
	line = buffer->UnbindBuffer();
	delete buffer;

	return line;
}
/*
	"Wed Jan 02 02:03:55 1980" -> "1980/01/02 (水) 02:03:55"
*/
char *makeJStamp(char *eStamp)
{
	autoList<char *> *dtParts = tokenize(eStamp, " ");
	errorCase(dtParts->GetCount() != 5);
	autoList<char *> *timeParts = tokenize(dtParts->GetElement(3), ":");
	errorCase(timeParts->GetCount() != 3);

	int y = s2i(dtParts->GetElement(4));
	int m = -1;
	int d = s2i(dtParts->GetElement(2));
	int h = s2i(timeParts->GetElement(0));
	int n = s2i(timeParts->GetElement(1));
	int s = s2i(timeParts->GetElement(2));
	int w = -1;

	const char *months[] =
	{
		"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", // "Dec",
	};
	const char *weeks[] =
	{
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", // "Sat",
	};
	const char *jWeeks[] =
	{
		"日", "月", "火", "水", "木", "金", "土",
	};

	for(m = 1; m < 12; m++)
		if(!strcmp(months[m - 1], dtParts->GetElement(1)))
			break;

	for(w = 1; w < 7; w++)
		if(!strcmp(weeks[w - 1], dtParts->GetElement(0)))
			break;

	errorCase(!m_isRange(y, 0, 9999));
	errorCase(!m_isRange(m, 1, 12));
	errorCase(!m_isRange(d, 1, 31));
	errorCase(!m_isRange(h, 0, 23));
	errorCase(!m_isRange(n, 0, 59));
	errorCase(!m_isRange(s, 0, 59));
	errorCase(!m_isRange(w, 1, 7));

	return xcout(
		"%04d/%02d/%02d (%s) %02d:%02d:%02d"
		,y
		,m
		,d
		,jWeeks[w - 1]
		,h
		,n
		,s
		);
}
char *makeJStamp_x(char *eStamp)
{
	char *out = makeJStamp(eStamp);
	memFree(eStamp);
	return out;
}
