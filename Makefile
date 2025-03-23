TARGET := rgu-labs
BUILD_TYPE ?= Release
GENERATOR ?= Ninja
BUILD_DIR := build
TARGET_DIR := target
CMAKE_CMD := cmake
DEBUGGER_CMD := pwndbg
ARGS := # For passing arguments to run/valgrind

ifeq ($(V),1)
	Q :=
else
	Q := @
endif

.PHONY: all configure build clean debug release native run pwn valgrind analyze help

all: build

configure:
	$(Q)echo "Configuring project for $(BUILD_TYPE) build [$(GENERATOR)]..."
	$(Q)mkdir -p $(BUILD_DIR)/$(BUILD_TYPE)
	$(Q)$(CMAKE_CMD) -G "$(GENERATOR)" \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-B "$(BUILD_DIR)/$(BUILD_TYPE)" \
		-S .

build: configure
	$(Q)echo "Building project in $(BUILD_TYPE) mode..."
	$(Q)$(CMAKE_CMD) --build "$(BUILD_DIR)/$(BUILD_TYPE)"
	$(Q)cp $(BUILD_DIR)/$(BUILD_TYPE)/compile_commands.json compile_commands.json
	$(Q)mkdir -p "$(TARGET_DIR)"
	$(Q)if [ -f "$(BUILD_DIR)/$(BUILD_TYPE)/$(TARGET)" ]; then \
		cp "$(BUILD_DIR)/$(BUILD_TYPE)/$(TARGET)" "$(TARGET_DIR)/$(TARGET)"; \
	else \
		echo "Error: Build failed - target not found"; exit 1; \
	fi

clean:
	$(Q)echo "Cleaning build artifacts..."
	$(Q)rm -rf "$(BUILD_DIR)" "$(TARGET_DIR)"

cleanbuild: clean build

debug:
	$(Q)$(MAKE) BUILD_TYPE=Debug build

release:
	$(Q)$(MAKE) BUILD_TYPE=Release build

run: debug
	$(Q)echo "Running Debug build..."
	$(Q)echo "----------------------"
	$(Q)"$(TARGET_DIR)/$(TARGET)" $(ARGS)

pwn: debug
	$(Q)echo "Starting debug session..."
	$(Q)echo "-------------------------"
	$(Q)$(DEBUGGER_CMD) "$(TARGET_DIR)/$(TARGET)"

valgrind: debug
	$(Q)echo "Running with Valgrind..."
	$(Q)echo "------------------------"
	$(Q)valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --error-exitcode=1 \
		"$(TARGET_DIR)/$(TARGET)" $(ARGS)

analyze: build
	$(Q)echo "Analyzing code with clang-tidy..."
	$(Q)find . -name '*.cpp' -o -name '*.h' -not -path "./$(BUILD_DIR)/*" -not -path "./$(TARGET_DIR)/*" | xargs clang-tidy -p.

analyze_fix: build
	$(Q)echo "Analyzing code with clang-tidy..."
	$(Q)find . -name '*.cpp' -o -name '*.h' -not -path "./$(BUILD_DIR)/*" -not -path "./$(TARGET_DIR)/*" | xargs clang-tidy -p . --fix

help:
	$(Q)echo "Project Build System"
	$(Q)echo "Targets:"
	$(Q)echo "  all           - Default build (Release)"
	$(Q)echo "  build         - Build project (BUILD_TYPE=Release)"
	$(Q)echo "  debug         - Build Debug version"
	$(Q)echo "  release       - Build Release version"
	$(Q)echo "  clean         - Remove build artifacts"
	$(Q)echo "  cleanbuild    - Clean and rebuild"
	$(Q)echo "  run           - Run Debug build (ARGS= for arguments)"
	$(Q)echo "  pwn           - Debug with pwndbg"
	$(Q)echo "  valgrind      - Run with Valgrind memcheck"
	$(Q)echo "  analyze       - Run static code analysis with clang-tidy"
	$(Q)echo "  help          - Show this help"
	$(Q)echo ""
	$(Q)echo "Variables:"
	$(Q)echo "  BUILD_TYPE    - Debug/Release (default: Release)"
	$(Q)echo "  GENERATOR     - CMake generator (default: Ninja)"
	$(Q)echo "  V=1           - Verbose output"
	$(Q)echo "  ARGS          - Arguments for run/valgrind"
	
