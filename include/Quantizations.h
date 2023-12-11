/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Quantizations.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Sep 24 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef QUANTIZATIONS_H
#define QUANTIZATIONS_H

#ifdef SYSTEMC_H
#include <ac_std_float.h>
#include <ac_sc.h>
#include <ac_sysc_trace.h>
#endif

// ---------------------------------------------------------------

#ifdef __AC_STD_FLOAT_H
struct Quantization
{
  // typedef ac::ac_float_represent<double>::type t_data;
  // typedef ac_std_float<64, 11> t_data;

  typedef ac_ieee_float<binary64> t_data;
  typedef ac_ieee_float<binary32> t_data32;
  typedef ac_int<16, false> t_ofmap_cpt;
};

#if 0
void
sc_trace(sc_trace_file* tf,
         const Quantization::t_data32& var,
         const std::string& nm)
{
  sc_core::sc_trace(tf, var.to_float(), nm);
}
void
sc_trace(sc_trace_file* tf,
         const Quantization::t_data& var,
         const std::string& nm)
{
  sc_core::sc_trace(tf, var.to_double(), nm);
}
#endif
#endif

// ---------------------------------------------------------------

struct convert
{
  template<typename T, int fake = 0>
  struct ieee_float
  {
    virtual T operator()(T input) = 0;
  };

  template<int fake>
  struct ieee_float<double, fake>
  {
    double operator()(double input) { return input; }
  };

#ifdef __AC_STD_FLOAT_H
  template<int fake>
  struct ieee_float<Quantization::t_data, fake>
  {
    double operator()(Quantization::t_data input) { return input.to_double(); }
    Quantization::t_data operator()(double input) { return input; }
  };

  template<int fake>
  struct ieee_float<Quantization::t_data32, fake>
  {
    float operator()(Quantization::t_data32 input) { return input.to_float(); }
    Quantization::t_data32 operator()(float input) { return input; }
  };
#endif
};

#endif
