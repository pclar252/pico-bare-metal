#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/../../build/test/target"

cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR" -DPICO_PLATFORM=rp2350
cmake --build "$BUILD_DIR"
