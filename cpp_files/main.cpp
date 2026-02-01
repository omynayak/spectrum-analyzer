#include "../headers/spectrum_analyzer.hpp"
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

void process_and_save(const std::vector<double>& signal, std::string base_filename, double fs){
    auto fft_result = spect_an::fft(signal);
    int fft_size = fft_result.size(); 
    auto magnitude = spect_an::abs_magnitude(fft_result);
    magnitude.resize(magnitude.size() / 2 + 1);
    
    auto freqs = spect_an::get_frequency_bins(fft_size, fs);
    freqs.resize(freqs.size() / 2 + 1);
    
    auto db_spectrum = spect_an::to_db(magnitude);
    
    writeFile(freqs, db_spectrum, base_filename + "_psd.csv");
    writeFile(freqs, db_spectrum, base_filename + ".csv"); 
}

int main(void){
    nd_rng rng(0, 0.8333);
    double fs = 44100.0;
    auto signal = spect_an::sine(0, 440.0, fs);  
    auto signal1 = spect_an::sine(0, 220.0, fs);
    auto signal2 = spect_an::sine(0, 1590.0, fs);
    
    std::vector<double> signal_nd = signal;
    std::vector<double> signal_xor = signal;

    Xorshift32 xor_rng;
    for(size_t i = 0; i < signal.size(); i++) {
        double clean_signal = signal[i] + signal1[i] + signal2[i];
        signal_nd[i] = clean_signal + rng.next();
        signal_xor[i] = clean_signal + xor_rng.next_double();
    }

    writeFile(signal_nd, "sine.csv");
    writeFile(signal_xor, "sine_xor.csv");

    for(int i{1}; i < 9; i++){
        process_and_save(spect_an::kaiser_window(signal_nd, i), "kaiser" + std::to_string(i), fs);
    }

    process_and_save(spect_an::hamming_window(signal_nd), "hamming", fs);
    process_and_save(spect_an::hann_window(signal_nd), "hann", fs);
    process_and_save(signal_nd, "rect", fs); 
    process_and_save(spect_an::blackman_window(signal_nd), "blackman", fs);


    for(int i{1}; i < 9; i++){
        process_and_save(spect_an::kaiser_window(signal_xor, i), "kaiser" + std::to_string(i) + "_xor", fs);
    }

    process_and_save(spect_an::hamming_window(signal_xor), "hamming_xor", fs);
    process_and_save(spect_an::hann_window(signal_xor), "hann_xor", fs);
    process_and_save(signal_xor, "rect_xor", fs); 
    process_and_save(spect_an::blackman_window(signal_xor), "blackman_xor", fs);


    return 0;
}
