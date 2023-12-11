/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : BufferSerialize.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Jun 18 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef BUFFER_SERIALIZE_H
#define BUFFER_SERIALIZE_H

#include <Buffer2D.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template<typename T, int HEIGHT, int WIDTH>
void
to_json(json& j, const Buffer2D<T, HEIGHT, WIDTH>& b)
{
  typedef std::vector<std::vector<T>> t_buf;
  t_buf buf;

  // Copy data from b to buf
  for (int r = 0; r < HEIGHT; r++) {
    std::vector<T> row;
    for (int c = 0; c < WIDTH; c++) {
      row.push_back(b.get(r, c));
    }
    buf.push_back(row);
  }

  // Write buf to json
  j = buf;
}

template<typename T, int HEIGHT, int WIDTH>
void
from_json(const json& j, Buffer2D<T, HEIGHT, WIDTH>& b)
{
  if (HEIGHT == 1 && WIDTH == 1) {

    b.get(0, 0) = j.get<T>();

  } else {

    typedef std::vector<std::vector<T>> t_buf;
    t_buf buf;

    // Read buf from json
    buf = j.template get<t_buf>();

    // Copy data from buf to b
    for (int r = 0; r < HEIGHT; r++) {
      for (int c = 0; c < WIDTH; c++) {
        b.get(r, c) = buf[r][c];
      }
    }
  }
}

#endif // BUFFER_SERIALIZE_H