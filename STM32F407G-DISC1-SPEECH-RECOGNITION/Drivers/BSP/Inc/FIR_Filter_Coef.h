/**
 *******************************************************************************
 * @file           : FIR_Filter_Coef.h
 * @brief          : This header file declares the FIR filter coefficients used in the audio processing
 * 					 of the MP45DT02 MEMS microphone data.
 * @author		   : Ben Boubaker Karim
 * @date	       : 2024-Jul
 *******************************************************************************
 */

#ifndef BSP_INC_FIR_FILTER_COEF_H_
#define BSP_INC_FIR_FILTER_COEF_H_

#include "MP45DT02-MEMS-Microphone.h" // Ensure FIR_TAPS is defined

/**
 * @brief FIR filter coefficients array.
 *
 * This array contains the coefficients used in the FIR filter for decimation.
 * The size of the array is defined by the FIR_TAPS macro.
 */
extern float fir_coef[FIR_TAPS];

#endif /* BSP_INC_FIR_FILTER_COEF_H_ */
