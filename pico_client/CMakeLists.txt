cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0135 NEW)

option(PICO_BUILD "Build firmware for Pico" ON)
option(PICO_TESTS_BUILD "Build tests" OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PICO_BOARD pico_w)

include(FetchContent)

if (PICO_BUILD)
  message(STATUS "Including Pico SDK for firmware build")
  FetchContent_Declare(
    pico_sdk
    GIT_REPOSITORY https://github.com/raspberrypi/pico-sdk.git
    GIT_TAG master
  )
  FetchContent_MakeAvailable(pico_sdk)
endif()

project(pico_client LANGUAGES C CXX ASM)

if (PICO_BUILD)
  pico_sdk_init()

  # olle needs to set this for compiling on arch-linux
  set(CMAKE_EXECUTABLE_SUFFIX ".elf")

  if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
  endif()

  add_executable(pico_client
    src/main.c
    src/wifi.c
    src/lcd.c
  )

  target_link_libraries(pico_client
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    hardware_i2c
    hardware_gpio
  )

  target_include_directories(pico_client
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/src
  )

  pico_add_extra_outputs(pico_client)
  pico_enable_stdio_usb(pico_client 1)
  pico_enable_stdio_uart(pico_client 0)
endif()

include(CTest)
if (PICO_TESTS_BUILD AND NOT PICO_BUILD)
  enable_testing()

  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )

  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  add_library(pico_client_test_lib
    src/test_lib.c
  )

  target_include_directories(pico_client_test_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

  add_subdirectory(tests)
endif()
