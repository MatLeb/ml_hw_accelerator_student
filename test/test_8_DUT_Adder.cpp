/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : test_8_DUT_Adder.cpp
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 24 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#include <DUT_Adder.h>
#include <DUT_base.h>
#include <mc_scverify.h>

SC_MODULE(testbench)
{
public:
  typedef Quantization::t_data t_data;
  // ...

  CCS_DESIGN(DUT_Adder)(dut);

  sc_clock clk;
  sc_in_clk clk_sig;
  sc_signal<bool> rst;

  Connections::Combinational<t_data> inA;
  Connections::Combinational<t_data> inB;
  Connections::Combinational<t_data> out;

  // ------------------------------------------
  // Connect the DUT
  // ------------------------------------------

  SC_CTOR(testbench)
    : inA("inA")
    , inB("inB")
    , out("out")
    , dut("dut")
    , clk("clk", 1, SC_NS)
    , clk_sig("clk_sig")
    , rst("rst")
  {
    clk_sig(clk);

    // Connect the DUT to the signals
    // ...

    SC_THREAD(reset);

    // Add the source and sink threads
    // ...
  }

  // ------------------------------------------
  // Reset
  // ------------------------------------------

  void reset()
  {
    // Add low reset pulse during 10 ns
    // ...
  }

  // ------------------------------------------
  // Source
  // ------------------------------------------

  void source()
  {
    // Send a counter of 100 values to the DUT
    // Then wait 120 ns before stopping the simulation
    // ...
  }

  // ------------------------------------------
  // Sink
  // ------------------------------------------

  void sink()
  {
    // Receive the result from the DUT and print it
    // ...
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