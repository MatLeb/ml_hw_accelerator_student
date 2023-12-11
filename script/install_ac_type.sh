cd $PROJECT_INSTALL

# Configure AC Datatypes
if [ ! -d ./ac_types ]; then
  echo "Downloading AC_Types..."
  git clone http://github.com/hlslibs/ac_types.git
fi

PROJECT_AC_TYPES=$PWD/ac_types
export PROJECT_AC_TYPES

echo "PROJECT_AC_TYPES = $PROJECT_AC_TYPES"

cd ..
