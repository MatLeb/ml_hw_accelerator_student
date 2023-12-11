/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Mem1D.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Fri Sep 15 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef _INCLUDED_MEM1D_H_
#define _INCLUDED_MEM1D_H_

#include <MemBase.h>

template<int S1, typename T = double, int START_OFFSET = 0>
class Mem1D : public MemBase<S1, T, START_OFFSET>
{
public:
  typedef MemBase<S1, T, START_OFFSET> t_base;

  using t_base::data;
  using t_base::get;
  using t_base::OFFSET;
  using t_base::SIZE;
  using t_base::WORDS;
  using t_base::operator=;
  using t_base::operator==;
  using t_base::operator();

  typedef Mem1D<S1, T, START_OFFSET> t_this;

public:
  // ---------------------------------------------------------------
  // Constructors
  // ---------------------------------------------------------------

  Mem1D(T* input)
    : t_base(input)
  {
  }

  Mem1D(const Mem1D& input)
    : t_base(input)
  {
  }

  // ---------------------------------------------------------------
  // Get max position
  // ---------------------------------------------------------------

  int getMaxPos() const
  {
    int pos = 0;
    T max = get(0);
  MAX:
    for (int i = 1; i < WORDS; i++) {
      if (get(i) > max) {
        max = get(i);
        pos = i;
      }
    }
    return pos;
  }

#ifndef __SYNTHESIS__
  // ---------------------------------------------------------------
  // Get Mem infos in string
  // ---------------------------------------------------------------

  std::string getInfo() const
  {
    std::ostringstream os;
    os << "Mem1D<" << WORDS << ", " << sizeof(T) << " bytes, " << START_OFFSET
       << " offset>" << std::endl;
    os << " - " << WORDS << " words " << std::endl;
    os << " - " << DisplayMemSize::showWords<t_this>() << std::endl;
    os << std::endl;
    return os.str();
  }

  // ---------------------------------------------------------------
  // Operator << for printing (display size1 index)
  // ---------------------------------------------------------------

  friend std::ostream& operator<<(std::ostream& os, const Mem1D& input)
  {
  PRINT:
    os << "[";
    for (int r = 0; r < WORDS; r++) {
      os << input.get(r);
      if (r != WORDS - 1) {
        os << ", ";
      }
    }
    os << "]" << std::endl;
    return os;
  }
#endif
};

#endif
