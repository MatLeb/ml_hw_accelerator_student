
set script_path [ file dirname [ file normalize [ info script ] ] ]

set_working_dir $script_path/../work

options defaults
options set /Input/CppStandard c++11
options set /Input/TargetPlatform x86
options set /Input/CompilerFlags {-DHLS_CATAPULT -DCONNECTIONS_ACCURATE_SIM -DCONNECTIONS_NAMING_ORIGINAL}
options save

project new -name work_conv2d

flow package require /SCVerify
flow run /SCVerify

solution options set /Input/SearchPath {../include ../local/json/include}
directive set -TRANSACTION_DONE_SIGNAL true

# Add directives here
exit
#  ...
