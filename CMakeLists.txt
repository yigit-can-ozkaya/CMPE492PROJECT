cmake_minimum_required(VERSION 3.20)

project("LIBBOUNCMPE" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(jsonCCL)
find_package(Boost 1.81 COMPONENTS json REQUIRED)
find_package(nlohmann_json 3.11.2 REQUIRED)

target_include_directories(
  jsonCCL
  PUBLIC 
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>/include
)
target_sources(
  jsonCCL
  PRIVATE 
    "src/jsonCCL.cpp"
)
target_link_libraries(
  jsonCCL
  PUBLIC 
    Boost::json
)


add_subdirectory(tests)
enable_testing()
find_package(Catch2 REQUIRED)
include(Catch)
include(CTest)

add_executable(
  bouncmpe_tests
  tests/jsonmerge.test.cpp
)

target_link_libraries(
  bouncmpe_tests
    PRIVATE  
      jsonCCL
      Catch2::Catch2WithMain
)

catch_discover_tests(bouncmpe_tests)

# if (ENABLE_TESTS)
#     add_subdirectory(tests)
#     enable_testing()
# endif()

if (BOUNCMPE_BUILD_APPS)
    add_subdirectory(apps)
endif()

