SRC_DIR=src
BUILD_DIR=build

BINARY=$(BUILD_DIR)/PhantomDiskd
TARGET=$(SRC_DIR)/main.cpp

all: $(BINARY)

$(BINARY): $(SRC_DIR)/main.cpp
	cmake --build $(BUILD_DIR)

run: $(BINARY)
	./$(BINARY)

clean:
	rm -rf $(BINARY)