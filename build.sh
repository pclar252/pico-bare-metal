#!/usr/bin/env bash
set -euo pipefail

TARGET=${1:-host}

case "$TARGET" in
  host)
    cmake -S . -B build/host
    cmake --build build/host
    ;;
  test)
    cmake -S . -B build/host
    cmake --build build/host
    ./build/host/test/test_runner
    ;;
  arm)
    echo "No ARM support yet"
    ;;
  clean)
    rm -rf build/
    ;;
  *)
    echo "usage: $0 [host|test|arm|clean]"
    exit 1
    ;;
esac
