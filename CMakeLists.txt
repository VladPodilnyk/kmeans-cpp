cmake_minimum_required (VERSION 3.9)

project (KMEANS)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories (
    ${PROJECT_SOURCE_DIR}/external/range-v3/include/
)

add_executable(
    findAnomaly
    ${PROJECT_SOURCE_DIR}/kmeans/find_anomaly.cpp
    ${PROJECT_SOURCE_DIR}/kmeans/kmeans.cpp
)