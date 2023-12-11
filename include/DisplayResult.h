/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : DisplayResult.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sat Sep 09 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef DISPLAY_RESULT_H
#define DISPLAY_RESULT_H

#include <iostream>
#include <iomanip>
#include <sstream>

class DisplayResult
{
  int count = 0;
  double max_value = 0;
  int max_pos = 0;

public:
  // ------------------------------------
  // Find max value
  // ------------------------------------

  void update(double value)
  {
    if (value > max_value) {
      max_value = value;
      max_pos = count;
    }
    count++;
  }
  void show(std::string image_num) { show(image_num, max_pos); }

  // ------------------------------------
  // Show result with memory
  // ------------------------------------

  template<typename t_mem>
  static void show(std::string image_num, t_mem& mem)
  {
    int pos = mem.getMaxPos();
    show(image_num, pos);
  }

private:
  // ------------------------------------
  // Print result
  // ------------------------------------

  static void show(std::string image_num, int pos)
  {
    // switch translate pos to string (clothing type)
    std::string type;
    switch (pos) {
      case 0:
        type = "T-shirt/top";
        break;
      case 1:
        type = "Trouser";
        break;
      case 2:
        type = "Pullover";
        break;
      case 3:
        type = "Dress";
        break;
      case 4:
        type = "Coat";
        break;
      case 5:
        type = "Sandal";
        break;
      case 6:
        type = "Shirt";
        break;
      case 7:
        type = "Sneaker";
        break;
      case 8:
        type = "Bag";
        break;
      case 9:
        type = "Ankle boot";
        break;
      default:
        type = "Unknown";
        break;
    }
    // print result
    std::stringstream s1, s2, line;
    int width = 50;
    for (int i = 0; i < width; i++)
      line << "-";
    s1 << "The image " << image_num << " is a " << type;
    int wid = width - s1.str().length() / 2 - 3;
    int pad = width - wid - 2;
    s2 << std::setw(wid) << std::right << s1.str();
    for (int i = 0; i < pad; i++)
      s2 << " ";

    std::cout << line.str() << std::endl;
    std::cout << "|" << s2.str() << "|" << std::endl;
    std::cout << line.str() << std::endl;
    std::cout << std::endl;
  }
};

#endif // DISPLAY_RESULT_H