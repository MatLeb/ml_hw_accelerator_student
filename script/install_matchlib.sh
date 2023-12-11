cd $PROJECT_INSTALL

# Configure MatchLib
if [ ! -d ./matchlib ]; then
 git clone http://github.com/NVlabs/matchlib.git
fi

PROJECT_MATCHLIB=$PWD/matchlib
export PROJECT_MATCHLIB

echo "PROJECT_MATCHLIB= $PROJECT_MATCHLIB"

cd ..
