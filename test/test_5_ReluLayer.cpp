/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_5_ReluLayer.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sat Sep 09 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <List1DJson.h>
#include <List2DJson.h>
#include <MultiMapJson.h>
#include <Relu.h>
#include <StimRefPath.h>
#include <gtest/gtest.h>

// ---------------------------------------------------------------

class TestReLuLayer : public ::testing::Test
{
public:
  static const int IN_HEIGHT = 6272;
  static const int OUT_HEIGHT = 32;
  static const int START_OFFSET = 0;

  typedef ReLu<IN_HEIGHT, OUT_HEIGHT, double, START_OFFSET> t_relu;
  t_relu relu;

  MultiMapJson<double> inFmap;
  MultiMapJson<double> outFmap;
  List1DJson<double> bias;
  List2DJson<double> weights;

  double* array_shared;
  double* array_ref;

  TestReLuLayer()
  {
    // initialisation commune aux tests
    array_shared = new double[t_relu::SIZE];
    array_ref = new double[t_relu::t_buf_feature_out::SIZE];
  }

  ~TestReLuLayer()
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

TEST_F(TestReLuLayer, TestRelu)
{
  // -------------
  // Load Stim Ref
  // -------------

  inFmap.loadJson(
    StimRefPath::getFmap("layer_4_image_1_output_feature_maps.json"));
  outFmap.loadJson(
    StimRefPath::getFmap("layer_5_image_1_output_feature_maps.json"));
  bias.loadJson(StimRefPath::getCoef("layer_5_relu_bias.json"));
  weights.loadJson(StimRefPath::getCoef("layer_5_relu_weights.json"));

  std::cout << std::endl;
  std::cout << "Input FMAP  : " << inFmap.info() << std::endl;
  std::cout << "Output FMAP : " << outFmap.info() << std::endl;
  std::cout << "Bias        : " << bias.info() << std::endl;
  std::cout << "Weights     : " << weights.info() << std::endl;
  std::cout << std::endl;

  // std::cout << "in fmap : " << inFmap << std::endl;
  // std::cout << "out fmap : " << outFmap << std::endl;
  // std::cout << "bias : " << bias << std::endl;
  // std::cout << "weights : " << weights << std::endl;

  std::cout << relu.infoMemory() << std::endl;

  // ----------------------
  // Copy features to array
  // ----------------------

  t_relu::t_buf_feature_in mem_in(array_shared);
  t_relu::t_buf_weight mem_weights(array_shared);
  t_relu::t_buf_bias mem_bias(array_shared);
  t_relu::t_buf_feature_out mem_out(array_shared);

  t_relu::t_buf_feature_ref mem_out_ref(array_ref);

  inFmap.exportToArray(mem_in);
  outFmap.exportToArray(mem_out_ref);
  bias.exportToArray(mem_bias);
  weights.exportToArray(mem_weights);

  // ----------------------

  relu.process(mem_in, mem_out, mem_weights, mem_bias);

  // ----------------------
  // Compare results
  // ----------------------
#if 0
  std::cout << "Output FW result : " << std::setprecision(8) << std::fixed
            << mem_out << std::endl;
  std::cout << "Output FW reference : " << std::setprecision(8) << std::fixed
            << mem_out_ref << std::endl;
#endif

  EXPECT_FALSE(mem_out.isEmpty());
  EXPECT_TRUE(mem_out.equals(mem_out_ref, 1e-4));
}