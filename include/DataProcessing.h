#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include <unordered_map>
#include <vector>
#include <string>
#include "MarketData.h"  // Provides Candle struct (historical data)
#include "Config.h"

// Class responsible for fetching and preprocessing market data
class DataProcessing {
public:
    DataProcessing();  // Constructor

    /**
     * @brief Preprocesses the fetched market data (e.g., filtering, normalizing).
     * @param market_data A reference to the market data that needs preprocessing.
     */
    void preprocess_data(std::unordered_map<std::string, std::vector<Candle>>& market_data);
};

#endif // DATA_PROCESSING_H
