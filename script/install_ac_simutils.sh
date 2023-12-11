cd $PROJECT_INSTALL

# Configure AC Simutils
if [ ! -d ./ac_simutils ]; then
  echo "Downloading AC_Simutils..."
  git clone http://github.com/hlslibs/ac_simutils.git
fi

PROJECT_AC_SIMUTILS=$PWD/ac_simutils
export PROJECT_AC_SIMUTILS

echo "PROJECT_AC_SIMUTILS= $PROJECT_AC_SIMUTILS"

cd ..
