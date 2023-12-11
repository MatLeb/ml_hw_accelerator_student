/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : HlsAssert.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Sun Nov 05 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef __HLS_ASSERT_H__
#define __HLS_ASSERT_H__

#include <ac_assert.h>

#ifdef __SYNTHESIS__
#define hls_assert(x)
#else
#define hls_assert(x) assert(x)
#endif

#endif
