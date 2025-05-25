
PROJECT_DIR=$(dirname $(cd $(dirname $0);pwd))
cd $PROJECT_DIR/build
ctest --output-on-failure

