#include "DataProcessing.h"
#include "MarketData.h"
#include <iostream>

/**
 * @brief Constructor for DataProcessing.
 */
DataProcessing::DataProcessing() {}

/**
 * @brief Fetches and preprocesses market data.
 * @return An unordered_map containing forex pairs and their corresponding candlestick data.
 */
std::unordered_map<std::string, std::vector<Candle>> DataProcessing::fetch_market_data() {
    std::unordered_map<std::string, std::vector<Candle>> market_data;
    MarketData market_source;

    std::cout << "[DataProcessing] Fetching market data..." << std::endl;

    // Fetch data from MarketData class
    market_data["EUR/USD"] = market_source.get_historical_data("EUR/USD");

    return market_data;
}

/**
 * @brief Preprocesses the fetched market data (e.g., filtering, normalizing).
 */
void DataProcessing::preprocess_data(std::unordered_map<std::string, std::vector<Candle>>& market_data) {
    std::cout << "[DataProcessing] Preprocessing market data..." << std::endl;

    for (auto& [pair, candles] : market_data) {
        if (candles.empty()) {
            std::cerr << "[DataProcessing] Warning: No candle data for " << pair << std::endl;
            continue;
        }

        // Example: Ensure all candle data is valid
        for (auto& candle : candles) {
            if (candle.open <= 0 || candle.high <= 0 || candle.low <= 0 || candle.close <= 0) {
                std::cerr << "[DataProcessing] Warning: Invalid candle detected in " << pair << std::endl;
            }
        }
    }
}
