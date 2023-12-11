/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_0_Json.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 11 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <List1DJson.h>
#include <List2DJson.h>
#include <MultiMap2DJson.h>
#include <MultiMapJson.h>
#include <StimRefPath.h>
#include <gtest/gtest.h>
#include <iostream>

// ---------------------------------------------------------------

class JsonTest : public ::testing::Test
{
public:
  JsonTest()
  {
    // initialisation commune aux tests
  }

  ~JsonTest()
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
};

// ---------------------------------------------------------------

TEST_F(JsonTest, test_List1DJson)
{
  List1DJson<double> list;
  list.loadJson(StimRefPath::getCoef("layer_6_softmax_bias.json"));
  std::cout << list << std::endl;

  double mem[64];
  list.exportToArray<64>(mem);
}

// ---------------------------------------------------------------

TEST_F(JsonTest, test_List2DJson)
{
  List2DJson<double> list;
  list.loadJson(StimRefPath::getCoef("layer_6_softmax_weights.json"));
  std::cout << list << std::endl;

  double mem[32][10];
  list.exportToArray<32, 10>(mem);
}

// ---------------------------------------------------------------

TEST_F(JsonTest, test_MultiMap2DJson1)
{
  MultiMap2DJson<double> map;
  map.loadJson(
    StimRefPath::getFmap("layer_3_image_1_output_feature_maps.json"));
  std::cout << map << std::endl;

  double mem[32][14][14];
  map.exportToArray<32, 14, 14>(mem);

  // display mem values with index of each value
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 14; j++) {
      std::cout << "mem[" << i << "][" << j << "][] = ";
      for (int k = 0; k < 14; k++) {
        std::cout << mem[i][j][k] << " ";
      }
      std::cout << std::endl;
    }
  }
}

// ---------------------------------------------------------------

TEST_F(JsonTest, test_MultiMap2DJson2)
{
  MultiMap2DJson<double> map;
  map.loadJson(StimRefPath::getCoef("layer_1_conv_weights_reordered.json"));
  std::cout << map << std::endl;

  double mem[32][1][3][3];
  map.exportToArray<32, 1, 3, 3>(mem);

  // display mem values with index of each value
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 1; j++) {
      for (int k = 0; k < 3; k++) {
        std::cout << "mem[" << i << "][" << j << "][" << k << "][] = ";
        for (int l = 0; l < 3; l++) {
          std::cout << mem[i][j][k][l] << " ";
        }
        std::cout << std::endl;
      }
    }
  }
}

// ---------------------------------------------------------------

TEST_F(JsonTest, test_MultiMapJson)
{
  MultiMapJson<double> map;
  map.loadJson(
    StimRefPath::getFmap("layer_6_image_1_output_feature_maps.json"));
  std::cout << map << std::endl;

  double mem[10];
  map.exportToArray<10>(mem);
}