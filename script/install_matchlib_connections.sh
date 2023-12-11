cd $PROJECT_INSTALL

# Configure MatchLib Connections
if [ ! -d ./matchlib_connections ]; then
  echo "Downloading MatchLib Connections..."
  git clone http://github.com/hlslibs/matchlib_connections.git
fi

PROJECT_CONNECTIONS=$PWD/matchlib_connections
export PROJECT_CONNECTIONS

echo "PROJECT_CONNECTIONS = $PROJECT_CONNECTIONS"

cd ..
