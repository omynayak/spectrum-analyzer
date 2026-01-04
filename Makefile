CXX = clang++
CXXFLAGS = -Wall -Wextra -O2

TARGET = main
SRC = ./cpp_files/main.cpp ./cpp_files/fft.cpp ./cpp_files/signals.cpp ./cpp_files/window.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
