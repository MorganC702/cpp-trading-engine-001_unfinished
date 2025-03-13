#ifndef MARKET_DATA_H
#define MARKET_DATA_H

#include <vector>
#include <string>

// Structure to represent a single candlestick
struct Candle {
    std::string timestamp;  // Time of the candle
    double open;   // Opening price
    double high;   // Highest price
    double low;    // Lowest price
    double close;  // Closing price
};

// Class for handling market data (fetching and preprocessing)
class MarketData {
public:
    // Constructor
    MarketData();

    // Fetches market data from an API or historical source
    std::vector<Candle> get_historical_data(const std::string& currency_pair);
};

#endif // MARKET_DATA_H
