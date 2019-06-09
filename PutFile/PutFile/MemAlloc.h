void *memAlloc(int size);
void *memRealloc(void *block, int size);
void memFree(void *block);

#define na(TYPE_T, count) \
	((TYPE_T *)memCalloc(sizeof(TYPE_T) * (count)))

#define nb(TYPE_T) \
	(na(TYPE_T, 1))
