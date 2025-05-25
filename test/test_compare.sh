
function fatal {
    echo "error: $1"
    exit 1
}

while [[ $# -gt 0 ]]; do
    case $1 in
        --name)
            if [[ -z "$1" ]]; then
                fatal "missing argument <test_name> to option $1"
            fi
            test_name="$2"
            shift
            shift
            ;;
        --src-dir)
            if [[ -z "$1" ]]; then
                fatal "missing argument <cmake source dir> to option $1"
            fi
            CMAKE_SOURCE_DIR="$2"
            shift
            shift
            ;;
        -h)
            echo "usage: $0 <options>"
            echo "options:"
            echo "  --name <test_name>"
            echo "  --src-dir <cmake source dir>"
            exit 0
            ;;
        *)
            fatal "unknown option '$1'"
            ;;
    esac
done

diff \
    <(${CMAKE_SOURCE_DIR}/build/preprocessor/everfit --cpp ${CMAKE_SOURCE_DIR}/test/${test_name}.cpp.in) \
    <(cat ${CMAKE_SOURCE_DIR}/test/${test_name}.cpp.expected)
