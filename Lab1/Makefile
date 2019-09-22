CURRENT_PATH:=$(shell pwd)
#list include,source and output directories
INC_DIR:= includes 
SRC_DIR:= src
OBJ_DIR:= obj
TARGET_DIR:=bin
TARGET:= $(TARGET_DIR)/mysort
#list files in each directory
SOURCES:=$(wildcard $(SRC_DIR)/*.cpp)
INCLUDES:= $(wildcard $(INC_DIR)/*.h)
OBJECTS:= $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC:= g++
CFLAGS:= -O0 -g -std=c++11 -Wall -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable #-fno-stack-protector 
LIBS:= -lm -pthread
LDFLAGS:=

.PHONY: all clean

#linking phase
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -I./$(INC_DIR) $(LDFLAGS) $^ -o $@ $(LIBS)

#creating obj files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET) $(TARGET_DIR)/*.out 
	# rm -rf $(CURRENT_PATH)/files/*txt
	rm -rf $(CURRENT_PATH)/bin/mysort