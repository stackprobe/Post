FILE *rfopen(char *file, char *mode);
FILE *fileOpen(char *file, char *mode);
void fileClose(FILE *fp);

__int64 getSeekPos(FILE *fp);
__int64 getFileSize(FILE *fp);
__int64 getFileSize(char *file);
void setFileSize(char *file, __int64 size);

extern int lastReadChar;

#define READLINE_DEFLENMAX 1000000

int readChar(FILE *fp);
char *readLine(FILE *fp, int lenmax = READLINE_DEFLENMAX);
char *readLine(char *file, int lenmax = READLINE_DEFLENMAX);

void writeChar(FILE *fp, int chr);
void writeToken(FILE *fp, char *token);
void writeToken_x(FILE *fp, char *token);
void writeToken(char *file, char *token);
void writeLine(FILE *fp, char *line);
void writeLine_x(FILE *fp, char *line);
void writeLine(char *file, char *line);
void writeLine_cx(char *file, char *line);

void fileSeek(FILE *fp, int origin, __int64 offset);
void fileRead(FILE *fp, void *block, int size);
void fileWrite(FILE *fp, void *block, int size);

int fileReadMax(FILE *fp, void *block, int size);
