/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : MultiMapJson.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 11 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef MULTIMAPJSON_H
#define MULTIMAPJSON_H

#include <BaseJson.h>
#include <Mem1D.h>
#include <map>
#include <deque>

template<typename T = double>
class MultiMapJson : public BaseJson
{

  typedef std::map<std::string, T> t_map;
  typedef std::list<t_map> t_top_list;

  t_top_list data;

public:
  using BaseJson::loadJson;

  // ---------------------------------------------------------------
  // Getters
  // ---------------------------------------------------------------

  t_top_list get() { return data; }

  // ---------------------------------------------------------------
  // Load data from json file
  // ---------------------------------------------------------------

  void loadJson(const char* filename) { BaseJson::loadJson(filename, data); }

  // ---------------------------------------------------------------
  // Export bias to array
  // ---------------------------------------------------------------

  template<int SIZE>
  void exportToArray(T array[SIZE])
  {
    int idx_dim1 = 0;
    for (auto& dim1 : data) {
      assert(idx_dim1 < SIZE);
      for (auto& dim2 : dim1) {
        array[idx_dim1] = dim2.second;
      }
      idx_dim1++;
    }
  }

  // ---------------------------------------------------------------
  // Export to Mem1D
  // ---------------------------------------------------------------

  template<int SIZE, int OFFSET>
  void exportToArray(Mem1D<SIZE, T, OFFSET>& array)
  {
    int idx_dim1 = 0;
    for (auto& dim1 : data) {
      assert(idx_dim1 < SIZE);
      for (auto& dim2 : dim1) {
        array(idx_dim1) = dim2.second;
      }
      idx_dim1++;
    }
  }

  // ---------------------------------------------------------------
  // Export to Channel
  // ---------------------------------------------------------------
#ifdef __CONNECTIONS__CONNECTIONS_H__
  template<typename t_data>
  void exportToChannel(Connections::Combinational<t_data>& chan)
  {
    for (auto& dim1 : data) {
      for (auto& dim2 : dim1) {
        chan.Push((t_data)dim2.second);
      }
    }
  }
#endif
  template<typename t_data>
  void exportToChannel(std::deque<t_data>& chan)
  {
    for (auto& dim1 : data) {
      for (auto& dim2 : dim1) {
        chan.push_back((t_data)dim2.second);
      }
    }
  }

  // ---------------------------------------------------------------
  // Display type + size
  // ---------------------------------------------------------------

  std::string info() const
  {
    std::stringstream os;
    os << "MultiMapJson ";
    os << "[" << data.size() << "]";
    return os.str();
  }

  // ---------------------------------------------------------------
  // Operator << for printing
  // ---------------------------------------------------------------
  friend std::ostream& operator<<(std::ostream& os, const MultiMapJson& buf)
  {
    os << buf.info() << std::endl;
    int idx_dim1 = 0;
    for (auto& dim1 : buf.data) {
      os << std::endl << idx_dim1 << ")";
      idx_dim1++;
      for (auto& dim2 : dim1) {
        os << " " << dim2.first << " : ";
        os << " " << dim2.second;
      }
    }
    os << std::endl;
    return os;
  }
};

#endif // MULTIMAPJSON_H