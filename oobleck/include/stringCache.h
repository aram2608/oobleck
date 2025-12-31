#ifndef STRING_CACHE_H
#define STRING_CACHE_H

#include <stdlib.h>

/// @enum CacheStatus
/// @brief An enum to store the Cached String's status
typedef enum {
    CacheStatusGood,
    CacheStatusBad,
} CacheStatus;

/// @struct StringCache
/// @brief A dynamically sized array using a Flexible Array member to store a string
typedef struct {
    CacheStatus cacheStatus;
    size_t size;
    char cache[];
} StringCache;

/**
 * @brief A method to create a new string cache
 * @return A pointer to the string cache
 */
StringCache* newStringCache(void);

/**
 * @brief Function to free a string cache's resources
 * @param stringCache A pointer to the string cache
 */
void destroyStringCache(StringCache* stringCache);

#endif
