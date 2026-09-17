# DIRECTORIES
BIN_DIR = bin
LIB_DIR = lib
LOG_DIR = log
OBJ_DIR = obj
SRC_DIR = src

# FILES
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# COMPILER AND FLAGS
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(LIB_DIR)

# TARGET
TARGET = $(BIN_DIR)/PhantomDisk

# RULES
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(TARGET)
	@./$(TARGET)

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR) $(LOG_DIR)
