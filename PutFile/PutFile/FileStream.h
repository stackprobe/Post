FILE *rfopen(char *file, char *mode);
FILE *fileOpen(char *file, char *mode);
void fileClose(FILE *fp);

__int64 getFileSize(FILE *fp);
__int64 getFileSize(char *file);

int readChar(FILE *fp);
char *readLine(FILE *fp);
char *readLine(char *file);
char *neReadLine(FILE *fp);
char *neReadLine(char *file);

autoList<char *> *readLines(char *file);
char *readText(char *file);

void writeChar(FILE *fp, int chr);
void writeToken(FILE *fp, char *token);
void writeToken_x(FILE *fp, char *token);
void writeLine(FILE *fp, char *line);
void writeLine(char *file, char *line);

void fileRead(FILE *fp, void *block, int size);
void fileWrite(FILE *fp, void *block, int size);

void readBlock(char *file, void *block, int size);

autoList<uchar> *readBinary(char *file);
