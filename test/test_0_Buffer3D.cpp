/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_0_Buffer3D.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Wed Sep 13 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <Buffer3D.h>
#include <gtest/gtest.h>

// ---------------------------------------------------------------

class Buffer3DTest : public ::testing::Test
{
public:
  static const int START_OFFSET = 10;
  static const int FMAP = 2;
  static const int HEIGHT = 4;
  static const int WIDTH = 4;

  typedef Buffer3D<FMAP, HEIGHT, WIDTH, double, START_OFFSET> t_buf3d;

  double ref[FMAP][HEIGHT][WIDTH];
  double mem[START_OFFSET + FMAP * HEIGHT * WIDTH];
  int cpt;

  Buffer3DTest()
  {
    // ---------------------------------
    // initialisation commune aux tests
    // ---------------------------------

    // init single_ref with value 2.0
    for (int i = 0; i < START_OFFSET + FMAP * HEIGHT * WIDTH; i++) {
      mem[i] = 256.0;
    }

    cpt = 0;
    // init ref and sigle_ref with cpt
    for (int f = 0; f < FMAP; f++) {
      for (int h = 0; h < HEIGHT; h++) {
        for (int w = 0; w < WIDTH; w++) {
          ref[f][h][w] = cpt;
          mem[START_OFFSET + cpt] = cpt;
          cpt++;
        }
      }
    }
  }
};

// ---------------------------------------------------------------

TEST_F(Buffer3DTest, buffer3d_read_write)
{
  t_buf3d buf3d(mem);

  // check that the buffer is correctly initialized
  for (int f = 0; f < FMAP; f++) {
    for (int h = 0; h < HEIGHT; h++) {
      for (int w = 0; w < WIDTH; w++) {
        EXPECT_EQ(ref[f][h][w], buf3d(f, h, w));
      }
    }
  }
}

// ---------------------------------------------------------------

TEST_F(Buffer3DTest, buffer3d_copy_window)
{
  t_buf3d buf3d(mem);

  // display buf3d
  std::cout << buf3d << std::endl;

  // copy a window from buf3d to buf3d2
  Buffer3D<1, 2, 2, double, 0> buf3d2;

  // buf3d2.copyWindow from buf3d for each f,h,w
  for (int f = 0; f < FMAP; f++) {
    for (int h = 0; h < HEIGHT; h++) {
      for (int w = 0; w < WIDTH; w++) {
        buf3d2.copyWindow(buf3d, f, h, w);
        std::cout << buf3d2 << std::endl;
        std::cout << "max = " << buf3d2.getMaxValue() << std::endl;
      }
    }
  }

  EXPECT_EQ(buf3d.getMaxValue(), cpt - 1);
}

// ---------------------------------------------------------------

TEST_F(Buffer3DTest, buffer3d_copy_window_centered)
{
  t_buf3d buf3d(mem);

  // display buf3d
  std::cout << buf3d << std::endl;

  // copy a window from buf3d to buf3d2
  Buffer3D<1, 3, 3, double, 0> buf3d2;

  // buf3d2.copyWindow from buf3d for each f,h,w
  for (int f = 0; f < FMAP; f++) {
    for (int h = 0; h < HEIGHT; h++) {
      for (int w = 0; w < WIDTH; w++) {
        buf3d2.copyCenteredWindow(buf3d, f, h, w);
        std::cout << buf3d2 << std::endl;
        std::cout << "max = " << buf3d2.getMaxValue() << std::endl;
      }
    }
  }
}