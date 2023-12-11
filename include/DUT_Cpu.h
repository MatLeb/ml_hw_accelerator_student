/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : DUT_Cpu.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 24 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef DUT_CPU_H
#define DUT_CPU_H

#include <DUT_base.h>
#include <Cpu.h>

// -----------------------------------------------

SC_MODULE(DUT_Cpu)
{
public:
  Runtime chrono;

  typedef Quantization::t_data t_data;
  // ...

  Cpu<t_data> cpu;

  // ------------------------------------
  // Signals
  // ------------------------------------

  sc_in_clk clk;
  sc_in<bool> rst;

  Connections::In<t_data> inFmap;
  Connections::In<t_data> inCoef;
  Connections::Out<t_data> outFmap;

  sc_signal<bool> done;

  // ------------------------------------
  // Constructor
  // ------------------------------------

  SC_CTOR(DUT_Cpu)
    : clk("clk")
    , rst("rst")
    , done("done")
    , inFmap("inFmap")
    , inCoef("inCoef")
    , outFmap("outFmap")
  {
    // [HELP] Instantiate the run thread
    // ...
  }

  // ------------------------------------
  // Run All remaining layers
  // ------------------------------------

  void run()
  {
    inFmap.Reset();
    inCoef.Reset();
    outFmap.Reset();

    bool coefLoaded = false;

    wait();

    while (true) {

      if (coefLoaded == false) {

        // [HELP] Load coefficients
        // ...

      } else {

        chrono.start();

        // [HELP] Run the Cpu layers
        // ...

        chrono.stop();
        chrono.printDuration("DUT_Cpu");
      }
    }
  }
};

#endif