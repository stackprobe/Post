int getZero(void);
__int64 s2i64(char *line);
__int64 s2i64_x(char *line);
int s2i(char *line);
int s2i_x(char *line);
__int64 hex2i64(char *line);
__int64 hex2i64_x(char *line);

int compInt(int a, int b);
int compI2D(i2D_t a, i2D_t b);

int isHitKey(int key);

void addValue(autoList<uchar> *block, uint64 value);
uint64 unaddValue64(autoList<uchar> *block);
