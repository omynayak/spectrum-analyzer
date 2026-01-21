import os
import numpy as np
import matplotlib.pyplot as plt

DATA_DIR = "./data"

# --- Files ---
window_files = [
    "rect_psd.csv",
    "hann_psd.csv",
    "hamming_psd.csv",
    "blackman_psd.csv",
]

kaiser_files = [f"kaiser{i}_psd.csv" for i in range(1, 9)]

plt.figure(figsize=(12, 8))

plt.subplot(2, 1, 1)

for fname in window_files:
    path = os.path.join(DATA_DIR, fname)
    data = np.loadtxt(path, delimiter=",")
    freq = data[:, 0]
    psd = data[:, 1]
    plt.plot(freq, psd, label=fname.replace("_psd.csv", ""))

plt.title("PSD Comparison: Rect / Hann / Hamming / Blackman")
plt.xlabel("Frequency")
plt.ylabel("PSD")
plt.ylim(-120, 120)
plt.xlim(0,2000)
plt.legend()
plt.grid(True)

plt.subplot(2, 1, 2)

for fname in kaiser_files:
    path = os.path.join(DATA_DIR, fname)
    data = np.loadtxt(path, delimiter=",")
    freq = data[:, 0]
    psd = data[:, 1]
    plt.plot(freq, psd, label=fname.replace("_psd.csv", ""))

plt.title("PSD Comparison: Kaiser Windows (β1 to β8)")
plt.xlabel("Frequency")
plt.ylabel("PSD")
plt.xlim(0,2000)
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
