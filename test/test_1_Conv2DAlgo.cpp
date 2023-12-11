/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_Conv2DArrayAlgo.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Jun 04 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <Conv2DArray.h>
#include <Eigen/Dense>
#include <gtest/gtest.h>
#include <iostream>

using namespace Eigen;

// ---------------------------------------------------------------
class TestConv2DArray : public ::testing::Test
{
public:
  TestConv2DArray()
  {
    // initialisation commune aux tests
  }

  ~TestConv2DArray()
  {
    // nettoyage après les tests
  }

  static void SetUpTestSuite()
  {
    // initialisation une fois pour la suite de tests
  }

  static void TearDownTestSuite()
  {
    // nettoyage une fois après la suite de tests
  }

  void SetUp() override
  {
    // initialisation avant chaque test
  }

  void TearDown() override
  {
    // nettoyage après chaque test
  }

  // Fonction de convolution 2D utilisant la librairie Eigen
  ArrayXXd convolve2D(const ArrayXXd& input, const ArrayXXd& filter)
  {
    int padding = filter.rows() / 2;

    Eigen::ArrayXXd padded_input = Eigen::ArrayXXd::Zero(
      input.rows() + padding * 2, input.cols() + padding * 2);
    padded_input.block(padding, padding, input.rows(), input.cols()) = input;

    Eigen::ArrayXXd output = Eigen::ArrayXXd::Zero(input.rows(), input.cols());

    for (int i = padding; i < padded_input.rows() - padding; i++) {
      for (int j = padding; j < padded_input.cols() - padding; j++) {
        Eigen::ArrayXXd input_patch = padded_input.block(
          i - padding, j - padding, filter.rows(), filter.cols());
        output(i - padding, j - padding) = (input_patch * filter).sum();
      }
    }

    return output;
  }
};

// ---------------------------------------------------------------
// Test de la convolution 2D avec un seul feature map
// Comparaison des résultats avec la librairie Eigen
// ---------------------------------------------------------------

TEST_F(TestConv2DArray, Convolution2D)
{
  ArrayXXd image(5, 5);
  image << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25;

  ArrayXXd filter(3, 3);
  filter << 1, 1, -1, 2, 1, -2, 1, 1, -1;

  ArrayXXd result = convolve2D(image, filter);

  Conv2DArray<5, 5, 1, 1, 3> conv2d;
  double in_fmaps[1][5][5];
  double kernel[1][1][3][3];
  double out_fmaps[1][5][5];

  // Initialisation des données
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      in_fmaps[0][r][c] = image(r, c);
    }
  }

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      kernel[0][0][r][c] = filter(r, c);
    }
  }

  // Convolution
  conv2d.process_array(in_fmaps, kernel, out_fmaps);

  // Comparaison des résultats
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      ASSERT_EQ(result(r, c), out_fmaps[0][r][c]);
    }
  }

  std::cout << "\nImage originale : \n" << image << std::endl;
  std::cout << "\nFiltre : \n" << filter << std::endl;
  std::cout << "\nResultat de la convolution avec Eigen : \n"
            << result << std::endl;

  Buffer3D<1, 5, 5> output_feature;
  output_feature.copy3Dfrom(out_fmaps);

  std::cout << "\nResultat de la convolution avec Conv2DArray : \n"
            << output_feature << std::endl;
}

// ---------------------------------------------------------------
// Test de la convolution 2D avec plusieurs feature maps
// Comparaison des résultats avec la librairie Eigen
// ---------------------------------------------------------------

TEST_F(TestConv2DArray, Convolution2D_MultiFeatures)
{
  ArrayXXd image1(5, 5);
  ArrayXXd image2(5, 5);

  image1 << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25;
  image2 << 10, 20, 30, 40, 50, 60, 70, 80, 90, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25;

  ArrayXXd filter1(3, 3);
  ArrayXXd filter2(3, 3);
  ArrayXXd filter3(3, 3);
  ArrayXXd filter4(3, 3);
  filter1 << 1, 1, -1, 2, 1, -2, 1, 1, -1;
  filter2 << 1, -1, -2, 1, 2, -1, 2, 1, -1;
  filter3 << 1, 1, -1, 3, 1, -2, 1, 4, -1;
  filter4 << 1, -1, -2, 4, 2, -1, 2, 2, -1;

  ArrayXXd resultOut1a = convolve2D(image1, filter1);
  ArrayXXd resultOut1b = convolve2D(image2, filter2);
  ArrayXXd resultOut2a = convolve2D(image1, filter3);
  ArrayXXd resultOut2b = convolve2D(image2, filter4);

  ArrayXXd result1 = resultOut1a + resultOut1b;
  ArrayXXd result2 = resultOut2a + resultOut2b;

  Conv2DArray<5, 5, 2, 2, 3> conv2d;
  double in_fmaps[2][5][5];
  double kernel[2][2][3][3];
  double out_fmaps[2][5][5];

  // Initialisation des données
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      in_fmaps[0][r][c] = image1(r, c);
      in_fmaps[1][r][c] = image2(r, c);
    }
  }

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      kernel[0][0][r][c] = filter1(r, c);
      kernel[0][1][r][c] = filter2(r, c);
      kernel[1][0][r][c] = filter3(r, c);
      kernel[1][1][r][c] = filter4(r, c);
    }
  }

  // Convolution
  conv2d.process_array(in_fmaps, kernel, out_fmaps);

  // Comparaison des résultats
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      ASSERT_EQ(result1(r, c), out_fmaps[0][r][c]);
      ASSERT_EQ(result2(r, c), out_fmaps[1][r][c]);
    }
  }

  // Comparaison des résultats
  Buffer3D<1, 5, 5> output_feature1, output_feature2;
  output_feature1.copy2Dfrom(out_fmaps[0]);
  output_feature2.copy2Dfrom(out_fmaps[1]);

  std::cout << "\nResultat de la convolution Out1 avec Eigen : \n"
            << result1 << std::endl;
  std::cout << "\nResultat de la convolution Out1 avec Conv2DArray : \n"
            << output_feature1 << std::endl;
  std::cout << "\nResultat de la convolution Out2 avec Eigen : \n"
            << result2 << std::endl;
  std::cout << "\nResultat de la convolution Out2 avec Conv2DArray : \n"
            << output_feature2 << std::endl;
}