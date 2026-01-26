# Policies

- Always branch when adding a feature / fixing bugs.
- No need to branch when modifying documentation files e.g. README.md.
- Atleast one approval in order to be allowed to merge to main.
- Use unittests when possible.
- TODO: Nasa.
- Use camelCase.
- Newline in-between functions / scopes.
- TODO: Name branch after ticket name.

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
