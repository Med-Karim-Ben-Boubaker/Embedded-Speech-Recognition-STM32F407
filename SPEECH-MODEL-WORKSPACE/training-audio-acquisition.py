"""
Audio Recording Script for STM32F407G-Discovery Board

This script records audio PCM data received via USB and saves it as WAV files.
It is specifically designed to work with 16-bit PCM data sent from an STM32F407G-Discovery board.
The script reads audio samples from the serial port and stores them in separate audio files.

Requirements:
- Ensure that the STM32F407G-Discovery board is configured to send 16-bit PCM audio data over USB.
- The necessary firmware to operate the STM32F407G-Discovery board for this purpose can be found in the following GitHub project:
  [https://github.com/Med-Karim-Ben-Boubaker/Discovery-STM32F407-Audio-Acquisition]

Script Details:
- Audio is recorded for a specified duration and sampling frequency.
- The recorded audio is saved in the 'recorded_audios' directory as WAV files.
- Each WAV file corresponds to a separate recording session.

Configuration:
- Serial Port: COM10
- Baud Rate: 9500
- Timeout: 1 second
- Audio Record Period: 1 second
- Sampling Frequency: 16,000 Hz
- Number of Files: 1500

Author: Ben Boubaker Mohamed Karim
Date: 2024-Aug
"""

import serial
import struct
import wave
import os

# Serial port configuration
# Create a serial port object for communication with the device
ser = serial.Serial('COM10', 9500, timeout=1)

# Audio recording settings
AUDIO_RECORD_PERIOD_S = 1 # Duration in seconds for each audio recording
SAMPLING_FREQUENCY = 16000 # Number of samples per second
TOTAL_SAMPLES = AUDIO_RECORD_PERIOD_S * SAMPLING_FREQUENCY # Total samples per file
NUM_FILES = 1500  # Number of audio files to record
OUTPUT_DIR = 'recorded_audios' # Directory to save the recorded audio files

# Create the output directory if it doesn't exist
if not os.path.exists(OUTPUT_DIR):
    os.makedirs(OUTPUT_DIR)
    
# Utility Functions ----------------------------------------------------------------------
def read_usb_data():
    """Read two bytes from the USB serial port and unpack them as a signed short.

    Returns:
        int or None: The unpacked signed short integer from the USB data, or None if not enough data was read.
    """
    usb_bytes = ser.read(2)
    if len(usb_bytes) == 2:
        usb_value = struct.unpack('h', usb_bytes)[0]
        return usb_value
    else:
        return None

def record_audio(file_index):
    """Record audio for the specified duration and save it to a WAV file.

    Args:
        file_index (int): The index of the audio file to be recorded.
    """
    frames = [] # List to store the audio samples

    print(f"Recording file {file_index + 1}/{NUM_FILES}...")
    # Loop to read the required number of samples
    for _ in range(TOTAL_SAMPLES):
        # Read audio data from the serial port
        usb_value = read_usb_data()
        if usb_value is not None:
            # Append the valid sample to the frames list
            frames.append(usb_value)

    # Construct the filename for the WAV file
    wav_filename = os.path.join(OUTPUT_DIR, f"recorded_audio_{file_index + 1}.wav")
    
    # Save the recorded data to a WAV file
    with wave.open(wav_filename, 'wb') as wf:
        wf.setnchannels(1)  # Set the number of channels to mono
        wf.setsampwidth(2)  # Set the sample width to 2 bytes (16 bits)
        wf.setframerate(SAMPLING_FREQUENCY) # Set the sampling frequency
        # Pack the frames into a byte format and write them to the file
        wf.writeframes(struct.pack(f'{len(frames)}h', *frames))

    print(f"File {wav_filename} saved.")

# Main Application ----------------------------------------------------------------------
def main():
    """Main function to record multiple audio files."""
    # Loop over the number of files to record
    for i in range(NUM_FILES):
        # Record and save each audio file
        record_audio(i)

    print("Recording complete.")

if __name__ == "__main__":
    main()