# QuickTurns

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

QuickTurns is a state-of-the-art ebook reader developed using C++ and the QT GUI interface. It offers users an intuitive and user-friendly interface that makes it easy to navigate and read books. The software application is designed to work on desktop computers and laptops running on Windows, Linux, or macOS.

One of the standout features of QuickTurns is its promise of a special text-to-speech engine that will be added in the future. This feature will enable users to listen to their favorite books, making it an excellent option for people who prefer listening to reading.

In addition to the forthcoming text-to-speech engine, QuickTurns also offers other impressive features. It supports various ebook formats, including EPUB, MOBI, and PDF, making it easy for users to read books in their preferred format. The ebook reader also offers customizable reading options, such as font size, font type, and background color, ensuring that users can personalize their reading experience.

QuickTurns is a highly versatile ebook reader that offers exceptional performance and features. Its promise of a special text-to-speech engine in the future makes it an excellent option for people who want to switch between reading and listening to their favorite books.

## Setting up QT Environment

Windows/Mac

1. Download the QT installer for Windows from the [QT online-installers](https://www.qt.io/download). For offline installer [QT offline-installers](https://www.qt.io/offline-installers)
2. Run the installer and follow the instructions to install QT on your computer. Make sure to select the components you want to install.
3. Make sure Qt location is added to PATH environment variables.

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
- `mkdir build`
- `cd build`
- `cmake .. && cmake --build .`

## Built With
[Qt](https://www.qt.io/) - The application framework used</br>
[C++](https://en.wikipedia.org/wiki/C%2B%2B) - The programming language used

## License
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/tmargary/QuickTurns/blob/main/LICENSE) file for details.
