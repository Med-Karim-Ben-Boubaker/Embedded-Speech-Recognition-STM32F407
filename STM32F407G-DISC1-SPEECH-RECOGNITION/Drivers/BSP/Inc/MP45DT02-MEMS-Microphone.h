/**
 *******************************************************************************
 * @file           : MP45DT02-MEMS-Microphone.h
 * @brief          : This header file provides declarations and macros for interfacing with
 * 					 the MP45DT02 MEMS microphone using I2S and DMA.
 * @author		   : Ben Boubaker Karim
 * @date	       : 2024-Jul
 *******************************************************************************
 */
#ifndef MP45DT02_MEMS_MICROPHONE_H
#define MP45DT02_MEMS_MICROPHONE_H

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Typedefs ------------------------------------------------------------------*/

typedef enum {
	OFFSET_NONE = -1, OFFSET_HALF, OFFSET_FULL,
} DMA_Buffer_State;

/* Macros ------------------------------------------------------------------*/

/* Microphone and processing configuration */
#define MICROPHONE_SAMPLING_FREQ_KH  1024U // Microphone sampling frequency in kHz
#define HARDWARE_PERIOD_MS           1U    // Hardware sampling period in milliseconds

/* FIR filter configuration */
#define FIR_TAPS                     258U  // Number of taps in the FIR filter
#define FIR_DECIMATION_FACTOR        64U   // Decimation factor for FIR filter
#define PDM_SAMPLE_BITS              16U   // Number of bits per PDM sample

/* Buffer size calculations */
#define PDM_BITS_SIZE                (MICROPHONE_SAMPLING_FREQ_KH * HARDWARE_PERIOD_MS)
#define PDM_BUFFER_SIZE              (PDM_BITS_SIZE / 16U) // PDM buffer size in words
#define PCM_BUFFER_SIZE              (PDM_BITS_SIZE / FIR_DECIMATION_FACTOR) // PCM buffer size
#define FLOAT32_PDM_BUFFER_SIZE      (PDM_BUFFER_SIZE * PDM_SAMPLE_BITS) // Float buffer size
#define FIR_STATE_BUFFER_SIZE        (FLOAT32_PDM_BUFFER_SIZE + FIR_TAPS - 1) // FIR state size
#define TOTAL_SAMPLES                (PCM_BUFFER_SIZE * 1000U) // Total samples for processing

/* Variables -----------------------------------------------------------------*/

extern float32_t pcm_buffer[PCM_BUFFER_SIZE];
extern int16_t pcm_buffer_int16[PCM_BUFFER_SIZE];
extern I2S_HandleTypeDef hi2s2;

/* Include  FIR_Filter_Coef.h after defining FIR_TAPS */
#include "FIR_Filter_Coef.h"

/* Functions -----------------------------------------------------------------*/

/* Private Function ---------------*/

void convert_to_pdm_float32(uint16_t* src, float32_t* dst, uint8_t buffer_to_process);
void convert_pcm_f32_to_int16(float32_t* src, int16_t* dst, size_t len);

/* Public Function ---------------*/

/**
 * @brief Initializes the microphone and FIR decimation filter.
 */
void microphone_init(void);

/**
 * @brief Starts the microphone to receive data using DMA.
 */
void microphone_start(void);

/**
 * @brief Processes the microphone data if processing is needed.
 */
uint8_t microphone_record_sample(void);

#endif // MP45DT02_MEMS_MICROPHONE_H
