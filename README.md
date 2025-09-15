# blossom 🌸
![Visitors](https://visitor-badge.laobi.icu/badge?page_id=YOUR_USERNAME.YOUR_REPO)
![License](https://img.shields.io/github/license/gjoacorp/blossom)
![GitHub issues](https://img.shields.io/github/issues/gjoacorp/blossom)
![GitHub repo stars](https://img.shields.io/github/stars/gjoacorp/blossom?style=social)
![GitHub forks](https://img.shields.io/github/forks/gjoacorp/blossom?style=social)

**blossom** is a fast and flexible OpenGL-based rendering engine written in C++. 

## Prerequisites 

To use **blossom**, you'll first need to install the following prerequisites:

- [OpenGL Mathematics (glm)](https://github.com/g-truc/glm)
- [GLFW](https://github.com/glfw/glfw)
- [The OpenGL Extension Wrangler Library (GLEW)](https://github.com/nigels-com/glew)

### Installation command for Arch Linux and its derivatives
```sh
sudo pacman -S glm glfw glew
```

## Building the examples

Install [CMake](https://cmake.org/) if you don't already have it, then run the following command in the project root:

```sh
mkdir build && cd build && cmake .. && make
```

## Building the documentation

To build the documentation, install [Doxygen](https://www.doxygen.nl/) and then run the following command in the project root:
```sh
doxygen Doxyfile
```
This will generate the directories `blossom/html` and `blossom/latex` containing the documentation. 
