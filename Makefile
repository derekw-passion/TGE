TARGET_NAME := TextGameEngine
CPPVERSION := c++23
CXX := g++

OBJ_DIR := obj
OUT_DIR := bin
SRC_DIRS := Engine Engine/UI Engine/Util

LDLIBS := -lopengl32 -lgdi32 -lsfml-window -lsfml-system -lsfml-graphics
TEST_LIBS := $(OUT_DIR)/$(TARGET_NAME).lib

GLOBALFLAGS := -std=$(CPPVERSION) -Wall -g -fPIC
CXXFLAGS := $(GLOBALFLAGS) -shared -o $(OUT_DIR)/$(TARGET_NAME).dll -Wl,--out-implib,$(OUT_DIR)/$(TARGET_NAME).lib
TESTFLAGS := $(GLOBALFLAGS) -o $(OUT_DIR)/test.exe

SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJECTS := $(addprefix $(OBJ_DIR)/,$(subst /,_,$(SRCS:.cpp=.o)))

$(OBJ_DIR)/Engine_%.o: Engine/%.cpp
	$(CXX) $(GLOBALFLAGS) -c $< -o $@

$(OBJ_DIR)/Engine_UI_%.o: Engine/UI/%.cpp
	$(CXX) $(GLOBALFLAGS) -c $< -o $@

$(OBJ_DIR)/Engine_Util_%.o: Engine/Util/%.cpp
	$(CXX) $(GLOBALFLAGS) -c $< -o $@

directories:
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@if not exist $(OUT_DIR) mkdir $(OUT_DIR)

all: directories $(OBJECTS)
	@echo "Building $(TARGET_NAME).dll..."
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDLIBS)

	@echo "Cleaning..."
	$(MAKE) clean
	@echo "Building test..."
	$(MAKE) test

	@echo "Build successful!"

test: $(wildcard test/*.cpp) $(TEST_LIBS)
	$(CXX) $(TESTFLAGS) $^ $(LDLIBS)

clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)

clean_all: clean
	@if exist $(OUT_DIR) rmdir /s /q $(OUT_DIR)

.PHONY: directories all test clean clean_all