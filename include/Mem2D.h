/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Mem2D.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Tue Sep 12 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef MEM2D_H
#define MEM2D_H

#include <MemBase.h>

template<int S1, int S2, typename T = double, int START_OFFSET = 0>
class Mem2D : public MemBase<S1 * S2, T, START_OFFSET>
{

public:
  static const int SIZE1 = S1;
  static const int SIZE2 = S2;

  typedef MemBase<S1 * S2, T, START_OFFSET> t_base;
  typedef Mem2D<S1, S2, T, START_OFFSET> t_this;

  using t_base::data;
  using t_base::get;
  using t_base::OFFSET;
  using t_base::SIZE;
  using t_base::WORDS;
  using t_base::operator=;
  using t_base::operator==;
  using t_base::operator();
  using typename t_base::t_data;

public:
  // ---------------------------------------------------------------
  // Constructors
  // ---------------------------------------------------------------

  Mem2D(T* input)
    : t_base(input)
  {
  }

  Mem2D(const Mem2D& input)
    : t_base(input)
  {
  }

  // ---------------------------------------------------------------
  // Get data from the local buffer
  // ---------------------------------------------------------------

  const T get(int r, int c) const
  {
    hls_assert(START_OFFSET + r * SIZE2 + c < SIZE);
    return data[START_OFFSET + r * SIZE2 + c];
  }

  T& operator()(int r, int c) { return get(r, c); }

  // ---------------------------------------------------------------
  // Get reference data from the local buffer
  // ---------------------------------------------------------------

  T& get(int r, int c)
  {
    hls_assert(START_OFFSET + r * SIZE2 + c < SIZE);
    return data[START_OFFSET + r * SIZE2 + c];
  }

  const T operator()(int r, int c) const { return get(r, c); }

  // ---------------------------------------------------------------
  // Load data from array 2D
  // ---------------------------------------------------------------

  void loadFromArray(T input[SIZE1][SIZE2])
  {
  LOAD1:
    for (int i = 0; i < SIZE1; i++) {
    LOAD2:
      for (int j = 0; j < SIZE2; j++) {
        get(i, j) = input[i][j];
      }
    }
  }

  // ---------------------------------------------------------------
  // Load data from array 1D
  // ---------------------------------------------------------------

  void loadFromArray(T input[SIZE])
  {
  LOAD:
    for (int i = START_OFFSET; i < SIZE; i++) {
      data[i] = input[i];
    }
  }

#ifndef __SYNTHESIS__
  // ---------------------------------------------------------------
  // Get Mem infos in string
  // ---------------------------------------------------------------

  std::string getInfo() const
  {
    std::ostringstream os;
    os << "Mem2D<" << SIZE1 << ", " << SIZE2 << ", " << sizeof(T) << " bytes, "
       << START_OFFSET << " offset>" << std::endl;
    os << " - " << SIZE1 << " x " << SIZE2 << " = " << WORDS << " words"
       << std::endl;
    os << " - " << DisplayMemSize::showWords<t_this>() << std::endl;
    os << std::endl;
    return os.str();
  }

  // ---------------------------------------------------------------
  // Operator << for printing (display size1 index)
  // ---------------------------------------------------------------

  friend std::ostream& operator<<(std::ostream& os, const Mem2D& input)
  {
  PRINT_ROW:
    for (int r = 0; r < SIZE1; r++) {
      os << "[" << r << "] : [";
    PRINT_COL:
      for (int c = 0; c < SIZE2; c++) {
        os << input.get(r, c);
        if (c != SIZE2 - 1) {
          os << ", ";
        }
      }
      os << "]" << std::endl;
    }
    return os;
  }
#endif

}; // class Mem2D

#endif
