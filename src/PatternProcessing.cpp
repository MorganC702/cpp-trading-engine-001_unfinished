#include "PatternProcessing.h"
#include <iostream>

// Constructor: Initializes the pattern type
PatternProcessing::PatternProcessing(PatternType type) : patternType(type) {}

/**
 * @brief Converts candlestick data into a binary pattern (1 = Up, 0 = Down).
 */
std::string PatternProcessing::convert_to_binary(const std::vector<Candle>& candles) {
    std::string binary_pattern;

    for (size_t i = 0; i < candles.size(); i++) {
        binary_pattern += (candles[i].close > candles[i].open) ? "1" : "0";
    }

    return binary_pattern;
}

/**
 * @brief Detects patterns within the given data for different lengths.
 */
std::unordered_map<std::string, int> PatternProcessing::detect_patterns(const std::vector<Candle>& candles, int min_length, int max_length) {
    std::unordered_map<std::string, int> pattern_counts;

    if (candles.size() < min_length) {
        std::cerr << "[PatternProcessing] Error: Not enough data for pattern detection!" << std::endl;
        return pattern_counts;
    }

    std::string sequence;
    
    // Use the appropriate method based on pattern type
    if (patternType == PatternType::BINARY) {
        sequence = convert_to_binary(candles);
    } else {
        std::cerr << "[PatternProcessing] Error: Pattern type not implemented yet!" << std::endl;
        return pattern_counts;
    }

    for (int length = min_length; length <= max_length; length++) {  // ✅ Iterate over pattern lengths
    for (size_t i = 0; i + length <= sequence.size(); i++) {  // ✅ Ensure no out-of-bounds access
        std::string pattern = sequence.substr(i, length);
        pattern_counts[pattern]++;
    }
}



    return pattern_counts;
}

/**
 * @brief Processes detected patterns and checks them against Redis for active signals.
 */
void PatternProcessing::process_patterns(const std::string& currency_pair, const std::vector<Candle>& candles) {
    const int min_pattern_length = 3;
    const int max_pattern_length = 10;

    // Detect patterns
    std::unordered_map<std::string, int> detected_patterns = detect_patterns(candles, min_pattern_length, max_pattern_length);

    // Trade Execution Instance
    TradeExecution trade_executor;

    // Redis Instance
    RedisCache redis;

    for (const auto& [pattern, count] : detected_patterns) {
        if (redis.is_pattern_active(currency_pair, pattern)) {
            std::cout << "[PatternProcessing] Executing trade for active pattern: " << pattern << " in " << currency_pair << std::endl;
            trade_executor.execute_trade(currency_pair, pattern);
            redis.remove_active_pattern(currency_pair, pattern); // Prevent duplicate trades
        } else {
            std::cout << "[PatternProcessing] New pattern detected: " << pattern << " in " << currency_pair << std::endl;
        }
    }
}
