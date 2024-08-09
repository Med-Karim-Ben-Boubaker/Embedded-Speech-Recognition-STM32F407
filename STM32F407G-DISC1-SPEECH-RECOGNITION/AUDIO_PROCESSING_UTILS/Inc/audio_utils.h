/*
 * audio_record.h
 *
 *  Created on: Jul 28, 2024
 *      Author: karim
 */

#ifndef INC_AUDIO_UTILS_H_
#define INC_AUDIO_UTILS_H_

#include "MP45DT02-MEMS-Microphone.h"
#include "usbd_cdc_if.h"
#include "feature_extraction.h"

#define AUDIO_STREAMING_MODE	  0U
#define AUDIO_RECORDING_MODE      1U

#define AUDIO_MODE                AUDIO_RECORDING_MODE
#define AUDIO_PCM_PERIODE_S       1U

/* Size of the recorder buffer ( Multiple of 4096 ) */
#define AUDIO_PCM_BUFFER_SIZE	  16384U //2048U

/* Number of FFT points. It must be greater or equal to FRAME_LEN */
#define FFT_LEN 				  512U

/* Window length and then padded with zeros to match FFT_LEN */
#define FRAME_LEN				  FFT_LEN

/* Number of overlapping samples between successive frames */
#define HOP_LEN        			  FFT_LEN / 4

/* FRAME_NUM */
#define FRAME_NUM                 122U //12U //1 + (AUDIO_PCM_BUFFER_SIZE - FRAME_LEN) / HOP_LEN

#define TOTAL_FRAME_NUM			  122U

#define SPECTROGRAM_SAMPLE_SIZE   50U//(FFT_LEN / 2) + 1

#define MELSPECTROGRAM_SAMPLE_SIZE   40U

#define NUM_SPECTROGRAM        	  16U

#define SAMPLE_RATE     		  16000U

#define NUM_MELS                  40U

#define NUM_MEL_COEFS             474U

void audio_preprocessing_init(void);
void audio_pcm_usb_stream(void);
void audio_pcm_record(int16_t* dst, size_t buffer_size);
void audio_init(void);
void audio_spectrogram(int16_t *input_signal, float32_t *out_spect,
		uint32_t signal_len);
void audio_logMelSpectrogram(int16_t *input_signal, float32_t *out_spect,
		uint32_t signal_len);


#endif /* INC_AUDIO_UTILS_H_ */
