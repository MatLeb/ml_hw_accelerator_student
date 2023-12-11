/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_6_SoftmaxLayer.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 10 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <DisplayResult.h>
#include <List1DJson.h>
#include <List2DJson.h>
#include <MultiMapJson.h>
#include <Softmax.h>
#include <StimRefPath.h>
#include <gtest/gtest.h>

// ---------------------------------------------------------------

class TestSoftmaxLayer : public ::testing::Test
{
public:
  static const int IN_HEIGHT = 32;
  static const int OUT_HEIGHT = 10;
  static const int START_OFFSET = 0;

  typedef Softmax<IN_HEIGHT, OUT_HEIGHT, double, START_OFFSET> t_softmax;

  t_softmax softmax;

  MultiMapJson<double> inFmap;
  MultiMapJson<double> outFmap;
  List1DJson<double> bias;
  List2DJson<double> weights;

  double* array_shared;
  double* array_ref;

  TestSoftmaxLayer()
  {
    // initialisation commune aux test
    array_shared = new double[t_softmax::SIZE];
    array_ref = new double[t_softmax::t_buf_feature_out::SIZE];
  }

  ~TestSoftmaxLayer()
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

TEST_F(TestSoftmaxLayer, TestSoftmaxLayer)
{
  std::string image_num = "1";

  // -------------
  // Load Stim Ref
  // -------------

  inFmap.loadJson(StimRefPath::getFmap("layer_5_image_" + image_num +
                                       "_output_feature_maps.json"));

  outFmap.loadJson(StimRefPath::getFmap("layer_6_image_" + image_num +
                                        "_output_feature_maps.json"));

  bias.loadJson(StimRefPath::getCoef("layer_6_softmax_bias.json"));
  weights.loadJson(StimRefPath::getCoef("layer_6_softmax_weights.json"));

  std::cout << std::endl;
  std::cout << "Input FMAP  : " << inFmap.info() << std::endl;
  std::cout << "Output FMAP : " << outFmap.info() << std::endl;
  std::cout << "Bias        : " << bias.info() << std::endl;
  std::cout << "Weights     : " << weights.info() << std::endl;

  // std::cout << "in fmap : " << inFmap << std::endl;
  // std::cout << "out fmap : " << outFmap << std::endl;
  // std::cout << "bias: " << bias << std::endl;
  // std::cout << "weights: " << weights << std::endl;

  std::cout << softmax.infoMemory() << std::endl;

  // ----------------------
  // Copy features to array
  // ----------------------

  t_softmax::t_buf_feature_in mem_in(array_shared);
  t_softmax::t_buf_weight mem_weights(array_shared);
  t_softmax::t_buf_bias mem_bias(array_shared);
  t_softmax::t_buf_feature_out mem_out(array_shared);
  t_softmax::t_buf_feature_ref mem_ref_out(array_ref);

  inFmap.exportToArray(mem_in);
  outFmap.exportToArray(mem_ref_out);
  bias.exportToArray(mem_bias);
  weights.exportToArray(mem_weights);

  // ----------------------

  softmax.process(mem_in, mem_out, mem_weights, mem_bias);

  // ----------------------
  // Compare results
  // ----------------------
#if 1
  std::cout << "Output FW result    : " << std::setprecision(8) << std::fixed
            << mem_out;
  std::cout << "Output FW reference : " << std::setprecision(8) << std::fixed
            << mem_ref_out << std::endl;
#endif

  EXPECT_FALSE(mem_out.isEmpty());
  EXPECT_TRUE(mem_out.equals(mem_ref_out, 1e-6));

  DisplayResult::show(image_num, mem_out);
}
