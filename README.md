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

2. Install [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) into `GCC_PATH`
```
${GCC_PATH}/arm-none-eabi-gcc --version
# arm-none-eabi-gcc (GNU Arm Embedded Toolchain 9-2020-q2-update) 9.3.1 20200408 (release)
```

### Windows 10
1. ST-LINK software:

	+ Install ST-LINK USB driver [STSW-LINK009](https://www.st.com/en/development-tools/stsw-link009.html)

	+ Download [OSS STlink Tools](https://github.com/stlink-org/stlink/releases/tag/v1.6.1) and extract into non-space directory path. Example: *E:\01-Hobbies\stlink-1.6.1-x86_64-w64-mingw32*

	+ (Optional) STM32 ST-LINK Utility [STSW-LINK004](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stsw-link004.html)

	+ (Optional) STM32 Cube Programmer [STM32CubeProg](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stm32cubeprog.html)

2. Install [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) into `GCC_PATH`. Default at *C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2020-q4-major*
```
${GCC_PATH}/arm-none-eabi-gcc.exe --version
# arm-none-eabi-gcc.exe (GNU Arm Embedded Toolchain 10-2020-q4-major) 10.2.1 20201103 (release)
```

3. Install [MobaXterm Home Edition](https://mobaxterm.mobatek.net/download.html)
	a. Install `make` tool in MobaXterm local shell
```
apt-get install -y make
```

## Build command

### MacOS & Linux
```sh
cd <PROJECT_DIRECTORY>
./unixformat.sh && make clean && make -j 4 && make board
```

### Windows 10 (Remember to correct your `GCC_PATH`)
Run the command below in MobaXterm local shell
```
cd <PROJECT_DIRECTORY>
./unixformat.sh && make clean && \
make GCC_PATH="/drives/c/Program\ Files\ \(x86\)/GNU\ Arm\ Embedded\ Toolchain/10\ 2020-q4-major/bin/" -j 4 && \
make ST_PROG_PATH="/drives/e/01-Hobbies/stlink-1.6.1-x86_64-w64-mingw32/bin/" board
```

License
----

GNU LGPLv3


**Free Software, Hell Yeah!**
