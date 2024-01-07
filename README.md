# State-of-the-Art Project Template

A comprehensive multi-library project template employing the latest CMake features.

- Compatible with CMake 3.23+
- Includes compiled and header-only library examples
- Header file management via file sets
- Allows unit testing of non-exported library symbols without recompiling
- Supports installing Debug and Release configuration to the same directory
- Provides versioning info to `find_package()` calls

## Building and Testing

This project uses CTest to run tests regardless of the test framework used.

<details>
<summary>Linux (Ninja build system)</summary>

The following commands will build the project with the default compiler in both Debug and Release configurations, run the tests in Debug configuration, and install the library to the `install` directory.

```bash
# Optional: Install ninja-build (Debian/Ubuntu shown)
sudo apt install ninja-build

# Configure and build (Release)
cmake -S . -B build/ -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/ --target install
rm -rf build/

# Configure amnd build (Debug)
cmake -S . -B build/ -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/ --target install

# Test
cd build/
ctest --output-on-failure
cd ..
```

The `install` directory will contain CMake configuration files for both Debug and Release configurations and can be used by other CMake projects. Add a `find_package(MyProject)` statement to the consuming project and make sure that the install path is added to the `CMAKE_PREFIX_PATH` variable.

</details>

<details>
<summary>Windows (Visual Studio 2022)</summary>

The following commands will build the project with MSVC v143 in both Debug and Release configurations, run the tests in Debug configuration, and install the library to the `install` directory.

```powershell
# Configure
cmake -S . -B .\build\ -G "Visual Studio 17 2022" -A x64

# Build
cmake --build .\build\ --target install --config Debug
cmake --build .\build\ --target install --config Release

# Test
cd .\build\
ctest --output-on-failure -C Debug
cd ..
```

The `install` directory will contain CMake configuration files for both Debug and Release configurations and can be used by other CMake projects. Add a `find_package(MyProject)` statement to the consuming project and make sure that the install path is added to the `CMAKE_PREFIX_PATH` variable.

</details>

## Adapting This Template

This template is designed to be easily adapted to your needs. The following steps will help you get started:

1. Click on "Use this template" at the top of the repository page to create a copy of this repository with a clean history.
2. Replace the placeholder library names with your own library name. The following files and paths will need to be adjusted:

    - Any occurrences of `Lib1` and `Lib2` targets and tests
    - Top-level `CMakeLists.txt` file
       - Project name specified for the `project()` call
    - Rename `MyProjectConfig.cmake.in` to match `${PROJECT_NAME}Config.cmake.in`
    - File paths in the `lib1/include/` directory
    - `lib1/CMakeLists.txt` file
       - Include path suffix in `set(INCLUDE_PREFIX ...)`
       - `lib1_export.h` filename in `set(EXPORT_HEADER ...)`
       - `LIB1_EXPORT` macro name in the `generate_export_header()` call
       - `EXPORT_NAME` in the `set_target_properties()` call
    - `lib1/tests/CMakeLists.txt` file
       - `MyProject_Lib1_EXPORTS` compile definition
    - File paths in the `lib2/include/` directory
    - `lib2/CMakeLists.txt` file
       - `EXPORT_NAME` in the `set_target_properties()` call

3. Update the `target_sources()` calls in the respective libraries as you replace the dummy sources with your own files.
4. If you want to add additional linked libaries, use the `lib1/` template, use `lib2/` for header-only libraries.

## Additional Notes

- When adding dependencies via `find_package()` calls (not counting test dependencies), be sure to also add them to a `find_dependency()` call in `cmake/MyProjectConfig.cmake.in`. This ensures that client code can simply call `find_package(MyProject)` without having to worry about hidden dependencies.
- The version config file written by this project uses the `SameMajorVersion` setting. Depending on your needs, you may want to change this to `SameMinorVersion`, `AnyNewerVersion`, or `ExactVersion`.
- The `MyProject_Lib2_EXPORTS` compile definition in the `lib1/tests/` test is used to select between exporting and importing the library. It is optional, but its omission would lead to MSVC warnings about local symbols being imported.
- Targets are named `${PROJECT_NAME}_<tgt>` to avoid name collisions with other libraries. This would lead to names like `MyProject::MyProject_Lib1`, so the `EXPORT_NAME` property is used to ensure the desired `MyProject::Lib1` name. Similarly, `OUTPUT_NAME` is used for `lib1` to control the name of the generated library file.
- Since the dummy library `lib1` already starts with "lib", the default library name would be `liblib1` on Unix systems. To avoid this, the `PREFIX` property is set to an empty string.

## Contributing

If you have any suggestions or improvements, please open an issue or pull request.

## License

This is free and unencumbered software released into the public domain.

For more information, please refer to the LICENSE file or <https://unlicense.org>.
