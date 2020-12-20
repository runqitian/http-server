CC = g++
COMPILE_FLAGS = -c -std=c++11
LD_FLAGS = -pthread

SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.d,$(SRCS))

all: $(BIN_DIR)/out

$(BIN_DIR)/out: $(OBJS)
	@echo "linking"
	@mkdir -p bin
	@$(CC) $(LD_FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR)/%.d
	@echo "compiling $@"
	@$(CC) $(COMPILE_FLAGS) -o $@ $<

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	@echo "building dependency $@"
	@mkdir -p build
	@set -e; rm -f $@; \
	$(CC) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPS)
