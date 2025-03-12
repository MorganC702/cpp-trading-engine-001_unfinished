#include "PatternMatching.h"
#include <iostream>

PatternMatching::PatternMatching(){}

std::string PatternMatching::convert_to_binary(const std::vector<Candle>& candles) {
    std::string binary_pattern;

    for (size_t i = 1;  i < candles.size(); i++ ) {
        if (candles[i].close > candles[i].open) {
            binary_pattern += "1";
        } else { 
            binary_pattern += "0"; 
        }
    }

    return binary_pattern;
}

std::vector<std::string> PatternMatching::detect_patterns(const std::vector<Candle>& candles, int pattern_length) {
    std::vector<std::string> patterns;

    if (candles.size() < pattern_length) {
         std::cerr << "Error: Not enough data for pattern detection!" << std::endl;
        return patterns;
    }

    std::string binary_sequence = convert_to_binary(candles);

    for (size_t i = 0; i<= binary_sequence.size()  - pattern_length; i++) {
        std::string pattern = binary_sequence.substr(i, pattern_length);
        patterns.push_back(pattern);
    }

    return patterns;

}