add_executable(caseFeedback
        src/main.c
	src/wifi.c
)

target_link_libraries(caseFeedback
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

target_include_directories(caseFeedback
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# target_link_libraries(caseFeedback PRIVATE caseFeedback_lib)

pico_enable_stdio_usb(caseFeedback 1)
pico_enable_stdio_uart(caseFeedback 1)
pico_add_extra_outputs(caseFeedback)


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
