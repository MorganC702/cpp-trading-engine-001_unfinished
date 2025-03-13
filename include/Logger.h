#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
    public:
        Logger();

        void log_trade(const std::string& currecy_par, const std::string& pattern, double profit);
};

#endif