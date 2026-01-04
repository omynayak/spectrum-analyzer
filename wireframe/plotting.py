import numpy as np
import matplotlib.pyplot as plt

orig = np.loadtxt("./data/original.txt")
sine = np.loadtxt("./data/demo.txt")

orig_sigval = orig[:, 1]
index = orig[:, 0]

plt.plot(index, orig_sigval)
plt.xlabel("Index")
plt.ylabel("Amplitude")
plt.title("Sine of 7, 15, 17, 19, 20, 23, 30 Hz added")
plt.grid()
plt.show()


fft_sigval = sine[:, 1]
index = sine[:, 0]

plt.plot(index, fft_sigval)
plt.xlabel("Index")
plt.ylabel("Amplitude")
plt.title("Spectrum of sine wave with f = 7, 15, 17, 19, 23, 30 Hz and fs = 1024Hz")
plt.grid()
plt.show()