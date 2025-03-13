#ifndef PATTERN_DETECTION_H
#define PATTERN_DETECTION_H

#include <vector>
#include <string>
#include <string_view>
#include "MarketData.h"

enum class PatternType { 
    BINARY,
}; 

class PatternDetection {
public:
    explicit PatternDetection(PatternType type = PatternType::BINARY);

    std::vector<std::string_view> detect_current_binary_patterns(
        const std::vector<Candle>& candles, 
        int min_length, 
        int max_length
    );

private:
    PatternType patternType;
    std::string binary_sequence; 
    
    std::string convert_to_binary(const std::vector<Candle>& candles);
};

#endif
