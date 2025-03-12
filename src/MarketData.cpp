#include "MarketData.h"
#include <iostream>
#include <fstream>
#include <sstream>

MarketData::MarketData() {
    load_mock_data();
};

void MarketData::load_mock_data() {
    std::ifstream file("../data/historical_data.csv");
    if (!file.is_open()) {
        std::cerr << "Error: could not open historical data file!" << std::endl;
        return;
    }

    std::string line;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string timestamp;
        double open, high, low, close;

        if (ss >> timestamp >> open >> high >> low >> close) {
            candles.push_back({timestamp, open, high, low, close});
        }
    }
}

void MarketData::fetch_data() {
    if (candles.empty()) {
        std::cerr << "Error: No market data available!" << std::endl;
        return;
    }

    std::cout << "Recent Forex Data:" << std::endl;
    for (size_t i = 0; i < candles.size(); i++) {
          std::cout << candles[i].timestamp << " O:" << candles[i].open
                  << " H:" << candles[i].high << " L:" << candles[i].low
                  << " C:" << candles[i].close << std::endl;
    }
}

std::vector<Candle> MarketData::get_historical_data() {
    return candles;
}

