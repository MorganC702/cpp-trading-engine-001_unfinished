#ifndef TRADE_EXECUTION_H
#define TRADE_EXECUTION_H

#include <string>

/**
 * @brief Class responsible for executing trades when a pattern match is found.
 */
class TradeExecution {
public:
    TradeExecution();  // Constructor

    /**
     * @brief Executes a trade when a pattern signal is triggered.
     * @param currency_pair The forex pair (e.g., "EUR/USD").
     * @param pattern The detected pattern.
     */
    void execute_trade(const std::string& currency_pair, const std::string& pattern);
};

#endif // TRADE_EXECUTION_H
