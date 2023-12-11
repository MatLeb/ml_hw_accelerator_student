/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : DUT_Conv2DBuffer.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 24 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef DUT_CONV2D_H
#define DUT_CONV2D_H

#include "DUT_base.h"
#define USE_OFMAP_CPT_CHAN
#include "Conv2DBuffer.h"

#pragma hls_design top
SC_MODULE(DUT_Conv2D)
{
  Runtime chrono;

public:
  typedef Quantization::t_data t_data;
  // ...
  typedef Quantization::t_ofmap_cpt t_ofmap_cpt;

  typedef Conv2DBuffer<28, 28, 1, 32, 3, t_data, OpBias<t_data>, 0> t_conv2D;

private:
  t_conv2D conv2D;

  t_data shared_mem[t_conv2D::SIZE];

  t_conv2D::t_buf_feature_in mem_conv_in;
  t_conv2D::t_buf_weight mem_conv_weights;
  t_conv2D::t_buf_bias mem_conv_bias;
  t_conv2D::t_buf_feature_out mem_conv_out;

public:
  // ------------------------------------
  // Signals
  // ------------------------------------

  sc_in_clk clk;
  sc_in<bool> rst;

  Connections::In<t_data> inCoef;
  Connections::In<t_data> inFmap;
  Connections::Out<t_data> outFmap;
  Connections::Out<t_ofmap_cpt> outFmapCpt;

  // ------------------------------------
  // Constructor
  // ------------------------------------

  SC_CTOR(DUT_Conv2D)
    : clk("clk")
    , rst("rst")
    , inCoef("inCoef")
    , inFmap("inFmap")
    , outFmap("outFmap")
    , outFmapCpt("outFmapCpt")
    , mem_conv_in(shared_mem)
    , mem_conv_weights(shared_mem)
    , mem_conv_bias(shared_mem)
    , mem_conv_out(shared_mem)
  {
    std::cout << std::endl << conv2D.infoMemory() << std::endl;

    // [HELP] Instantiate the run thread
    // ...
  }

  void run()
  {
    // [HELP] Load the weights and bias
    // and process the 2D convolutions
    // ...
  }
};

#endif
