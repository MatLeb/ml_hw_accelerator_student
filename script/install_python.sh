cd $PROJECT_INSTALL

# Check if python3 is installed
if ! command -v python3 &> /dev/null
then
    echo "python3 could not be found"
    exit
fi

# Check if pip is installed
if ! command -v pip &> /dev/null
then
    python3 -m pip install pip
    pip install --upgrade pip
fi
# Check if poetry is installed
if ! command -v poetry &> /dev/null
then
    pip3 install poetry
fi

cd ../script

# Install dependencies
poetry install --quiet --no-root

cd ..