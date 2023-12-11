/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : List2DJson.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Jun 18 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef _INCLUDED_LIST2DJSON_H_
#define _INCLUDED_LIST2DJSON_H_

#include <BaseJson.h>
#include <Mem2D.h>

template<typename T = double>
class List2DJson : public BaseJson
{
  // List type for all input/output feature maps
  typedef std::list<T> t_list1d;
  typedef std::list<t_list1d> t_list;

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
  // Export to array
  // ---------------------------------------------------------------

  template<int SIZE1, int SIZE2>
  void exportToArray(T array[SIZE1][SIZE2])
  {
    int idx_group = 0;
    for (auto& b : data) {
      int idx = 0;
      for (auto& d : b) {
        array[idx_group][idx] = d;
        idx++;
      }
      idx_group++;
    }
  }

  // -----------------------------------------------:----------------
  // Export to Mem2D
  // ---------------------------------------------------------------

  template<int SIZE1, int SIZE2, int OFFSET>
  void exportToArray(Mem2D<SIZE1, SIZE2, T, OFFSET>& mem)
  {
    int idx_group = 0;
    for (auto& b : data) {
      int idx = 0;
      for (auto& d : b) {
        mem(idx_group, idx) = d;
        idx++;
      }
      idx_group++;
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
      for (auto& d : b) {
        convert::ieee_float<t_data> conv;
        channel.Push(conv(d));
      }
    }
  }
#endif

  // ---------------------------------------------------------------
  // Display type + size
  // ---------------------------------------------------------------

  std::string info() const
  {
    std::stringstream os;
    os << "List2DJson ";
    os << "[" << data.size() << "]";
    os << "[" << data.front().size() << "]" << std::endl;
    return os.str();
  }

  // ---------------------------------------------------------------
  // Operator << for printing
  // ---------------------------------------------------------------
  friend std::ostream& operator<<(std::ostream& os, const List2DJson& buf)
  {
    os << buf.info() << std::endl;
    os << "Data: ";
    int idx_group = 0;
    for (auto& b : buf.data) {
      os << std::endl << idx_group << ")";
      idx_group++;
      int idx = 0;
      for (auto& d : b) {
        os << " " << d;
        idx++;
      }
    }
    os << std::endl;
    return os;
  }
};

#endif // _INCLUDED_LIST2DJSON_H_