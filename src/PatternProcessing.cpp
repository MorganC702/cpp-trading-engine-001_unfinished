// #include "PatternProcessing.h"
// #include <iostream>
// #include <future>

// // Constructor
// PatternProcessing::PatternProcessing(PatternType type) : patternType(type), detector(type) {}

// /**
//  * @brief Processes detected patterns, compares with Redis, and executes trades if necessary.
//  */
// void PatternProcessing::process_patterns(const std::string& currency_pair, const std::vector<Candle>& candles) {
//     const int min_pattern_length = 2;
//     const int max_pattern_length = 10;

//     // Detect active patterns using the PatternDetection class
//     std::vector<std::string_view> active_patterns = detector.detect_current_patterns(candles, min_pattern_length, max_pattern_length);

//     // Trade Execution Instance
//     TradeExecution trade_executor;

//     // Redis Instance
//     RedisCache redis;

//     // Fetch all active patterns in **one** Redis call (O(1) batch lookup)
//     std::unordered_set<std::string> active_patterns_in_redis = redis.get_all_active_patterns(currency_pair);

//     // Multi-threaded trade execution for active patterns
//     std::vector<std::future<void>> tasks;
//     tasks.reserve(active_patterns.size());

//     for (const auto& pattern : active_patterns) {
//         tasks.push_back(std::async(std::launch::async, [&]() {
//             std::string pattern_str(pattern);  // Convert string_view to string for Redis lookup

//             if (active_patterns_in_redis.count(pattern_str)) {
//                 std::cout << "[PatternProcessing] Executing trade for active pattern: " << pattern << " in " << currency_pair << std::endl;
//                 trade_executor.execute_trade(currency_pair, pattern);
//                 redis.remove_active_pattern(currency_pair, pattern);
//             } else {
//                 std::cout << "[PatternProcessing] New active pattern: " << pattern << " in " << currency_pair << std::endl;
//             }
//         }));
//     }

//     // Ensure all async tasks complete
//     for (auto& task : tasks) {
//         task.get();
//     }
// }
