import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile
import librosa
import librosa.display

# Load the audio file
filename = 'no.wav'
sample_rate, data = wavfile.read(filename)

# Ensure it's a 1-second audio file
assert len(data) == sample_rate, "Audio file is not 1 second long."

# Plotting the results
plt.figure(figsize=(12, 6))

# Plot the normal spectrogram
plt.subplot(1, 2, 1)
plt.specgram(data, Fs=sample_rate, NFFT=1024, noverlap=512, cmap='viridis')
plt.title('Normal Spectrogram')
plt.xlabel('Time [s]')
plt.ylabel('Frequency [Hz]')

# Compute the Mel-scaled spectrogram
S = librosa.feature.melspectrogram(y=data.astype(float), sr=sample_rate, n_fft=1024, hop_length=512, n_mels=128)
S_dB = librosa.power_to_db(S, ref=np.max)

# Plot the Mel-scaled spectrogram
plt.subplot(1, 2, 2)
librosa.display.specshow(S_dB, sr=sample_rate, hop_length=512, x_axis='time', y_axis='mel', cmap='viridis')
plt.title('Mel-scaled Spectrogram')
plt.xlabel('Time [s]')
plt.ylabel('Mel Frequency')

plt.tight_layout()
plt.show()
