# blossom 🌸
![Visitors](https://visitor-badge.laobi.icu/badge?page_id=YOUR_USERNAME.YOUR_REPO)
![License](https://img.shields.io/github/license/gjoacorp/blossom)
![GitHub issues](https://img.shields.io/github/issues/gjoacorp/blossom)
![GitHub repo stars](https://img.shields.io/github/stars/gjoacorp/blossom?style=social)
![GitHub forks](https://img.shields.io/github/forks/gjoacorp/blossom?style=social)

**blossom** is a fast and flexible OpenGL-based rendering engine written in C++. 

## Demos

https://github.com/user-attachments/assets/d5b73877-5381-43ae-8963-58169aaaf4ad

## Prerequisites 

To use **blossom**, you'll first need to install the following prerequisites:

- [OpenGL Mathematics (GLM)](https://github.com/g-truc/glm)
- [GLFW](https://github.com/glfw/glfw)
- [The OpenGL Extension Wrangler Library (GLEW)](https://github.com/nigels-com/glew)
- [EnTT](https://github.com/skypjack/entt)

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
