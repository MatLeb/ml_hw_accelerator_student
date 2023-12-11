/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Conv2DArray.h
 * Description : 2D Convolution with stride 1 and odd size kernel
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Jun 04 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef _INCLUDED_CONV2D_ARRAY_H_
#define _INCLUDED_CONV2D_ARRAY_H_

#include "OpBias.h"
#include "OpEmpty.h"

#include <Conv2DBase.h>

template<int HEIGHT,
         int WIDTH,
         int IN_FMAP,
         int OUT_FMAP,
         int KSIZE,
         typename T = double,
         typename t_bias = OpEmpty<T>,
         int START_OFFSET = 0>
class Conv2DArray
  : public Conv2DBase<HEIGHT, WIDTH, IN_FMAP, OUT_FMAP, KSIZE, T, START_OFFSET>
{
public:
  typedef Conv2DBase<HEIGHT, WIDTH, IN_FMAP, OUT_FMAP, KSIZE, T, START_OFFSET>
    t_base;

  // ...

  Conv2DArray() {}

  // ---------------------------------------------------------------
  // Calculate the convolution of one input feature map
  // with one kernel
  // ---------------------------------------------------------------

  // ...

  // ---------------------------------------------------------------
  // Calculate the convolution of all input and output feature maps
  // ---------------------------------------------------------------

  void process_array(T in_fmaps[IN_FMAP][HEIGHT][WIDTH],
                     T kernel[OUT_FMAP][IN_FMAP][KSIZE][KSIZE],
                     T bias[OUT_FMAP],
                     T out_fmaps[OUT_FMAP][HEIGHT][WIDTH])
  {
    // ...

  OUT_FEATURE_MAP:
    for (int ofm = 0; ofm < OUT_FMAP; ofm++) {

      // ...

    IN_FEATURE_MAP:
      for (int ifm = 0; ifm < IN_FMAP; ifm++) {

        // [HELP] create a fonction (above) to calculate
        // the convolution of one input feature map with one kernel
        // ...
      }

      // ...
    }
  }

  // ---------------------------------------------------------------
  // Calculate the convolution of all input and output feature maps
  // bias are set to 0
  // ---------------------------------------------------------------

  void process_array(T in_fmaps[IN_FMAP][HEIGHT][WIDTH],
                     T kernel[OUT_FMAP][IN_FMAP][KSIZE][KSIZE],
                     T out_fmaps[OUT_FMAP][HEIGHT][WIDTH])
  {
    T bias[OUT_FMAP];
    for (int i = 0; i < OUT_FMAP; i++)
      bias[i] = 0;
    process_array(in_fmaps, kernel, bias, out_fmaps);
  }
};

#endif
