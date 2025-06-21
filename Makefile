CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS  = -lGL -lglfw -lGLEW
SOURCES  = src/window.cpp src/shader.cpp

MULTI_CUBE_SRC = examples/multi_cube.cpp
WAVES_SRC      = examples/waves.cpp
TRIANGLES_SRC  = examples/triangles.cpp

MULTI_CUBE_BIN = multi_cube
WAVES_BIN      = waves
TRIANGLES_BIN  = triangles

.PHONY: all clean run_multi_cube run_waves run_triangles

all: $(MULTI_CUBE_BIN) $(WAVES_BIN) $(TRIANGLES_BIN)

$(MULTI_CUBE_BIN): $(SOURCES) $(MULTI_CUBE_SRC)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(MULTI_CUBE_SRC) $(LDFLAGS) -o $@

$(TRIANGLES_BIN): $(SOURCES) $(TRIANGLES_SRC)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(TRIANGLES_SRC) $(LDFLAGS) -o $@

$(WAVES_BIN): $(SOURCES) $(WAVES_SRC)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(WAVES_SRC) $(LDFLAGS) -o $@

run_multi_cube: $(MULTI_CUBE_BIN)
	./$(MULTI_CUBE_BIN)

run_waves: $(WAVES_BIN)
	./$(WAVES_BIN)

run_triangles: $(TRIANGLES_BIN)
	./$(TRIANGLES_BIN)


clean:
	rm -f $(MULTI_CUBE_BIN) $(WAVES_BIN) $(TRIANGLES_BIN)
