#include "PatternDetection.h"
#include <iostream>


PatternDetection::PatternDetection(PatternType type) : patternType(type) {}


std::string PatternDetection::convert_to_binary(const std::vector<Candle>& candles) {
    std::string binary_pattern;
    binary_pattern.reserve(candles.size());

    for (const auto& candle : candles) {
        binary_pattern += (candle.close > candle.open) ? '1' : '0';
    }

    return binary_pattern;
}


std::vector<std::string_view> PatternDetection::detect_current_binary_patterns(
    const std::vector<Candle>& candles, 
    int min_length, 
    int max_length
) {
    std::vector<std::string_view> current_patterns;

    if (candles.size() < min_length) {
        std::cerr << "[PatternDetection] Error: Not enough data for pattern detection!" << std::endl;
        return current_patterns;
    }

    // Only use the latest max_length candles
    int max_candles_to_check = std::min(static_cast<int>(candles.size()), max_length);
    
    // 🔥 Store sequence in the class so string_views remain valid
    binary_sequence = convert_to_binary({candles.end() - max_candles_to_check, candles.end()});

    // Reserve space for efficiency
    current_patterns.reserve(max_candles_to_check - min_length + 1);

    // Extract exactly one pattern per length
    for (int length = min_length; length <= max_candles_to_check; length++) {
        current_patterns.emplace_back(binary_sequence.data() + binary_sequence.size() - length, length);
    }

    return current_patterns;
}