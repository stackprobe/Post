// sync > @ updateDiskSpace_h

extern uint64 lastDiskFree_User; // このプロセスが使用出来る空き領域サイズ
extern uint64 lastDiskFree;
extern uint64 lastDiskSize;

void updateDiskSpace(int drive);
void updateDiskSpace_Dir(char *dir);

// < sync
