#include "PatternMatching.h"
#include <iostream>

PatternMatching::PatternMatching(PatternType type){
    patternType = type;
}

std::string PatternMatching::convert_to_binary(const std::vector<Candle>& candles) {
    std::string binary_pattern;

    for (size_t i = 0;  i < candles.size(); i++ ) {
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

    std::string sequence;
    if (patternType == PatternType::BINARY) {
        sequence = convert_to_binary(candles);
    } else {
        std::cerr << "Pattern type not implemented yet!" << std::endl;
        return patterns;
    }

    for (size_t i = 0; i <= sequence.size() - pattern_length; i++) {
        patterns.push_back(sequence.substr(i, pattern_length));
    }

    return patterns;

}



