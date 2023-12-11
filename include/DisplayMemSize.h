/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : DisplayMemSize.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 24 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef __DISPLAY_MEM_SIZE_H__
#define __DISPLAY_MEM_SIZE_H__

#include <iomanip>
#include <iostream>
#include <sstream>

class DisplayMemSize
{
  template<typename t_mem>
  static std::string toString(long SIZE)
  {
    std::stringstream ss;
    long word_bytes = sizeof(typename t_mem::t_data);
    long size = SIZE * word_bytes;
    float size_kb = size / 1024.0;
    float size_mb = size_kb / 1024.0;
    float size_gb = size_mb / 1024.0;
    ss << std::right << std::setw(10) << SIZE << " x " << word_bytes
       << " Bytes = ";
    ss << std::setprecision(3);
    if (size_gb > 1)
      ss << std::right << std::setw(8) << size_gb << " Go";
    else if (size_mb > 1)
      ss << std::right << std::setw(8) << size_mb << " Mo";
    else if (size_kb > 1)
      ss << std::right << std::setw(8) << size_kb << " Ko";
    else
      ss << std::right << std::setw(8) << size << " o";
    return ss.str();
  }

public:
  template<typename t_mem>
  static std::string showWords()
  {
    return DisplayMemSize::toString<t_mem>(t_mem::WORDS);
  }
  template<typename t_mem>
  static std::string showTotal(long OFFSET = 0)
  {
    return DisplayMemSize::toString<t_mem>(t_mem::SIZE - OFFSET);
  }
  template<typename t_mem>
  static std::string showSum()
  {
    return DisplayMemSize::toString<t_mem>(t_mem::SIZE);
  }
};

#endif
