#ifndef SPECTRUM_ANALYZER_HPP
#define SPECTRUM_ANALYZER_HPP

#include <complex>
#include <vector>
#include <cmath>

#define SIGNAL_SIZE 1024
namespace spect_an{
    struct Peak {
        int bin;
        double frequency;
        double magnitude;
    };

    std::vector<std::complex<double>> fft(const std::vector<double>& input);
    std::vector<double> unit_step(int k = 0);
    std::vector<double> dirac_delta(int k = 0);
    std::vector<double> sine(int k = 0, double freq = 1, const double fs = 1024);
    std::vector<double> abs_magnitude(const std::vector<std::complex<double>>& input);
    std::vector<double> hamming_window(const std::vector<double>& input);
    std::vector<double> hann_window(const std::vector<double>& input);
    std::vector<double> kaiser_window(const std::vector<double>& input, const double beta = 8);

    std::vector<double> get_frequency_bins(int fft_size, double sample_rate);
    std::vector<std::vector<double>> compute_spectrogram(const std::vector<double>& signal, int window_size, int hop_size);
    std::vector<Peak> find_peaks(const std::vector<double>& spectrum, const std::vector<double>& freqs, double threshold_db = -40.0, int min_distance = 5);
    std::vector<double> to_db(const std::vector<double>& input, double reference = 1.0);
    std::vector<double> compute_psd(const std::vector<std::complex<double>>& fft_result, double sample_rate); 
}

#endif