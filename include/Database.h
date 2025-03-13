#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include <vector>
#include <string>
#include "MarketData.h"  // Includes the Candle struct

/**
 * @brief Class for handling PostgreSQL storage of trading patterns.
 */
class Database {
public:
    Database();  // Constructor
    ~Database(); // Destructor

    /**
     * @brief Stores a detected pattern in PostgreSQL.
     * @param pattern_length The length of the detected pattern.
     * @param pattern The actual pattern string.
     * @param ohlc_data The OHLC candle data associated with the pattern.
     */
    void store_pattern(int pattern_length, const std::string& pattern, const std::vector<Candle>& ohlc_data);

    /**
     * @brief Queries stored patterns.
     */
    void query_patterns();
};

#endif // DATABASE_H
