#!/usr/bin/env sh
set -eu
if [ ! -x ./build/eniac_cpm22 ]; then
  echo "Executable not found; run scripts/build.sh first." >&2
  exit 1
fi
exec ./build/eniac_cpm22 "${1:-disk}"
