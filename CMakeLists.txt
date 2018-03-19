
cmake_minimum_required(VERSION 3.2)

project(variant-range CXX)

set (CMAKE_CXX_STANDARD 11)

find_package(mpark_variant 1.2 REQUIRED)
find_package(range-v3 REQUIRED)
find_package(platform REQUIRED)

add_executable(${PROJECT_NAME} src/example.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_constexpr)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC mpark_variant platform range-v3)
