#include "MarketData.h"
#include "DataProcessing.h"
#include "PatternProcessing.h"
#include "TradeExecution.h"
#include "RedisCache.h"
#include "Database.h"
#include <iostream>

int main() {
    // Step 1: Fetch raw market data
    DataProcessing data_processor;
    auto raw_data = data_processor.fetch_market_data();
    data_processor.preprocess_data(raw_data);

    // Step 2: Detect patterns (only binary for now)
    PatternProcessing pattern_processor(PatternType::BINARY);
    
    // Redis for checking active patterns
    RedisCache redis;

    // Trade Execution
    TradeExecution trade_executor;

    // Database for storing detected patterns
    Database db;

    for (const auto& [pair, candles] : raw_data) {
        // Detect and process patterns
        pattern_processor.process_patterns(pair, candles);
        
        // Check detected patterns against Redis
        std::unordered_map<std::string, int> detected_patterns = pattern_processor.detect_patterns(candles, 3, 10);

        for (const auto& [pattern, count] : detected_patterns) {
            if (redis.is_pattern_active(pair, pattern)) {
                std::cout << "[Main] Executing trade for active pattern: " << pattern << " in " << pair << std::endl;
                trade_executor.execute_trade(pair, pattern);
                redis.remove_active_pattern(pair, pattern); // Prevent duplicate trades
            } else {
                std::cout << "[Main] New pattern detected: " << pattern << " in " << pair << std::endl;
                db.store_pattern(pattern.length(), pattern, candles);
            }
        }
    }

    return 0;
}
