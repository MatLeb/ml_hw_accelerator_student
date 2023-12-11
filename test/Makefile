
HOSTNAME := $(shell uname)
$(info HOSTNAME is $(HOSTNAME))

ifeq ($(HOSTNAME), Darwin)
#CXXFLAGS += -g -std=c++11 -Wno-everything -Wl,-stack_size,0x20000000
CXXFLAGS += -g -std=c++11 -Wno-everything
else
CXXFLAGS += -g -std=c++11
endif

CURRENT_DIR := `pwd`
RTL_DIR := $(HOME)/thindrives/share

CONF_CATAPULT := /softs/MENTOR/catapult_21.aime/start_sh
CONF_QUESTA := /softs/MENTOR/amsv.aime/start_sh

# ---------------------------------------------------------------------

bold := $(shell tput bold)
sgr0 := $(shell tput sgr0)
cyan := $(shell tput setaf 6)
green := $(shell tput setaf 2)
yellow := $(shell tput setaf 3)
color := $(cyan)

define print_color
    @printf "$(color)$(bold)$(1)$(sgr0)\n"
endef

# ---------------------------------------------------------------------
#  Check ENV
# ---------------------------------------------------------------------

ifndef PROJECT_SYSTEMC
$(warning Please run : source env.sh)
$(error - Environment variable PROJECT_SYSTEMC must be defined)
endif
ifndef PROJECT_CONNECTIONS
$(warning Please run : source env.sh)
$(error - Environment variable PROJECT_CONNECTIONS must be defined)
endif
ifndef PROJECT_MATCHLIB
$(warning Please run : source env.sh)
$(error - Environment variable PROJECT_MATCHLIB must be defined)
endif
ifndef PROJECT_AC_TYPES
$(warning Please run : source env.sh)
$(error - Environment variable PROJECT_AC_TYPES must be defined)
endif
ifndef PROJECT_AC_SIMUTILS
$(warning Please run : source env.sh)
$(error - Environment variable PROJECT_AC_SIMUTILS must be defined)
endif
ifndef PROJECT_JSON
$(warning Please run : source env.sh)
$(error - Environment variable PROJECT_JSON must be defined)
endif

# ---------------------------------------------------------------------
# Set SYSTEMC
# ---------------------------------------------------------------------

# Default to the compiler installed on the machine
CXX ?= g++

ifeq ($(HOSTNAME), Darwin)
LIBDIRS += -L$(PROJECT_SYSTEMC)/lib -L$(PROJECT_GTEST)/lib
LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(PROJECT_GTEST)/lib:$(PROJECT_SYSTEMC)/lib
else
LIBDIRS += -L$(PROJECT_SYSTEMC)/lib64 -L$(PROJECT_GTEST)/lib64
LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(PROJECT_GTEST)/lib:$(PROJECT_SYSTEMC)/lib64
endif

# ---------------------------------------------------------------------
# Check INSTALLATIONS
# ---------------------------------------------------------------------

# Check: $(PROJECT_SYSTEMC)/include/systemc.h must exist
checkvar_PROJECT_SYSTEMC: $(PROJECT_SYSTEMC)/include/systemc.h

# Check: $(PROJECT_CONNECTIONS)/include/connections/connections.h must exist
checkvar_PROJECT_CONNECTIONS: $(PROJECT_CONNECTIONS)/include/connections/connections.h

# Check: $(PROJECT_MATCHLIB)/cmod/include/nvhls_marshaller.h
checkvar_PROJECT_MATCHLIB: $(PROJECT_MATCHLIB)/cmod/include/nvhls_marshaller.h

# Check: $(PROJECT_AC_TYPES)/include/ac_int.h
checkvar_PROJECT_AC_TYPES: $(PROJECT_AC_TYPES)/include/ac_int.h

# Check: $(PROJECT_AC_SIMUTILS)/include/mc_scverify.h
checkvar_PROJECT_AC_SIMUTILS: $(PROJECT_AC_SIMUTILS)/include/mc_scverify.h

# Check: $(PROJECT_GTEST)/include/gtest/gtest.h
checkvar_PROJECT_GTEST: $(PROJECT_GTEST)/include/gtest/gtest.h

# Check: $(PROJECT_EIGEN)/include/eigen3/Eigen/Eigen
checkvar_PROJECT_EIGEN: $(PROJECT_EIGEN)/include/eigen3/Eigen/Eigen

# Check: $(PROJECT_JSON)/include/nlohmann/json.hpp
checkvar_PROJECT_JSON: $(PROJECT_JSON)/include/nlohmann/json.hpp

