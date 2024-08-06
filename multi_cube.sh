#!/bin/bash

g++ src/window.cpp src/shader.cpp src/multi_cube.cpp -lGL -lglfw -lGLEW -o multi_cube && ./multi_cube
