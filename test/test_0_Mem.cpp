/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_0_Mem.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Tue Sep 12 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <Mem1D.h>
#include <Mem2D.h>
#include <Mem3D.h>
#include <Mem4D.h>
#include <gtest/gtest.h>

// ---------------------------------------------------------------

class MemTest : public ::testing::Test
{
public:
  static const int START_OFFSET = 10;
  static const int SIZE1 = 4;
  static const int SIZE2 = 4;
  static const int SIZE3 = 3;
  static const int SIZE4 = 2;

  typedef Mem1D<SIZE2, double, START_OFFSET> t_mem1d;
  typedef Mem2D<SIZE2, SIZE1, double, START_OFFSET> t_mem2d;
  typedef Mem3D<SIZE3, SIZE2, SIZE1, double, START_OFFSET> t_mem3d;
  typedef Mem4D<SIZE4, SIZE3, SIZE2, SIZE1, double, START_OFFSET> t_mem4d;

  t_mem1d::t_data array1[t_mem1d::SIZE];
  t_mem2d::t_data array2[t_mem2d::SIZE];
  t_mem3d::t_data array3[t_mem3d::SIZE];
  t_mem4d::t_data array4[t_mem4d::SIZE];

  double ref1d[SIZE2];
  double ref2d[SIZE2][SIZE1];
  double ref3d[SIZE3][SIZE2][SIZE1];
  double ref4d[SIZE4][SIZE3][SIZE2][SIZE1];

  double single_ref1d[START_OFFSET + SIZE2];
  double single_ref2d[START_OFFSET + SIZE2 * SIZE1];
  double single_ref3d[START_OFFSET + SIZE3 * SIZE2 * SIZE1];
  double single_ref4d[START_OFFSET + SIZE4 * SIZE3 * SIZE2 * SIZE1];

  MemTest()
  {
    // ---------------------------------
    // initialisation commune aux tests
    // ---------------------------------

    // init ref1d and single_ref1d with cpt
    int cpt = 0;
    for (int r = 0; r < SIZE2; r++) {
      ref1d[r] = cpt;
      single_ref1d[START_OFFSET + cpt++] = cpt;
    }

    // init single_ref2d with value 2.0
    for (int i = 0; i < START_OFFSET + SIZE2 * SIZE1; i++) {
      single_ref2d[i] = 2.0;
    }

    // init ref2d and sigle_ref2d with cpt
    cpt = 0;
    for (int r = 0; r < SIZE2; r++) {
      for (int c = 0; c < SIZE1; c++) {
        ref2d[r][c] = cpt;
        single_ref2d[START_OFFSET + cpt++] = cpt;
      }
    }
    // init ref3d and sigle_ref3d with cpt
    cpt = 0;
    for (int d = 0; d < SIZE3; d++) {
      for (int r = 0; r < SIZE2; r++) {
        for (int c = 0; c < SIZE1; c++) {
          ref3d[d][r][c] = cpt;
          single_ref3d[START_OFFSET + cpt++] = cpt;
        }
      }
    }
    // init ref4d and sigle_ref4d with cpt
    cpt = 0;
    for (int d = 0; d < SIZE4; d++) {
      for (int d2 = 0; d2 < SIZE3; d2++) {
        for (int r = 0; r < SIZE2; r++) {
          for (int c = 0; c < SIZE1; c++) {
            ref4d[d][d2][r][c] = cpt;
            single_ref4d[START_OFFSET + cpt++] = cpt;
          }
        }
      }
    }
  }

  ~MemTest()
  {
    // nettoyage après les tests
  }

  void SetUp() override
  {
    // initialisation avant chaque test
  }

  void TearDown() override
  {
    // nettoyage après chaque test
  }
};
// ---------------------------------------------------------------

TEST_F(MemTest, test_mem1D_read_write)
{
  t_mem1d mem1(array1);

  // write SIZE elements using () operator 2D
  for (int r = 0; r < SIZE1; r++) {
    mem1(r) = ref1d[r];
  }

  // check SIZE elements using () operator 2D
  for (int r = 0; r < SIZE1; r++) {
    EXPECT_EQ(mem1(r), ref1d[r]);
  }
}

// ---------------------------------------------------------------

TEST_F(MemTest, test_mem1D_init)
{
  t_mem1d mem2(single_ref1d);
  t_mem1d mem1(array1);
  mem1.loadFromArray(ref1d);

  std::cout << mem1;
  std::cout << mem2 << std::endl;

  std::cout << mem1.getInfo() << std::endl;

  EXPECT_TRUE(mem1 == mem2);
}

// ---------------------------------------------------------------

TEST_F(MemTest, test_mem1D_copy)
{
  t_mem1d mem1(array1);
  t_mem1d mem2(array1);

  mem1.loadFromArray(ref1d);
  mem2 = mem1;

  EXPECT_TRUE(mem1 == mem2);
}

// ---------------------------------------------------------------

