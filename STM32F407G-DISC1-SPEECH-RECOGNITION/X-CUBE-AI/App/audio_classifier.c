/**
  ******************************************************************************
  * @file    audio_classifier.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Fri Aug  9 11:16:28 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "audio_classifier.h"
#include "audio_classifier_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_audio_classifier
 
#undef AI_AUDIO_CLASSIFIER_MODEL_SIGNATURE
#define AI_AUDIO_CLASSIFIER_MODEL_SIGNATURE     "462c10869f11a63826c0370d82586120"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Fri Aug  9 11:16:28 2024"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_AUDIO_CLASSIFIER_N_BATCHES
#define AI_AUDIO_CLASSIFIER_N_BATCHES         (1)

static ai_ptr g_audio_classifier_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_audio_classifier_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  gemm_5_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  nl_6_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 3, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 512, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  gemm_4_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  gemm_4_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  gemm_5_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 96, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_keras_tensor0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 4880, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  gemm_5_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  upsample_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1024, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1352, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  nl_1_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1352, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  pool_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  gemm_4_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  nl_4_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)
/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  gemm_5_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &gemm_5_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  nl_6_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &nl_6_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 8, 8), AI_STRIDE_INIT(4, 4, 4, 32, 256),
  1, &conv2d_1_weights_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &conv2d_1_bias_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  gemm_4_weights, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 288, 32, 1, 1), AI_STRIDE_INIT(4, 4, 1152, 36864, 36864),
  1, &gemm_4_weights_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  gemm_4_bias, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &gemm_4_bias_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  gemm_5_weights, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 1, 1), AI_STRIDE_INIT(4, 4, 128, 384, 384),
  1, &gemm_5_weights_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_keras_tensor0_output, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 40, 122), AI_STRIDE_INIT(4, 4, 4, 4, 160),
  1, &serving_default_keras_tensor0_output_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  gemm_5_bias, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &gemm_5_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  upsample_0_output, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 32, 32), AI_STRIDE_INIT(4, 4, 4, 4, 128),
  1, &upsample_0_output_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 13, 13), AI_STRIDE_INIT(4, 4, 4, 32, 416),
  1, &conv2d_1_output_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  nl_1_nl_output, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 13, 13), AI_STRIDE_INIT(4, 4, 4, 32, 416),
  1, &nl_1_nl_output_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  pool_2_output, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 6, 6), AI_STRIDE_INIT(4, 4, 4, 32, 192),
  1, &pool_2_output_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  pool_2_output0, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 288, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1152, 1152),
  1, &pool_2_output_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  gemm_4_output, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &gemm_4_output_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  nl_4_nl_output, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &nl_4_nl_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_6_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_6_layer, 6,
  NL_TYPE, 0x0, NULL,
  nl, forward_sm,
  &nl_6_chain,
  NULL, &nl_6_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_4_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_5_weights, &gemm_5_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  gemm_5_layer, 5,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &gemm_5_chain,
  NULL, &nl_6_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_4_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_4_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_4_nl_layer, 4,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_4_nl_chain,
  NULL, &gemm_5_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_4_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_2_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_4_weights, &gemm_4_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  gemm_4_layer, 4,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &gemm_4_chain,
  NULL, &nl_4_nl_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  pool_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_1_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_2_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  pool_2_layer, 2,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp,
  &pool_2_chain,
  NULL, &gemm_4_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_1_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_1_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_1_nl_layer, 1,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_1_nl_chain,
  NULL, &pool_2_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &upsample_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 1,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_1_chain,
  NULL, &nl_1_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


AI_STATIC_CONST ai_float upsample_0_scales_data[] = { 0.26229508196721313, 0.8, 1.0, 1 };
AI_ARRAY_OBJ_DECLARE(
    upsample_0_scales, AI_ARRAY_FORMAT_FLOAT,
    upsample_0_scales_data, upsample_0_scales_data, 4, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  upsample_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_keras_tensor0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &upsample_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  upsample_0_layer, 0,
  UPSAMPLE_TYPE, 0x0, NULL,
  upsample, forward_upsample_bilinear,
  &upsample_0_chain,
  NULL, &conv2d_1_layer, AI_STATIC, 
  .scales = &upsample_0_scales, 
  .center = true, 
  .mode = AI_UPSAMPLE_BILINEAR, 
  .nearest_mode = AI_ROUND_FLOOR, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 39468, 1, 1),
    39468, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 23616, 1, 1),
    23616, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_AUDIO_CLASSIFIER_IN_NUM, &serving_default_keras_tensor0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_AUDIO_CLASSIFIER_OUT_NUM, &nl_6_output),
  &upsample_0_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 39468, 1, 1),
      39468, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 23616, 1, 1),
      23616, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_AUDIO_CLASSIFIER_IN_NUM, &serving_default_keras_tensor0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_AUDIO_CLASSIFIER_OUT_NUM, &nl_6_output),
  &upsample_0_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool audio_classifier_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_audio_classifier_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_keras_tensor0_output_array.data = AI_PTR(g_audio_classifier_activations_map[0] + 0);
    serving_default_keras_tensor0_output_array.data_start = AI_PTR(g_audio_classifier_activations_map[0] + 0);
    
    upsample_0_output_array.data = AI_PTR(g_audio_classifier_activations_map[0] + 19520);
    upsample_0_output_array.data_start = AI_PTR(g_audio_classifier_activations_map[0] + 19520);
    
    conv2d_1_output_array.data = AI_PTR(g_audio_classifier_activations_map[0] + 0);
    conv2d_1_output_array.data_start = AI_PTR(g_audio_classifier_activations_map[0] + 0);
    
    nl_1_nl_output_array.data = AI_PTR(g_audio_classifier_activations_map[0] + 5408);
    nl_1_nl_output_array.data_start = AI_PTR(g_audio_classifier_activations_map[0] + 5408);
    
    pool_2_output_array.data = AI_PTR(g_audio_classifier_activations_map[0] + 0);
    pool_2_output_array.data_start = AI_PTR(g_audio_classifier_activations_map[0] + 0);
    
    gemm_4_output_array.data = AI_PTR(g_audio_classifier_activations_map[0] + 1152);
    gemm_4_output_array.data_start = AI_PTR(g_audio_classifier_activations_map[0] + 1152);
    
    nl_4_nl_output_array.data = AI_PTR(g_audio_classifier_activations_map[0] + 0);
    nl_4_nl_output_array.data_start = AI_PTR(g_audio_classifier_activations_map[0] + 0);
    
    gemm_5_output_array.data = AI_PTR(g_audio_classifier_activations_map[0] + 128);
    gemm_5_output_array.data_start = AI_PTR(g_audio_classifier_activations_map[0] + 128);
    
    nl_6_output_array.data = AI_PTR(g_audio_classifier_activations_map[0] + 0);
    nl_6_output_array.data_start = AI_PTR(g_audio_classifier_activations_map[0] + 0);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool audio_classifier_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_audio_classifier_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(g_audio_classifier_weights_map[0] + 0);
    conv2d_1_weights_array.data_start = AI_PTR(g_audio_classifier_weights_map[0] + 0);
    
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(g_audio_classifier_weights_map[0] + 2048);
    conv2d_1_bias_array.data_start = AI_PTR(g_audio_classifier_weights_map[0] + 2048);
    
    gemm_4_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_4_weights_array.data = AI_PTR(g_audio_classifier_weights_map[0] + 2080);
    gemm_4_weights_array.data_start = AI_PTR(g_audio_classifier_weights_map[0] + 2080);
    
    gemm_4_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_4_bias_array.data = AI_PTR(g_audio_classifier_weights_map[0] + 38944);
    gemm_4_bias_array.data_start = AI_PTR(g_audio_classifier_weights_map[0] + 38944);
    
    gemm_5_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_5_weights_array.data = AI_PTR(g_audio_classifier_weights_map[0] + 39072);
    gemm_5_weights_array.data_start = AI_PTR(g_audio_classifier_weights_map[0] + 39072);
    
    gemm_5_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_5_bias_array.data = AI_PTR(g_audio_classifier_weights_map[0] + 39456);
    gemm_5_bias_array.data_start = AI_PTR(g_audio_classifier_weights_map[0] + 39456);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_audio_classifier_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_AUDIO_CLASSIFIER_MODEL_NAME,
      .model_signature   = AI_AUDIO_CLASSIFIER_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 102560,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_audio_classifier_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_AUDIO_CLASSIFIER_MODEL_NAME,
      .model_signature   = AI_AUDIO_CLASSIFIER_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 102560,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_audio_classifier_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_audio_classifier_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_audio_classifier_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_audio_classifier_create(network, AI_AUDIO_CLASSIFIER_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_audio_classifier_data_params_get(&params) != true) {
        err = ai_audio_classifier_get_error(*network);
        return err;
    }
#if defined(AI_AUDIO_CLASSIFIER_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_AUDIO_CLASSIFIER_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_audio_classifier_init(*network, &params) != true) {
        err = ai_audio_classifier_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_audio_classifier_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_audio_classifier_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_audio_classifier_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_audio_classifier_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= audio_classifier_configure_weights(net_ctx, params);
  ok &= audio_classifier_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_audio_classifier_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_audio_classifier_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_AUDIO_CLASSIFIER_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

