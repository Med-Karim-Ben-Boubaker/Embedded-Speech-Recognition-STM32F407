/**
 *******************************************************************************
 * @file           : MP45DT02-MEMS-Microphone.c
 * @brief          : This module initializes and processes audio data from the MP45DT02 MEMS microphone.
 * 					 It uses the CMSIS-DSP library to perform decimation and convert PDM to PCM.
 * @author		   : Ben Boubaker Karim
 * @date	       : 2024-Jul
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "MP45DT02-MEMS-Microphone.h"
#include "main.h"

/* Macros -----------------------------------------------------------------*/

/* Constants and definitions */
#define PDM_BUFFER_DOUBLE_SIZE (PDM_BUFFER_SIZE * 2)
#define PCM_DATA_SIZE (sizeof(float32_t) * PCM_BUFFER_SIZE)

/* Variables -----------------------------------------------------------------*/

/* Indicates the transfer of PDM data from microphone into `pdm_buffer` */
DMA_Buffer_State dma_transfer_state;

/* Input audio signal in PDM form */
uint16_t pdm_buffer[PDM_BUFFER_DOUBLE_SIZE];

/* PCM data of input audio signal */
float32_t pcm_buffer[PCM_BUFFER_SIZE];

/* PCM data of type int16_t */
int16_t pcm_buffer_int16[PCM_BUFFER_SIZE];

/* Converted float PDM buffer for the fir filter */
float32_t pdm_float_buffer[FLOAT32_PDM_BUFFER_SIZE];

/* FIR filter state buffer */
float32_t fir_state[FIR_STATE_BUFFER_SIZE];

// FIR filter parameters
uint8_t fir_decimation_factor = FIR_DECIMATION_FACTOR;
uint16_t fir_num_taps = FIR_TAPS;
uint32_t fir_block_size = FLOAT32_PDM_BUFFER_SIZE;

/* FIR decimation filter instance */
arm_fir_decimate_instance_f32 fir_decimate_f32;

void convert_to_pdm_float32(uint16_t* src, float32_t* dst, uint8_t buffer_to_process);

/* Functions -----------------------------------------------------------------*/

/**
 * @brief Initializes the microphone and FIR decimation filter.
 */
void microphone_init(void) {
	/* Initialize fir CMSIS filter */
    if (arm_fir_decimate_init_f32(
        &fir_decimate_f32,
        fir_num_taps,
        fir_decimation_factor,
        fir_coef,
        fir_state,
        fir_block_size
    ) != ARM_MATH_SUCCESS) {
        Error_Handler();
    }
}

/**
 * @brief Starts the microphone to receive data using DMA.
 */
void microphone_start(void) {
	/* Initialize DMA State */
	dma_transfer_state = OFFSET_NONE;

    HAL_I2S_Receive_DMA(&hi2s2, pdm_buffer, PDM_BUFFER_DOUBLE_SIZE);
}

/**
 * @brief Processes microphone data by converting PDM samples to PCM.
 */
uint8_t microphone_record_sample(void) {

    if (dma_transfer_state == OFFSET_HALF || dma_transfer_state == OFFSET_FULL) {
        /* Determine which buffer to process */
        uint8_t buffer_to_process = dma_transfer_state;

        /* Convert PDM buffer to float buffer */
        convert_to_pdm_float32(pdm_buffer, pdm_float_buffer, buffer_to_process);

        /* Convert PDM to PCM using FIR decimation */
        arm_fir_decimate_f32(
            &fir_decimate_f32,
            pdm_float_buffer,
            pcm_buffer,
            fir_block_size
        );

        convert_pcm_f32_to_int16(pcm_buffer, pcm_buffer_int16, PCM_BUFFER_SIZE);

        dma_transfer_state = OFFSET_NONE;

        return 1;
    }

    return 0;
}

/**
 * @brief I2S DMA half-complete callback.
 *        Indicates the first half of the buffer is filled.
 */
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s2) {
	dma_transfer_state = OFFSET_HALF;
}

/**
 * @brief I2S DMA complete callback.
 *        Indicates the second half of the buffer is filled.
 */
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s2) {
	dma_transfer_state = OFFSET_FULL;
}

/**
 * @brief Converts PDM data to float32 format for processing.
 *
 * @param src Source PDM buffer
 * @param dst Destination float32 buffer
 * @param buffer_to_process Buffer index to process (0 or 1)
 */
void convert_to_pdm_float32(uint16_t* src, float32_t* dst, uint8_t buffer_to_process) {
    uint32_t bitIndex = 0;
    uint16_t modifiedCurrentWord = 0;

    /* Initialize destination buffer with zeros */
    memset(dst, 0, sizeof(float32_t) * FLOAT32_PDM_BUFFER_SIZE);

    /* Convert each bit from the uint16_t word to a float element */
    for (bitIndex = 0; bitIndex < FLOAT32_PDM_BUFFER_SIZE; bitIndex++) {
        /* Load a new word every 16 bits */
        if (bitIndex % 16 == 0) {
            modifiedCurrentWord = src[(bitIndex / 16) + (buffer_to_process * PDM_BUFFER_SIZE)];
        }

        /* Check the MSB and set the corresponding float value */
        dst[bitIndex] = (modifiedCurrentWord & 0x8000) ? INT16_MAX : INT16_MIN;

        /* Shift the word to process the next bit */
        modifiedCurrentWord <<= 1;
    }
}

// Function to convert PCM buffer from float32_t to int16_t by truncating the decimal part
void convert_pcm_f32_to_int16(float32_t* src, int16_t* dst, size_t len) {
    for (size_t i = 0; i < len; i++) {
        // Truncate the float value to int16_t range
        float32_t sample = src[i];

        // Clamp the sample to fit within the int16_t range
        if (sample > 32767.0f) {
        	dst[i] = INT16_MAX;
        } else if (sample < -32768.0f) {
        	dst[i] = INT16_MIN;
        } else {
        	/* Truncate the decimal part */
        	dst[i] = (int16_t)sample;
        }
    }
}
