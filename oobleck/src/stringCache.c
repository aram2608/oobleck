#include "../include/stringCache.h"

StringCache* newStringCache(void) {
    StringCache* stringCache = (StringCache*)malloc(sizeof(StringCache) + sizeof(char));
    stringCache->cacheStatus = CacheStatusBad;
    stringCache->size = 0;
    return stringCache;
}

void destroyStringCache(StringCache* stringCache) {
    free(stringCache);
    stringCache = NULL;
}
