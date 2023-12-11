/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_11_DUT_Top.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 24 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <DUT_testBase.h>
#include <DUT_Top.h>
#include <List2DJson.h>
#include <List1DJson.h>

class testbench : public DUT_testBase<DUT_Top::t_data>
{
public:
  typedef DUT_Top::t_ofmap_cpt t_ofmap_cpt;

  DUT_Top dut;

  Connections::Combinational<t_data> inCoefConv;
  Connections::Combinational<t_ofmap_cpt> outFmapCpt;
  Connections::Combinational<t_data> inCoefCpu;

  MultiMap2DJson<double> stim_conv_weights;
  List1DJson<double> stim_conv_bias;

  List2DJson<double> stim_relu_weights;
  List1DJson<double> stim_relu_bias;

  List2DJson<double> stim_softmax_weights;
  List1DJson<double> stim_softmax_bias;

  // ------------------------------------------
  // Connect the DUT
  // ------------------------------------------

  SC_CTOR_BASE(testbench, DUT_testBase)
  , inCoefConv("inCoefConv"), dut("dut"), outFmapCpt("outFmapCpt"),
    inCoefCpu("inCoefCpu")
  {
    in_image_prefix = { "2D", "layer_1", "input" };
    out_image_prefix = { "1D", "layer_6", "output" };

    max_images = 12;
    show_image_name = true;

    // Connect the DUT to the signals
    // and instanciate the source coef and sink cpt threads
    // ...
  }

  // ------------------------------------------
  // Source Coef
  // ------------------------------------------

  void source_coef()
  {
    inCoefConv.ResetWrite();
    inCoefCpu.ResetWrite();
    wait();

    // --------------------------

    stim_conv_weights.loadJson(
      StimRefPath::getCoef("layer_1_conv_weights_reordered.json"));
    stim_conv_bias.loadJson(StimRefPath::getCoef("layer_1_conv_bias.json"));

    stim_relu_weights.loadJson(
      StimRefPath::getCoef("layer_5_relu_weights.json"));
    stim_relu_bias.loadJson(StimRefPath::getCoef("layer_5_relu_bias.json"));

    stim_softmax_weights.loadJson(
      StimRefPath::getCoef("layer_6_softmax_weights.json"));
    stim_softmax_bias.loadJson(
      StimRefPath::getCoef("layer_6_softmax_bias.json"));

    // --------------------------

    stim_conv_weights.exportToChannel(inCoefConv);
    stim_conv_bias.exportToChannel(inCoefConv);

    stim_relu_weights.exportToChannel(inCoefCpu);
    stim_relu_bias.exportToChannel(inCoefCpu);

    stim_softmax_weights.exportToChannel(inCoefCpu);
    stim_softmax_bias.exportToChannel(inCoefCpu);
  }

  // ------------------------------------------
  // Sink Cpt
  // ------------------------------------------

  void sink_cpt()
  {
    outFmapCpt.ResetRead();
    wait();

    while (true) {
      for (int i = 0; i < 32; i++) {
        t_ofmap_cpt cpt = outFmapCpt.Pop();
        if (i == 0)
          std::cout << "[Sink ofmap] : ";
        std::cout << cpt << " ";
        std::flush(std::cout);
      }
      std::cout << "Done" << std::endl;
    }
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