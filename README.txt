#-------------------------------------------------------------"
# HW ACCELERATOR DESIGN FOR ML                                "
#-------------------------------------------------------------"
# Version : 0.1                                               "
# Date    : 09/2023                                           "
# Author  : Mathieu Lebon                                     "
#-------------------------------------------------------------"

Please follow these steps in order to :
- configure and test the environnement
- check the existing C++ code is correct
- check your C++/SystemC code is correct

Write the commands in a terminal.

____________________________________________________________________
[Environment]

1) Install dependencies => 'source env.sh'
2) Read available commands => 'cd test; make help'
3) Test build (empty code) => 'make build'

____________________________________________________________________
[Already completed code]

All following tests should be OK

4) Test json => 'make run_0_json'
5) Test memories => 'make run_0_mem'
6) Test buffers => 'make run_0_buffer'

____________________________________________________________________
[Code to be completed]

All tests are failing (since code is missing)
Nox complete empty code and check.
Note : complete the tests in order (ie : from run_1 to run_11)

Open vscode => 'make open_vscode'

- Complete code : (already completed testbenches)
1) 'make run_1'  : Check Conv2D layer algo (Array version)
2) 'make run_2'  : Check Conv2D layer algo (Buffer version)
3) 'make run_3'  : Check Maxpool layer algo
4) 'make run_4'  : Check Flatten layer algo
5) 'make run_5'  : Check ReLU layer algo
6) 'make run_6'  : Check Softmax layer algo
7) 'make run_7'  : Check All Layer algo

- Complete code + testbenches :
1) 'make run_8'  : Check SystemC Module Adder
2) 'make run_9'  : Check SystemC Module Conv2D
3) 'make run_10' : Check SystemC Module Cpu (all layers without Conv2D)
4) 'make run_11' : Check SystemC Module Top (Conv2D + Cpu)

____________________________________________________________________
[HLS Synthesis]

When your code is completed and working,
You can start the RTL generation with Catapult.

Available commands => 'cd test; make help'

----------------------------------
[Adder] RTL Synthesis + simulation
----------------------------------
1) 'make adder_synth' : generate RTL for adder with Catapult
2) 'make adder_open'  : open Catapult Adder project
3) Complete architecture constraints in order to get a throughput of
   1 output (sum) at each clock cycle
4) Generate RTL
5) CoSimulate SystemC/RTL in questa sim
   - You can do it from Catapult
   - You can also call 'make adder_simu'
4) When your results are OK, save your Catapult directives
   in file "synthesis/directives_adder.tcl"
5) 'make adder_export' : copy generated rtl into export path
   (synthesis/output)

-----------------------------------
[Conv2D] RTL Synthesis + simulation
-----------------------------------
- Follow the same steps as for the "Adder" design
- Add architectural constraints in Catapult to improve throughput

____________________________________________________________________
[Zybo Design]

Now the output products can be used to create the HW/SW design running
on the Zynq SoC of the Zybo board.

- Vivado : the RTL IP "Conv2D" is ready for instanciation (can use "Adder" for tests)
- Vitis  : the "Cpu" code can be used for baremetal instanciation
