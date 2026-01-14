#ifndef STRING_CACHE_H
#define STRING_CACHE_H

/**
 * @headerfile string_cache.h
 * @brief A string cache to store the current buffer string
 */

#include <stdlib.h>

/// @enum CacheStatus
/// @brief An enum to store the Cached String's status
typedef enum {
  CacheStatusGood,
  CacheStatusBad,
} CacheStatus;

/// @struct StringCache
/// @brief A dynamically sized array using a Flexible Array member to store a
/// string
typedef struct {
  CacheStatus cache_status;
  size_t size;
  char cache[];
} StringCache;

/**
 * @brief A method to create a new string cache
 * @return A pointer to the string cache
 */
StringCache* NewStringCache(void);

/**
 * @brief Function to free a string cache's resources
 * @param string_cache A pointer to the string cache
 */
void DestroyStringCache(StringCache* string_cache);

#endif
