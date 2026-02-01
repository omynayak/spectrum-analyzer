CXX = clang++
CXXFLAGS = -Wall -Wextra -O2

TARGET = main
SRC = ./cpp_files/main.cpp ./cpp_files/signals.cpp ./cpp_files/fft.cpp ./cpp_files/window.cpp ./cpp_files/spectrum_analyzer.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)


run: $(TARGET)
	./$(TARGET)
	python3 ./plotting/plot_gaussian.py
	python3 ./plotting/plot_psd_gaussian.py
	python3 ./plotting/plot_uniform.py
	python3 ./plotting/plot_psd_uniform.py

clean:
	rm -f $(TARGET)
