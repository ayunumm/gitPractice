cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0135 NEW)

set(PICO_BOARD pico_w)
include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

project(caseFeedback LANGUAGES C CXX ASM)
pico_sdk_init()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

add_subdirectory(pico_client)