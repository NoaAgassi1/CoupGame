CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude -Isrc -Itests
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRC))

TEST_MAIN = tests/test_main.cpp
TEST_SRCS = $(filter-out $(TEST_MAIN), $(wildcard tests/*.cpp))
TEST_OBJS = $(patsubst tests/%.cpp, build/%.o, $(TEST_SRCS))
TEST_BIN = build/tests.out

all: coup_gui

coup_gui: $(OBJS) build/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/main.o: src/main.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: tests/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_BIN): $(TEST_MAIN) $(TEST_SRCS) $(TEST_OBJS) $(OBJS)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

tests: $(TEST_BIN)

runtests: tests
	./$(TEST_BIN)

valgrind: $(TEST_BIN)
	valgrind --leak-check=full ./$(TEST_BIN)

Main: coup_gui
	./coup_gui

clean:
	rm -rf build *.out coup_gui
