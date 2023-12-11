/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Buffer3D.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Wed Sep 13 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef _INCLUDED_BUFFER3D_H_
#define _INCLUDED_BUFFER3D_H_

#include <Mem3D.h>

template<int FMAP,
         int HEIGHT,
         int WIDTH,
         typename T = double,
         int START_OFFSET = 0>
class Buffer3D
{
  typedef Buffer3D<FMAP, HEIGHT, WIDTH, T, START_OFFSET> t_this;
  typedef Mem3D<FMAP, HEIGHT, WIDTH, T, START_OFFSET> t_mem;
  t_mem mem;

public:
  typedef T t_data;
  static const int OFFSET = START_OFFSET;
  static const int WORDS = t_mem::WORDS;
  static const int SIZE = t_mem::SIZE;

  // ---------------------------------------------------------------
  // Constructors
  // ---------------------------------------------------------------

#if 1
  T data_local[SIZE];

  Buffer3D()
    : mem(data_local)
  {
  }
#endif

  Buffer3D(T* input)
    : mem(input)
  {
  }

  Buffer3D(const Buffer3D& input)
    : mem(input.mem)
  {
  }

  Buffer3D(const Mem3D<FMAP, HEIGHT, WIDTH, T, START_OFFSET>& input)
    : mem(input)
  {
  }

  // ---------------------------------------------------------------
  // Copy 2D array
  // ---------------------------------------------------------------

  void copy2Dfrom(const T input[HEIGHT][WIDTH])
  {
  HEIGHT_COPY:
    for (int h = 0; h < HEIGHT; h++) {
    WIDTH_COPY:
      for (int w = 0; w < WIDTH; w++) {
        mem(0, h, w) = input[h][w];
      }
    }
  }

  void export2Dto(T output[HEIGHT][WIDTH])
  {
  HEIGHT_COPY:
    for (int h = 0; h < HEIGHT; h++) {
    WIDTH_COPY:
      for (int w = 0; w < WIDTH; w++) {
        output[h][w] = mem(0, h, w);
      }
    }
  }

  // ---------------------------------------------------------------
  // Copy 3D array
  // ---------------------------------------------------------------

  void copy3Dfrom(const T input[FMAP][HEIGHT][WIDTH])
  {
  FMAP_COPY:
    for (int f = 0; f < FMAP; f++) {
    HEIGHT_COPY:
      for (int h = 0; h < HEIGHT; h++) {
      WIDTH_COPY:
        for (int w = 0; w < WIDTH; w++) {
          mem(f, h, w) = input[f][h][w];
        }
      }
    }
  }

  void export3Dto(T output[FMAP][HEIGHT][WIDTH])
  {
  FMAP_COPY:
    for (int f = 0; f < FMAP; f++) {
    HEIGHT_COPY:
      for (int h = 0; h < HEIGHT; h++) {
      WIDTH_COPY:
        for (int w = 0; w < WIDTH; w++) {
          output[f][h][w] = mem(f, h, w);
        }
      }
    }
  }

  // ---------------------------------------------------------------
  // Get internal memory
  // ---------------------------------------------------------------

  T* getArray() { return mem.getMem(); }

  t_mem& getMem() { return mem; }

  // ---------------------------------------------------------------
  // Reset internal memory
  // ---------------------------------------------------------------

  void reset() { mem.reset(); }

  // ---------------------------------------------------------------
  // Copy Operator
  // ---------------------------------------------------------------

  Buffer3D& operator=(const Buffer3D& input)
  {
#if 1
    mem = input.mem;
#else
  FMAP_COPY:
    for (int f = 0; f < FMAP; f++) {
    HEIGHT_COPY:
      for (int h = 0; h < HEIGHT; h++) {
      WIDTH_COPY:
        for (int w = 0; w < WIDTH; w++) {
          mem(f, h, w) = input(f, h, w);
        }
      }
    }
#endif
    return *this;
  }

  // ---------------------------------------------------------------
  // Access Operators
  // ---------------------------------------------------------------

  T& operator()(int f, int h, int w) { return mem(f, h, w); }

  const T operator()(int f, int h, int w) const { return mem(f, h, w); }

  T& operator()(int h, int w) { return mem(0, h, w); }

  const T operator()(int h, int w) const { return mem(0, h, w); }

  // ---------------------------------------------------------------
  // Copy window
  // ---------------------------------------------------------------

