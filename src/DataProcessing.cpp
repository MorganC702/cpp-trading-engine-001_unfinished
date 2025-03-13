#include "DataProcessing.h"
#include "MarketData.h"
#include <iostream>
#include <fstream>
#include <sstream>


/**
 * @brief Constructor for DataProcessing.
 */
DataProcessing::DataProcessing() {}


/**
 * @brief Preprocesses the fetched market data (e.g., filtering, normalizing).
 */
void DataProcessing::preprocess_data(std::unordered_map<std::string, std::vector<Candle>>& market_data) {
    std::cout << "[DataProcessing] Preprocessing market data..." << std::endl;

    for (auto& [source, candles] : market_data) {
        if (candles.empty()) {
            std::cerr << "[DataProcessing] Warning: No candle data for " << source << std::endl;
            continue;
        }

        // Ensure all candle data is valid
        for (auto& candle : candles) {
            if (candle.open <= 0 || candle.high <= 0 || candle.low <= 0 || candle.close <= 0) {
                std::cerr << "[DataProcessing] Warning: Invalid candle detected in " << source << std::endl;
            }
        }
    }
    std::cout <<"[DataProcessing] market data processed Successfully" << std::endl;
}
