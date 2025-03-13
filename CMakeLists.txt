cmake_minimum_required(VERSION 3.10)
project(ForexTradingBot)

set(CMAKE_CXX_STANDARD 17)

# Include project headers
include_directories(${PROJECT_SOURCE_DIR}/include)

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    add_compile_options(-Wno-unknown-attributes)
endif()

# Detect Operating System
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")  # ✅ Mac (Darwin is macOS's system name)
    message(STATUS "Configuring for macOS...")
    
    # Include paths for Homebrew installed libraries
    include_directories(/opt/homebrew/include /opt/homebrew/Cellar/libpqxx/7.10.0/include)

    # Set library paths
    set(PostgreSQL_LIBRARIES /opt/homebrew/lib/libpq.dylib)
    set(PQXX_LIB /opt/homebrew/lib/libpqxx.dylib)

    # Fix linking issues by explicitly setting rpath
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath,/opt/homebrew/lib")

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")  # ✅ Linux
    message(STATUS "Configuring for Linux...")
    include_directories(/usr/local/include /usr/include)
    set(PostgreSQL_LIBRARIES /usr/lib/x86_64-linux-gnu/libpq.so)
    set(PQXX_LIB /usr/lib/x86_64-linux-gnu/libpqxx.so)
else()
    message(FATAL_ERROR "Unsupported OS: ${CMAKE_SYSTEM_NAME}")
endif()

# Add source files
add_executable(trading_bot 
    config/Config.cpp
    src/main.cpp
    src/MarketData.cpp
    src/DataProcessing.cpp
    src/PatternDetection.cpp
    src/PatternProcessing.cpp
    src/TradeExecution.cpp
    db/RedisCache.cpp
    db/Database.cpp
)

# Find and link PostgreSQL and libpqxx
find_package(PostgreSQL REQUIRED)
include_directories(${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(trading_bot ${PostgreSQL_LIBRARIES} ${PQXX_LIB})
