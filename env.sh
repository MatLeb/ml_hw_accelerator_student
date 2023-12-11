#!/bin/bash
HOST=`uname`
HOST_NAME=`uname -n`
export HOST
export HOST_NAME

if [[ $HOST_NAME == "vega.aime.local" ]]; then
    echo "Linux : $HOST_NAME"
    scl enable devtoolset-7 "bash -c 'source ./env_install.sh; bash'"
else
    echo "MacOS : $HOST_NAME"
    source ./env_install.sh
fi
