CC = g++
COMPILE_FLAGS = -c -fPIC -std=c++11
# LD_FLAGS = -pthread -shared -Wall 
# use static link instead

SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
HDRS = $(wildcard $(SRC_DIR)/*.h)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
INCS = $(patsubst $(SRC_DIR)/%.h,$(BIN_DIR)/include/%.h,$(HDRS))
DEPS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.d,$(SRCS))

all: $(BIN_DIR)/libhttplib.a $(INCS)

$(BIN_DIR)/libhttplib.a: $(OBJS)
	@echo "linking $@"
	@mkdir -p bin
	@ar rcs $@ $^

$(BIN_DIR)/include/%.h: $(SRC_DIR)/%.h
	@echo "copying $@"
	@mkdir -p bin/include
	@cp $< $@

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

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
