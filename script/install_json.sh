cd $PROJECT_INSTALL

# Configure MatchLib
if [ ! -d ./json ]; then
 mkdir -p ./BUILD
 cd ./BUILD
 git clone --branch v3.11.2 --depth 1 https://github.com/nlohmann/json.git
 #git clone --branch v3.11.2 --depth 1 git@github.com:nlohmann/json.git
 #git clone --branch v3.1.0 --depth 1 git@github.com:nlohmann/json.git
 cd json
 mkdir build
 cd build
 if [[ $HOST == "Darwin" ]]; then
  echo "MAC install"
  cmake -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_FLAGS='-std=c++11' -DCMAKE_INSTALL_PREFIX:PATH=$PWD/../../../json ..
 else
  echo "Linux install"
  cmake -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_FLAGS='-std=c++11' -DCMAKE_INSTALL_PREFIX:PATH=$PWD/../../../json ..
 fi
 make -j4 all install
 cd ../../..
fi

PROJECT_JSON=$PWD/json
export PROJECT_JSON

echo "PROJECT_JSON= $PROJECT_JSON"

cd ..
