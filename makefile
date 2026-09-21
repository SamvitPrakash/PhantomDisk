# DIRECTORIES
BUILD_DIR := build

# EXECUTABLES
PHANTOM := $(BUILD_DIR)/Phantom
PHANTOMD := $(BUILD_DIR)/Phantomd
PHANTOMHAUNT := $(BUILD_DIR)/PhantomHaunt

BINARIES := $(PHANTOM) $(PHANTOMD) $(PHANTOMHAUNT)

# CMAKE
CMAKE := CMakeLists.txt
CMAKE_GENERATOR := cmake -S . -B $(BUILD_DIR)

# DEFAULT TARGET
all: $(BINARIES)

# CONFIGURE CMAKE
$(BUILD_DIR):
	$(CMAKE_GENERATOR)

# BUILD INDIVIDUAL EXECUTABLES
$(PHANTOM): $(BUILD_DIR)
	cmake --build $(BUILD_DIR) --target Phantom

$(PHANTOMD): $(BUILD_DIR)
	cmake --build $(BUILD_DIR) --target Phantomd

$(PHANTOMHAUNT): $(BUILD_DIR)
	cmake --build $(BUILD_DIR) --target PhantomHaunt

# CONVENIENCE TARGETS
phantom: $(PHANTOM)

phantomd: $(PHANTOMD)

phantomhaunt: $(PHANTOMHAUNT)

# RUN
run: $(PHANTOM)
	./$(PHANTOM)

run-phantom: $(PHANTOM)
	./$(PHANTOM)

run-phantomd: $(PHANTOMD)
	./$(PHANTOMD)

run-phantomhaunt: $(PHANTOMHAUNT)
	./$(PHANTOMHAUNT)

# CLEAN
clean:
	cmake --build $(BUILD_DIR) --target clean

cleanV:
	rm -rf $(BUILD_DIR)

# PHONY TARGETS
.PHONY: all phantom phantomd phantomhaunt run run-phantom run-phantomd run-phantomhaunt clean cleanV