#include "MarketData.h"
#include "PatternMatching.h"
#include <iostream>


int main() {
    MarketData market;
    market.fetch_data();

    PatternMatching PatternMatcher;
    std::vector<Candle> historical_data = market.get_historical_data();

    int pattern_leength = 3;
    std::vector<std::string> detected_patterns = PatternMatcher.detect_patterns(historical_data, pattern_leength);

    std::cout << "Detected Patterns: " << std::endl;
    for (const auto& pattern: detected_patterns) {
        std::cout << pattern << std::endl;
    }

    return 0;
}