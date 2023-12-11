/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : MaxPool.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 04 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef MAXPOOL_H
#define MAXPOOL_H

#include <Buffer3D.h>
#include <DisplayMemSize.h>

template<int IN_HEIGHT,
         int IN_WIDTH,
         int OUT_HEIGHT,
         int OUT_WIDTH,
         int N_FMAP,
         int KSIZE,
         typename T = double,
         int START_OFFSET = 0>
class MaxPool
{
public:
  // Buffer types for feature map and kernel
  typedef Mem3D<N_FMAP, IN_HEIGHT, IN_WIDTH, T, START_OFFSET> t_buf_feature_in;

  typedef Mem3D<N_FMAP, OUT_HEIGHT, OUT_WIDTH, T, t_buf_feature_in::SIZE>
    t_buf_feature_out;

  typedef Mem3D<N_FMAP, OUT_HEIGHT, OUT_WIDTH, T> t_buf_feature_ref;

  typedef Buffer3D<1, KSIZE, KSIZE, T> t_buf_kernel;

  static const int OUT_OFFSET = t_buf_feature_out::OFFSET;
  static const int SIZE = t_buf_feature_out::SIZE;

  MaxPool(){};

  void process(t_buf_feature_in& input_feature,
               t_buf_feature_out& output_feature)
  {
    t_buf_kernel kernel;

    // ...
  }

  // ---------------------------------------------------------------
  // Total Memory needs to string
  // ---------------------------------------------------------------

#ifndef __SYNTHESIS__
  std::string infoMemory() const
  {
    std::stringstream ss;
    ss << "[Memory needs] MaxPool Layer" << std::endl;
    ss << "  - Input feature map :  "
       << DisplayMemSize::showWords<t_buf_feature_in>() << std::endl;
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
  }
#endif
};

#endif