#!/bin/sh
# Run from any directory, after extracting tests/ alongside src/.
set -eu
PROJECT_ROOT=$(CDPATH='' cd -- "$(dirname -- "$0")/.." && pwd)
SRC="$PROJECT_ROOT/src"
TEST="$PROJECT_ROOT/tests/test_optional_late_features.cpp"
if [ ! -f "$SRC/item.cc" ] || [ ! -f "$SRC/item.hpp" ]; then
  echo 'Missing src/item.cc / src/item.hpp: extract tests/ into the Elvex project root.' >&2
  exit 2
fi
CXX=${CXX:-c++}
DIR=$(mktemp -d "${TMPDIR:-/tmp}/elvex-normalize-regression.XXXXXX")
trap 'rm -rf "$DIR"' EXIT HUP INT TERM
case "$(uname -s)" in
  Darwin) GC_FLAGS='-Wl,-dead_strip' ;;
  *) GC_FLAGS='-Wl,--gc-sections' ;;
esac

# Compile independent translation units in groups of four. On macOS,
# ld's -dead_strip removes unrelated Elvex entry points at link time.
# Compile the exact source under test; no mocked implementation is used.
compile_one() {
  "$CXX" -std=c++17 -O0 -ffunction-sections -fdata-sections \
    -I"$SRC" -c "$1" -o "$2"
}

jobs=''
count=0
for f in item rule terms facade serializable flags uniq-id features feature value listfeatures orderspecs orderspec bitset vartable pairp statement statements fatal_exception; do
  compile_one "$SRC/$f.cc" "$DIR/$f.o" &
  jobs="$jobs $!"
  count=$((count + 1))
  if [ "$count" -eq 4 ]; then
    for pid in $jobs; do wait "$pid"; done
    jobs=''
    count=0
  fi
done
compile_one "$TEST" "$DIR/test.o" &
jobs="$jobs $!"
for pid in $jobs; do wait "$pid"; done
"$CXX" "$DIR"/*.o "$GC_FLAGS" -o "$DIR/test_optional_late_features"
"$DIR/test_optional_late_features"
