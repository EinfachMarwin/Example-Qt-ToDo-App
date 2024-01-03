# ToDo-Applikation

---
# Table of Contents
1. [Introduction](#introduction)
3. [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [Windows](#windows)
    - [Linux](#linux)
    - [macOS](#macos)
    - [Troubleshooting](#troubleshooting)
5. [App Color Scheme](#app-color-scheme)
6. [References](#references)

---

# Introduction
The ToDo List application is a simple and intuitive task management tool that allows users to create, 
edit, and delete tasks. The application is designed to be user-friendly and easy to navigate, with a sleek and modern interface that is visually appealing and functional. 
The application is built using C++ and Qt, and is compatible with Windows, macOS, and Linux operating systems.
For Data Storage, the application uses a SQLite database to store user data locally on the user's device.

---

# Installation
At the moment, the ToDo List application is not available for download as a standalone executable. We are working on making the application available for download in the near future. In the meantime, you can download the source code and build the application yourself. See the instructions below for your operating system.

**The application is built using the following technologies:**
- C++ 20
- Qt6
- SQLite3
- TinyORM 0.36.5
- CMake 3.9
- vcpkg package manager

## Prerequisites
1. Download the vcpkg package manager from [here](https://vcpkg.io/en/getting-started.html) and follow the instructions to install it.
2. Download the source code from this repository.
3. You don´t need to install Qt or TinyORM, vcpkg will do that for you.

Ensure you have CMake and vcpkg installed on your system. These tools are necessary for building the program and 
managing its dependencies. Dont´t forget to add the vcpkg directory to your PATH environment variable.
## Windows 
To use use this project on Windows, you need to add the following options to your CMake settings:

1. **Set the VCPKG Target Triplet:**
   Add the following option to your CMake settings to specify the correct vcpkg target triplet:
   ```bash
   -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic"
    ```
   This informs CMake which architecture and build configuration to use.
2. **Define the VCPKG Overlay Port:**
   Set the VCPKG overlay port to the path containing the `tinyorm` library:
   ```bash
   -DVCPKG_OVERLAY_PORTS="<your installation path>/ports/overlays/tinyorm"
   ```
   Replace `<your installation path>` with the actual path to your CMake project directory.

3. **Specify the CMake Toolchain File:**
   Provide the path to your CMake toolchain file:
   ```bash
   -DCMAKE_TOOLCHAIN_FILE="<your installation path>/cmake/Toolchain.cmake"
   ```
   Again, replace `<your installation path>` with the path to your CMake project directory.

After you have made these settings, you should be able to configure and build the project using CMake. 
Follow the usual steps to build a CMake project in your development environment.
Be aware that the first build will take some time, as vcpkg needs to download and build all the dependencies.

## Linux
The instructions for building the project on Linux will be added soon.

## macOS
Unfortunately, the ToDo List can´t be built on macOS at the moment. The reason for this is that the TinyORM library, which is used in the project, is not compatible with macOS. 

## Troubleshooting
If you encounter any issues during the installation or configuration, please check that all paths are set correctly and that the required dependencies have been installed via vcpkg. If you continue to experience problems, do not hesitate to create an issue in the project repository.

---

# App Color Scheme
The ToDo List application showcases a sleek and contemporary design, utilizing a harmonious palette of cool tones that underpin its modern and user-friendly interface. The color scheme is implemented throughout the app to ensure visual consistency and a seamless user experience.

## Color Palette

- ![#ffffff](https://via.placeholder.com/15/ffffff/000000?text=+) `#ffffff` 

- ![#4d0e1f9](https://via.placeholder.com/15/d0e1f9/000000?text=+) `#d0e1f9` 

- ![#4d648d](https://via.placeholder.com/15/4d648d/000000?text=+) `#4d648d`

- ![#283655](https://via.placeholder.com/15/283655/000000?text=+) `#283655` 

- ![#1c1f26](https://via.placeholder.com/15/1c1f26/000000?text=+) `#1c1f26`

# References
## Icon-Attribution
This project uses icons from [Icons8](https://icons8.com/). The icons are not modified. <br>
1. <a target="_blank" href="https://icons8.com/icon/83214/einstellungen">Einstellungen</a> 
2. <a target="_blank" href="https://icons8.com/icon/84094/doppel-tick">Doppel Tick</a> 
3. <a target="_blank" href="https://icons8.com/icon/59807/hilfe">Hilfe</a> 
4. <a target="_blank" href="https://icons8.com/icon/59782/fehler">Fehler</a> 
5. <a target="_blank" href="https://icons8.com/icon/100835/inbox">Inbox</a>
6. <a target="_blank" href="https://icons8.com/icon/60002/sun">Sun</a> 