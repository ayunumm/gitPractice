# Building

```
./scripts/build.sh
```
or build manually
```
cmake -B build
cmake --build build
```

# Testing

```
./scripts/run_tests.sh
```
or build manually
```
cmake -B build -DPICO_BUILD=OFF -DPICO_TESTS_BUILD=ON
cmake --build build
ctest --output-on-failure
```
# Raspberry Pi Pico W setup

<img width="845" height="646" alt="Screenshot 2026-01-26 192517" src="https://github.com/user-attachments/assets/ff6990c3-5750-4d80-be5f-45a62966e49b" />

```
 The three push buttons are connected to GPIO pins 6, 7, and 8 on the Pico W, from top to bottom. This may not be clearly visible in the image.
 ```
