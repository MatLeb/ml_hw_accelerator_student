#include "DUT_base.h"

SC_MODULE(DUT_Adder)
{
public:
  // ------------------------------------

  sc_in_clk clk;
  sc_in<bool> rst;

  sc_in<int10> inA;
  sc_in<int10> inB;
  sc_out<int10> out;

  // ------------------------------------

  SC_CTOR(DUT_Adder)
    : clk("clk")
    , rst("rst")
    , inA("inA")
    , inB("inB")
    , out("out")
  {
    SC_THREAD(run);
    sensitive << clk.pos();
    async_reset_signal_is(rst, false);
  }

  // ------------------------------------

  void run()
  {
    wait();

    while (true) {
      out.write(inA.read() + inB.read());
      wait();
    }
  }
};

#endif
