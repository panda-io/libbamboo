cmake_minimum_required(VERSION 4.0)

project (bamboo C)

set(SRCS
  src/allocator.c
  )

add_library(bamboo ${SRCS})
target_include_directories(bamboo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_subdirectory(tests)