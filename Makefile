#adapted from GunshipPenguin/shallow-blue

CXX = g++

SRC_DIR = $(shell pwd)/src

CPP_FILES = $(wildcard src/*.cpp)
TEST_CPP_FILES = $(filter-out src/main.cpp, $(sort $(CPP_FILES) $(wildcard tests/*.cpp)))

OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
TEST_OBJ_FILES = $(addprefix obj/,$(notdir $(TEST_CPP_FILES:.cpp=.o)))

LD_FLAGS ?= -pthread -flto
CC_FLAGS ?= -Wall -std=c++17 -O3 -march=native -flto -pthread -fno-exceptions

test: CC_FLAGS = -Wall -std=c++17 -O3 -march=native -flto -pthread

OBJ_DIR = obj

BIN_NAME = SubPerfect
TEST_BIN_NAME = SubPerfectTest

all: $(OBJ_DIR) $(BIN_NAME)
test: $(OBJ_DIR) $(TEST_BIN_NAME)
$(BIN_NAME): $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $^

$(TEST_BIN_NAME): $(TEST_OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CXX) $(CC_FLAGS) -c -o $@ $<

obj/%.o: tests/%.cpp
	$(CXX) $(CC_FLAGS) -I $(SRC_DIR) -c -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TEST_BIN_NAME)
	rm -f $(BIN_NAME)