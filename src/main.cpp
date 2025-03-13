#include "MarketData.h"
#include "DataProcessing.h"
#include "PatternProcessing.h"
#include "PatternDetection.h"
#include "TradeExecution.h"
#include "RedisCache.h"
#include "Database.h"
#include <iostream>
#include "Config.h"

int main() {

      
    //----------------FETCH MARKET DATA -----------------------------// 
    //---------------------------------------------------------------// 

    MarketData marketData;

    std::vector filepaths = 
    {
        "../data/EURUSD1H.csv",
        "../data/AUDCAD1H.csv",
    };

    std::unordered_map<std::string, std::vector<Candle>> raw_data;

    for (const auto& filepath : filepaths) {
        raw_data[filepath] = marketData.get_historical_data(filepath);
    }

    
    //----------------DATA PROCESSING--------------------------------// 
    //---------------------------------------------------------------// 

    DataProcessing data_processor;
    data_processor.preprocess_data(raw_data);



    //----------------PATTERN PROCESSORS-----------------------------// 
    //---------------------------------------------------------------// 
   
    PatternDetection binary_pattern_detector(PatternType::BINARY);

    const int min_binary_pattern_length = 2;
    const int max_binary_pattern_length = 10;

    std::unordered_map<std::string, std::vector<std::string_view>> detected_binary_patterns;

    for (const auto& [pair, candles] : raw_data) {
        if (candles.size() < min_binary_pattern_length) {
            std::cerr << "[PatternDetection] Not enough candles for " << pair << " to detect patterns!" << std::endl;
            continue;
        }

        // Detect the latest binary patterns
        detected_binary_patterns[pair] = binary_pattern_detector
            .detect_current_binary_patterns(
                candles, 
                min_binary_pattern_length, 
                max_binary_pattern_length
            );


        std::cout << "\n[PatternDetection] Detected Binary Patterns for " << pair << ":\n";
        int length = min_binary_pattern_length;
        for (const auto& pattern : detected_binary_patterns[pair]) {
            std::cout << "Length " << length++ << ": " << pattern << std::endl;
        }
    }







    //----------------ORDER PROCESSING-------------------------------// 
    //---------------------------------------------------------------// 

    // TradeExecution trade_executor; // Object for exectuting trades

    // RedisCache redis;
    // Database db;



    return 0;
}
