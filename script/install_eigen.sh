cd $PROJECT_INSTALL

PROJECT_EIGENVER=3.4.0
if [ ! -d ./eigen-$PROJECT_EIGENVER ]; then
  
  mkdir -p ./BUILD
  cd ./BUILD

  echo "Downloading and building Eigen $PROJECT_EIGENVER ..."

  # Download SystemC
  rm -f eigen-$PROJECT_EIGENVER.tar.gz
  git clone https://gitlab.com/libeigen/eigen.git eigen-$PROJECT_EIGENVER
  cd eigen-$PROJECT_EIGENVER
  git fetch --all --tags
  git checkout tags/$PROJECT_EIGENVER
  
  # Build/Install
  rm -rf build
  mkdir build
  cd build
  if [[ $HOST == "Darwin" ]]; then
    echo "MAC install"
    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_FLAGS='-std=c++11' -DCMAKE_INSTALL_PREFIX:PATH=$PWD/../../../eigen-$PROJECT_EIGENVER ..
  else
    echo "Linux install"
    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_FLAGS='-std=c++11' -DCMAKE_INSTALL_PREFIX:PATH=$PWD/../../../eigen-$PROJECT_EIGENVER ..
  fi
  make -j4 all install
	
  cd ../../..
fi

PROJECT_EIGEN=$PWD/eigen-$PROJECT_EIGENVER
export PROJECT_EIGEN

echo "PROJECT_EIGEN = $PROJECT_EIGEN"

cd ..
