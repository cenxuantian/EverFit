# this file runs clang format for all files

PROJECT_DIR=$(dirname $(cd $(dirname $0);pwd))
echo "-- PROJECT_DIR is $PROJECT_DIR"
cd $PROJECT_DIR
find . -path "./build/*" -prune \
    -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \
    | xargs clang-format --style=file --verbose -i