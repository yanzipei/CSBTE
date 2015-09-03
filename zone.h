void Z_Free(void *ptr);
void *Z_Malloc(int size);
void *Z_TagMalloc(int size, int tag);
void Z_CheckHeap(void);
void Z_Init(int zonesize);