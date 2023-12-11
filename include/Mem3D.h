/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Mem3D.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Tue Sep 12 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef MEM3D_H
#define MEM3D_H

#include <MemBase.h>

template<int S1, int S2, int S3, typename T = double, int START_OFFSET = 0>
class Mem3D : public MemBase<S1 * S2 * S3, T, START_OFFSET>
{
public:
  static const int SIZE1 = S1;
  static const int SIZE2 = S2;
  static const int SIZE3 = S3;
  static const int SIZE_SUB = SIZE2 * SIZE3;

  typedef MemBase<S1 * S2 * S3, T, START_OFFSET> t_base;
  typedef Mem3D<S1, S2, S3, T, START_OFFSET> t_this;

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

  Mem3D(T* input)
    : t_base(input)
  {
  }

  Mem3D(const Mem3D& input)
    : t_base(input)
  {
  }

  // ---------------------------------------------------------------
  // Copy Operator
  // ---------------------------------------------------------------

  void copyTo(T* output)
  {
  COPY:
    for (int i = START_OFFSET; i < SIZE; i++) {
      output[i] = data[i];
    }
  }

  // ---------------------------------------------------------------
  // Get data from the local buffer
  // ---------------------------------------------------------------

  const T get(int i, int j, int k) const
  {
    hls_assert(START_OFFSET + i * SIZE_SUB + j * SIZE3 + k < SIZE);
    return data[START_OFFSET + i * SIZE_SUB + j * SIZE3 + k];
  }

  const T operator()(int i, int j, int k) const { return get(i, j, k); }

  // ---------------------------------------------------------------
  // Get reference data from the local buffer
  // ---------------------------------------------------------------

  T& get(int i, int j, int k)
  {
    hls_assert(START_OFFSET + i * SIZE_SUB + j * SIZE3 + k < SIZE);
    return data[START_OFFSET + i * SIZE_SUB + j * SIZE3 + k];
  }

  T& operator()(int i, int j, int k) { return get(i, j, k); }

  // ---------------------------------------------------------------
  // Load data from array 3D using get() method
  // ---------------------------------------------------------------

  void loadFromArray(T input[SIZE1][SIZE2][SIZE3])
  {
  LOAD:
    for (int i = 0; i < SIZE1; i++) {
      for (int j = 0; j < SIZE2; j++) {
        for (int k = 0; k < SIZE3; k++) {
          get(i, j, k) = input[i][j][k];
        }
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
    os << "Mem3D<" << SIZE1 << ", " << SIZE2 << ", " << SIZE3 << ", "
       << sizeof(T) << " bytes, " << START_OFFSET << " offset>" << std::endl;
    os << " - " << SIZE1 << " x " << SIZE2 << " x " << SIZE3 << " = " << WORDS
       << " words" << std::endl;
    os << " - " << DisplayMemSize::showWords<t_this>() << std::endl;
    return os.str();
  }

  // ---------------------------------------------------------------
  // Operator << for printing (display SIZE1 index and SIZE2 index)
  // ---------------------------------------------------------------

  friend std::ostream& operator<<(std::ostream& os, const Mem3D& mem)
  {
    std::ostringstream oss;
    for (int i = 0; i < SIZE1; i++) {
      oss << "[" << i << "]" << std::endl;
      for (int j = 0; j < SIZE2; j++) {
        oss << "     [" << j << "] : [";
        for (int k = 0; k < SIZE3; k++) {
          oss << mem.get(i, j, k);
          if (k != SIZE3 - 1) {
            oss << ", ";
          }
        }
        oss << "]" << std::endl;
      }
    }
    os << oss.str();
    return os;
  }
#endif
};
#endif // MEM3D_H
