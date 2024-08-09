import serial
import struct
import wave
import os

# Serial port configuration
ser = serial.Serial('COM10', 9500, timeout=1)

# Audio recording settings
AUDIO_RECORD_PERIOD_S = 1
SAMPLING_FREQUENCY = 16000
TOTAL_SAMPLES = AUDIO_RECORD_PERIOD_S * SAMPLING_FREQUENCY
NUM_FILES = 1500  # Number of audio files to record
OUTPUT_DIR = 'recorded_random'

# Create the output directory if it doesn't exist
if not os.path.exists(OUTPUT_DIR):
    os.makedirs(OUTPUT_DIR)

def read_usb_data():
    """Read two bytes from the USB serial port and unpack them as a signed short."""
    usb_bytes = ser.read(2)
    if len(usb_bytes) == 2:
        usb_value = struct.unpack('h', usb_bytes)[0]
        return usb_value
    else:
        return None

def record_audio(file_index):
    """Record audio for the specified duration and save it to a WAV file."""
    frames = []

    print(f"Recording file {file_index + 1}/{NUM_FILES}...")
    for _ in range(TOTAL_SAMPLES):
        usb_value = read_usb_data()
        if usb_value is not None:
            frames.append(usb_value)

    # Save the recorded data to a WAV file
    wav_filename = os.path.join(OUTPUT_DIR, f"recorded_audio_{file_index + 1}.wav")
    with wave.open(wav_filename, 'wb') as wf:
        wf.setnchannels(1)  # Mono
        wf.setsampwidth(2)  # 2 bytes for int16
        wf.setframerate(SAMPLING_FREQUENCY)
        wf.writeframes(struct.pack(f'{len(frames)}h', *frames))

    print(f"File {wav_filename} saved.")

def main():
    """Main function to record multiple audio files."""
    for i in range(NUM_FILES):
        record_audio(i)

    print("Recording complete.")

if __name__ == "__main__":
    main()