add_executable(blink
        src/main.c
)

target_link_libraries(blink
    pico_stdlib
)

target_include_directories(blink
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

pico_add_extra_outputs(blink)

pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 1)


if(NOT PICO_PLATFORM)
    include(CTest)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )

    add_library(caseFeedback
      src/test_lib.c
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()