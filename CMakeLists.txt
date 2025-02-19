cmake_minimum_required(VERSION 3.15)
project(HelloClap VERSION 1.0 LANGUAGES CXX)

# CLAP SDK setup
include(FetchContent)
FetchContent_Declare(
  clap
  GIT_REPOSITORY https://github.com/free-audio/clap
  GIT_TAG main
)
FetchContent_MakeAvailable(clap)

# Plugin target
add_library(HelloClap SHARED
  hello_clap.cpp
)

target_include_directories(HelloClap PRIVATE ${clap_SOURCE_DIR}/include)
set_target_properties(HelloClap PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
  POSITION_INDEPENDENT_CODE ON
)

if(WIN32)
  target_compile_definitions(HelloClap PRIVATE CLAP_EXPORT=__declspec(dllexport))
endif()
