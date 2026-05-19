#!/usr/bin/env bash
set -euo pipefail

DEVICE="${1:-/dev/ttyACM0}"
BAUD="${2:-115200}"

if [[ ! -e "$DEVICE" ]]; then
    echo "Device $DEVICE not found. Is the Pico attached via usbipd?"
    exit 1
fi

# Escape key remapped to Ctrl+T (0x14) to avoid conflict with tmux Ctrl+A prefix.
# Exit with: Ctrl+T Ctrl+X
exec picocom --escape 0x14 --noreset -b "$BAUD" "$DEVICE"
