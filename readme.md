BPVM
=

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Build Status](https://travis-ci.com/majestic53/bpvm.svg?branch=master)](https://travis-ci.com/majestic53/bpvm)

A BytePusher VM, written in C++

Table of Contents
=

1. [About](https://github.com/majestic53/bpvm#about) -- About the project
2. [Usage](https://github.com/majestic53/bpvm#usage) -- How to use the project
3. [Building](https://github.com/majestic53/bpvm#building) -- How to build the project
4. [Changelog](https://github.com/majestic53/bpvm#changelog) -- Log of project changes

About
=

BytePusher is a minimalistic single-instruction computer, based off the CHIP-8. Some features of the system include:
* A big-endian ByteByteJump processor, running at \~3.93 MIPS
* A 24-bit memory bus, allowing up-to 16 MB of memory
* A 256x256 pixel display, supporting 216 websafe colors
* A 16-key keyboard
* 8-bit audio output

For additional information, see: [https://esolangs.org/wiki/BytePusher](https://esolangs.org/wiki/BytePusher)

Usage
=

#### Interface

The project is implemented in C++ and exposes a simple C-style API, described in ```include/bpvm.h``` and ```lib/libbpvm.a```:

|Name    |Description                             |Signature                               |
|--------|----------------------------------------|----------------------------------------|
|bpvm_run|Run BPVM with a specified configuration |```int bpvm_run(const bpvm_t *config)```|
|bpvm_err|Retrieve the last BPVM error as a string|```const char *bpvm_err(void)```        |
|bpvm_ver|Retrieve the BPVM version as a string   |```const char *bpvm_ver(void)```        |

For an example usage of this API, see the launcher tool, under ```tool/```

Building
=

__NOTE__: Tested under MacOS with the GCC/Clang C++ compilers. Modification to the makefiles might be required to build with a different OS/compiler.

### Building from Makefile

#### Arguments

Run the following commands from the projects root directory:

```
$ export CXX=<COMPILER>
$ make <BUILD_TYPE>
```

Where COMPILER corrisponds to either ```clang++``` or ```g++```

Where BUILD_TYPE corrisponds to either ```release``` or ```debug```

#### Optional Arguments

To build with tracing enabled, run the following command from the project's root directory:

```
$ make TRACE=<LEVEL>
```

Where LEVEL corrisponds to the tracing verbosity (0=Off, 1=Error, 2=Warnings, 3=Information, 4=Verbose)

#### Examples

The following example shows how to build the release project, under the Clang C++ compiler:

```
$ export CXX=clang++
$ make release
```

The following example shows how to build the debug project with informational tracing, under the GCC C++ compiler:

```
$ export CXX=gcc
$ make TRACE=3
```

Changelog
=

Version 0.1.1934
-

*Updated: 8/22/2019*

* Initial commit

*Changelog truncated (see file history for full log)*
