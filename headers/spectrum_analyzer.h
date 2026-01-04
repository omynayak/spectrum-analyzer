#ifndef SPECTRUM_ANALYZER_HPP
#define SPECTRUM_ANALYZER_HPP

#include <complex>
#include <vector>
#include <cmath>

#define SIGNAL_SIZE 1024
namespace spect_an{
    std::vector<std::complex<double>> fft(const std::vector<double>& input);
    std::vector<double> unit_step(int k = 0);
    std::vector<double> dirac_delta(int k = 0);
    std::vector<double> sine(int k = 0, double freq = 1, const double fs = 1024);
    std::vector<double> abs_magnitude(const std::vector<std::complex<double>>& input);
    std::vector<double> hamming_window(const std::vector<double>& input);
    std::vector<double> hann_window(const std::vector<double>& input);
}

#endif