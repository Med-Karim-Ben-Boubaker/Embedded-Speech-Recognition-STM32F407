/*
 * audio_record.c
 *
 *  Created on: Jul 28, 2024
 *      Author: karim
 */
#include "audio_utils.h"

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

/* Initialize audio processing structures */
void audio_preprocessing_init(void);

void audio_init(void) {

	microphone_init();

	microphone_start();
}
void audio_spectrogram(int16_t *input_signal, float32_t *out_spect,
		uint32_t signal_len) {

	for (uint32_t frame_index = 0; frame_index < num_frames; frame_index++) {

		/* Convert 16-bit PCM into normalized floating point values */
		buf_to_float_normed(&input_signal[HOP_LEN * frame_index], frame_buffer,
		FRAME_LEN);

		SpectrogramColumn(&spectrogram, frame_buffer, spectrogram_col_buffer);

		/* Reshape column into `out_spectrogram` */
		for (uint32_t i = 0; i < MELSPECTROGRAM_SAMPLE_SIZE; i++) {
			out_spect[frame_index * MELSPECTROGRAM_SAMPLE_SIZE + i] = spectrogram_col_buffer[i];
		}
	}
}

void audio_logMelSpectrogram(int16_t* input_signal, float32_t* out_melSpect,
		uint32_t signal_len) {

	for (uint32_t frame_index = 0; frame_index < num_frames; frame_index++) {

		/* Convert 16-bit PCM into normalized floating point values */
		buf_to_float_normed(&input_signal[HOP_LEN * frame_index], frame_buffer,
		FRAME_LEN);

		LogMelSpectrogramColumn(&log_mel_spectrogram, frame_buffer, logMelSpectrogram_col_buffer);

		/* Reshape column into `out_spectrogram` */
		for (uint32_t i = 0; i < MELSPECTROGRAM_SAMPLE_SIZE; i++) {
			out_melSpect[frame_index * MELSPECTROGRAM_SAMPLE_SIZE + i] = logMelSpectrogram_col_buffer[i];
		}
	}
}
/**
 * @brief Initialize the data structures to preprocess the audio signal.
 *
 * @param  None
 *
 * @retval None
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

void audio_pcm_record(int16_t* dst, size_t buffer_size) {

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
