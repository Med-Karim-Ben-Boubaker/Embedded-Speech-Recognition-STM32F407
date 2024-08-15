import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
import librosa
import librosa.display

def get_spectrogram(waveform):
    # Convert the waveform to a spectrogram via STFT
    spectrogram = tf.signal.stft(
        waveform, frame_length=512, frame_step=128, fft_length=512)
    # Compute the power of the STFT (magnitude squared)
    spectrogram_power = tf.abs(spectrogram) ** 2
    return spectrogram_power

def normalize_log_mel_spectrogram(log_mel_spectrogram):
    # Normalizing from range [-16, -3] to [-70, -10]
    min_input = -11.0
    max_input = -3.0
    min_output = -60.0
    max_output = -20.0

    # Performing normalization
    normalized = ((log_mel_spectrogram - min_input) / (max_input - min_input)) * (max_output - min_output) + min_output
    return normalized

def get_log_mel_spectrogram(waveform, sample_rate=16000, num_mels=40):
    # Get the spectrogram using the provided function
    spectrogram_power = get_spectrogram(waveform)
    
    # Create the Mel filter banks using the built-in function
    linear_to_mel_weight_matrix = tf.signal.linear_to_mel_weight_matrix(
        num_mel_bins=num_mels,  
        num_spectrogram_bins=spectrogram_power.shape[-1], 
        sample_rate=sample_rate,
        lower_edge_hertz=300, 
        upper_edge_hertz=sample_rate / 2 
    )
    
    # Apply the Mel filter banks to the spectrogram
    mel_spectrogram = tf.tensordot(spectrogram_power,
                                   linear_to_mel_weight_matrix,
                                   axes=[-1, 0])

    # Convert to log scale
    log_mel_spectrogram = tf.math.log(mel_spectrogram + 1e-6)
    
    # Normalize the log mel spectrogram
    normalized_log_mel_spectrogram = normalize_log_mel_spectrogram(log_mel_spectrogram)
    
    # Add a `channels` dimension for compatibility with convolution layers
    normalized_log_mel_spectrogram = normalized_log_mel_spectrogram[..., tf.newaxis]
    
    return normalized_log_mel_spectrogram

# Function to generate and resize mel-spectrogram
def generate_mel_spectrogram(audio_path, target_height=122, target_width=40):
    y, sr = librosa.load(audio_path, sr=16000)
    
    # Convert waveform to TensorFlow tensor
    waveform = tf.convert_to_tensor(y, dtype=tf.float32)
    
    # Get the log mel spectrogram
    mel_spectrogram = get_log_mel_spectrogram(waveform, sample_rate=sr)
    
    # Convert tensor to numpy array
    mel_spectrogram_np = mel_spectrogram.numpy().squeeze()  # Remove singleton dimensions
    
    # Resize to target height and width if necessary
    mel_spectrogram_resized = np.resize(mel_spectrogram_np, (target_height, target_width))
    
    return mel_spectrogram_resized

# Function to plot mel-spectrogram
def plot_mel_spectrogram(mel_spectrogram, title='Mel-Spectrogram'):
    plt.figure(figsize=(10, 4))
    plt.pcolormesh(np.arange(mel_spectrogram.shape[1]), np.arange(mel_spectrogram.shape[0]), mel_spectrogram, shading='gouraud', cmap='viridis')
    plt.colorbar(format='%+2.0f dB')
    plt.title(title)
    plt.tight_layout()
    plt.show()

import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf

def visualize_cnn_layers(model, mel_spectrogram):
    # Create a model that outputs the activations of each layer
    input_layer = model.inputs[0]  # Get the actual input layer
    layer_outputs = [layer.output for layer in model.layers]

    # Use the functional API to create the activation model
    activation_model = tf.keras.Model(inputs=input_layer, outputs=layer_outputs)

    # Reshape and normalize the input for the CNN
    mel_spectrogram_resized = np.resize(mel_spectrogram, (1, 122, 40, 1))  # Resize to (1, 122, 40, 1)

    # Get activations
    activations = activation_model.predict(mel_spectrogram_resized)

    # Plotting the activations
    for i, activation in enumerate(activations):
        if len(activation.shape) == 4:  # If it's a convolutional layer
            for j in range(min(activation.shape[3], 8)):  # Show first 8 filters
                plt.figure(figsize=(10, 10))
                plt.imshow(activation[0, :, :, j], aspect='auto', cmap='viridis')
                plt.title(f'Layer {i} Filter {j}')
                plt.axis('off')
                plt.show()
        elif len(activation.shape) == 2:  # If it's a flatten or dense layer
            plt.figure(figsize=(10, 5))
            plt.imshow(activation, aspect='auto', cmap='viridis')
            plt.title(f'Layer {i} Activation')
            plt.axis('off')
            plt.show()
        else:
            raise ValueError(f"Unexpected activation shape: {activation.shape}")



# Load the original Keras model
model_path = 'model.h5'  # Replace with your Keras model path
model = tf.keras.models.load_model(model_path)

# Print the model summary
model.summary()  # Check the model structure and input shape

# Example audio file path
audio_path = 'no.wav'  # Replace with your audio file path

# Generate and plot mel-spectrogram
mel_spectrogram_resized = generate_mel_spectrogram(audio_path)
plot_mel_spectrogram(mel_spectrogram_resized.T)

# Visualize CNN layer outputs
visualize_cnn_layers(model, mel_spectrogram_resized)
