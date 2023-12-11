/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : MultiMap2DJson.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 11 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef MULTIMAP2DJSON_H
#define MULTIMAP2DJSON_H

#include <BaseJson.h>
#include <Mem3D.h>
#include <Mem4D.h>
#include <map>
#include <list>
#include <deque>

template<typename T = double>
class MultiMap2DJson : public BaseJson
{

  typedef std::list<T> t_list1d;
  typedef std::list<t_list1d> t_list2d;
  typedef std::map<std::string, t_list2d> t_map;
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
  // Export to array
  // ---------------------------------------------------------------

  template<int SIZE1, int SIZE2, int SIZE3>
  void exportToArray(T array[SIZE1][SIZE2][SIZE3])
  {
    int idx_dim1 = 0;
    int idx_dim2 = 0;
    int idx_dim3 = 0;

    for (auto& dim1 : data) {
      if (idx_dim1 >= SIZE1)
        break;
      for (auto& dim2 : dim1) {
        int idx_dim3 = 0;
        for (auto& dim3 : dim2.second) {
          if (idx_dim3 >= SIZE2)
            break;
          int idx_dim4 = 0;
          for (auto& dim4 : dim3) {
            if (idx_dim4 >= SIZE3)
              break;
            array[idx_dim1][idx_dim3][idx_dim4] = dim4;
            idx_dim4++;
          }
          idx_dim3++;
        }
      }
      idx_dim1++;
    }
  }

  template<int SIZE1, int SIZE2, int SIZE3, int SIZE4>
  void exportToArray(T array[SIZE1][SIZE2][SIZE3][SIZE4])
  {
    int idx_dim1 = 0;
    int idx_dim2 = 0;
    int idx_dim3 = 0;
    int idx_dim4 = 0;

    for (auto& dim1 : data) {
      if (idx_dim1 >= SIZE1)
        break;
      int idx_dim2 = 0;
      for (auto& dim2 : dim1) {
        if (idx_dim2 >= SIZE2)
          break;
        int idx_dim3 = 0;
        for (auto& dim3 : dim2.second) {
          if (idx_dim3 >= SIZE3)
            break;
          int idx_dim4 = 0;
          for (auto& dim4 : dim3) {
            if (idx_dim4 >= SIZE4)
              break;
            array[idx_dim1][idx_dim2][idx_dim3][idx_dim4] = dim4;
            idx_dim4++;
          }
          idx_dim3++;
        }
        idx_dim2++;
      }
      idx_dim1++;
    }
  }

  // ---------------------------------------------------------------
  // Export to Mem3D
  // ---------------------------------------------------------------

  template<int SIZE1, int SIZE2, int SIZE3, typename T2, int OFFSET>
  void exportToArray(Mem3D<SIZE1, SIZE2, SIZE3, T2, OFFSET>& array)
  {
    int idx_dim1 = 0;
    for (auto& dim1 : data) {
      if (idx_dim1 >= SIZE1)
        break;
      for (auto& dim2 : dim1) {
        int idx_dim3 = 0;
        for (auto& dim3 : dim2.second) {
          if (idx_dim3 >= SIZE2)
            break;
          int idx_dim4 = 0;
          for (auto& dim4 : dim3) {
            if (idx_dim4 >= SIZE3)
              break;
            array(idx_dim1, idx_dim3, idx_dim4) = dim4;
            idx_dim4++;
          }
          idx_dim3++;
        }
      }
      idx_dim1++;
    }
  }

  // ---------------------------------------------------------------
  // Export to Mem4D
  // ---------------------------------------------------------------

  template<int SIZE1, int SIZE2, int SIZE3, int SIZE4, typename T2, int OFFSET>
  void exportToArray(Mem4D<SIZE1, SIZE2, SIZE3, SIZE4, T2, OFFSET>& array)
  {
    int idx_dim1 = 0;
    for (auto& dim1 : data) {
      if (idx_dim1 >= SIZE1)
        break;
      int idx_dim2 = 0;
      for (auto& dim2 : dim1) {
        if (idx_dim2 >= SIZE2)
          break;
        int idx_dim3 = 0;
        for (auto& dim3 : dim2.second) {
          if (idx_dim3 >= SIZE3)
            break;
          int idx_dim4 = 0;
          for (auto& dim4 : dim3) {
            if (idx_dim4 >= SIZE4)
              break;
            array(idx_dim1, idx_dim2, idx_dim3, idx_dim4) = dim4;
            idx_dim4++;
          }
          idx_dim3++;
        }
        idx_dim2++;
      }
      idx_dim1++;
    }
  }

  // ---------------------------------------------------------------
  // Export to Buffer3D
  // ---------------------------------------------------------------

  template<int SIZE1, int SIZE2, int SIZE3, typename T2, int OFFSET>
  void exportToArray(Buffer3D<SIZE1, SIZE2, SIZE3, T2, OFFSET>& array)
  {
    exportToArray(array.getMem());
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
        for (auto& dim3 : dim2.second) {
          for (auto& dim4 : dim3) {
            chan.Push((t_data)dim4);
          }
        }
      }
    }
  }
#endif
  template<typename t_data>
  void exportToChannel(std::deque<t_data>& chan)
  {
    for (auto& dim1 : data) {
      for (auto& dim2 : dim1) {
        for (auto& dim3 : dim2.second) {
          for (auto& dim4 : dim3) {
            chan.push_back((t_data)dim4);
          }
        }
      }
    }
  }

  // ---------------------------------------------------------------
  // Display type + size
  // ---------------------------------------------------------------

  std::string info() const
  {
    std::stringstream os;
    os << "MultiMap2DJson ";
    os << "[" << data.size() << "]";
    os << "[" << data.front().size() << "]";
    os << "[" << data.front().begin()->second.size() << "]";
    os << "[" << data.front().begin()->second.front().size() << "]";
    return os.str();
  }

  // ---------------------------------------------------------------
  // Operator << for printing
  // ---------------------------------------------------------------
  friend std::ostream& operator<<(std::ostream& os, const MultiMap2DJson& buf)
  {
    os << buf.info() << std::endl;
    int idx_dim1 = 0;
    for (auto& dim1 : buf.data) {
      os << std::endl << idx_dim1 << ")";
      idx_dim1++;
      for (auto& dim2 : dim1) {
        os << " " << dim2.first << std::endl;
        os << std::endl;
        int idx_dim3 = 0;
        for (auto& dim3 : dim2.second) {
          os << "     " << idx_dim3 << ")";
          idx_dim3++;
          for (auto& dim4 : dim3) {
            os << " " << dim4;
          }
          os << std::endl;
        }
      }
    }

    os << std::endl;
    return os;
  }
};

#endif
