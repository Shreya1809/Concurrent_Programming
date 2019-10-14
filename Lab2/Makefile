CURRENT_PATH:=$(shell pwd)
#list include,source and output directories
INC_DIR:= includes 
COMMON_SRC_DIR:=src/common
SRC_DIR1:= src/bucksortsrc
SRC_DIR2:= src/microbenchmark
OBJ_DIR1:= obj/sortobj
OBJ_DIR2:= obj/microobj
COMMON_OBJ:= obj/common
TARGET_DIR:=bin
TARGET1:= $(TARGET_DIR)/mysort
TARGET2:= $(TARGET_DIR)/benchmark
#list files in each directory
SOURCES1:=$(wildcard $(SRC_DIR1)/*.cpp)
SOURCES2:=$(wildcard $(SRC_DIR2)/*.cpp)
COMMON_SOURCES:=$(wildcard $(COMMON_SRC_DIR)/*.cpp)
INCLUDES:= $(wildcard $(INC_DIR)/*.h)
OBJECTS1:= $(SOURCES1:$(SRC_DIR1)/%.cpp=$(OBJ_DIR1)/%.o)
OBJECTS2:= $(SOURCES2:$(SRC_DIR2)/%.cpp=$(OBJ_DIR2)/%.o)
COMMON_OBJECTS:= $(COMMON_SOURCES:$(COMMON_SRC_DIR)/%.cpp=$(COMMON_OBJ)/%.o)

CC:= g++
CFLAGS:= -O0 -g -std=c++17 -faligned-new -Wall -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable 
LIBS:= -lm -pthread
LDFLAGS:=

.PHONY: all clean

all: $(TARGET1) $(TARGET2)

test: 
	$(CC) $(CFLAGS) -I./$(INC_DIR) -DDEBUG src/common/locks.cpp -o $@

#linking phase
$(TARGET1): $(OBJECTS1) $(COMMON_OBJECTS)
	$(CC) $(CFLAGS) -I./$(INC_DIR) $(LDFLAGS) $^ -o $@ $(LIBS)

$(TARGET2): $(OBJECTS2) $(COMMON_OBJECTS)
	$(CC) $(CFLAGS) -I./$(INC_DIR) $(LDFLAGS) $^ -o $@ $(LIBS)

#creating obj files from source files
$(OBJ_DIR1)/%.o: $(SRC_DIR1)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR2)/%.o: $(SRC_DIR2)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(COMMON_OBJ)
	rm -rf $(OBJ_DIR1) $(TARGET1) $(TARGET_DIR) 
	rm -rf $(OBJ_DIR2) $(TARGET2) $(TARGET_DIR)
	rm -rf test
	# rm -rf $(CURRENT_PATH)/files/*txt