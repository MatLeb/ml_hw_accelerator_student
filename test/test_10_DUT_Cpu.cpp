/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_10_DUT_Cpu.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 25 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <DUT_testBase.h>
#include <DUT_Cpu.h>
#include <List2DJson.h>
#include <List1DJson.h>

class testbench : public DUT_testBase<DUT_Cpu::t_data>
{
public:
  DUT_Cpu dut;

  Connections::Combinational<t_data> inCoef;

  List2DJson<double> stim_relu_weights;
  List1DJson<double> stim_relu_bias;

  List2DJson<double> stim_softmax_weights;
  List1DJson<double> stim_softmax_bias;

  // ------------------------------------------
  // Connect the DUT
  // ------------------------------------------

  SC_CTOR_BASE(testbench, DUT_testBase)
  , inCoef("inCoef"), dut("dut")
  {
#if defined(DBG_MAXPOOL)
    in_image_prefix = { "2D", "layer_1", "output" };
    out_image_prefix = { "2D", "layer_2", "output" };
    show_image_name = false;
#elif defined(DBG_FLATTEN)
    in_image_prefix = { "2D", "layer_3", "output" };
    out_image_prefix = { "1D", "layer_4", "output" };
    show_image_name = false;
#elif defined(DBG_RELU)
    in_image_prefix = { "1D", "layer_4", "output" };
    out_image_prefix = { "1D", "layer_5", "output" };
    show_image_name = false;
#elif defined(DBG_SOFTMAX)
    in_image_prefix = { "1D", "layer_5", "output" };
    out_image_prefix = { "1D", "layer_6", "output" };
    show_image_name = true;
#else
    in_image_prefix = { "2D", "layer_1", "output" };
    out_image_prefix = { "1D", "layer_6", "output" };
    show_image_name = true;
#endif
    max_images = 12;

    // Connect the DUT to the signals
    // and instanciate the source coef thread
    // ...
  }

  // ------------------------------------------
  // Source Coef
  // ------------------------------------------

  void source_coef()
  {
    inCoef.ResetWrite();
    wait();

#if defined(DBG_RELU)

    stim_relu_weights.loadJson(
      StimRefPath::getCoef("layer_5_relu_weights.json"));
    stim_relu_bias.loadJson(StimRefPath::getCoef("layer_5_relu_bias.json"));

    stim_relu_weights.exportToChannel(inCoef);
    stim_relu_bias.exportToChannel(inCoef);

#elif defined(DBG_SOFTMAX)

    stim_softmax_weights.loadJson(
      StimRefPath::getCoef("layer_6_softmax_weights.json"));
    stim_softmax_bias.loadJson(
      StimRefPath::getCoef("layer_6_softmax_bias.json"));

    stim_softmax_weights.exportToChannel(inCoef);
    stim_softmax_bias.exportToChannel(inCoef);

#else

    stim_relu_weights.loadJson(
      StimRefPath::getCoef("layer_5_relu_weights.json"));
    stim_relu_bias.loadJson(StimRefPath::getCoef("layer_5_relu_bias.json"));

    stim_softmax_weights.loadJson(
      StimRefPath::getCoef("layer_6_softmax_weights.json"));
    stim_softmax_bias.loadJson(
      StimRefPath::getCoef("layer_6_softmax_bias.json"));

    stim_relu_weights.exportToChannel(inCoef);
    stim_relu_bias.exportToChannel(inCoef);

    stim_softmax_weights.exportToChannel(inCoef);
    stim_softmax_bias.exportToChannel(inCoef);
#endif
  }
};

// ----------------------------------------------------------------------------
// SystemC Main for running the test-bench
// ----------------------------------------------------------------------------

int
sc_main(int argc, char** argv)
{
  testbench tb("tb");
  sc_start();
  std::cout << std::endl;
  return 0;
}