# Rule to check that environment variables are set correctly
checkvars: checkvar_PROJECT_SYSTEMC checkvar_PROJECT_CONNECTIONS checkvar_PROJECT_MATCHLIB checkvar_PROJECT_AC_TYPES checkvar_PROJECT_AC_SIMUTILS checkvar_PROJECT_GTEST checkvar_PROJECT_EIGEN

# ---------------------------------------------------------------------
# Export variables to any sub-invoked Make
# ---------------------------------------------------------------------

export PROJECT_SYSTEMC
export PROJECT_CONNECTIONS
export PROJECT_MATCHLIB
export PROJECT_AC_TYPES
export PROJECT_AC_SIMUTILS
export PROJECT_GTEST
export PROJECT_EIGEN
export PROJECT_JSON
export LD_LIBRARY_PATH

# ---------------------------------------------------------------------
# 
# ---------------------------------------------------------------------

PWD := $(shell pwd)
SOURCE_DIR1 = $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))
SOURCE_DIR = $(if $(subst ./,,$(SOURCE_DIR1)),$(SOURCE_DIR1),$(PWD)/)

INCDIRS := -I$(SOURCE_DIR)
INCDIRS += -I$(PROJECT_SYSTEMC)/include
INCDIRS += -I$(PROJECT_CONNECTIONS)/include
INCDIRS += -I$(PROJECT_MATCHLIB)/cmod/include
INCDIRS += -I$(PROJECT_AC_TYPES)/include
INCDIRS += -I$(PROJECT_AC_SIMUTILS)/include
INCDIRS += -I$(PROJECT_GTEST)/include
INCDIRS += -I$(PROJECT_EIGEN)/include/eigen3
INCDIRS += -I$(PROJECT_JSON)/include
INCDIRS += -I$(SOURCE_DIR)../include

CPPFLAGS += $(INCDIRS)
CPPFLAGS_FAST = $(INCDIRS)
CPPFLAGS_FAST += -DCONNECTIONS_FAST_SIM -DSC_INCLUDE_DYNAMIC_PROCESSES -O3
CPPFLAGS_SYSC += $(INCDIRS) -DAC_IEEE_FLOAT_USE_BUILTIN
#CPPFLAGS += -DCONNECTIONS_SIM_ONLY -DCONNECTIONS_ACCURATE_SIM -DSC_INCLUDE_DYNAMIC_PROCESSES
CPPFLAGS += -DCONNECTIONS_ACCURATE_SIM -DSC_INCLUDE_DYNAMIC_PROCESSES

LIBS_SYSC += -lsystemc -lpthread
ifeq ($(HOSTNAME), Darwin)
LIBS += -lgtest -lgtest_main
else
LIBS += -lgtestd -lgtest_maind -lpthread
endif

# ---------------------------------------------------------------------

# sources_PROJECT_JSON := $(shell find $(PROJECT_JSON) -name '*.hpp')
# json_header: checkvar_PROJECT_JSON
#	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -x c++-header $(wildcard $(sources_PROJECT_JSON))

