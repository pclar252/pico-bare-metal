#!/usr/bin/env bash
set -euo pipefail

TARGET=${1:-host}

case "$TARGET" in
  host)
    cmake -S . -B build/host
    cmake --build build/host
    ;;
  host-test)
    cmake -S . -B build/host
    cmake --build build/host
    ./build/host/test/host/test_runner
    ;;
  pico)
    echo "No ARM support yet"
#    cmake -S . -B build/pico \
#      -DCMAKE_TOOLCHAIN_FILE=$PICO_SDK_PATH/cmake/toolchain/pico-arm.gcc.cmake \
#      -DPICO_PLATFORM=rp2350
#    cmake --build build/pico
    ;;
  pico-test)
    echo "No ARM support yet"
#    cmake -S . -B build/pico-test \
#      -DCMAKE_TOOLCHAIN_FILE=$PICO_SDK_PATH/cmake/toolchain/pico-arm.gcc.cmake \
#      -DPICO_PLATFORM=rp2350
#    cmake --build build/pico-test
#    picotool load build/pico-test/test/target/test_runner.uf2 --force
#     serial capture?
    ;;
  clean)
    rm -rf build/
    ;;
  *)
    echo "usage: $0 [host|host-test|pico|pico-test|clean]"
    exit 1
    ;;
esac
