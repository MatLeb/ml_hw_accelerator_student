/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_9_DUT_Conv2D.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 24 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <DUT_testBase.h>
#include <DUT_Conv2D.h>

class testbench : public DUT_testBase<DUT_Conv2D::t_data>
{
public:
  typedef DUT_Conv2D::t_ofmap_cpt t_ofmap_cpt;

  CCS_DESIGN(DUT_Conv2D)(dut);

  Connections::Combinational<t_data> inCoef;
  Connections::Combinational<t_ofmap_cpt> outFmapCpt;

  MultiMap2DJson<double> stim_weights;
  List1DJson<double> stim_bias;

  // ------------------------------------------
  // Connect the DUT
  // ------------------------------------------

  SC_CTOR_BASE(testbench, DUT_testBase)
  , inCoef("inCoef"), dut("dut"), outFmapCpt("outFmapCpt")
  {
    in_image_prefix = { "2D", "layer_1", "input" };
    out_image_prefix = { "2D", "layer_1", "output" };
#ifdef CCS_SYSC
    max_images = 1;
#else
    max_images = 12;
#endif
    show_image_name = false;

    // Connect the DUT to the signals
    // and instanciate the source and sink threads
    // ...
  }

  // ------------------------------------------
  // Source Coef
  // ------------------------------------------

  void source_coef()
  {
    inCoef.ResetWrite();
    wait();

    std::cout << "[Simulation] : " << max_images << " images\n";

    // Load JSON ---------
    stim_weights.loadJson(
      StimRefPath::getCoef("layer_1_conv_weights_reordered.json"));
    stim_bias.loadJson(StimRefPath::getCoef("layer_1_conv_bias.json"));
    // -------------------

    // Load Coef ---------
    stim_weights.exportToChannel(inCoef);
    stim_bias.exportToChannel(inCoef);
    // -------------------

    while (true)
      wait();
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