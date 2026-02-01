import numpy as np
import matplotlib.pyplot as plt

sine_signal = np.loadtxt("./data/sine_xor.csv", delimiter=",")
time_index = sine_signal[:, 0]
amplitude = sine_signal[:, 1]

fig, (ax_time, ax_kaiser, ax_hamming) = plt.subplots(3, 1, figsize=(10, 8))

ax_time.plot(time_index, amplitude)
ax_time.set_xlabel("Sample Index")
ax_time.set_ylabel("Amplitude")
ax_time.set_title("Time Domain: Sine Waves (220, 440, 1590 Hz) + Uniform Noise (Xorshift32)")
ax_time.grid(True)

for i in range(1, 9):
    filename = f"./data/kaiser{i}_xor.csv"
    spectrum = np.loadtxt(filename, delimiter=",")
    
    frequency = spectrum[:, 0]
    magnitude_db = spectrum[:, 1]
    
    ax_kaiser.plot(frequency, magnitude_db, label=f"Kaiser {i}")
ax_kaiser.set_xlabel("Frequency (Hz)")
ax_kaiser.set_ylabel("Magnitude (dB)")
ax_kaiser.set_title("Frequency Spectrum (220, 440, 1590 Hz) with Kaiser Windows (Uniform Noise)")
ax_kaiser.set_xlim(0, 2000)
ax_kaiser.grid(True)
ax_kaiser.legend(loc="upper right")

filename = "./data/hamming_xor.csv"
spectrum = np.loadtxt(filename, delimiter=",")
frequency = spectrum[:, 0]
magnitude_db = spectrum[:, 1]
ax_hamming.plot(frequency, magnitude_db, label="Hamming Window")

filename = "./data/hann_xor.csv"
spectrum = np.loadtxt(filename, delimiter=",")
frequency = spectrum[:, 0]
magnitude_db = spectrum[:, 1]
ax_hamming.plot(frequency, magnitude_db, label="Hann Window")

filename = "./data/rect_xor.csv"
spectrum = np.loadtxt(filename, delimiter=",")
frequency = spectrum[:, 0]
magnitude_db = spectrum[:, 1]
ax_hamming.plot(frequency, magnitude_db, label="Rectangular Window")

filename = "./data/blackman_xor.csv"
spectrum = np.loadtxt(filename, delimiter=",")
frequency = spectrum[:, 0]
magnitude_db = spectrum[:, 1]
ax_hamming.plot(frequency, magnitude_db, label="Blackman Window")

ax_hamming.set_xlabel("Frequency (Hz)")
ax_hamming.set_ylabel("Magnitude (dB)")
ax_hamming.set_title("Frequency Spectrum (220, 440, 1590 Hz) with Hamming, Hann, Blackman Windows (Uniform Noise)")
ax_hamming.set_xlim(0, 2000)
ax_hamming.grid(True)
ax_hamming.legend(loc="upper right")


plt.tight_layout()
plt.show()
