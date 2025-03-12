#ifndef MARKETDATA_H
#define MARKETDATA_H

#include <vector> 
#include <string>

struct Candle {
    std::string timestamp;
    double open, high, low, close;
};

class MarketData{
    public:
        MarketData();
        void fetch_data();
        std::vector<Candle> get_historical_data();

    private:
        std::vector<Candle> candles;
        void load_mock_data();
};

#endif