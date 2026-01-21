#include "../headers/spectrum_analyzer.hpp"

namespace spect_an
{
    std::vector<double> unit_step(int k){
        std::vector<double>output (SIGNAL_SIZE, 1.0);
        if(k != 0){
            for(int i{}; i < k; i++) output[i] = 0;
        }
        return output;
    }

    std::vector<double> dirac_delta(int k){
        std::vector<double>output (SIGNAL_SIZE, 0.0);
        output[k] = 1;
        return output;
    }    

    std::vector<double> sine(int k, double freq_hz, const double fs){
        std::vector<double> output(SIGNAL_SIZE, 0.0);

        for(int i = k; i < SIGNAL_SIZE; i++){
            output[i] = std::sin(2 * M_PI * freq_hz * i / fs);
        }
        return output;
    }


    inline double mag(std::complex<double> a){
        return (double) std::sqrt((a.imag() * a.imag()) +(a.real() * a.real()));
    }

    std::vector<double> abs_magnitude(const std::vector<std::complex<double>>& input){
        std::vector<double> output (input.size());

        for(size_t i{}; i < input.size(); i++) output[i] = mag(input[i]);
        return output;
    }

} // namespace spect_an


