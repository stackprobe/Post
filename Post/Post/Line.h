char *strx(char *line);
char *strr(char *line);
void strz(char *&buffer, char *line);
char *n2x(char *str);

void copyBlock(void *dest, void *src, int size);
void copyLine(char *dest, char *src);

void trimLead(char *line, int chr);
void trimTrail(char *line, int chr);
void trimEdge(char *line, int chr);
void trimSequ(char *line, int delimChr);
void trim(char *line, int chr);

#define isMbc1(chr) \
	(_ismbblead((chr)))

#define isMbc2(chr) \
	(_ismbbtrail((chr)))

#define mbcNext(p) \
	((p) + (isMbc1(*(p)) && (p)[1] ? 2 : 1))

#define mbcInc(p) \
	((p) = mbcNext((p)))

void replaceMbsChar(char *line, int chr1, int chr2);
void escapeYen(char *line);
void unescapeYen(char *line);
char *replace(char *str, char *srcPtn, char *destPtn, int ignoreCase = 0);

int toLower(int chr);
int mbs_stricmp(char *str1, char *str2, int num = INT_MAX);
int mbs_stristart(char *str, char *ptn);
char *mbs_stristr(char *str, char *ptn);

int my_strncmp(char *str1, char *str2, int num);
int strstart(char *str, char *ptn);

char *addToken(char *buffer, char *token);

void toRangeToken(char *token, int minchr, int maxchr, int subchr);
void toAsciiToken(char *token);
void to09AZazToken(char *token);
