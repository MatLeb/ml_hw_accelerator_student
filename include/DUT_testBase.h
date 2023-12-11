/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : DUT_testBase.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 25 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef TEST_DUT_BASE_H
#define TEST_DUT_BASE_H

#include <DUT_base.h>
#include <DisplayResult.h>
#include <mc_scverify.h>
#include <MultiMapJson.h>
#include <MultiMap2DJson.h>
#include <List1DJson.h>
#include <StimRefPath.h>

template<typename T>
SC_MODULE(DUT_testBase)
{
  Runtime chrono;

public:
  typedef T t_data;

  sc_clock clk;
  sc_in_clk clk_sig;
  sc_signal<bool> rst;

  Connections::Combinational<t_data> inFmap;
  Connections::Combinational<t_data> outFmap;
  std::deque<t_data> refFmap;

  MultiMap2DJson<double> stim_inFmap2D;
  MultiMapJson<double> stim_inFmap1D;

  MultiMap2DJson<double> ref_outFmap2D;
  MultiMapJson<double> ref_outFmap1D;

  int max_images = 1;
  bool show_image_name = false;
  std::vector<std::string> in_image_prefix = { "", "", "" };
  std::vector<std::string> out_image_prefix = { "", "", "" };

  // ------------------------------------------
  // Connect the DUT
  // ------------------------------------------

  SC_CTOR(DUT_testBase)
    : clk("clk", 1, SC_NS)
    , clk_sig("clk_sig")
    , rst("rst")
    , inFmap("inFmap")
    , outFmap("outFmap")
  {
    clk_sig(clk);

    SC_THREAD(reset);

    SC_THREAD(source_inFmap);
    sensitive << clk_sig.pos();
    async_reset_signal_is(rst, false);

    SC_THREAD(sink);
    sensitive << clk_sig.pos();
    async_reset_signal_is(rst, false);
  }

  // ------------------------------------------
  // Reset
  // ------------------------------------------

  void reset()
  {
    rst = 0;
    wait(10, SC_NS);
    rst = 1;
    wait(10, SC_NS);
  }

  // ------------------------------------------
  // Source
  // ------------------------------------------

  void source_inFmap()
  {
    assert(in_image_prefix[0].empty() == false);
    assert(in_image_prefix[1].empty() == false);
    assert(in_image_prefix[2].empty() == false);

    inFmap.ResetWrite();
    wait();

    chrono.start();

    for (int i = 1; i <= max_images; i++) {

      std::string image_num = std::to_string(i);

      if (in_image_prefix[0] == "1D") {
        stim_inFmap1D.loadJson(StimRefPath::getFmap(
          in_image_prefix[1] + "_image_" + image_num + "_" +
          in_image_prefix[2] + "_feature_maps.json"));
        stim_inFmap1D.exportToChannel(inFmap);
      } else {
        stim_inFmap2D.loadJson(StimRefPath::getFmap(
          in_image_prefix[1] + "_image_" + image_num + "_" +
          in_image_prefix[2] + "_feature_maps.json"));
        stim_inFmap2D.exportToChannel(inFmap);
      }
    }
  }

  // ------------------------------------------
  // Sink
  // ------------------------------------------

  void sink()
  {
    assert(out_image_prefix[0].empty() == false);
    assert(out_image_prefix[1].empty() == false);
    assert(out_image_prefix[2].empty() == false);

    outFmap.ResetRead();
    wait();

    for (int i = 1; i <= max_images; i++) {

      std::string image_num = std::to_string(i);

      // Load outFmap reference from JSON

      if (out_image_prefix[0] == "1D") {
        ref_outFmap1D.loadJson(StimRefPath::getFmap(
          out_image_prefix[1] + "_image_" + image_num + "_" +
          out_image_prefix[2] + "_feature_maps.json"));
        ref_outFmap1D.exportToChannel(refFmap);
      } else {
        ref_outFmap2D.loadJson(StimRefPath::getFmap(
          out_image_prefix[1] + "_image_" + image_num + "_" +
          out_image_prefix[2] + "_feature_maps.json"));
        ref_outFmap2D.exportToChannel(refFmap);
      }

      // Compare refFmap with outFmap while reFmap is not empty

      DisplayResult result;

      t_data ref, res;
      while (!refFmap.empty()) {

        wait();

        ref = refFmap.front();
        res = outFmap.Pop();
        convert::ieee_float<T> conv;

        if (show_image_name) {
          result.update(conv(res));
          // result.update(res.to_float());
        }

        if (abs(conv(ref - res)) > 1e-4) {
          std::cout << "[Sink] Error" << std::endl;
          std::cout << "[Sink] ref = " << ref << " "
                    << " res = " << res << std::endl;

          chrono.stop();
          chrono.printDuration("All images");
          sc_stop();
        }
        refFmap.pop_front();
      }

      std::cout << "[Sink] Image " << i << " OK" << std::endl;
      std::cout << std::endl;

      if (show_image_name)
        result.show(image_num);
    }

    chrono.stop();
    chrono.printDuration("all images");
    sc_stop();
  }
};

#endif
