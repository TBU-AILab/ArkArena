# ArkArena
## System for Augmented Reality for Kilobots (ARK)
### Introduction
This project is originally developed by Tomas Bata University in Zlin, Faculty of applied informatics. 
Even if it is built on greenfield, some algorithms and principles were used from the previously used system [KilobotArena](https://github.com/TBU-AILab/KilobotArena)

The main aim is to provide a software tool for Kilobots laboratories, which can be used for the execution and documentation Kilobots based experiments.

### Installation

The Ubuntu (or Ubuntu based distributions) is preferred as the OS for ArkArena. 

Ark arena is composed by using opnesource version of [Qt 6](https://www.qt.io/download-open-source) library and [OpenCV](https://opencv.org).
Be aware of the version of Qt library installed by the distro package manager (`sudo apt install qt`), the repositories may contain older than supported versions. The recommended way is to use the official online installer.

As a project management system the [CMake](https://cmake.org) is used. Moreover, corresponding C++ compiler need to be installed on target system (Ubuntu: `sudo apt install build-essentials`).
Thanks to the CMake, the various set of IDE's can be used for compilation/development (QtCreator, Eclipse, CLion, etc...) Furthermore, the compilation itself can be done by using simple commands in terminal.

### OHC Controller

TODO: Add documentation...

### Contribution

Please follow the rules defined in [CONTRIBUTION.md](CONTRIBUTION.md)

### Unit tests

The unit tests are based on [GTest](https://google.github.io/googletest/) testing framework.

The framework sources are added as a git submodule. In order to download it run following command from the project root after cloning of the KilobotArena repository:

```
git submodule init
git submodule update
```
Moreover, in order to clone the tests, the CMake project tool need to be used and the **PACKAGE_TESTS** parameter need to be set to ON.

The unit tests are place in "test" folder, where each unit has their own file.

### See Also

* ARK makes use of a redesigned overhead controller: [ARK_OHC](https://github.com/DiODeProject/ARK_OHC)
* [Kilobot Wiki](http://diode.group.shef.ac.uk/kilobots/index.php/Kilobots)