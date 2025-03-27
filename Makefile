CXX_LINUX = g++
SOURCES = ../src/window.cpp ../src/shader.cpp

multi_cube:
	$(CXX_LINUX) $(SOURCES) ../src/multi_cube.cpp -lGL -lglfw -lGLEW -o multi_cube && ./multi_cube

waves:
	$(CXX_LINUX) $(SOURCES) ../src/waves.cpp -lGL -lglfw -lGLEW -o waves && ./waves

run_waves:
	./waves

run_multi_cube:
	./multi_cube
