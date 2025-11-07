CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -Wpedantic -O2
LDFLAGS   :=

TARGET    := Lab9
SRC       := Lab9.cpp


all: $(TARGET)


$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all run debug clean format