  template<int F1, int H1, int W1, typename T1, int S1>
  void copyWindow(const Buffer3D<F1, H1, W1, T1, S1>& input,
                  int f_start,
                  int h_start,
                  int w_start)
  {
  FMAP_COPY:
    for (int f = 0; f < FMAP; f++) {
    HEIGHT_COPY:
      for (int h = 0; h < HEIGHT; h++) {
      WIDTH_COPY:
        for (int w = 0; w < WIDTH; w++) {
          T data = (T)0.0;
          int fidx = f + f_start;
          int hidx = h + h_start;
          int widx = w + w_start;
          if (fidx >= 0 && fidx < F1 && hidx >= 0 && hidx < H1 && widx >= 0 &&
              widx < W1) {
            data = input(fidx, hidx, widx);
          }
          mem(f, h, w) = data;
        }
      }
    }
  }

  template<int F1, int H1, int W1, typename T1, int S1>
  void copyWindow(const Mem3D<F1, H1, W1, T1, S1>& input,
                  int f_start,
                  int h_start,
                  int w_start)
  {
    Buffer3D<F1, H1, W1, T1, S1> tmp(input);
    copyWindow(tmp, f_start, h_start, w_start);
  }

  // ---------------------------------------------------------------
  // Copy centered window
  // ---------------------------------------------------------------

  template<int F1, int H1, int W1, typename T1, int S1>
  void copyCenteredWindow(const Buffer3D<F1, H1, W1, T1, S1>& input,
                          int f_start,
                          int h_start,
                          int w_start)
  {
    int h_offset = HEIGHT / 2;
    int w_offset = WIDTH / 2;
    copyWindow(input, f_start, h_start - h_offset, w_start - w_offset);
  }

  // ---------------------------------------------------------------
  // Operator *
  // ---------------------------------------------------------------

  template<int F1, int H1, int W1, typename T1, int S1>
  Buffer3D operator*(const Buffer3D<F1, H1, W1, T1, S1>& input) const
  {
#if 0
    T array[SIZE];
    t_this output(array);
#else
    t_this output;
#endif
  FMAP_MULT:
    for (int f = 0; f < FMAP; f++) {
    HEIGHT_MULT:
      for (int h = 0; h < HEIGHT; h++) {
      WIDTH_MULT:
        for (int w = 0; w < WIDTH; w++) {
          output(f, h, w) = mem(f, h, w) * input(f, h, w);
        }
      }
    }
    return output;
  }

  // ---------------------------------------------------------------
  // Operator +=
  // ---------------------------------------------------------------

  template<int F1, int H1, int W1, typename T1, int S1>
  Buffer3D& operator+=(const Buffer3D<F1, H1, W1, T1, S1>& input)
  {
  FMAP_ADD:
    for (int f = 0; f < FMAP; f++) {
    HEIGHT_ADD:
      for (int h = 0; h < HEIGHT; h++) {
      WIDTH_ADD:
        for (int w = 0; w < WIDTH; w++) {
          mem(f, h, w) += input(f, h, w);
        }
      }
    }
    return *this;
  }

  // ---------------------------------------------------------------
  // Apply function
  // ---------------------------------------------------------------

  template<typename T1>
  void apply(T1 func)
  {
  FMAP_APPLY:
    for (int f = 0; f < FMAP; f++) {
    HEIGHT_APPLY:
      for (int h = 0; h < HEIGHT; h++) {
      WIDTH_APPLY:
        for (int w = 0; w < WIDTH; w++) {
          mem(f, h, w) = func(mem(f, h, w));
        }
      }
    }
  }

  // ---------------------------------------------------------------
  // Get max value of Buffer3D
  // ---------------------------------------------------------------

  T getMaxValue() const
  {
    T max = mem(0);
    for (int i = 0; i < mem.WORDS; i++) {
      if (mem(i) > max) {
        max = mem(i);
      }
    }
    return max;
  }

  // ---------------------------------------------------------------
  // Get sum of all elements
  // ---------------------------------------------------------------

  T getSum() const
  {
    T sum = (T)0.0;
    for (int i = 0; i < mem.SIZE; i++) {
      sum += mem(i);
    }
    return sum;
  }

  // ---------------------------------------------------------------
  // Operator ==
  // ---------------------------------------------------------------

  template<int OFFSET>
  bool operator==(Buffer3D<FMAP, HEIGHT, WIDTH, T, OFFSET>& input) const
  {
    return mem == input.getMem();
  }

  // ---------------------------------------------------------------
  // Check equals with tolerance
  // ---------------------------------------------------------------

  bool equals(const Buffer3D& input, T tolerance) const
  {
    return mem.equals(input.mem, tolerance);
  }

// ---------------------------------------------------------------
// Operator << for printing
// ---------------------------------------------------------------
#ifndef __SYNTHESIS__
  friend std::ostream& operator<<(std::ostream& os, const Buffer3D& buf)
  {
    os << buf.mem;
    return os;
  }
#endif
};

#endif
