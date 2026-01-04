#include "../headers/spectrum_analyzer.h"

namespace spect_an
{
    std::vector<double> hamming_window(const std::vector<double>& input){
        const double two_pi_N = 2.0 * M_PI / (input.size() - 1); 
        std::vector<double> output(input);
        for(size_t i{}; i < output.size(); i++) output[i] *= (0.54 - 0.46 * std::cos(two_pi_N * i));
        return output;
    }

    std::vector<double> hann_window(const std::vector<double>& input){
        const double two_pi_N = 2.0 * M_PI / (input.size() - 1);
        std::vector<double> output(input);
        for(size_t i{}; i < output.size(); i++) output[i] *= (0.5 - 0.5 * std::cos(two_pi_N * i));
        return output;
    }
} // namespace spect_an