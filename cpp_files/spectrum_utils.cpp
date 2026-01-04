#include "../headers/spectrum_analyzer.h"

namespace spect_an{
    std::vector<std::vector<double>> compute_spectrogram(const std::vector<double>& signal, int window_size,
        int hop_size) {
        
        int num_frames = (signal.size() - window_size) / hop_size + 1;
        std::vector<std::vector<double>> spectrogram;
        
        for(int i = 0; i < num_frames; i++) {
            int start = i * hop_size;
            std::vector<double> frame(signal.begin() + start,
                                    signal.begin() + start + window_size);
            
            frame = hamming_window(frame);
            auto fft_result = fft(frame);
            auto magnitude = abs_magnitude(fft_result);
            
            magnitude.resize(window_size / 2 + 1);
            spectrogram.push_back(magnitude);
        }
        
        return spectrogram;
    }

    std::vector<Peak> find_peaks(const std::vector<double>& spectrum,
                                const std::vector<double>& freqs,
                                double threshold_db,
                                int min_distance) {
        std::vector<Peak> peaks;
    
    for(size_t i = min_distance; i < spectrum.size() - min_distance; i++) {
        if(spectrum[i] < threshold_db) continue;
        
        bool is_peak = true;
        for(int j = -min_distance; j <= min_distance; j++) {
            if(j != 0 && spectrum[i] <= spectrum[i + j]) {
                is_peak = false;
                break;
            }
        }
        
        if(is_peak) {
            peaks.push_back({static_cast<int>(i), freqs[i], spectrum[i]});
        }
    }
    
    return peaks;
}


    std::vector<double> to_db(const std::vector<double>& input, double reference) {
        std::vector<double> output(input.size());
        for(size_t i = 0; i < input.size(); i++) {
            output[i] = 20.0 * std::log10(input[i] / reference + 1e-12);
        }
        return output;
    }

    std::vector<double> compute_psd(const std::vector<std::complex<double>>& fft_result, 
                                    double sample_rate) {
        int N = fft_result.size();
        std::vector<double> psd(N / 2 + 1);
        
        for(int i = 0; i <= N / 2; i++) {
            double mag = std::abs(fft_result[i]);
            psd[i] = (mag * mag) / (N * sample_rate);
            
            if(i > 0 && i < N / 2) {
                psd[i] *= 2.0;
            }
        }
        return psd;
    }

    std::vector<double> get_frequency_bins(int fft_size, double sample_rate) {
        std::vector<double> freqs(fft_size / 2 + 1);
        for(int i = 0; i <= fft_size / 2; i++) {
            freqs[i] = i * sample_rate / fft_size;
        }
        return freqs;
    }

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