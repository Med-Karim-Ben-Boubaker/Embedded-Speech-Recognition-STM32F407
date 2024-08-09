/**
 ******************************************************************************
 * @file           : audio_utils.c
 * @brief          : This module contains functions for initializing and processing
 *                    audio data from the microphone. It includes functionalities
 *                    for initializing audio components, recording audio samples,
 *                    computing log mel spectrograms, and streaming PCM data over USB.
 *                    The CMSIS-DSP library is used for various signal processing
 *                    tasks, including real fast Fourier transform (RFFT), mel filterbank,
 *                    and log mel spectrogram calculations.
 *
 * @author          : Ben Boubaker Karim
 * @date            : 2024-Aug
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "audio_utils.h"

/* Variables -----------------------------------------------------------------*/

/* Instance for floating-point RFFT/RIFFT */
arm_rfft_fast_instance_f32 rfft;

/* Instance for the floating-point Spectrogram function */
SpectrogramTypeDef spectrogram;

/* Instance for the floating-point MelFilterbank function */
MelFilterTypeDef mel_filter;

/* Instance for the floating-point MelSpectrogram function */
MelSpectrogramTypeDef mel_spectrogram;

/* Instance for the floating-point Log-MelSpectrogram function */
LogMelSpectrogramTypeDef log_mel_spectrogram;

/* Intermediate buffer that contains a signal frame */
float32_t frame_buffer[FRAME_LEN];

/* Intermediate buffer that contains Spectrogram column  */
float32_t spectrogram_col_buffer[FRAME_NUM];

/* Intermediate buffer that contains Spectrogram column  */
float32_t logMelSpectrogram_col_buffer[MELSPECTROGRAM_SAMPLE_SIZE];

/* Intermediate buffer that contains the window function  */
float32_t window_func_buffer[FRAME_LEN];

/* Temporary calculation buffer of length `FFT_LEN` */
float32_t spectrogram_scratch_buffer[FFT_LEN];

/* Number of frames of the input signal */
uint32_t num_frames = FRAME_NUM; //1 + (AUDIO_PCM_BUFFER_SIZE - FRAME_LEN) / HOP_LEN;

int16_t pcm_frame_buffer[FRAME_LEN];

/*Intermediate buffer that contains the Mel filter weights of length `NUM_MEL_COEFS` */
float32_t mel_filter_coefs[NUM_MEL_COEFS];

/* Intermediate buffer that contains the Mel filter coefficients start indices */
uint32_t mel_filter_start_indices[NUM_MELS];

/* Intermediate buffer that contains the Mel filter coefficients stop indices */
uint32_t mel_filter_stop_indices[NUM_MELS];

/* Functions -----------------------------------------------------------------*/

/* Initialize audio processing structures */
void audio_preprocessing_init(void);

/**
 * @brief Initialize and start the audio recording system.
 *
 * This function initializes the microphone and starts audio recording.
 * It sets up the microphone hardware and begins capturing audio data.
 *
 * @note Ensure that the microphone hardware is properly configured
 * before calling this function. This function assumes that
 * the microphone initialization and start procedures are handled by
 * `microphone_init()` and `microphone_start()`, respectively.
 */
void audio_init(void) {
    microphone_init();
    microphone_start();
}

/**
 * @brief Compute the log mel spectrogram from an audio signal.
 *
 * This function processes an input audio signal to compute the log mel
 * spectrogram. It converts 16-bit PCM audio samples into normalized
 * floating-point values, processes them frame by frame, and fills the
 * output buffer with the computed log mel spectrogram values.
 *
 * @param[in] input_signal Pointer to the input audio signal in 16-bit PCM format.
 * @param[out] out_melSpect Pointer to the output buffer where the log mel
 * spectrogram values will be stored.
 * @param[in] signal_len Length of the input audio signal.
 *
 * @note The function processes the signal in frames, and the output buffer
 * must be large enough to hold all computed log mel spectrogram values for
 * each frame. Ensure `num_frames`, `HOP_LEN`, `FRAME_LEN`, and
 * `MELSPECTROGRAM_SAMPLE_SIZE` are correctly defined for the input signal.
 */
void audio_logMelSpectrogram(int16_t* input_signal, float32_t* out_melSpect,
		uint32_t signal_len) {

	for (uint32_t frame_index = 0; frame_index < num_frames; frame_index++) {

		/* Convert 16-bit PCM into normalized floating point values */
		buf_to_float_normed(&input_signal[HOP_LEN * frame_index], frame_buffer,
		FRAME_LEN);

		LogMelSpectrogramColumn(&log_mel_spectrogram, frame_buffer, logMelSpectrogram_col_buffer);

		/* Reshape column into `out_melSpect` */
		for (uint32_t i = 0; i < MELSPECTROGRAM_SAMPLE_SIZE; i++) {
			out_melSpect[frame_index * MELSPECTROGRAM_SAMPLE_SIZE + i] = logMelSpectrogram_col_buffer[i];
		}
	}
}

