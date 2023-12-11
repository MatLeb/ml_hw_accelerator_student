/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : DUT_Top.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 24 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef DUT_TOP_H
#define DUT_TOP_H

#include <DUT_base.h>
#include <DUT_Conv2D.h>
#include <DUT_Cpu.h>

SC_MODULE(DUT_Top)
{
  typedef Quantization::t_data t_data;
  // ...
  typedef Quantization::t_ofmap_cpt t_ofmap_cpt;

  // ...

public:
  // ------------------------------------
  // Signals
  // ------------------------------------

  sc_in_clk clk;
  sc_in<bool> rst;

  Connections::In<t_data> inFmap;
  Connections::In<t_data> inCoefConv;
  Connections::In<t_data> inCoefCpu;
  Connections::Out<t_data> outFmap;
  Connections::Out<t_ofmap_cpt> outFmapCpt;

  Connections::Combinational<t_data> interFmap;

  // ------------------------------------
  // Constructor
  // ------------------------------------

  SC_CTOR(DUT_Top)
    : clk("clk")
    , rst("rst")
    , inFmap("inFmap")
    , inCoefConv("inCoefConv")
    , inCoefCpu("inCoefCpu")
    , outFmap("outFmap")
    , outFmapCpt("outFmapCpt")
    , interFmap("interFmap")
  // ...
  {
    // ...
  }
};

#endif