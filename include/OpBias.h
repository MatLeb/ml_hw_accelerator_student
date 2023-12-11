/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : OpBias.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Jun 18 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef OP_BIAS_H
#define OP_BIAS_H

template<typename T>
struct OpBias
{
  T bias;

  OpBias(T bias)
    : bias(bias)
  {
  }

  T operator()(T& data) const
  {
    T res = data + bias;
    T zero = (T)0.0;
    if (res < zero)
      res = zero;
    return res;
  }
};

#endif // BIAS_OP_H
