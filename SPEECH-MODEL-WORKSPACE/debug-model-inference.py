import serial
import struct
import numpy as np
import matplotlib.pyplot as plt
from enum import Enum
import tensorflow as tf  # Add this import for TensorFlow

# Initialize serial communication
ser = serial.Serial('COM10', 9500, timeout=2)

# Define constants
FFT_LEN = 512
FRAME_NUM = 122
AUDIO_PCM_BUFFER_SIZE = 16000
SPECTROGRAM_SAMPLE_SIZE = 40
BEGIN_FLAG = 0.0

# Define States
class PC_States_t(Enum):
    PC_IDLE = 0
    PC_READY = 1

# Load the TFLite model
interpreter = tf.lite.Interpreter(model_path="models/model_no_quant.tflite")
interpreter.allocate_tensors()

# Get input and output tensors
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

def read_usb_data_f32():
    usb_bytes = ser.read(4)  # Read 4 bytes from the serial port
    if len(usb_bytes) == 4:
        usb_value = struct.unpack('f', usb_bytes)[0]  # Unpack the float value
        return usb_value 

def read_usb_data_int8():
    usb_bytes = ser.read(1)  # Read 1 byte from the serial port
    if len(usb_bytes) == 1:
        usb_value = struct.unpack('B', usb_bytes)[0]  # Unpack the float value
        return usb_value
    else:
        return None
    
def write_usb_data_int8(value):
    # Pack the value as a single byte
    data = struct.pack('B', value)
    
    # Write the data to the serial port
    ser.write(data)
    
    # Flush the output buffer to ensure immediate transmission
    ser.flush()

def construct_spectrogram():
    spectrogram_matrix = np.zeros((SPECTROGRAM_SAMPLE_SIZE, FRAME_NUM), dtype=np.float32)
    spectrogram_updated = 0
    
    for col in range(FRAME_NUM):
        for row in range(SPECTROGRAM_SAMPLE_SIZE):
            
            value = read_usb_data_f32()
            
            if value is not None or value != 0.0:
                spectrogram_updated = 1
                spectrogram_matrix[row, col] = value
            
            else:
                spectrogram_updated = 0
                break
            
        if not (value is not None or value != 0.0):
            break
            
    if spectrogram_updated == 1:
        return spectrogram_matrix
    
    else:
        return None

def plot_spectrogram(spectrogram_matrix, ax):
    ax.clear()  # Clear the previous plot
    ax.imshow(spectrogram_matrix, aspect='auto', origin='lower', cmap='viridis')
    ax.set_xlabel('Time (columns)')
    ax.set_ylabel('Frequency (rows)')
    ax.set_title('Spectrogram')
    plt.draw()
    plt.pause(0.5)  # Pause to update the plot

def new_data_received(max_attempts=10):
    zero_count = 0
    value = None
    
    for _ in range(max_attempts):
        value = read_usb_data_f32()
        
        if value is None:
            print("No data received. Retrying...")
            continue  # Skip the rest of the loop if no data is received
        
        if value == 0.0:
            zero_count += 1
        else:
            break  # Exit the loop if we receive a non-zero value
    
    # Return True if we received 10 consecutive zeros, otherwise False
    return zero_count == max_attempts

def run_inference(spectrogram):
    # Crop to 122 frames if necessary
    if spectrogram.shape[1] != 122:
        print(f"Spectrogram shape mismatch. Expected width of 122, got {spectrogram.shape[1]}")
        spectrogram = spectrogram[:, :122]
    
    # Preprocess the input (add batch dimension and channel dimension)
    input_data = np.expand_dims(spectrogram, axis=0).astype(np.float32)  # Add batch dimension
    input_data = np.expand_dims(input_data, axis=-1)  # Add channel dimension

    # Rearrange dimensions to match model input shape [1, 122, 40, 1]
    input_data = np.transpose(input_data, (0, 2, 1, 3))
    
    # Check if the input shape matches the model's expected input shape
    if input_data.shape != tuple(input_details[0]['shape']):
        print(f"Input shape mismatch. Expected {input_details[0]['shape']}, got {input_data.shape}")
        return None

    # Set the input tensor
    interpreter.set_tensor(input_details[0]['index'], input_data)

    # Run inference
    interpreter.invoke()

    # Get the output tensor
    output_data = interpreter.get_tensor(output_details[0]['index'])

    return output_data



def main():
    # Set print options to print the entire matrix
    np.set_printoptions(threshold=np.inf, linewidth=np.inf)
    plt.ion()  # Turn on interactive mode
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))
    
    # Define States
    pc_state = PC_States_t.PC_IDLE.value
    
    while True:
        if (new_data_received()):
            # Construct logMelSpectrogram
            spectrogram_matrix = construct_spectrogram()
            
            if spectrogram_matrix is not None:
                plot_spectrogram(spectrogram_matrix, ax1)
                
                # Run inference
                inference_result = run_inference(spectrogram_matrix)
                
                if inference_result is not None:
                    # Plot or process the inference result
                    ax2.clear()
                    probabilities = inference_result[0]
                    classes = range(len(probabilities))
                    
                    # Plot probabilities as a bar chart
                    bars = ax2.bar(classes, probabilities)
                    ax2.set_title('Inference Result')
                    ax2.set_xlabel('Class')
                    ax2.set_ylabel('Probability')

                    # Annotate bars with probability values
                    for bar, probability in zip(bars, probabilities):
                        ax2.text(
                            bar.get_x() + bar.get_width() / 2,  # X position (center of bar)
                            bar.get_height(),                  # Y position (top of bar)
                            f"{probability:.2f}",              # Probability text
                            ha='center',                       # Horizontal alignment
                            va='bottom'                        # Vertical alignment
                        )

                    plt.draw()
                    plt.pause(0.1)

                    # Print all class probabilities
                    for cls, prob in enumerate(probabilities):
                        print(f"Class {cls}: Probability {prob:.4f}")

                    # Print the top prediction
                    top_prediction = np.argmax(probabilities)
                    print(f"Top prediction: Class {top_prediction} with probability {probabilities[top_prediction]:.4f}")
                else:
                    print("Inference failed.")


if __name__ == "__main__":
    main()