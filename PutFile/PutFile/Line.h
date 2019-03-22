char *strx(char *line);
char *strr(char *line);
void strz(char *&buffer, char *line);
void strz_x(char *&buffer, char *line);

char *getConstNullString(void);
char *getNullString(void);

autoList<char *> *tokenize(char *line, char *delimiters);
autoList<char *> *tokenize_xc(char *line, char *delimiters);
autoList<char *> *resTokenize(char *line, char *delimiters);
autoList<char *> *resTokenize_xc(char *line, char *delimiters);
char *untokenize(autoList<char *> *tokens, char *separator);
char *untokenize_xc(autoList<char *> *tokens, char *separator);

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

#define isMbc(p) \
	(isMbc1(*(p)) && (p)[1])

#define mbcNext(p) \
	((p) + (isMbc((p)) ? 2 : 1))

#define mbcInc(p) \
	((p) = mbcNext((p)))

char *findMbsChar(char *line, int chr);
char *findMbsLastChar(char *line, int chr);
void replaceMbsChar(char *line, int chr1, int chr2);
void escapeYen(char *line);
void unescapeYen(char *line);
char *replace(char *str, char *srcPtn, char *destPtn, int ignoreCase = 0);

int toUpper(int chr);
int toLower(int chr);
int mbs_stricmp(char *str1, char *str2, int num = INT_MAX);

char *addToken(char *buffer, char *token);
char *addToken_x(char *buffer, char *token);
char *addChar(char *buffer, int chr);
char *addLine(char *buffer, char *line);
char *addLine_x(char *buffer, char *line);

char *getEnd(char *str, int num);
char *getEnd(char *str, char *ptn);

void toRangeToken(char *str, int minchr, int maxchr);
char *toJToken(char *str, int minchr, int maxchr);
char *toJToken_x(char *str, int minchr, int maxchr);
