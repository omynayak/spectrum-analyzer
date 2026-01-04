#include "../headers/spectrum_analyzer.h"
#include <iostream>
#include <fstream>

void writeFile(const std::vector<double>& input, std::string filename){
    filename = "./data/" + filename;
    std::ofstream file(filename);
    for(size_t i{}; i < input.size(); i++) file << i << " " << input[i] << "\n"; 
    file.close();
}


int main(void){
    std::vector<double> sine1 = spect_an::sine(0, 15);
    std::vector<double> sine2 = spect_an::sine(0, 19);
    std::vector<double> sine3 = spect_an::sine(0, 30);
    std::vector<double> sine4 = spect_an::sine(0, 23);
    std::vector<double> sine5 = spect_an::sine(0, 17);
    std::vector<double> sine6 = spect_an::sine(0, 7);
    std::vector<double> sine(1024);
    for(size_t i{}; i < sine.size(); i++) sine[i] = sine1[i] + sine2[i] + sine3[i] + sine4[i] + sine5[i] + sine6[i];
    sine = spect_an::hann_window(sine);
    std::vector<double> output = spect_an::abs_magnitude(spect_an::fft(sine));

    writeFile(sine, "original.txt");
    writeFile(output, "demo.txt");
    system("python3 ./wireframe/plotting.py");
    return 0;
}