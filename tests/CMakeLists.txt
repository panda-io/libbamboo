function(add_bamboo_executable name)
  add_executable(${name} ${name}.c)
endfunction()

foreach(name IN ITEMS
  run-allocator
  )
  add_bamboo_executable(${name})
endforeach()