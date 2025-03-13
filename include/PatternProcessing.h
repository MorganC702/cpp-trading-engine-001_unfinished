#ifndef PATTERN_PROCESSING_H
#define PATTERN_PROCESSING_H

#include <vector>
#include <string>
#include <unordered_map>
#include "MarketData.h"   // Includes Candle struct
#include "TradeExecution.h"
#include "RedisCache.h"

// Enum to define different pattern types
enum class PatternType {
    BINARY,       // 10101 style patterns (Up = 1, Down = 0)
    CANDLESTICK   // (Future Implementation: Hammer, Engulfing, etc.)
};

// Class for identifying and managing trading patterns
class PatternProcessing {
public:
    PatternProcessing(PatternType type = PatternType::BINARY); // Constructor

    void process_patterns(const std::string& currency_pair, const std::vector<Candle>& candles);

    /**
     * @brief Detects patterns of different lengths within the data.
     * @param candles The vector of candles to analyze.
     * @param min_length The minimum pattern length.
     * @param max_length The maximum pattern length.
     * @return A dictionary (unordered_map) containing pattern sequences and their occurrences.
     */
    std::unordered_map<std::string, int> detect_patterns(const std::vector<Candle>& candles, int min_length, int max_length);

private:
    PatternType patternType;  // Stores which pattern type we're using

    /**
     * @brief Converts a sequence of candles into a binary representation.
     */
    std::string convert_to_binary(const std::vector<Candle>& candles);
};

#endif // PATTERN_PROCESSING_H
