
BIN := main
OBJ := main.o func.o
SRC := main.cpp func.hpp

.PHONY: all

all: $(BIN)

$(BIN): $(OBJ)
	g++ $^ -o $@

%.o: %.cpp
	g++ $< -c -o $@
	