/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : MemBase.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Nov 05 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef MEMBASE_H
#define MEMBASE_H

#ifndef __SYNTHESIS__
#include <iostream>
#include <sstream>
#endif
#include <DisplayMemSize.h>
#include <HlsAssert.h>

template<int S1, typename T = double, int START_OFFSET = 0>
class MemBase
{
public:
  static const int WORDS = S1;
  static const int SIZE = WORDS + START_OFFSET;
  static const int OFFSET = START_OFFSET;

  typedef T t_data;

  T* data;

  MemBase(T* input)
    : data(input)
  {
  }

  MemBase(const MemBase& input)
    : data(input.data)
  {
  }

  // ---------------------------------------------------------------
  // Get internal data pointer
  // ---------------------------------------------------------------

  T* getMem() { return data; }
  T* getArray() { return data; }

  // ---------------------------------------------------------------
  // Copy Operator
  // ---------------------------------------------------------------

  MemBase& operator=(const MemBase& input)
  {
  COPY:
    for (int i = 0; i < WORDS; i++) {
      get(i) = input.get(i);
    }
    return *this;
  }

  // ---------------------------------------------------------------
  // Get data from the local buffer
  // ---------------------------------------------------------------

  const T get(int i) const
  {
    hls_assert(i + START_OFFSET < SIZE);
    return data[START_OFFSET + i];
  }

  // ---------------------------------------------------------------
  // Get reference to data from the local buffer
  // ---------------------------------------------------------------

  T& get(int i)
  {
    hls_assert(i + START_OFFSET < SIZE);
    return data[START_OFFSET + i];
  }

  // ---------------------------------------------------------------
  // Operator () for accessing data reference
  // ---------------------------------------------------------------

  T& operator()(int i) { return get(i); }

  // ---------------------------------------------------------------
  // Const operator () for accessing data
  // ---------------------------------------------------------------

  const T operator()(int i) const { return get(i); }

  // ---------------------------------------------------------------
  // Load data from channel
  // ---------------------------------------------------------------

  template<typename t_chan>
  void loadFromChannel(t_chan& input)
  {
  LOAD_CHAN:
    for (int i = 0; i < WORDS; i++) {
      get(i) = input.Pop();
    }
  }

  // ---------------------------------------------------------------
  // Dump data to channel
  // ---------------------------------------------------------------

  template<typename t_chan>
  void exportToChannel(t_chan& output)
  {
  EXPORT_CHAN:
    for (int i = 0; i < WORDS; i++) {
      output.Push(get(i));
    }
  }

  // ---------------------------------------------------------------
  // Load data from array 1D
  // ---------------------------------------------------------------

  void loadFromArray(T input[WORDS])
  {
  LOAD:
    for (int i = 0; i < WORDS; i++) {
      get(i) = input[i];
    }
  }

  // ---------------------------------------------------------------
  // Reset local buffer
  // ---------------------------------------------------------------

  void reset()
  {
  RESET:
    for (int i = 0; i < WORDS; i++) {
      get(i) = (T)0.0;
    }
  }

  void noReset()
  {
    T dc;
  NO_RESET:
    for (int i = 0; i < WORDS; i++) {
      get(i) = dc;
    }
  }

  // ---------------------------------------------------------------
  // Operator Equal MemBase
  // ---------------------------------------------------------------

  template<int OFFSET>
  bool operator==(const MemBase<S1, T, OFFSET>& input) const
  {
  COMPARE:
    for (int i = 0; i < WORDS; i++) {
      if (get(i) != input(i)) {
        return false;
      }
    }
    return true;
  }

  // ---------------------------------------------------------------
  // Check equals Mem1D with tolerance
  // ---------------------------------------------------------------

  template<int OFFSET>
  bool equals(const MemBase<S1, T, OFFSET>& input, T tolerance) const
  {
  EQUALS:
    for (int i = 0; i < WORDS; i++) {
      if (get(i) - input(i) > tolerance) {
        return false;
      }
    }
    return true;
  }

  // ---------------------------------------------------------------
  // Check is empty
  // ---------------------------------------------------------------

  bool isEmpty() const
  {
  EMPTY:
    for (int i = 0; i < WORDS; i++) {
      if (get(i) != (T)0.0) {
        return false;
      }
    }
    return true;
  }
};

#endif