/**
 * @brief Initialize audio preprocessing components.
 *
 * This function initializes various components required for audio preprocessing,
 * including the window function, real fast Fourier transform (RFFT), mel filterbank,
 * spectrogram, mel spectrogram, and log mel spectrogram configurations.
 * It ensures that all components are set up with the correct parameters before
 * starting audio processing.
 *
 * @note The function contains infinite loops as error handlers if any
 * initialization step fails. Ensure that the configurations are correctly set
 * before calling this function.
 */
void audio_preprocessing_init(void) {
	/* Init window function */
	if (Window_Init(window_func_buffer, FRAME_LEN, WINDOW_HANN) != 0) {
		while (1)
			;
	}

	/* Init RFFT */
	arm_rfft_fast_init_f32(&rfft, FFT_LEN);

	/* Init mel filterbank */
	mel_filter.pStartIndices = mel_filter_start_indices;
	mel_filter.pStopIndices = mel_filter_stop_indices;
	mel_filter.pCoefficients = mel_filter_coefs;
	mel_filter.NumMels = NUM_MELS;
	mel_filter.FFTLen = FFT_LEN;
	mel_filter.SampRate = SAMPLE_RATE;
	mel_filter.FMin = 300.0f;
	mel_filter.FMax = mel_filter.SampRate / 2.0;
	mel_filter.Formula = MEL_SLANEY;
	mel_filter.Normalize = 1;
	mel_filter.Mel2F = 1;
	MelFilterbank_Init(&mel_filter);
	if (mel_filter.CoefficientsLength != NUM_MEL_COEFS) {
		while (1)
			;
	}

	/* Init Spectrogram */
	spectrogram.pRfft = &rfft;
	spectrogram.Type = SPECTRUM_TYPE_POWER;
	spectrogram.pWindow = window_func_buffer;
	spectrogram.SampRate = SAMPLE_RATE;
	spectrogram.FrameLen = FRAME_LEN;
	spectrogram.FFTLen = FFT_LEN;
	spectrogram.pScratch = spectrogram_scratch_buffer;

	/* Init MelSpectrogram */
	mel_spectrogram.SpectrogramConf = &spectrogram;
	mel_spectrogram.MelFilter = &mel_filter;

	/* Init LogMelSpectrogram */
	log_mel_spectrogram.MelSpectrogramConf = &mel_spectrogram;
	log_mel_spectrogram.LogFormula = LOGMELSPECTROGRAM_SCALE_DB;
	log_mel_spectrogram.Ref = 1.0;
	log_mel_spectrogram.TopdB = HUGE_VALF;

}

/**
 * @brief Record audio samples into a buffer.
 *
 * This function records audio samples into the provided buffer. It toggles
 * an orange LED to indicate the start of the recording phase and fills the
 * buffer with audio samples segment by segment until the entire buffer is filled.
 *
 * @param[out] dst Pointer to the destination buffer where recorded audio
 * samples will be stored.
 * @param[in] buffer_size Size of the destination buffer in number of samples.
 *
 * @note The buffer size should be a multiple of PCM_BUFFER_SIZE to ensure
 * that each segment is filled correctly. The function blocks until the
 * entire buffer is filled.
 */
void audio_pcm_record(int16_t* dst, size_t buffer_size) {

	/* Toggle Orange Led to Indicate Starting of a Recording phase. */
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

    /* Calculate the total number of segments needed */
    const uint32_t num_segments = buffer_size / PCM_BUFFER_SIZE;

    uint32_t segment_index = 0;

    /* Loop through each segment of the audio buffer */
    while (segment_index < num_segments) {
    	/* Record a sample into the pcm_buffer */
    	while(!microphone_record_sample());

        /* Calculate the offset position in the pcm_audio_record buffer */
        int16_t* destination = &dst[segment_index * PCM_BUFFER_SIZE];

        /* Copy recorded samples from pcm_buffer to pcm_audio_record */
        memcpy(destination, pcm_buffer_int16, sizeof(int16_t) * PCM_BUFFER_SIZE);

        /* Move to the next segment */
        segment_index++;
    }
}

void audio_pcm_usb_stream(void){

	/* Record a sample into the pcm_buffer */
	while(!microphone_record_sample());

    /* Send a chunk of PCM values to USB Interface */
	CDC_Transmit_FS((uint8_t*)pcm_buffer_int16, sizeof(int16_t) * PCM_BUFFER_SIZE);

}
