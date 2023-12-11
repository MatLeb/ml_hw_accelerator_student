
set script_path [ file dirname [ file normalize [ info script ] ] ]

set_working_dir $script_path/../work

options defaults
options set /Input/CppStandard c++11
options set /Input/TargetPlatform x86
options set /Input/CompilerFlags {-DHLS_CATAPULT -DCONNECTIONS_ACCURATE_SIM -DCONNECTIONS_NAMING_ORIGINAL}
options set Flows/QuestaSIM/SCCOM_OPTS {-g -x c++ -Wall -Wno-unused-label -Wno-unknown-pragmas -std=c++11 -D__STRICT_ANSI__ -D__GXX_EXPERIMENTAL_CXX0X__ }
options save

project new -name work_adder

flow package require /SCVerify
flow run /SCVerify

solution options set /Input/SearchPath {../include}
directive set -TRANSACTION_DONE_SIGNAL true

# Add directives here

solution file add $script_path/../include/DUT_Adder.h -type CHEADER
solution file add $script_path/../test/test_8_DUT_Adder.cpp -exclude true

go analyze

solution library add nangate-45nm_beh -- -rtlsyntool DesignCompiler -vendor Nangate -technology 045nm
solution library add ram_nangate-45nm-dualport_beh
solution library add ram_nangate-45nm-separate_beh
solution library add ram_nangate-45nm-singleport_beh
solution library add amba

go libraries
directive set -CLOCKS {clk {-CLOCK_PERIOD 20 -CLOCK_HIGH_TIME 10 -CLOCK_OFFSET 0.000000 -CLOCK_UNCERTAINTY 0.0}}

go assembly

exit
#  ...
