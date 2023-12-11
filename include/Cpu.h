/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Cpu.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Nov 06 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef CPU_H
#define CPU_H

#include <Flatten.h>
#include <MaxPool.h>
#include <Relu.h>
#include <Softmax.h>

// ...

template<typename T = double>
class Cpu
{

  Runtime chrono;

  // -----------------------------------------------
  // Types for each layer
  // -----------------------------------------------

  // [HELP] Declare each layer types in this order :
  // MaxPool, Flatten, ReLu, Softmax
  // Use the previous testbenches to find the correct
  // parameters for each layer
  // ...

  // -----------------------------------------------
  // Layers + shared memory
  // -----------------------------------------------

  // [HELP] Instantiate each layer and the shared memory
  // using the types defined above
  // ...

  // -----------------------------------------------
  // Buffers
  // -----------------------------------------------

  // [HELP] Instanciate all the buffers needed for each layer
  // using the types defined above
  // ...

  // -----------------------------------------------
  // Constructor
  // -----------------------------------------------

public:
  Cpu()
  // [HELP] Connect the buffers to the shared memory
  // ...
  {
    // ...
    // [HELP] Display the memory usage for each layer :
    // std::cout << std::endl << maxPool.infoMemory() << std::endl;
    // std::cout << std::endl << flatten.infoMemory() << std::endl;
    // std::cout << std::endl << relu.infoMemory() << std::endl;
    // std::cout << std::endl << softmax.infoMemory() << std::endl;
  }

  // -----------------------------------------------
  // Load coefs
  // -----------------------------------------------

  template<typename t_chan>
  void loadCoefs(t_chan& inCoef)
  {
    // [HELP] Load the coefficients (weights and bias) for each layer
    // ...
  }

  // -----------------------------------------------
  // Process
  // -----------------------------------------------

  template<typename t_chan_in, typename t_chan_out>
  void process(t_chan_in& inFmap, t_chan_out& outFmap)
  {
    // [HELP] Process each layer
    // (in the correct order : MaxPool, Flatten, ReLu, Softmax)
    // + calculate the processing duration of each layer
    // + export the output feature map to the output channel
    // ...
  }
};

#endif
