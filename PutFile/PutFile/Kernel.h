// sync > @ updateDiskSpace_h

extern uint64 lastDiskFree_User; // ���̃v���Z�X���g�p�o����󂫗̈�T�C�Y
extern uint64 lastDiskFree;
extern uint64 lastDiskSize;

void updateDiskSpace(int drive);
void updateDiskSpace_Dir(char *dir);

// < sync
