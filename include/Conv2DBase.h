/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Conv2DBase.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Nov 06 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef CONV2DBASE_H
#define CONV2DBASE_H

#include <Buffer3D.h>
#include <Mem1D.h>
#include <Mem2D.h>
#include <Mem3D.h>
#include <Mem4D.h>

template<int HEIGHT,
         int WIDTH,
         int IN_FMAP,
         int OUT_FMAP,
         int KSIZE,
         typename T = double,
         int START_OFFSET = 0>
class Conv2DBase
{
public:
  // [HELP] read the documentation of Mem1D, Mem3D, Mem4D
  // and Buffer3D to understand the following typedefs

  // ---------------------------------------------------
  // Buffer types for concatenated mem
  // => feature map + kernel + bias
  // ---------------------------------------------------
  typedef Mem3D<IN_FMAP, HEIGHT, WIDTH, T, START_OFFSET> t_buf_feature_in;
  typedef Mem4D<OUT_FMAP, IN_FMAP, KSIZE, KSIZE, T, t_buf_feature_in::SIZE>
    t_buf_weight;
  typedef Mem1D<OUT_FMAP, T, t_buf_weight::SIZE> t_buf_bias;
  typedef Mem3D<OUT_FMAP, HEIGHT, WIDTH, T, t_buf_bias::SIZE> t_buf_feature_out;

  // ---------------------------------------------------
  // Buffer types for reference output feature map
  // ---------------------------------------------------
  typedef Mem3D<OUT_FMAP, HEIGHT, WIDTH, T> t_buf_feature_ref;

  // ---------------------------------------------------
  // Buffer types for one feature map and one kernel
  // ---------------------------------------------------
  typedef Buffer3D<1, HEIGHT, WIDTH, T> t_buf_one_feature;
  typedef Buffer3D<1, KSIZE, KSIZE, T> t_buf_one_kernel;

  // ---------------------------------------------------
  // Static constants for offset and size
  // ---------------------------------------------------

  static const int OUT_OFFSET = t_buf_feature_out::OFFSET;
  static const int SIZE = t_buf_feature_out::SIZE;
};

#endif
