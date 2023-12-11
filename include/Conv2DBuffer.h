/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Conv2DBuffer.h
 * Description : 2D Convolution with stride 1 and odd size kernel
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Jun 04 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef _INCLUDED_CONV2D_BUFFER_H_
#define _INCLUDED_CONV2D_BUFFER_H_

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
class Conv2DBuffer
  : public Conv2DBase<HEIGHT, WIDTH, IN_FMAP, OUT_FMAP, KSIZE, T, START_OFFSET>
{
public:
  // ---------------------------------------------------
  // [HELP] read the documentation of Mem1D, Mem3D, Mem4D
  // and Buffer3D to understand the following typedefs
  // ---------------------------------------------------

  typedef Conv2DBase<HEIGHT, WIDTH, IN_FMAP, OUT_FMAP, KSIZE, T, START_OFFSET>
    t_base;

  using typename t_base::t_buf_bias;
  using typename t_base::t_buf_feature_in;
  using typename t_base::t_buf_feature_out;
  using typename t_base::t_buf_feature_ref;
  using typename t_base::t_buf_weight;

  using typename t_base::t_buf_one_feature;
  using typename t_base::t_buf_one_kernel;

  using t_base::OUT_OFFSET;
  using t_base::SIZE;

  // ---------------------------------------------------
  // [HELP] the following arrays are used to store the intermediate
  // results of the convolution. They are declared as member variables
  // of the class to avoid allocating them at each call of the
  // process() method.
  // ---------------------------------------------------

  T array_acc1[t_buf_one_feature::SIZE];
  T array_acc2[t_buf_one_feature::SIZE];
  T array_kernel1[t_buf_one_kernel::SIZE];
  T array_kernel2[t_buf_one_kernel::SIZE];

  Conv2DBuffer() {}

  // ---------------------------------------------------------------
  // Calculate the convolution of all input and output feature maps
  // with all kernels for one layer
  // ---------------------------------------------------------------

#ifdef USE_OFMAP_CPT_CHAN
  template<typename t_chan>
#endif
  void process(t_buf_feature_in& input_feature,
               t_buf_weight& weights,
               t_buf_bias& bias,
#ifdef USE_OFMAP_CPT_CHAN
               t_buf_feature_out& output_feature,
               t_chan& ofmapCptChannel
#else
               t_buf_feature_out& output_feature
#endif
  )
  {
    t_buf_one_feature acc_buf(array_acc1);

  OUT_FEATURE_MAP:
    for (int ofm = 0; ofm < OUT_FMAP; ofm++) {

      // ...

    IN_FEATURE_MAP:
      for (int ifm = 0; ifm < IN_FMAP; ifm++) {

        // [HELP] use process_one_input_feature() to calculate the
        // convolution of one input feature map with one kernel
        // ...
      }

      // ...

#ifdef USE_OFMAP_CPT_CHAN
      ofmapCptChannel.Push(ofm + 1);
#endif
    }
  }
  // ---------------------------------------------------------------
  // Calculate the convolution of one input feature map
  // with one kernel
  // ---------------------------------------------------------------

  t_buf_one_feature process_one_input_feature(t_buf_one_feature& input_feature,
                                              t_buf_one_kernel& kernel_weights)
  {
    t_buf_one_feature acc_feature(array_acc2);
    t_buf_one_kernel input_data(array_kernel1);
    t_buf_one_kernel kernel_mults(array_kernel2);

    // ...

  ROW_FEATURE:
    for (int r = 0; r < HEIGHT; r++) { // Process feature map
    COL_FEATURE:
      for (int c = 0; c < WIDTH; c++) {

        // [HELP] use copyCenteredWindow() to copy a window of the
        // input feature map centered on (r,c) into input_data
        // ...
      }
    }
    return acc_feature;
  }

  // ---------------------------------------------------------------
  // Total Memory needs to string
  // ---------------------------------------------------------------

  std::string infoMemory() const
  {
#ifndef __SYNTHESIS__
    std::stringstream ss;
    ss << "[Memory needs] Conv2DBuffer Layer" << std::endl;
    ss << "  - Input feature map :  "
       << DisplayMemSize::showWords<t_buf_feature_in>() << std::endl;
    ss << "  - Weights :            "
       << DisplayMemSize::showWords<t_buf_weight>() << std::endl;
    ss << "  - Bias :               " << DisplayMemSize::showWords<t_buf_bias>()
       << std::endl;
    ss << "  - Output feature map : "
       << DisplayMemSize::showWords<t_buf_feature_out>() << std::endl;
    ss << "  - Total :              "
       << DisplayMemSize::showTotal<t_buf_feature_out>(START_OFFSET)
       << std::endl
       << std::endl;
    ss << "    (First word : " << START_OFFSET << ")" << std::endl;
    ss << "    (Last word  : " << SIZE - 1 << ")" << std::endl;
    ss << std::endl;
    ss << "    [Total Mem Sum]     "
       << DisplayMemSize::showSum<t_buf_feature_out>() << std::endl;
    return ss.str();
#else
    return "";
#endif
  }
};

#endif