TEST_F(MemTest, test_mem2D_read_write)
{
  t_mem2d mem1(array2);

  // write SIZE elements using () operator 2D
  for (int r = 0; r < SIZE1; r++) {
    for (int c = 0; c < SIZE2; c++) {
      mem1(r, c) = ref2d[r][c];
    }
  }

  // check SIZE elements using () operator 2D
  for (int r = 0; r < SIZE1; r++) {
    for (int c = 0; c < SIZE2; c++) {
      EXPECT_EQ(mem1(r, c), ref2d[r][c]);
    }
  }
}

// ---------------------------------------------------------------

TEST_F(MemTest, test_mem2D_init)
{
  t_mem2d mem2(single_ref2d);
  t_mem2d mem1(array2);
  mem1.loadFromArray(ref2d);

  std::cout << mem1 << std::endl;

  std::cout << mem1.getInfo() << std::endl;

  EXPECT_TRUE(mem1 == mem2);
}

// ---------------------------------------------------------------

TEST_F(MemTest, test_mem2D_copy)
{
  t_mem2d mem1(array2);
  t_mem2d mem2(array2);

  mem1.loadFromArray(ref2d);
  mem2 = mem1;

  EXPECT_TRUE(mem1 == mem2);
}

// ---------------------------------------------------------------

TEST_F(MemTest, test_mem3D_init)
{
  t_mem3d mem2(single_ref3d);
  t_mem3d mem1(array3);
  mem1.loadFromArray(ref3d);

  std::cout << mem1 << std::endl;

  std::cout << mem1.getInfo() << std::endl;

  EXPECT_TRUE(mem1 == mem2);
}

// ---------------------------------------------------------------

TEST_F(MemTest, test_mem3D_copy)
{
  t_mem3d mem1(array3);
  t_mem3d mem2(array3);

  mem1.loadFromArray(ref3d);
  mem2 = mem1;

  EXPECT_TRUE(mem1 == mem2);
}

// ---------------------------------------------------------------

TEST_F(MemTest, test_mem4D_init)
{
  t_mem4d mem2(single_ref4d);
  t_mem4d mem1(array4);
  mem1.loadFromArray(ref4d);

  std::cout << mem1 << std::endl;

  std::cout << mem1.getInfo() << std::endl;

  EXPECT_TRUE(mem1 == mem2);
}

// ---------------------------------------------------------------

TEST_F(MemTest, test_mem4D_copy)
{
  t_mem4d mem1(array4);
  t_mem4d mem2(array4);

  mem1.loadFromArray(ref4d);
  mem2 = mem1;

  EXPECT_TRUE(mem1 == mem2);
}
// ---------------------------------------------------------------

TEST_F(MemTest, test_mem_concat)
{
  typedef Mem2D<2, 2, double, 10> t_m2d;
  typedef Mem3D<2, 2, 2, double, t_m2d::SIZE> t_m3d;
  typedef Mem4D<2, 2, 2, 2, double, t_m3d::SIZE> t_m4d;

  double buf[t_m4d::SIZE];
  double ref[t_m4d::SIZE];

  t_m2d mem2d(buf);
  t_m3d mem3d(buf);
  t_m4d mem4d(buf);

  std::cout << mem2d.getInfo() << std::endl;
  std::cout << mem3d.getInfo() << std::endl;
  std::cout << mem4d.getInfo() << std::endl;

  // init buf with value 256.0
  for (int i = 0; i < t_m4d::SIZE; i++) {
    buf[i] = 256.0;
    ref[i] = 256.0;
  }
  // init ref with counter
  for (int i = 10; i < t_m4d::SIZE; i++) {
    ref[i] = i;
  }

  int cpt = 10;
  // init mem2d with cpt
  for (int r = 0; r < t_m2d::SIZE2; r++) {
    for (int c = 0; c < t_m2d::SIZE1; c++) {
      mem2d(r, c) = cpt++;
    }
  }
  // init mem3d with cpt
  for (int d = 0; d < t_m3d::SIZE3; d++) {
    for (int r = 0; r < t_m3d::SIZE2; r++) {
      for (int c = 0; c < t_m3d::SIZE1; c++) {
        mem3d(d, r, c) = cpt++;
      }
    }
  }
  // init mem4d with cpt
  for (int d = 0; d < t_m4d::SIZE4; d++) {
    for (int d2 = 0; d2 < t_m4d::SIZE3; d2++) {
      for (int r = 0; r < t_m4d::SIZE2; r++) {
        for (int c = 0; c < t_m4d::SIZE1; c++) {
          mem4d(d, d2, r, c) = cpt++;
        }
      }
    }
  }

  // display buf values with index
  for (int i = 0; i < t_m4d::SIZE; i++) {
    std::cout << i << ") " << buf[i] << std::endl;
  }

  // check buf equals 256.0
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(buf[i], 256.0);
  }
  // check buf equals counter
  for (int i = 10; i < t_m4d::SIZE; i++) {
    EXPECT_EQ(buf[i], ref[i]);
  }
}
// ---------------------------------------------------------------