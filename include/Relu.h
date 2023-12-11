/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : ReLu.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sat Sep 09 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef RELU_H
#define RELU_H

#include <Mem1D.h>
#include <Mem2D.h>

template<int IN_SIZE, int OUT_SIZE, typename T = double, int START_OFFSET = 0>
class ReLu
{
public:
  typedef Mem1D<IN_SIZE, T, START_OFFSET> t_buf_feature_in;
  typedef Mem2D<IN_SIZE, OUT_SIZE, T, t_buf_feature_in::SIZE> t_buf_weight;
  typedef Mem1D<OUT_SIZE, T, t_buf_weight::SIZE> t_buf_bias;
  typedef Mem1D<OUT_SIZE, T, t_buf_bias::SIZE> t_buf_feature_out;

  typedef Mem1D<OUT_SIZE, T> t_buf_feature_ref;

  static const int OUT_OFFSET = t_buf_feature_out::OFFSET;
  static const int SIZE = t_buf_feature_out::SIZE;

  ReLu() {}

  void process(t_buf_feature_in& input_feature,
               t_buf_feature_out& output_feature,
               t_buf_weight& weights,
               t_buf_bias& bias)
  {
    // ...
  }

  // ---------------------------------------------------------------
  // Total Memory needs to string
  // ---------------------------------------------------------------

#ifndef __SYNTHESIS__
  std::string infoMemory() const
  {
    std::stringstream ss;
    ss << "[Memory needs] Relu Layer" << std::endl;
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
  }
#endif
};

#endif // RELU_H