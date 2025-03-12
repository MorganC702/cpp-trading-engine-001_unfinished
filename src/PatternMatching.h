#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H

#include <vector>
#include <string>
#include "MarketData.h"

enum class PatternType {
    BINARY, 
    CANDLESTICK,
};

class PatternMatching {
    public: 
        PatternMatching(PatternType type);
        
        std::vector<std::string> detect_patterns( 
            const std::vector<Candle> & candles, 
            int pattern_length 
        );

    private: 
        PatternType patternType;

        std::string convert_to_binary( 
            const std::vector<Candle>& candles
        );

};


#endif 
