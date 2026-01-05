#include "../include/string_cache.h"

StringCache* NewStringCache(void) {
  StringCache* string_cache =
      (StringCache*)malloc(sizeof(StringCache) + sizeof(char));
  string_cache->cache_status = CacheStatusBad;
  string_cache->size = 0;
  return string_cache;
}

void DestroyStringCache(StringCache* stringCache) {
  free(stringCache);
  stringCache = NULL;
}
