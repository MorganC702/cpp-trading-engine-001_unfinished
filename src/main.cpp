#include "MarketData.h"
#include "PatternMatching.h"
#include <iostream>
#include <vector>
#include <thread>  // Include threading
#include <mutex>   // For thread-safe output

std::mutex print_mutex;  // Mutex to prevent output overlapping

// Function to run pattern detection for a given length
void process_pattern_length(int pattern_length, const std::vector<Candle>& historical_data) {
    PatternMatching patternMatcher(PatternType::BINARY);
    std::vector<std::string> detected_patterns = patternMatcher.detect_patterns(historical_data, pattern_length);

    // Use mutex to prevent mixed-up console output
    std::lock_guard<std::mutex> lock(print_mutex);
    std::cout << "Pattern Length: " << pattern_length << std::endl;
    for (const auto& pattern : detected_patterns) {
        std::cout << pattern << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}

int main() {
    MarketData market;
    market.fetch_data(); 

    std::vector<Candle> historical_data = market.get_historical_data();
    if (historical_data.empty()) {
        std::cerr << "Error: No historical data available!" << std::endl;
        return 1;
    }

    std::vector<std::thread> threads;

    // Create a thread for each pattern length (2-10)
    for (int length = 2; length <= 20; length++) {
        threads.emplace_back(process_pattern_length, length, std::ref(historical_data));
    }

    // Join all threads (wait for all to finish)
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
