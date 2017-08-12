extern char *HomeDir;
extern char *SendFileFullPath;
extern int RemoveSendFileAtTermination;
extern char *ResponseModeFileFullPath;
extern char *UserProgram;

void HTT_Disconnect(void);
void DeleteFileDataPart(char *file, __int64 beginPos, __int64 delSize);
void TrimHeaderToken(char *token);
void CheckDiskFree2(char *source, int lineno, char *function);
void WriteResponseHtmlFile(char *text);

#define CheckDiskFree() \
	CheckDiskFree2(__FILE__, __LINE__, __FUNCTION__)
