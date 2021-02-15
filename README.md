# Blluepill (STM32F103C8T6) Blinking LED

## Board diagram
![Bluepill Pin Diagram](Images/Bluepill-Pin-Details.png)

## Development Environment

### Linux
T.B.D

### MacOS (preinstall x-code and Homebrew)
Reference: https://github.com/glegrain/STM32-with-macOS

1. Install [St-Link](https://github.com/texane/stlink) tool by [homebrew](https://formulae.brew.sh/formula/stlink)
```
brew install stlink
st-info --version
# v1.6.1
```
1. Install [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) into `GCC_PATH`
```
${GCC_PATH}/arm-none-eabi-gcc --version
# arm-none-eabi-gcc (GNU Arm Embedded Toolchain 9-2020-q2-update) 9.3.1 20200408 (release)
```

### Windows
T.B.D

## Build command
```sh
cd <PROJECT_DIRECTORY>
./unixformat.sh && make clean && make -j 4 && make board
```

License
----

GNU LGPLv3


**Free Software, Hell Yeah!**
