#!/bin/bash

g++ src/window.cpp src/shader.cpp src/waves.cpp -lGL -lglfw -lGLEW -o waves && ./waves
