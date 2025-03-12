#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H

#include <vector>
#include <string>
#include "MarketData.h"

class PatternMatching {
    public: 
        PatternMatching();
        std::vector<std::string> detect_patterns( 
            const std::vector<Candle> & candles, 
            int pattern_length 
        );

    private: 
        std::string convert_to_binary( 
            const std::vector<Candle>& candles
        );

};


#endif 
