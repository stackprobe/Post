extern int BatchMode;
extern int SilentMode;

void termination(int errorlevel);
void error2(char *source, int lineno, char *function, char *message = NULL);

#define error() \
	error2(__FILE__, __LINE__, __FUNCTION__)

#define error_m(message) \
	error2(__FILE__, __LINE__, __FUNCTION__, (message))

#define errorCase(status) \
	do { \
	if((status)) error(); \
	} while(0)

#define errorCase_m(status, message) \
	do { \
	if((status)) error_m((message)); \
	} while(0)

#define LOGPOS() \
	cout("%s (%d) %s\n", __FILE__, __LINE__, __FUNCTION__)

// sync > @ cout_h
void cout(char *format, ...);
char *xcout(char *format, ...);
char *vxcout(char *format, va_list marker);
void coutLongText(char *text);
void coutLongText_x(char *text);
// < sync

int argIs(char *spell);

char *getSelfFile(void);
char *getSelfDir(void);
