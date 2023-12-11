/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : DUT_Adder.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 24 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef DUT_ADDER_H
#define DUT_ADDER_H

#include "DUT_base.h"

// -----------------------------------------------

#pragma hls_design top
SC_MODULE(DUT_Adder)
{
  Runtime chrono;
  Runtime chronoAll;

  typedef Quantization::t_data t_data;
  // ...

public:
  // ------------------------------------
  // Signals
  // ------------------------------------

  sc_in_clk clk;
  sc_in<bool> rst;

  Connections::In<t_data> inA;
  Connections::In<t_data> inB;
  Connections::Out<t_data> out;

  // ------------------------------------
  // Constructor
  // ------------------------------------

  SC_CTOR(DUT_Adder)
    : clk("clk")
    , rst("rst")
    , inA("inA")
    , inB("inB")
    , out("out")
  {
    // [HELP] Instantiate the run thread
    // ...
  }

  // ------------------------------------
  // Run All remaining layers
  // ------------------------------------

  void run()
  {
    // [HELP] calculate the sum of the two inputs
    // ...
  }
};

#endif
