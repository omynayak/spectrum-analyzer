import numpy as np
import matplotlib.pyplot as plt

sine_signal = np.loadtxt("./data/sine.txt")
time_index = sine_signal[:, 0]
amplitude = sine_signal[:, 1]

plt.figure(figsize=(10, 5))
plt.plot(time_index, amplitude)
plt.xlabel("Sample Index")
plt.ylabel("Amplitude")
plt.title("Time Domain: 440 Hz Sine Wave")
plt.grid()
plt.tight_layout()
plt.show()

spectrum = np.loadtxt("./data/demo.txt")
frequency = spectrum[:, 0]
magnitude_db = spectrum[:, 1]

plt.figure(figsize=(10, 5))
plt.plot(frequency, magnitude_db)
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude (dB)")
plt.title("Frequency Spectrum of 440 Hz Sine Wave")
plt.grid()
plt.xlim(0, 2000)  
plt.tight_layout()
plt.show()