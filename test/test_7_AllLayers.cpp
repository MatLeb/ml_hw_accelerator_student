/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_7_AllLayers.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 10 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <DisplayResult.h>
#include <Conv2DBuffer.h>
#include <Flatten.h>
#include <List1DJson.h>
#include <List2DJson.h>
#include <MaxPool.h>
#include <MultiMap2DJson.h>
#include <MultiMapJson.h>
#include <Relu.h>
#include <Softmax.h>
#include <StimRefPath.h>
#include <Runtime.h>
#include <gtest/gtest.h>

// ---------------------------------------------------------------

class TestAllLayers : public ::testing::Test
{
public:
  // ------------------------------------
  // Layers
  // ------------------------------------

  typedef Conv2DBuffer<28, 28, 1, 32, 3, double, OpBias<double>, 0> t_conv2D;
  typedef MaxPool<28, 28, 14, 14, 32, 2, double, t_conv2D::OUT_OFFSET>
    t_maxPool;
  typedef Flatten<14, 14, 32, double, t_maxPool::OUT_OFFSET> t_flatten;
  typedef ReLu<6272, 32, double, t_flatten::OUT_OFFSET> t_relu;
  typedef Softmax<32, 10, double, t_relu::OUT_OFFSET> t_softmax;

  t_conv2D conv2D;
  t_maxPool maxPool;
  t_flatten flatten;
  t_relu relu;
  t_softmax softmax;

  // ------------------------------------
  // Stimuli / References
  // ------------------------------------

  MultiMap2DJson<double> conv_inFmap;
  MultiMap2DJson<double> conv_weights;
  List1DJson<double> conv_bias;

  List1DJson<double> relu_bias;
  List2DJson<double> relu_weights;

  MultiMapJson<double> softmax_outFmap;
  List1DJson<double> softmax_bias;
  List2DJson<double> softmax_weights;

  // ------------------------------------

  double* array_shared;
  double* array_ref;

  // ------------------------------------

  TestAllLayers()
  {
    // initialisation commune aux test
    array_shared = new double[t_softmax::SIZE];
    array_ref = new double[t_softmax::t_buf_feature_out::SIZE];
  }

  ~TestAllLayers()
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

TEST_F(TestAllLayers, test_all_layers)
{
  std::cout << std::endl;
  std::cout << conv2D.infoMemory() << std::endl;
  std::cout << maxPool.infoMemory() << std::endl;
  std::cout << flatten.infoMemory() << std::endl;
  std::cout << relu.infoMemory() << std::endl;
  std::cout << softmax.infoMemory() << std::endl;

  // ------------------------------------
  // 1 Shared Memory for each layer
  // ------------------------------------

  t_conv2D::t_buf_feature_in mem_conv_in_fmaps(array_shared);
  t_conv2D::t_buf_weight mem_conv_weights(array_shared);
  t_conv2D::t_buf_bias mem_conv_bias(array_shared);
  t_conv2D::t_buf_feature_out mem_conv_out(array_shared);

  t_maxPool::t_buf_feature_in mem_maxpool_in(array_shared);
  t_maxPool::t_buf_feature_out mem_maxpool_out(array_shared);

  t_flatten::t_buf_feature_in mem_flatten_in(array_shared);
  t_flatten::t_buf_feature_out mem_flatten_out(array_shared);

  t_relu::t_buf_feature_in mem_relu_in(array_shared);
  t_relu::t_buf_weight mem_relu_weights(array_shared);
  t_relu::t_buf_bias mem_relu_bias(array_shared);
  t_relu::t_buf_feature_out mem_relu_out(array_shared);

  t_softmax::t_buf_feature_in mem_softmax_in(array_shared);
  t_softmax::t_buf_weight mem_softmax_weights(array_shared);
  t_softmax::t_buf_bias mem_softmax_bias(array_shared);
  t_softmax::t_buf_feature_out mem_softmax_out(array_shared);

  t_softmax::t_buf_feature_ref mem_ref_out(array_ref);

  // ------------------------------------
  // Load Coefficients
  // ------------------------------------

  conv_weights.loadJson(
    StimRefPath::getCoef("layer_1_conv_weights_reordered.json"));
  conv_bias.loadJson(StimRefPath::getCoef("layer_1_conv_bias.json"));

  relu_weights.loadJson(StimRefPath::getCoef("layer_5_relu_weights.json"));
  relu_bias.loadJson(StimRefPath::getCoef("layer_5_relu_bias.json"));

  softmax_bias.loadJson(StimRefPath::getCoef("layer_6_softmax_bias.json"));
  softmax_weights.loadJson(
    StimRefPath::getCoef("layer_6_softmax_weights.json"));

  // ------------------------------------

  for (int i = 1; i <= 12; i++) {

    std::string image_num = std::to_string(i);

    // -------------
    // Load Stim Ref
    // -------------

    conv_inFmap.loadJson(StimRefPath::getFmap("layer_1_image_" + image_num +
                                              "_input_feature_maps.json"));

    softmax_outFmap.loadJson(StimRefPath::getFmap("layer_6_image_" + image_num +
                                                  "_output_feature_maps.json"));

    // ----------------------
    // Copy features to array
    // ----------------------

    conv_inFmap.exportToArray(mem_conv_in_fmaps);
    conv_weights.exportToArray(mem_conv_weights);
    conv_bias.exportToArray(mem_conv_bias);

    relu_weights.exportToArray(mem_relu_weights);
    relu_bias.exportToArray(mem_relu_bias);

    softmax_weights.exportToArray(mem_softmax_weights);
    softmax_bias.exportToArray(mem_softmax_bias);

    softmax_outFmap.exportToArray(mem_ref_out);

    // ----------------------
    // Process All Layers
    // ----------------------

    Runtime chrono;

    // Run all layers 1 by 1
    // And measure execution time using chrono.printDuration();
    // ...

    // ----------------------
    // Compare results
    // ----------------------

#if 1
    std::cout << "Output FW result    : " << std::setprecision(8) << std::fixed
              << mem_softmax_out;
    std::cout << "Output FW reference : " << std::setprecision(8) << std::fixed
              << mem_ref_out << std::endl;
#endif

    DisplayResult::show(image_num, mem_softmax_out);

    EXPECT_FALSE(mem_softmax_out.isEmpty());
    EXPECT_TRUE(mem_softmax_out.equals(mem_ref_out, 1e-5));
  }
}
