cd $PROJECT_INSTALL

# Configure MatchLib
if [ ! -d ./googletest ]; then
 
 mkdir -p ./BUILD
 cd ./BUILD
 git clone git@github.com:google/googletest.git
 cd googletest
 git fetch --all --tags

 if [[ $HOST == "Darwin" ]]; then

  echo "MAC install"
  #git checkout tags/v1.14.0
  git checkout tags/release-1.12.1
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_FLAGS='-std=c++11' -DCMAKE_INSTALL_PREFIX:PATH=$PWD/../../../googletest ..

 else

  echo "Linux install"
  if [ $GCC_VERSION -gt 9 ]; then
    git checkout tags/release-1.12.1
  else
    git checkout tags/release-1.10.0
  fi
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_FLAGS='-std=c++11' -DCMAKE_INSTALL_PREFIX:PATH=$PWD/../../../googletest ..

 fi

 make CPPFLAGS="-Wno-error=format-truncation" -j4 all install
 cd ../../..

fi

PROJECT_GTEST=$PWD/googletest
export PROJECT_GTEST

echo "PROJECT_GTEST= $PROJECT_GTEST"

cd ..
