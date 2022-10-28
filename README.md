# OneTBB Example Test

## Usage

0. Requirements

    - [CMake 3.20 or later](https://cmake.org/download). On Unix, CMake installed from `apt` can be
      outdated. Check with `cmake --version`.
    - Command line (Unix) or Powershell/Git Bash (Windows).

1. Clone the repository:

    ```bash
    git clone https://github.com/jdumas/onetbb-sanitizer.git
    ```

2. Setup build:

    ```bash
    cd <repo-dir>
    mkdir build
    cd build
    cmake ..
    ```

    By default, this will generate a Visual Studio project on Windows, and Unix Makefiles on OSX and
    Linux. If you wish to use XCode on Mac, use `cmake -G "Xcode" ..` instead.

3. Build

    ```bash
    cmake --build .
    ```

    Or open the Visual Studio/XCode project with `cmake --open .`

## Contributing

Read the [Contributing Guide](./.github/CONTRIBUTING.md) for more
information.

## Licensing

This example project is licensed under the MIT license. See [LICENSE](LICENSE) for more information.
