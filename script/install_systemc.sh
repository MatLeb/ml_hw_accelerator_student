cd $PROJECT_INSTALL

# Configure SystemC 2.3.3 (download and build if needed)
PROJECT_SYSCVER=2.3.3
if [ ! -d ./systemc-$PROJECT_SYSCVER ]; then
  
  mkdir -p ./BUILD
  cd ./BUILD

	echo "Downloading and building SystemC $PROJECT_SYSCVER ..."

  # Download SystemC
  rm -f systemc-$PROJECT_SYSCVER.tar.gz
  wget --no-check-certificate https://www.accellera.org/images/downloads/standards/systemc/systemc-$PROJECT_SYSCVER.tar.gz
  tar xvfz ./systemc-$PROJECT_SYSCVER.tar.gz

  # Build/Install SystemC
  CXX="g++ -std=c++11"
  export CXX
  cd systemc-$PROJECT_SYSCVER
  rm -rf build
  mkdir build
  cd build
  if [[ $HOST == "Darwin" ]]; then
   echo "MAC install"
   cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_FLAGS='-std=c++11' -DCMAKE_INSTALL_PREFIX:PATH=$PROJECT_INSTALL/systemc-$PROJECT_SYSCVER ..
  else
   echo "Linux install"
   cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_FLAGS='-std=c++11' -DCMAKE_INSTALL_PREFIX:PATH=$PROJECT_INSTALL/systemc-$PROJECT_SYSCVER ..
  fi
  #cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_CXX_STANDARD=11 -DENABLE_PTHREADS=true -DCMAKE_CXX_FLAGS='-std=c++11' -DCMAKE_INSTALL_PREFIX:PATH=$PWD/../../systemc-$PROJECT_SYSCVER-install ..
  make -j4 all install
	
  # Clean SystemC
  cd ../..
  rm -rf systemc-$PROJECT_SYSCVER.tar.gz
  cd ..
fi

PROJECT_SYSTEMC=$PROJECT_INSTALL/systemc-$PROJECT_SYSCVER
export PROJECT_SYSTEMC
PROJECT_SYSTEMC_BUILD=$PROJECT_INSTALL/BUILD/systemc-$PROJECT_SYSCVER
export PROJECT_SYSTEMC_BUILD

echo "PROJECT_SYSTEMC = $PROJECT_SYSTEMC"
echo "PROJECT_SYSTEMC_BUILD = $PROJECT_SYSTEMC_BUILD"

cd ..
