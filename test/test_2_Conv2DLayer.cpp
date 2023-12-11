/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_Conv2DBufferLayer.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Jun 04 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <Conv2DBuffer.h>
#include <List1DJson.h>
#include <MultiMap2DJson.h>
#include <OpBias.h>
#include <StimRefPath.h>
#include <gtest/gtest.h>
#include <iostream>

// ---------------------------------------------------------------
class TestConv2DBufferLayer : public ::testing::Test
{
public:
  static const int KSIZE = 3;
  static const int HEIGHT = 28;
  static const int WIDTH = 28;
  static const int IN_FMAP = 1;
  static const int OUT_FMAP = 32;
  static const int START_OFFSET = 0;

  typedef Conv2DBuffer<HEIGHT,
                       WIDTH,
                       IN_FMAP,
                       OUT_FMAP,
                       KSIZE,
                       double,
                       OpBias<double>,
                       START_OFFSET>
    t_conv2D;

  t_conv2D conv2D;

  MultiMap2DJson<double> inFmap;
  MultiMap2DJson<double> outFmap;
  MultiMap2DJson<double> weights;
  List1DJson<double> bias;

  double* array_shared;
  double* array_ref;

  TestConv2DBufferLayer()
  {
    // initialisation commune aux tests
    array_shared = new double[t_conv2D::SIZE];
    array_ref = new double[t_conv2D::t_buf_feature_out::SIZE];
  }

  ~TestConv2DBufferLayer()
  {
    // nettoyage après les tests
    delete[] array_shared;
    delete[] array_ref;
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
};

// ---------------------------------------------------------------
TEST_F(TestConv2DBufferLayer, Conv2DBufferWithStimRef)
{
  // -------------
  // Load Stim Ref
  // -------------

  inFmap.loadJson(
    StimRefPath::getFmap("layer_1_image_1_input_feature_maps.json"));
  outFmap.loadJson(
    StimRefPath::getFmap("layer_1_image_1_output_feature_maps.json"));
  weights.loadJson(StimRefPath::getCoef("layer_1_conv_weights_reordered.json"));
  bias.loadJson(StimRefPath::getCoef("layer_1_conv_bias.json"));

  std::cout << std::endl;
  std::cout << "Input FMAP  : " << inFmap.info() << std::endl;
  std::cout << "Output FMAP : " << outFmap.info() << std::endl;
  std::cout << "Bias        : " << bias.info() << std::endl;
  std::cout << "Weights     : " << weights.info() << std::endl;
  std::cout << std::endl;

  // std::cout << weights << std::endl;

  std::cout << conv2D.infoMemory() << std::endl;

  // ---------------------

  t_conv2D::t_buf_feature_in mem_in(array_shared);
  t_conv2D::t_buf_weight mem_weight(array_shared);
  t_conv2D::t_buf_bias mem_bias(array_shared);
  t_conv2D::t_buf_feature_out mem_out(array_shared);

  t_conv2D::t_buf_feature_ref mem_ref_out(array_ref);

  // ----------------------
  // Copy features to array
  // ----------------------

  inFmap.exportToArray(mem_in);
  weights.exportToArray(mem_weight);
  bias.exportToArray(mem_bias);
  outFmap.exportToArray(mem_ref_out);

  // std::cout << mem_weight << std::endl;

  // ----------------------
  // Process convolution 2D
  // ----------------------

  conv2D.process(mem_in, mem_weight, mem_bias, mem_out);

  // ----------------------------------------
  // Compare output feature maps with stimref
  // ----------------------------------------
#if 0
  std::cout << "Output FW result : " << std::setprecision(8) << std::fixed
            << mem_out << std::endl;
  std::cout << "Output FW reference : " << std::setprecision(8) << std::fixed
             << mem_ref_out << std::endl;
#endif

  EXPECT_FALSE(mem_out.isEmpty());
  EXPECT_TRUE(mem_out.equals(mem_ref_out, 1e-6));
}
