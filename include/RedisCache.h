#ifndef REDIS_CACHE_H
#define REDIS_CACHE_H

#include <string>

/**
 * @brief Class responsible for tracking active patterns in Redis.
 */
class RedisCache {
public:
    RedisCache();  // Constructor

    /**
     * @brief Stores an active pattern in Redis.
     * @param currency_pair The forex pair (e.g., "EUR/USD").
     * @param pattern The detected pattern.
     */
    void store_active_pattern(const std::string& currency_pair, const std::string& pattern);

    /**
     * @brief Checks if a pattern is already active in Redis.
     * @param currency_pair The forex pair (e.g., "EUR/USD").
     * @param pattern The detected pattern.
     * @return True if pattern is active, false otherwise.
     */
    bool is_pattern_active(const std::string& currency_pair, const std::string& pattern);

    /**
     * @brief Removes a pattern from Redis.
     * @param currency_pair The forex pair (e.g., "EUR/USD").
     * @param pattern The pattern to be removed.
     */
    void remove_active_pattern(const std::string& currency_pair, const std::string& pattern);
};

#endif // REDIS_CACHE_H