import_stimref:
	@echo "Importing Keras Stimulus Reference Data"
	@echo "--------------------------------------"
	@cp -f $(SOURCE_DIR)../../KERAS/output/*image* $(SOURCE_DIR)../stimref/fmap
	@cp -f $(SOURCE_DIR)../../KERAS/output/*weight* $(SOURCE_DIR)../stimref/coef
	@cp -f $(SOURCE_DIR)../../KERAS/output/*bias* $(SOURCE_DIR)../stimref/coef

# ---------------------------------------------------------------------

test_0_Mem.exe: checkvars test_0_Mem.cpp
	$(call print_color,[Building test_0_Mem.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_0_Mem.cpp) -o $@ $(LIBS)

test_0_Buffer3D.exe: checkvars test_0_Buffer3D.cpp
	$(call print_color,[Building test_0_Buffer3D.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_0_Buffer3D.cpp) -o $@ $(LIBS)

test_0_Json.exe: checkvars test_0_Json.cpp
	$(call print_color,[Building test_0_Json.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_0_Json.cpp) -o $@ $(LIBS)

test_1_Conv2DAlgo.exe: checkvars test_1_Conv2DAlgo.cpp
	$(call print_color,[Building test_1_Conv2DAlgo.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_1_Conv2DAlgo.cpp) -o $@ $(LIBS)

test_2_Conv2DLayer.exe: checkvars test_2_Conv2DLayer.cpp
	$(call print_color,[Building test_2_Conv2DLayer.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_2_Conv2DLayer.cpp) -o $@ $(LIBS)

test_3_MaxPoolLayer.exe: checkvars test_3_MaxPoolLayer.cpp
	$(call print_color,[Building test_3_MaxPoolLayer.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_3_MaxPoolLayer.cpp) -o $@ $(LIBS)

test_4_FlattenLayer.exe: checkvars test_4_FlattenLayer.cpp
	$(call print_color,[Building test_4_FlattenLayer.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_4_FlattenLayer.cpp) -o $@ $(LIBS)

test_5_ReluLayer.exe: checkvars test_5_ReluLayer.cpp
	$(call print_color,[Building test_5_ReluLayer.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_5_ReluLayer.cpp) -o $@ $(LIBS)

test_6_SoftmaxLayer.exe: checkvars test_6_SoftmaxLayer.cpp
	$(call print_color,[Building test_6_SoftmaxLayer.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_6_SoftmaxLayer.cpp) -o $@ $(LIBS)

test_7_AllLayers.exe: checkvars test_7_AllLayers.cpp
	$(call print_color,[Building test_7_AllLayers.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_7_AllLayers.cpp) -o $@ $(LIBS)

test_8_DUT_Adder.exe: checkvars test_8_DUT_Adder.cpp
	$(call print_color,[Building test_8_DUT_Adder.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS_SYSC) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_8_DUT_Adder.cpp) -o $@ $(LIBS_SYSC)

test_9_DUT_Conv2D.exe: checkvars test_9_DUT_Conv2D.cpp
	$(call print_color,[Building test_9_DUT_Conv2D.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS_SYSC) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_9_DUT_Conv2D.cpp) -o $@ $(LIBS_SYSC)

test_10_DUT_Cpu.exe: checkvars test_10_DUT_Cpu.cpp
	$(call print_color,[Building test_10_DUT_Cpu.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS_SYSC) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_10_DUT_Cpu.cpp) -o $@ $(LIBS_SYSC)

test_11_DUT_Top.exe: checkvars test_11_DUT_Top.cpp
	$(call print_color,[Building test_11_DUT_Top.exe])
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS_SYSC) $(LIBDIRS) $(wildcard $(SOURCE_DIR)test_11_DUT_Top.cpp) -o $@ $(LIBS_SYSC)

build_0_mem: test_0_Mem.exe
build_0_buffer: test_0_Buffer3D.exe
build_0_json: test_0_Json.exe
build_1: test_1_Conv2DAlgo.exe
build_2: test_2_Conv2DLayer.exe
build_3: test_3_MaxPoolLayer.exe
build_4: test_4_FlattenLayer.exe
build_5: test_5_ReluLayer.exe
build_6: test_6_SoftmaxLayer.exe
build_7: test_7_AllLayers.exe
build_8: test_8_DUT_Adder.exe
build_9: test_9_DUT_Conv2D.exe
build_10: test_10_DUT_Cpu.exe
build_11: test_11_DUT_Top.exe

build:	build_0_mem \
		build_0_buffer \
		build_0_json \
		build_1 \
		build_2 \
		build_3 \
		build_4 \
		build_5 \
		build_6 \
		build_7 \
		build_8 \
		build_9 \
		build_10 \
		build_11

run_test_0_Mem: test_0_Mem.exe
	$(call print_color,[Running $^])
	@./$^
run_test_0_Buffer3D: test_0_Buffer3D.exe
	$(call print_color,[Running $^])
	@./$^
run_test_0_Json: test_0_Json.exe
	$(call print_color,[Running $^])
	@./$^
run_test_1_Conv2DAlgo: test_1_Conv2DAlgo.exe
	$(call print_color,[Running $^])
	@./$^
run_test_2_Conv2DLayer: test_2_Conv2DLayer.exe
	$(call print_color,[Running $^])
	@./$^
run_test_3_MaxPoolLayer: test_3_MaxPoolLayer.exe
	$(call print_color,[Running $^])
	@./$^
run_test_4_FlattenLayer: test_4_FlattenLayer.exe
	$(call print_color,[Running $^])
	@./$^
run_test_5_ReluLayer: test_5_ReluLayer.exe
	$(call print_color,[Running $^])
	@./$^
run_test_6_SoftmaxLayer: test_6_SoftmaxLayer.exe
	$(call print_color,[Running $^])
	@./$^
run_test_7_AllLayers: test_7_AllLayers.exe
	$(call print_color,[Running $^])
	@./$^
run_test_8_DUT_Adder: test_8_DUT_Adder.exe
	$(call print_color,[Running $^])
	@./$^
run_test_9_DUT_Conv2D: test_9_DUT_Conv2D.exe
	$(call print_color,[Running $^])
	@./$^
run_test_10_DUT_Cpu: test_10_DUT_Cpu.exe
	$(call print_color,[Running $^])
	@./$^
run_test_11_DUT_Top: test_11_DUT_Top.exe
	$(call print_color,[Running $^])
	@./$^

run_0_mem: build_0_mem run_test_0_Mem
run_0_buffer: build_0_buffer run_test_0_Buffer3D
run_0_json: build_0_json run_test_0_Json
run_1: build_1 run_test_1_Conv2DAlgo
run_2: build_2 run_test_2_Conv2DLayer
run_3: build_3 run_test_3_MaxPoolLayer
run_4: build_4 run_test_4_FlattenLayer
run_5: build_5 run_test_5_ReluLayer
run_6: build_6 run_test_6_SoftmaxLayer
run_7: build_7 run_test_7_AllLayers
run_8: build_8 run_test_8_DUT_Adder
run_9: build_9 run_test_9_DUT_Conv2D
run_10: build_10 run_test_10_DUT_Cpu
run_11: build_11 run_test_11_DUT_Top

run:	run_0_mem \
		run_0_buffer \
		run_0_json \
		run_1 \
		run_2 \
		run_3 \
		run_4 \
		run_5 \
		run_6 \
		run_7 \
		run_8 \
		run_9 \
		run_10 \
		run_11

#.PHONY: build

# ---------------------------------------------------------------------------------------

define synth_hls
	mkdir -p ../work; cd ../work; \
	rm -rf ./$(1); \
	source ${CONF_QUESTA}; source ${CONF_CATAPULT}; \
	catapult -shell -product hls -file ../synthesis/$(2)
endef
define open_hls
	source ${CONF_QUESTA}; source ${CONF_CATAPULT}; \
	cd ../work; catapult $(1)
endef
define simu_rtl
	source ${CONF_QUESTA}; source ${CONF_CATAPULT}; \
	cd ../work/$(1); \
	/softs/MENTOR/catapult_2021/Mgc_home/bin/make -f ./scverify/Verify_concat_sim_rtl_vhdl_msim.mk SIMTOOL=msim simgui < "/dev/null"
endef
define export_rtl
	if [ ! -f ../work/$(1)/concat_rtl.v ] ; then \
		echo "File ../work/$(1)/concat_rtl.v does not exist";\
		exit 1; \
	else \
		echo "File ../work/$(1)/concat_rtl.v exists";\
		if [ -d ${RTL_DIR} ] ; then \
			cp ../work/$(1)/concat_rtl.v ${RTL_DIR}/concat_rtl_$(2).v;\
		fi; \
		cp ../work/$(1)/concat_rtl.v ${CURRENT_DIR}/../synthesis/output/concat_rtl_$(2).v;\
	fi;
endef

adder_synth:
	$(call synth_hls,work_adder,directives_adder.tcl)
adder_open:
	$(call open_hls,work_adder)	
adder_simu:
	$(call simu_rtl,work_adder/DUT_Adder.v1/)
adder_export:
	@$(call export_rtl,work_adder/DUT_Adder.v1,adder)

conv_synth:
	$(call synth_hls,work_conv2d,directives_conv2d.tcl)
conv_open:
	$(call open_hls,work_conv2d)
conv_simu:
	$(call simu_rtl,work_conv2d/DUT_Conv2D.v1/)
conv_export:
	@$(call export_rtl,work_conv2d/DUT_Conv2D.v1,conv)

export_code:
	@python3 ../script/generateCode.py

# ---------------------------------------------------------------------------------------

open_vscode:
	code

help:
	@echo "#-------------------------------------------------------------"
	@echo "# HW ACCELERATOR DESIGN FOR ML                                "
	@echo "#-------------------------------------------------------------"
	@echo "# Version : 0.1                                               "
	@echo "# Date    : 09/2023                                           "
	@echo "# Author  : Mathieu Lebon                                     "
	@echo "#-------------------------------------------------------------"
	@echo ""
	@echo "[Global]"
	@echo "  help               : print this help"
	@echo "  clean_local        : clean local directory (C++ dependencies)"
	@echo "  clean_test         : clean test directory (test executables))"
	@echo "  clean_work         : clean work directory (HLS)"
	@echo "  clean_all          : clean all directories (local, test, work)"
	@echo "  work_size          : print work directories size"
	@echo ""
	@echo "[C++/SystemC builds]"
	@echo "  open_vscode        : open VSCode"
	@echo "  build_0_mem        : build test_0_Mem.exe"
	@echo "  build_0_buffer     : build test_0_Buffer3D.exe"
	@echo "  build_0_json       : build test_0_Json.exe"
	@echo "  build_1            : build test_1_Conv2DAlgo.exe"
	@echo "  build_2            : build test_2_Conv2DLayer.exe"
	@echo "  build_3            : build test_3_MaxPoolLayer.exe"
	@echo "  build_4            : build test_4_FlattenLayer.exe"
	@echo "  build_5            : build test_5_ReluLayer.exe"
	@echo "  build_6            : build test_6_SoftmaxLayer.exe"
	@echo "  build_7            : build test_7_AllLayers.exe"
	@echo "  build_8            : build test_8_DUT_Adder.exe"
	@echo "  build_9            : build test_9_DUT_Conv2D.exe"
	@echo "  build_10           : build test_10_DUT_Cpu.exe"
	@echo "  build_11           : build test_11_DUT_Top.exe"
	@echo "  build              : build all tests"
	@echo ""
	@echo "[C++/SystemC runs]"
	@echo "  run_0_mem          : run test_0_Mem.exe"
	@echo "  run_0_buffer       : run test_0_Buffer3D.exe"
	@echo "  run_0_json         : run test_0_Json.exe"
	@echo "  run_1              : run test_1_Conv2DAlgo.exe"
	@echo "  run_2              : run test_2_Conv2DLayer.exe"
	@echo "  run_3              : run test_3_MaxPoolLayer.exe"
	@echo "  run_4              : run test_4_FlattenLayer.exe"
	@echo "  run_5              : run test_5_ReluLayer.exe"
	@echo "  run_6              : run test_6_SoftmaxLayer.exe"
	@echo "  run_7              : run test_7_AllLayers.exe"
	@echo "  run_8              : run test_8_DUT_Adder.exe"
	@echo "  run_9              : run test_9_DUT_Conv2D.exe"
	@echo "  run_10             : run test_10_DUT_Cpu.exe"
	@echo "  run_11             : run test_11_DUT_Top.exe"
	@echo ""
	@echo "[HLS]"
	@echo "  adder_synth        : run HLS synthesis for adder"
	@echo "  adder_open         : open HLS GUI for adder"
	@echo "  adder_simu         : run RTL simulation for adder"
	@echo "  adder_export       : export RTL for adder"
	@echo "  conv_synth         : run HLS synthesis for conv2d"
	@echo "  conv_open          : open HLS GUI for conv2d"
	@echo "  conv_simu          : run RTL simulation for conv2d"
	@echo "  conv_export        : export RTL for conv2d"
	@echo ""
	
# ---------------------------------------------------------------------------------------

ifeq ($(HOSTNAME), Darwin)
DELETE_OBJECTS := $(shell find . -name "*.dSYM") $(shell find . -name "*.exe" -maxdepth 1)
else
DELETE_OBJECTS := $(shell find . -name "*.exe")
endif

define split_line
	@echo "-------------------------------------------------------------"
endef

define print_size
	$(call split_line)
	@echo "$(1) :"
	$(call split_line)
	@find $(1) -maxdepth 1 -exec du -sh {} \;
	$(call split_line)
endef

work_size:
	$(call split_line)
	@echo "$(CURRENT_DIR) :"
	$(call split_line)
	@du -sh $(DELETE_OBJECTS)
	$(call print_size,$(CURRENT_DIR)/../local)
	$(call print_size,$(CURRENT_DIR)/../work)

clean_local:
	@echo "Cleaning up directory $(CURRENT_DIR)/../local"
	@rm -rf $(CURRENT_DIR)/../local
	@mkdir -p $(CURRENT_DIR)/../local
	@touch $(CURRENT_DIR)/../local/.gitkeep

clean_test:
	@echo "Cleaning up directory $(CURRENT_DIR)"
	@rm -rf $(DELETE_OBJECTS)

clean_work:
	@echo "Cleaning up directory $(CURRENT_DIR)/../work"
	@rm -rf $(CURRENT_DIR)/../work
	@mkdir -p $(CURRENT_DIR)/../work
	@touch $(CURRENT_DIR)/../work/.gitkeep

clean_all: clean_test clean_local clean_work

# ---------------------------------------------------------------------------------------

init_branch:
	@cd ../script; poetry run --quiet python ../script/gitHelper.py -rp $(CURRENT_DIR)/../ -m 'main' -bfm

get_updates:
	@cd ../script; poetry run --quiet python ../script/gitHelper.py -rp $(CURRENT_DIR)/../ -m 'main' -rfm
