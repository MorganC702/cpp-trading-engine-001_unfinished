cmake_minimum_required(VERSION 3.10)
project(ForexTradingBot)

set(CMAKE_CXX_STANDARD 17)

# Add header directory
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(trading_bot 
    src/main.cpp
    src/MarketData.cpp
    src/DataProcessing.cpp
    src/PatternProcessing.cpp
    src/TradeExecution.cpp
    db/RedisCache.cpp
    db/Database.cpp
)

# PostgreSQL linking
find_package(PostgreSQL REQUIRED)
include_directories(${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(trading_bot ${PostgreSQL_LIBRARIES} pqxx)
