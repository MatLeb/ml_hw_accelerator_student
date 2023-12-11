#!/bin/bash

export PATH="/softs/cmake-3.27.6-linux-x86_64/bin:$PATH"

PROJECT_INSTALL=$PWD/local
export PROJECT_INSTALL

# Check GCC version and store in variable
GCC_VERSION=$(gcc -dumpversion)
GCC_PATH=$(which gcc)

echo "--------------------------------------"
echo "PROJECT_INSTALL = $PROJECT_INSTALL"
echo "HOST            = $HOST"
echo "GCC_VERSION     = $GCC_VERSION"
echo "GCC_PATH        = $GCC_PATH"
echo "--------------------------------------"

mkdir -p $PROJECT_INSTALL

source ./script/install_python.sh
source ./script/install_systemc.sh
source ./script/install_matchlib_connections.sh
source ./script/install_matchlib.sh
source ./script/install_ac_type.sh
source ./script/install_ac_simutils.sh
source ./script/install_gtest.sh
source ./script/install_eigen.sh
source ./script/install_json.sh

rm -rf $PROJECT_INSTALL/BUILD

