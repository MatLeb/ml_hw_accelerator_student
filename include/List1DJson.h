/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : List1DJson.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Jun 18 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef _INCLUDED_LIST1DJSON_H_
#define _INCLUDED_LIST1DJSON_H_

#include <BaseJson.h>
#include <Mem1D.h>

template<typename T = double>
class List1DJson : public BaseJson
{

  // List type for all input/output feature maps
  typedef std::list<T> t_list;

  t_list data;

public:
  using BaseJson::loadJson;

  // ---------------------------------------------------------------
  // Getters
  // ---------------------------------------------------------------

  t_list get() { return data; }

  // ---------------------------------------------------------------
  // Load data from json file
  // ---------------------------------------------------------------

  void loadJson(const char* filename) { BaseJson::loadJson(filename, data); }

  // ---------------------------------------------------------------
  // Export data to array
  // ---------------------------------------------------------------

  template<int SIZE>
  void exportToArray(T array[SIZE], int max = -1)
  {
    int idx = 0;
    for (auto& b : data) {
      array[idx] = b;
      idx++;
      if (idx == max)
        break;
    }
  }

  // ---------------------------------------------------------------
  // Export data to Mem1D
  // ---------------------------------------------------------------

  template<int SIZE, int OFFSET>
  void exportToArray(Mem1D<SIZE, T, OFFSET>& array, int max = -1)
  {
    int idx = 0;
    for (auto& b : data) {
      array(idx) = b;
      idx++;
      if (idx == max)
        break;
    }
  }

  // ---------------------------------------------------------------
  // Export data to Channel
  // ---------------------------------------------------------------

#ifdef __CONNECTIONS__CONNECTIONS_H__
  template<typename t_data>
  void exportToChannel(Connections::Combinational<t_data>& channel)
  {
    for (auto& b : data) {
      channel.Push((t_data)b);
    }
  }
#endif

  // ---------------------------------------------------------------
  // Display type + size
  // ---------------------------------------------------------------

  std::string info() const
  {
    std::stringstream os;
    os << "List1DJson ";
    os << "[" << data.size() << "]";
    return os.str();
  }

  // ---------------------------------------------------------------
  // Operator << for printing
  // ---------------------------------------------------------------
  friend std::ostream& operator<<(std::ostream& os, const List1DJson& buf)
  {
    os << buf.info() << std::endl;
    os << "Data: ";
    int idx = 0;
    for (auto& b : buf.data) {
      os << std::endl << idx << ") " << b;
      idx++;
    }
    os << std::endl;
    return os;
  }
};

#endif // _INCLUDED_LIST1DJSON_H_