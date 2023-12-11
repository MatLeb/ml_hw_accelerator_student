/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_4_Flatten.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sat Sep 09 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <Flatten.h>
#include <MultiMap2DJson.h>
#include <MultiMapJson.h>
#include <StimRefPath.h>
#include <gtest/gtest.h>

// ---------------------------------------------------------------

class TestFlattenLayer : public ::testing::Test
{
public:
  static const long IN_HEIGHT = 14;
  static const long IN_WIDTH = 14;
  static const long IN_FMAP = 32;
  static const long START_OFFSET = 0;

  typedef Flatten<IN_HEIGHT, IN_WIDTH, IN_FMAP, double, START_OFFSET> t_flatten;
  t_flatten flatten;

  MultiMap2DJson<double> inFmap;
  MultiMapJson<double> outFmap;

  double* array_shared;
  double* array_ref;

  TestFlattenLayer()
  {
    // initialisation commune aux tests
    array_shared = new double[t_flatten::SIZE];
    array_ref = new double[t_flatten::t_buf_feature_out::SIZE];
  }

  ~TestFlattenLayer()
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

TEST_F(TestFlattenLayer, TestFlatten)
{
  // -------------
  // Load Stim Ref
  // -------------

  inFmap.loadJson(
    StimRefPath::getFmap("layer_3_image_1_output_feature_maps.json"));

  outFmap.loadJson(
    StimRefPath::getFmap("layer_4_image_1_output_feature_maps.json"));

  std::cout << std::endl;
  std::cout << "Input FMAP  : " << inFmap.info() << std::endl;
  std::cout << "Output FMAP : " << outFmap.info() << std::endl;
  std::cout << std::endl;

  std::cout << flatten.infoMemory() << std::endl;

  // ----------------------
  // Copy features to array
  // ----------------------

  t_flatten::t_buf_feature_in mem_in(array_shared);
  t_flatten::t_buf_feature_out mem_out(array_shared);

  t_flatten::t_buf_feature_ref mem_ref(array_ref);

  inFmap.exportToArray(mem_in);
  outFmap.exportToArray(mem_ref);

  // ----------------------

  flatten.process(mem_in, mem_out);

  // ----------------------
  // Compare results
  // ----------------------
#if 0
  std::cout << "Output FW result : " << std::setprecision(8) << std::fixed
            << mem_out << std::endl;
  std::cout << "Output FW reference : " << std::setprecision(8) << std::fixed
            << mem_ref << std::endl;
#endif

  EXPECT_TRUE(mem_out == mem_ref);
}