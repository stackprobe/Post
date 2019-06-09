int existPath(char *path);
int existFile(char *file);
int existDir(char *dir);

void trimPath(char *path);
char *combine(char *dir, char *file);
char *combine_cx(char *dir, char *file);
char *getDir(char *path);
char *getLocalPath(char *path);
char *getLocalPath_x(char *path);

void setCwd(char *dir);
void setCwd_x(char *dir);
char *getCwd(void);
void addCwd(char *dir);
void unaddCwd(void);

void removeFile(char *file);
void clearDir(char *dir);
void forceRemoveDir(char *dir);

void fileMove(char *rFile, char *wFile);

char *getFullPath(char *path, char *baseDir = ".");
char *getLocal(char *path);
char *getExt(char *path);
char *getExtWithDot(char *path);
int removeExt(char *path);
char *addExt(char *path, char *ext);

char *makeFairLocalPath(char *localPath);
char *makeFairLocalPath_x(char *localPath);
