cmake_minimum_required(VERSION 3.15)
project(ML-Algorithms-in-CPP)



set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_BINARY_DIR "import/lib")



if(NOT CMAKE_BUILD_TYPE AND NOT (MSVC_IDE OR XCODE))
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type, one of: Release, Debug" FORCE)
endif()

message( STATUS "Build type: ${CMAKE_BUILD_TYPE}" )
message( STATUS "Configuration types: ${CMAKE_CONFIGURATION_TYPES}" )


file(GLOB srcs *.cpp *.c)
file(GLOB hdrs *.hpp *.h)

include_directories("${CMAKE_CURRENT_LIST_DIR}")
macro(add_example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} ${CMAKE_BINARY_DIR})

endmacro()


add_example(main)

