#include "../headers/spectrum_analyzer.h"
#include <iostream>
#include <fstream>

void writeFile(const std::vector<double>& data, std::string filename){
    filename = "./data/" + filename;
    std::ofstream file(filename);
    for(size_t i{}; i < data.size(); i++) {
        file << i << "," << data[i] << "\n"; 
    }
    file.close();
}

void writeFile(const std::vector<double>& col1, const std::vector<double>& col2, std::string filename){
    filename = "./data/" + filename;
    std::ofstream file(filename);
    for(size_t i{}; i < col1.size(); i++) {
        file << col1[i] << "," << col2[i] << "\n"; 
    }
    file.close();
}

int main(void){
    double fs = 44100.0;
    auto signal = spect_an::sine(0, 440.0, fs);  

    writeFile(signal, "sine.csv");

    signal = spect_an::kaiser_window(signal, 8);

    auto fft_result = spect_an::fft(signal);
    int fft_size = fft_result.size(); 

    auto magnitude = spect_an::abs_magnitude(fft_result);
    magnitude.resize(magnitude.size() / 2 + 1);

    auto freqs = spect_an::get_frequency_bins(fft_size, fs);
    freqs.resize(freqs.size() / 2 + 1);

    auto db_spectrum = spect_an::to_db(magnitude);

    writeFile(freqs, db_spectrum, "demo.csv"); 

    auto peaks = spect_an::find_peaks(db_spectrum, freqs);
    
    system("python3 ./plotting/plotting.py");
    return 0;
}