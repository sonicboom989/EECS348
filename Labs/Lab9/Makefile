CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra -g
SRC = Lab9.cpp
OBJ = $(SRC:.cpp=.o)
EXE = Lab9.exe

.PHONY: all clean run

all: $(EXE)

$(EXE): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
    $(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
    .\$(EXE) < input.txt

clean:
    rm -f $(OBJ) $(EXE)