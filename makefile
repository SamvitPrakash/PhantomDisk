# DIRECTORIES
SRC_DIR=src
BUILD_DIR=build

# FILES
SOURCES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
BINARY=$(BUILD_DIR)/Phantomd
TARGET=$(SRC_DIR)/main.cpp

# RULES
all: $(BINARY)

$(BUILD_DIR):
	cmake -S . -B $(BUILD_DIR)

$(BINARY): $(BUILD_DIR) $(SOURCES)
	cmake --build $(BUILD_DIR)

run: $(BINARY)
	./$(BINARY)

clean:
	rm -rf $(BINARY)

cleanV:
	rm -rf $(BUILD_DIR)

# PHONY TARGETS
.PHONY: all run clean cleanV