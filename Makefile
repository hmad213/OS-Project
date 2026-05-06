
CC      := gcc
SRC_DIR := src
BUILD   := build
TARGET  := $(BUILD)/game
 
RAYLIB_DIR := deps/raylib
CFLAGS  := -I$(RAYLIB_DIR)/include -Wall -Wextra -O2
LDFLAGS := -L$(RAYLIB_DIR)/lib -lraylib -lm -lpthread -ldl
 
SRCS := $(wildcard $(SRC_DIR)/*.c)
 
.PHONY: all run clean
 
all: $(TARGET)
 
$(TARGET): $(SRCS) | $(BUILD)
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $@
 
$(BUILD):
	mkdir -p $(BUILD)
 
run: all
	./$(TARGET)
 
clean:
	rm -rf $(BUILD)
 