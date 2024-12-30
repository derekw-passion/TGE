TARGET_NAME := TextGameEngine
CPPVERSION := c++23
CXX := g++

OBJ_DIR := obj
OUT_DIR := bin
SRC_DIRS := Engine Lib

LDLIBS := -lglfw3 -lgdi32 -lopengl32
TEST_LIBS := $(OUT_DIR)/$(TARGET_NAME).lib

GLOBALFLAGS := -std=$(CPPVERSION) -Wall -Wextra -g -fPIC
CXXFLAGS := $(GLOBALFLAGS) -shared -o $(OUT_DIR)/$(TARGET_NAME).dll -Wl,--out-implib,$(OUT_DIR)/$(TARGET_NAME).lib
TESTFLAGS := $(GLOBALFLAGS) -o $(OUT_DIR)/test.exe

SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp)) Lib/glad/glad.cpp
OBJECTS := $(addprefix $(OBJ_DIR)/,$(subst /,_,$(SRCS:.cpp=.o)))

$(OBJ_DIR)/Engine_%.o: Engine/%.cpp
	$(CXX) $(GLOBALFLAGS) -c $< -o $@

$(OBJ_DIR)/Lib_%.o: Lib/%.cpp
	$(CXX) $(GLOBALFLAGS) -c $< -o $@

$(OBJ_DIR)/Lib_glad_glad.o: Lib/glad/glad.cpp
	$(CXX) $(GLOBALFLAGS) -c $< -o $@

directories:
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@if not exist $(OUT_DIR) mkdir $(OUT_DIR)
	@echo "Directories created!"

all: directories $(OBJECTS)
	@echo "Building $(TARGET_NAME).dll..."
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDLIBS)

	$(MAKE) clean
	$(MAKE) test

	@echo "Build successful!"

test: test.cpp $(TEST_LIBS)
	@echo "Building test..."
	$(CXX) $(TESTFLAGS) $(TEST_LIBS) $^

clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)

clean_all: clean
	@if exist $(OUT_DIR) rmdir /s /q $(OUT_DIR)

.PHONY: directories all test clean clean_all