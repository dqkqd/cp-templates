cmake_minimum_required(VERSION 3.18)
project(templates)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wstrict-overflow=5"
)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_subdirectory(tests)
