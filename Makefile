LDFLAGS = -lGL -lglfw -lGLEW

Blossom: src/window.cpp src/shader.cpp src/main.cpp
	g++ src/window.cpp src/shader.cpp src/main.cpp $(LDFLAGS) -o Blossom

Multicube: src/window.cpp src/shader.cpp src/multi_cube.cpp
	g++ src/window.cpp src/shader.cpp src/multi_cube.cpp $(LDFLAGS) -o Multicube


.PHONY:	run clean

run: Blossom
	./Blossom

multicube: Multicube
	./Multicube

clean:
	rm -f Blossom
