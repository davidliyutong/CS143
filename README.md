# Project LAC

## Environment

- gcc 7.5.0, installed at /usr/bin/gcc
- Ubuntu 18.04 LTS

## Build Instruction

The project is designed to be built with `cmake`. It can be accomplished by executing following instructions in the
terminal:

```bash
$ mkdir cmake_build && cd cmake_build
$ cmake -DCMAKE_BUILD_TYEPE=Debug ${PATH_TO_PROJECT}
$ make
```

![compile-cmake](./misc/img/compile-cmake.png)

or the `build.sh` script:

```bash
$ sudo chmod +x ./build.sh
$ export PROJET_DIR=${PATH_TO_PROJECT}
$ ./build.sh
[ Info ] Enable Debug Mode? [Y/n]:
```

![compile-cmake](./misc/img/compile-script.png)

The variable `PROJET_DIR` **must** be set to project directory correctly by `export`.

These commands will generate executables in the `build` directory:

- `projet1-projet4` are answers for project 1 - project 4
- `lac` is the final executable (project 5)
- `color` serves as a code highlighter

## Project contents

Each directory contains a part of project:

- `common` Common components
- `demo` Demonstrations
- `lex` Lexicale analyse
- `runtime` Runtime functions
- `tests` Test units
- `playground` Examples de LAC
- `utils` Other functions that are useful
- `tools` Scripts and tools

## Compile Modes

Use cmake flags to build the release version and debug version:

```bash
$ cmake -DCMAKE_BUILD_TYEPE=Debug ${PATH_TO_PROJECT}
```

```bash
$ cmake -DCMAKE_BUILD_TYEPE=Release ${PATH_TO_PROJECT}
```

### Interpretation

Release version has `-O3` option enabled, output debug informations are switched off

Rebug version outputs useful debug information