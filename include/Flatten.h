/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Flatten.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sat Sep 09 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef FLATTEN_H
#define FLATTEN_H

#include <Buffer3D.h>
#include <Mem1D.h>
#include <Mem2D.h>

template<int IN_HEIGHT,
         int IN_WIDTH,
         int IN_FMAP,
         typename T = double,
         int START_OFFSET = 0>
class Flatten
{

public:
  typedef Mem3D<IN_FMAP, IN_HEIGHT, IN_WIDTH, T, START_OFFSET> t_buf_feature_in;
  typedef Mem1D<t_buf_feature_in::WORDS, T, t_buf_feature_in::SIZE>
    t_buf_feature_out;
  typedef Mem1D<t_buf_feature_in::WORDS, T> t_buf_feature_ref;

  static const int OUT_OFFSET = t_buf_feature_out::OFFSET;
  static const int SIZE = t_buf_feature_out::SIZE;

  int idx;

  Flatten() {}

  void process(t_buf_feature_in& input_feature,
               t_buf_feature_out& output_feature)
  {
    // ...
  }

  // ---------------------------------------------------------------
  // Total memory needs to string
  // ---------------------------------------------------------------

#ifndef __SYNTHESIS__
  std::string infoMemory() const
  {
    std::stringstream ss;
    ss << "[Memory needs] Flatten Layer " << std::endl;
    ss << "  - Input feature map  : "
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

#endif // FLATTEN_H