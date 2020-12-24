CC = g++
CC_FLAGS = -Wall -L../bin -Wl,-rpath=../bin

SRCS = $(wildcard ./*.cpp)
BINS = $(patsubst %.cpp,%.o,$(SRCS))

all: clean $(BINS)

%.o: %.cpp
	@echo "generate $@"
	@$(CC) $(CC_FLAGS) $< -o $@ -lhttplib

clean:
	@echo "clean object files"
	@rm -f *.o
	
