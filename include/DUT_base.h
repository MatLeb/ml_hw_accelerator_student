/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : DUT_base.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 25 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef DUT_BASE_H
#define DUT_BASE_H

#include <systemc.h>
#include "Quantizations.h"
#include <connections/connections.h>
#include "Runtime.h"

#define SC_CTOR_BASE(name, base)                                               \
  SC_HAS_PROCESS(name);                                                        \
  name(sc_module_name name_)                                                   \
    : base(name_)

#endif
