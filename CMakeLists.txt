cmake_minimum_required(VERSION 3.10)

# Define the project name
project(ForexTradingBot)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Define the executable and link source files
add_executable(trading_bot 
    src/main.cpp
    src/MarketData.cpp
    src/PatternMatching.cpp
)

# Include headers
target_include_directories(trading_bot PRIVATE include)
