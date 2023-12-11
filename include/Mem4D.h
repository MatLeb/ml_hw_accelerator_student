/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Mem4D.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Tue Sep 12 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef MEM4D_H
#define MEM4D_H

#include <MemBase.h>

template<int S1,
         int S2,
         int S3,
         int S4,
         typename T = double,
         int START_OFFSET = 0>
class Mem4D : public MemBase<S1 * S2 * S3 * S4, T, START_OFFSET>
{
public:
  static const int SIZE1 = S1;
  static const int SIZE2 = S2;
  static const int SIZE3 = S3;
  static const int SIZE4 = S4;
  static const int SIZE_SUB1 = SIZE3 * SIZE4;
  static const int SIZE_SUB2 = SIZE2 * SIZE_SUB1;

  typedef MemBase<S1 * S2 * S3 * S4, T, START_OFFSET> t_base;
  typedef Mem4D<S1, S2, S3, S4, T, START_OFFSET> t_this;

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

  Mem4D(T* input)
    : t_base(input)
  {
  }

  Mem4D(const Mem4D& input)
    : t_base(input)
  {
  }

  // ---------------------------------------------------------------
  // Get data from the local buffer
  // ---------------------------------------------------------------

  const T get(int i, int j, int k, int l) const
  {
    hls_assert(START_OFFSET + i * SIZE_SUB2 + j * SIZE_SUB1 + k * SIZE4 + l <
               SIZE);
    return data[START_OFFSET + i * SIZE_SUB2 + j * SIZE_SUB1 + k * SIZE4 + l];
  }

  const T operator()(int i, int j, int k, int l) const
  {
    return get(i, j, k, l);
  }

  // ---------------------------------------------------------------
  // Get reference to data from the local buffer
  // ---------------------------------------------------------------

  T& get(int i, int j, int k, int l)
  {
    hls_assert(START_OFFSET + i * SIZE_SUB2 + j * SIZE_SUB1 + k * SIZE4 + l <
               SIZE);
    return data[START_OFFSET + i * SIZE_SUB2 + j * SIZE_SUB1 + k * SIZE4 + l];
  }

  T& operator()(int i, int j, int k, int l) { return get(i, j, k, l); }

  // ---------------------------------------------------------------
  // Load data from array 4D using get() method
  // ---------------------------------------------------------------

  void loadFromArray(T input[SIZE1][SIZE2][SIZE3][SIZE4])
  {
  LOAD:
    for (int i = 0; i < SIZE1; i++) {
      for (int j = 0; j < SIZE2; j++) {
        for (int k = 0; k < SIZE3; k++) {
          for (int l = 0; l < SIZE4; l++) {
            get(i, j, k, l) = input[i][j][k][l];
          }
        }
      }
    }
  }

#ifndef __SYNTHESIS__
  // ---------------------------------------------------------------
  // Get Mem infos in string
  // ---------------------------------------------------------------

  std::string getInfo() const
  {
    std::ostringstream os;
    os << "Mem4D<" << SIZE1 << ", " << SIZE2 << ", " << SIZE3 << ", " << SIZE4
       << ", " << sizeof(T) << " bytes, " << START_OFFSET << " offset>"
       << std::endl;
    os << " - " << SIZE1 << " x " << SIZE2 << " x " << SIZE3 << " x " << SIZE4
       << " = " << WORDS << " words" << std::endl;
    os << " - " << DisplayMemSize::showWords<t_this>() << std::endl;
    os << std::endl;
    return os.str();
  }

  // ---------------------------------------------------------------
  // Operator << for printing
  // ---------------------------------------------------------------

  friend std::ostream& operator<<(std::ostream& os, const Mem4D& mem)
  {
    for (int i = 0; i < SIZE1; i++) {
      os << "[" << i << "]" << std::endl;
      for (int j = 0; j < SIZE2; j++) {
        os << "     [" << j << "]" << std::endl;
        for (int k = 0; k < SIZE3; k++) {
          os << "         [" << k << "] : [";
          for (int l = 0; l < SIZE4; l++) {
            os << mem.get(i, j, k, l);
            if (l != SIZE4 - 1) {
              os << ", ";
            }
          }
          os << "]" << std::endl;
        }
      }
    }
    return os;
  }
#endif
};

#endif
