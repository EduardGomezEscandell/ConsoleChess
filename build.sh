PROJECT_DIR=$PWD

if $1 -z
then
	BUILD_TYPE=Release
else
	BUILD_TYPE=$1
fi


BUILD_DIR=$PROJECT_DIR/build
SOURCE_DIR=$PROJECT_DIR/source
EXECUTABLE=ConsoleChess

echo "Building $EXECUTABLE in $BUILD_TYPE mode"

mkdir $BUILD_DIR
cd $BUILD_DIR
mkdir $BUILD_TYPE

cd $BUILD_TYPE
cmake $SOURCE_DIR -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build .

cd $PROJECT_DIR

echo
echo "Your executable is at $BUILD_DIR/$BUILD_TYPE"