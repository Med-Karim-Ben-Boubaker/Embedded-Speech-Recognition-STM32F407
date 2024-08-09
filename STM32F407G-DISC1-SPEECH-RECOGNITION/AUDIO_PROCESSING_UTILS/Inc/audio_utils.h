/**
 ******************************************************************************
 * @file           : audio_utils.h
 * @brief          : This header file provides function declarations and macro
 *                    definitions for audio processing tasks, including recording,
 *                    streaming, and feature extraction. It supports operations such
 *                    as audio preprocessing, PCM recording, log mel spectrogram
 *                    computation, and audio data streaming over USB.
 *                    It depends on the MP45DT02 MEMS microphone interface, USB CDC
 *                    interface for data transmission, and feature extraction modules.
 *
 * @author          : Ben Boubaker Karim
 * @date            : 2024-Aug
 ******************************************************************************
 */

#ifndef INC_AUDIO_UTILS_H_
#define INC_AUDIO_UTILS_H_

/* Includes ------------------------------------------------------------------*/

#include "MP45DT02-MEMS-Microphone.h"
#include "usbd_cdc_if.h"
#include "feature_extraction.h"

/* Macros ------------------------------------------------------------------*/

/* Audio Recording Parameters. */
#define AUDIO_PCM_BUFFER_SIZE       16384U // Size of the recorder buffer (Multiple of 4096)
#define SAMPLE_RATE     		    16000U

/* Short-Time Fourier Transform (STFT) Parameters. */
#define FFT_LEN 				    512U // Number of FFT points. It must be greater or equal to FRAME_LEN
#define FRAME_NUM                   122U // = 1 + (AUDIO_PCM_BUFFER_SIZE - FRAME_LEN) / HOP_LEN
#define FRAME_LEN				    FFT_LEN // Window length and then padded with zeros to match FFT_LEN.
#define HOP_LEN        			    FFT_LEN / 4 // Number of overlapping samples between successive frames

/* Log-Mel-Spectrogram Parameters. */
#define MELSPECTROGRAM_SAMPLE_SIZE  40U // Each FFT Sample has this number of values.
#define NUM_MELS                    40U // Number of Mel Filters.
#define NUM_MEL_COEFS               474U // Number of Mel Coef ( Determined by a Test ).

/* Functions -----------------------------------------------------------------*/

/**
 * @brief Initialize audio preprocessing components.
 *
 * Sets up window functions, RFFT, mel filterbank, and spectrogram settings.
 */
void audio_preprocessing_init(void);

/**
 * @brief Record and stream audio data over USB.
 *
 * Captures audio from the microphone and sends it via USB.
 */
void audio_pcm_usb_stream(void);

/**
 * @brief Record audio samples into a buffer.
 *
 * Records audio into the specified buffer and toggles an LED to indicate recording.
 *
 * @param[out] dst Pointer to the destination buffer.
 * @param[in]  buffer_size Size of the buffer.
 */
void audio_pcm_record(int16_t* dst, size_t buffer_size);

/**
 * @brief Initialize and start audio recording.
 *
 * Sets up the microphone and begins audio recording.
 */
void audio_init(void);

/**
 * @brief Compute log mel spectrogram from audio.
 *
 * Converts PCM audio samples to log mel spectrogram and stores in the output buffer.
 *
 * @param[in]  input_signal PCM audio data.
 * @param[out] out_spect    Output buffer for the spectrogram.
 * @param[in]  signal_len   Length of the audio signal.
 */
void audio_logMelSpectrogram(int16_t *input_signal,
		float32_t *out_spect, uint32_t signal_len);

#endif /* INC_AUDIO_UTILS_H_ */
