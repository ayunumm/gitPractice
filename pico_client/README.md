# Policies

- Always branch when adding a feature / fixing bugs.
- No need to branch when modifying documentation files e.g. README.md.
- Atleast one approval in order to be allowed to merge to main.
- Use unittests when possible.
- TODO: Nasa.
- Use camelCase.
- Newline in-between functions / scopes.
- TODO: Name branch after ticket name.

# Setup
create the following file named secrets.h in the /include directory following the template below
```
#ifndef SECRETS_H
#define SECRETS_H

#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASS"

#define THINGSPEAK_API_KEY "MYAPIKEY"

#endif // SECRETS_H
```

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
