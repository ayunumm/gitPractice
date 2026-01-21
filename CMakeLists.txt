cmake_minimum_required(VERSION 3.16)

set(PICO_BOARD pico_w)
include(pico_sdk_import.cmake)

pico_sdk_init()
include(pico_extras_import_optional.cmake)


set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

project(caseFeedback LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

add_subdirectory(pico_client)
