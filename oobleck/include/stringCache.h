#ifndef STRING_CACHE_H
#define STRING_CACHE_H

#include <stdlib.h>

typedef enum {
    CacheStatusGood,
    CacheStatusBad,
} CacheStatus;

typedef struct {
    CacheStatus cacheStatus;
    size_t size;
    char cache[];
} StringCache;

StringCache* newStringCache(void);
void destroyStringCache(StringCache* cachedStr);

#endif
