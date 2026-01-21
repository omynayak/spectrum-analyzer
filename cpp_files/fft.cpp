#include "../headers/spectrum_analyzer.hpp"

namespace spect_an{

    int bit_reverse(int x, int log2n) {
        int result = 0;
        for(int i = 0; i < log2n; i++) {
            result = (result << 1) | (x & 1);
            x >>= 1;
        }
        return result;
    }

    std::vector<std::complex<double>> fft_helper(std::vector<double>& input){
        int N = input.size();
        std::vector<std::complex<double>> X(N);
        for(size_t i = 0; i < input.size(); i++){
            X[i] = input[i];
        }
        
        for(int i = 0; i < N; i++){
            int j = bit_reverse(i, std::log2(N));
            if(j > i) std::swap(X[i], X[j]);
        }
        
        for(int s = 1; s <= std::log2(N); s++){
            int m = 1 << s;
            std::complex<double> wm = std::polar(1.0, -2.0 * M_PI / m);
            
            for(int k = 0; k < N; k += m){
                std::complex<double> w = 1.0;
                for(int j = 0; j < m/2; j++){
                    std::complex<double> t = w * X[k + j + m/2];
                    std::complex<double> u = X[k + j];
                    X[k + j] = u + t;
                    X[k + j + m/2] = u - t;
                    w *= wm;
                }
            }
        }
        
        return X;
    }

    std::vector<std::complex<double>> fft(const std::vector<double>& input){
        int n = input.size();
        int result = 1;
        while(result < n) result = result << 1;

        std::vector<double> data(result, 0.0);
        for(size_t i = 0; i < input.size(); i++) data[i] = input[i];

        return fft_helper(data);
    }
}
