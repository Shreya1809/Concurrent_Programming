CURRENT_PATH:=$(shell pwd)
#list include,source and output directories
INC_DIR:= -I./includes 
SRC_DIR:= src
OBJ_DIR:= obj
TARGET:= bin/mysort
#list files in each directory
SOURCES:=$(wildcard $(SRC_DIR)/*.c)
INCLUDES:= $(wildcard $(INC_DIR)/*.h)
OBJECTS:= $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC:= gcc
CFLAGS:= -fopenmp -O0 -g3 -Wall -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -std=c99 #-fno-stack-protector 
LIBS:= -lm -lgomp
LDFLAGS:= -fopenmp

.PHONY: all clean

#linking phase
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

#creating obj files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INC_DIR) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(CURRENT_PATH)/obj/*.o *.out
	#rm -rf $(CURRENT_PATH)/files/*txt
	rm -rf $(CURRENT_PATH)/bin/mysort