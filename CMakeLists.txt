cmake_minimum_required(VERSION 4.0)

project (bamboo C)

set(SRCS
  src/allocator.c
  )

add_library(bamboo ${SRCS})

enable_testing()

add_subdirectory(tests)