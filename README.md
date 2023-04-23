# QuickTurns

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

QuickTurns is a state-of-the-art ebook reader developed using C++ and the QT GUI interface. It offers users an intuitive and user-friendly interface that makes it easy to navigate and read books. The software application is designed to work on desktop computers and laptops running on Windows, Linux, or macOS.

[Slides](https://docs.google.com/presentation/d/1JWWIJeA5GChfNUFarCOqWLlyUM1J1mbe73Wsd7jwBDk)</br>

## Demo
![output](https://user-images.githubusercontent.com/56524296/233860135-2ad6e2bb-a6c3-4772-aec1-46b100751456.gif)


## Setting up QT Environment

Windows/Mac

1. Download the QT installer for Windows from the [QT online-installers](https://www.qt.io/download). For offline installer [QT offline-installers](https://www.qt.io/offline-installers)
2. Run the installer and follow the instructions to install QT on your computer. Make sure to select the components you want to install.
3. Make sure Qt location is added to PATH environment variables.

Linux

Install the QT development tools using your distribution's package manager.

- Ubuntu

    ```
    sudo apt update
    sudo apt upgrade
    sudo apt install qt6-default libqt6webenginecore-dev libqt6webenginewidgets-dev
    qmake -v
    ```

- Arch

    ```
    sudo pacman -Syu
    sudo pacman -S qt6-base qt6-webengine
    qmake -v
    ```

- Fedora

    ```
    sudo dnf update
    sudo dnf install qt6-qtbase-devel qt6-qtwebengine-devel
    qmake -v
    ```

- CentOS/RHEL

    ```
    sudo yum install epel-release
    sudo yum update
    sudo yum install qt6-qtbase-devel qt6-qtwebengine-devel
    qmake -v
    ```

- openSUSE

    ```
    sudo zypper update
    sudo zypper install libQt6WebEngineWidgets5 libQt6WebEngineCore5-devel
    qmake -v
    ```

## Installation
- `git clone --recurse-submodules git@github.com:tmargary/QuickTurns.git`
- `cd QuickTurns`
- `mkdir build`
- `cd build`
- `cmake .. && cmake --build .`

## Built With
[Qt 6](https://www.qt.io/) - The application framework used</br>
[C++](https://en.wikipedia.org/wiki/C%2B%2B) - The programming language used

## License
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/tmargary/QuickTurns/blob/main/LICENSE) file for details.
