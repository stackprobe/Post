int existPath(char *path);
int existFile(char *file);

char *getDir(char *path);

void setCwd(char *dir);
void setCwd_x(char *dir);
char *getCwd(void);
void addCwd(char *dir);
void unaddCwd(void);

void createFile(char *file);
void removeFile(char *file);

char *getFullPath(char *path, char *baseDir = ".");
