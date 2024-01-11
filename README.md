# Chip8 Emulator

CHIP-8 emulator written in C++ using SDL2

## Features

- Support for all 36 original CHIP-8 instructions
- Adjustable instructions per second through command line
- Functional sound emulation 🔊!
- Cross platform

## Screenshots

![Logo](/img/ibm.png)
![Logo](/img/space.png)
![Logo](/img/pong.png)

## Installation and Running

### Cloning:

```console
git clone https://github.com/jlofti/Chip8Emulator.git
git submodule init
cd Chip8Emulator
git submodule update --init --recursive
```

_Note: be sure SDL2 is installed!_

### Build and Run:

```console
cd Chip8Emulator
cd build
make -j4
./Chip8Emulator -ROM {path} -FPS {FPS}
```

Command line inputs are only partially validated so don't go too crazy 😬. Place your roms in the rom folder. I think 540 is accurate for FPS

### Example:

```console
/Chip8Emulator -ROM pong.ch8 -FPS 540




```
