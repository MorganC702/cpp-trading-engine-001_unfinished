#include "MarketData.h"
#include <iostream>
#include <fstream>
#include <sstream>


MarketData::MarketData() {}


std::vector<Candle> MarketData::load_data_from_csv(
    const std::string& filepath
) {
    std::vector<Candle> candles;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "[MARKETDATA] Error: Could not open file " << filepath << std::endl;
        return candles;
    }

    std::string line;
    bool first_line = true;

    while (std::getline(file, line)) {
        if (first_line) {
            first_line = false;
            continue;
        }

        std::stringstream ss(line);
        Candle candle;
        std::string timestamp, open, high, low, close;

        if (std::getline(ss, timestamp, ',') &&
            std::getline(ss, open, ',') &&
            std::getline(ss, high, ',') &&
            std::getline(ss, low, ',') &&
            std::getline(ss, close, ',')) {

            try {
                candle.timestamp = timestamp;
                candle.open = std::stod(open);
                candle.high = std::stod(high);
                candle.low = std::stod(low);
                candle.close = std::stod(close);
                candles.push_back(candle);
            } catch (const std::exception& e) {
                std::cerr << "[MarketData] Error parsing line: " << line << " | " << e.what() << std::endl;
            }
        }
    }
    file.close();
    std::cout << "[MarketData] Loaded " << candles.size() << " candles from " << filepath << std::endl;
    return candles;
}


std::vector<Candle> MarketData::get_historical_data(const std::string& identifier) {
    if (testing) {
        return load_data_from_csv(identifier);
    } else {

    // -------------------- NEEDS UPDATE WITH ACTUAL API LOGIC --------------------- //
        
        std::vector<Candle> historical_data;
        std::cout << "[MarketData] Fetching historical data for " << identifier << "..." << std::endl;

        historical_data = {
            {"2024-03-11T10:00:00-05:00", 1.1, 1.105, 1.098, 1.1025},
            {"2024-03-11T10:01:00-05:00", 1.1025, 1.107, 1.1, 1.106},
            {"2024-03-11T10:02:00-05:00", 1.106, 1.108, 1.103, 1.1045},
            {"2024-03-11T10:03:00-05:00", 1.1045, 1.1065, 1.1015, 1.102},
            {"2024-03-11T10:04:00-05:00", 1.102, 1.104, 1.099, 1.1005}
        };

        return historical_data;
    }
}

