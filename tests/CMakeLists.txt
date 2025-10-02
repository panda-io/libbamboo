cmake_minimum_required(VERSION 4.0)

function(add_bamboo_executable name)
  add_executable(${name} ${name}.c)
  target_link_libraries(${name} bamboo)
  add_test(NAME ${name} COMMAND ${name})
endfunction()

foreach(name IN ITEMS
  run-allocator
  run-list
  run-string
  )
  add_bamboo_executable(${name})
endforeach()