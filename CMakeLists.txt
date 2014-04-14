cmake_minimum_required(VERSION 2.6)
project(spimdle)

set(spimdle_VERSION_MAJOR 0)
set(spimdle_VERSION_MINOR 1)
set(spimdle_VERSION_PATCH 0)

include_directories("${PROJECT_SOURCE_DIR}")

enable_testing()

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

add_subdirectory(spim)
