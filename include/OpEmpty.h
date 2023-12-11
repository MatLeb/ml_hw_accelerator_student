/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : OpEmpty.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Jun 18 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef OP_EMPTY_H
#define OP_EMPTY_H

template<typename T>
struct OpEmpty
{
  OpEmpty(T bias) {}

  T operator()(T& data) const { return data; }
};

#endif
