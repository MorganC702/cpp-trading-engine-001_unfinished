#ifndef MARKET_DATA_H
#define MARKET_DATA_H

#include <vector>
#include <string>
#include "Config.h"

struct Candle {
    std::string timestamp;  
    double open;   
    double high;   
    double low;    
    double close;  
};

class MarketData {
    public:
        MarketData();
        std::vector<Candle> get_historical_data(const std::string& identifier);

    private:
        std::vector<Candle> load_data_from_csv(const std::string& filepath);
};

#endif
