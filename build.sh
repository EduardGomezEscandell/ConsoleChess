PROJECT_DIR=$PWD
BUILD_DIR=$PROJECT_DIR/build
SOURCE_DIR=$PROJECT_DIR/source
EXECUTABLE=ConsoleChess

echo "Building $EXECUTABLE"

mkdir $BUILD_DIR

cd $BUILD_DIR
cmake $SOURCE_DIR
cmake --build .

cd $PROJECT_DIR

if test -f "$EXECUTABLE"; then
	rm "$EXECUTABLE"
fi
ln -s "$BUILD_DIR/$EXECUTABLE" .
