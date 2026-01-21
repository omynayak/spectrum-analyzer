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

int main(void){
    double fs = 44100.0;
    auto signal = spect_an::sine(0, 440.0, fs);  

    writeFile(signal, "sine.csv");

    for(int i{1}; i < 9; i++){
        auto fft_result = spect_an::fft(spect_an::kaiser_window(signal, i));
        int fft_size = fft_result.size(); 
        auto magnitude = spect_an::abs_magnitude(fft_result);
        magnitude.resize(magnitude.size() / 2 + 1);
        auto freqs = spect_an::get_frequency_bins(fft_size, fs);
        freqs.resize(freqs.size() / 2 + 1);
        auto db_spectrum = spect_an::to_db(magnitude);
        std::string filename = "kaiser" + std::to_string(i) + ".csv";
        std::string filename1 = "kaiser" + std::to_string(i) + "_psd.csv";
        std::vector<double> psd = spect_an::compute_psd(fft_result, fs);
        writeFile(freqs, db_spectrum, filename1);
        writeFile(freqs, db_spectrum, filename); 
    }
    auto fft_result = spect_an::fft(spect_an::hamming_window(signal));
    int fft_size = fft_result.size(); 
    auto magnitude = spect_an::abs_magnitude(fft_result);
    magnitude.resize(magnitude.size() / 2 + 1);
    auto freqs = spect_an::get_frequency_bins(fft_size, fs);
    freqs.resize(freqs.size() / 2 + 1);
    auto db_spectrum = spect_an::to_db(magnitude);
    std::vector<double> psd = spect_an::compute_psd(fft_result, fs);
    writeFile(freqs, db_spectrum, "hamming_psd.csv");
    writeFile(freqs, db_spectrum, "hamming.csv"); 
    

    fft_result = spect_an::fft(spect_an::hann_window(signal));
    fft_size = fft_result.size(); 
    magnitude = spect_an::abs_magnitude(fft_result);
    magnitude.resize(magnitude.size() / 2 + 1);
    freqs = spect_an::get_frequency_bins(fft_size, fs);
    freqs.resize(freqs.size() / 2 + 1);
    db_spectrum = spect_an::to_db(magnitude);
    psd = spect_an::compute_psd(fft_result, fs);
    writeFile(freqs, db_spectrum, "hann_psd.csv");
    writeFile(freqs, db_spectrum, "hann.csv"); 



    fft_result = spect_an::fft(signal);
    fft_size = fft_result.size(); 
    magnitude = spect_an::abs_magnitude(fft_result);
    magnitude.resize(magnitude.size() / 2 + 1);
    freqs = spect_an::get_frequency_bins(fft_size, fs);
    freqs.resize(freqs.size() / 2 + 1);
    psd = spect_an::compute_psd(fft_result, fs);
    writeFile(freqs, db_spectrum, "rect_psd.csv");
    db_spectrum = spect_an::to_db(magnitude);
    writeFile(freqs, db_spectrum, "rect.csv"); 


    fft_result = spect_an::fft(spect_an::blackman_window(signal));
    fft_size = fft_result.size(); 
    magnitude = spect_an::abs_magnitude(fft_result);
    magnitude.resize(magnitude.size() / 2 + 1);
    freqs = spect_an::get_frequency_bins(fft_size, fs);
    freqs.resize(freqs.size() / 2 + 1);
    db_spectrum = spect_an::to_db(magnitude);
    psd = spect_an::compute_psd(fft_result, fs);
    writeFile(freqs, db_spectrum, "blackman_psd.csv");
    writeFile(freqs, db_spectrum, "blackman.csv"); 


    system("python3 ./plotting/plot_spectrum.py");
    system("python3 ./plotting/plot_psd.py");
    return 0;
}
