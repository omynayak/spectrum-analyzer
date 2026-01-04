#include "../headers/spectrum_analyzer.h"

namespace spect_an
{
    std::vector<double> hamming_window(const std::vector<double>& input){
        if(input.size() < 2) return input;
        const double two_pi_N = 2.0 * M_PI / (input.size() - 1); 
        std::vector<double> output(input);
        for(size_t i{}; i < output.size(); i++) output[i] *= (0.54 - 0.46 * std::cos(two_pi_N * i));
        return output;
    }

    std::vector<double> hann_window(const std::vector<double>& input){
        if(input.size() < 2) return input;
        const double two_pi_N = 2.0 * M_PI / (input.size() - 1);
        std::vector<double> output(input);
        for(size_t i{}; i < output.size(); i++) output[i] *= (0.5 - 0.5 * std::cos(two_pi_N * i));
        return output;
    }

    std::vector<double> kaiser_window(const std::vector<double>& input, const double beta){
        if(input.size() < 2) return input;
        
        const size_t N = input.size();
        std::vector<double> output(input);

        double denominator = std::cyl_bessel_i(0, beta);

        for (size_t n = 0; n < N; ++n) {
            double r = 2.0 * n / (N - 1) - 1.0;
            double w = std::cyl_bessel_i(0, beta * std::sqrt(1 - r * r)) / denominator;
            output[n] *= w;
        }
        return output;
    }

    std::vector<double> blackman_window(const std::vector<double>& input){
        if(input.size() < 2) return input;
        const double two_pi_N = 2.0 * M_PI / (input.size() - 1);
        std::vector<double> output(input);
        for(size_t i{}; i < output.size(); i++) output[i] *= (0.42 - 0.5 * std::cos(two_pi_N * i) + 0.08 * std::cos(2 * two_pi_N * i));
        return output;
    }
} // namespace spect_an