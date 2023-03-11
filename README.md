# QuickTurns

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

The future of reading and listening to e-books

## Setting up QT Environment

Windows/Mac

1. Download the QT installer for Windows from the [QT website](https://www.qt.io/download).
2. Run the installer and follow the instructions to install QT on your computer. Make sure to select the components you want to install.

Linux

Install the QT development tools using your distribution's package manager.

- Ubuntu
    ```
    sudo apt-get update
    sudo apt-get install build-essential qt5-qmake qtbase5-dev
    ```
- Fedora
    ```
    sudo dnf update
    sudo dnf groupinstall "Development Tools"
    sudo dnf install qt5-devel
    ```
- CentOS/RHEL
    ```
    sudo yum update
    sudo yum groupinstall "Development Tools"
    sudo yum install qt5-devel
    ```
- Arch Linux
    ```
    sudo pacman -Syu
    sudo pacman -S base-devel
    sudo pacman -S qt5-base
    ```
- openSUSE
    ```
    sudo zypper update
    sudo zypper install -t pattern devel_basis
    sudo zypper install libqt5-qtbase-devel
    ```

## Installation
- `git clone --recurse-submodules git@github.com:tmargary/QuickTurns.git`
- `cd QuickTurns`
- `mkdir build && cd build`
- `cmake ..`

## Built With
[Qt](https://www.qt.io/) - The application framework used</br>
[C++](https://en.wikipedia.org/wiki/C%2B%2B) - The programming language used

## License
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/tmargary/QuickTurns/blob/main/LICENSE) file for details.
