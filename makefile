# DIRECTORIES
SRC_DIR=src
BUILD_DIR=build

# FILES
BINARY=$(BUILD_DIR)/PhantomDiskd
TARGET=$(SRC_DIR)/main.cpp

# RULES
all: $(BINARY)

$(BINARY): $(BUILD_DIR) $(SRC_DIR)/main.cpp
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -S . -B $(BUILD_DIR)

run: $(BINARY)
	./$(BINARY)

clean:
	rm -rf $(BINARY)

cleanV:
	rm -rf $(BUILD_DIR)

# PHONY TARGETS
.PHONY: all run clean cleanV