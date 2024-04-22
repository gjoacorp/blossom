#!/bin/bash

g++ src/window.cpp src/shader.cpp src/main.cpp -lGL -lglfw -lGLEW -o main && ./main
