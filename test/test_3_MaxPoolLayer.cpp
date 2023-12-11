/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_3_MaxPool.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 04 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <MaxPool.h>
#include <MultiMap2DJson.h>
#include <StimRefPath.h>
#include <gtest/gtest.h>
#include <iostream>

// ---------------------------------------------------------------
class TestMaxPoolLayer : public ::testing::Test
{
public:
  static const int IN_HEIGHT = 28;
  static const int IN_WIDTH = 28;
  static const int OUT_HEIGHT = 14;
  static const int OUT_WIDTH = 14;
  static const int N_FMAP = 32;
  static const int KSIZE = 2;
  static const int START_OFFSET = 0;

  typedef MaxPool<IN_HEIGHT,
                  IN_WIDTH,
                  OUT_HEIGHT,
                  OUT_WIDTH,
                  N_FMAP,
                  KSIZE,
                  double,
                  START_OFFSET>
    t_maxPool;

  t_maxPool maxPool;

  MultiMap2DJson<double> inFmap;
  MultiMap2DJson<double> outFmap;

  double* array_shared;
  double* array_ref;

  TestMaxPoolLayer()
  {
    // initialisation commune aux tests
    array_shared = new double[t_maxPool::SIZE];
    array_ref = new double[t_maxPool::t_buf_feature_out::SIZE];
  }

  ~TestMaxPoolLayer()
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

TEST_F(TestMaxPoolLayer, MaxPoolWithStimRef)
{
  // -------------
  // Load Stim Ref
  // -------------

  inFmap.loadJson(
    StimRefPath::getFmap("layer_1_image_1_output_feature_maps.json"));
  outFmap.loadJson(
    StimRefPath::getFmap("layer_2_image_1_output_feature_maps.json"));

  std::cout << std::endl;
  std::cout << "Input FMAP  : " << inFmap.info() << std::endl;
  std::cout << "Output FMAP : " << outFmap.info() << std::endl;
  std::cout << std::endl;

  std::cout << maxPool.infoMemory() << std::endl;

  // ----------------------
  // Copy features to array
  // ----------------------

  t_maxPool::t_buf_feature_in mem_in(array_shared);
  t_maxPool::t_buf_feature_out mem_out(array_shared);
  t_maxPool::t_buf_feature_ref mem_out_ref(array_ref);

  inFmap.exportToArray(mem_in);
  outFmap.exportToArray(mem_out_ref);

  // ----------------------

  maxPool.process(mem_in, mem_out);

  // ----------------------
  // Compare results
  // ----------------------

#if 0
  std::cout << "Output FW result :\n"
            << std::setprecision(8) << std::fixed << mem_out << std::endl;
  std::cout << "Output FW reference :\n"
            << std::setprecision(8) << std::fixed << mem_out_ref << std::endl;
#endif

  EXPECT_TRUE(mem_out == mem_out_ref);
}