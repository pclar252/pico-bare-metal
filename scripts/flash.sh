#!/usr/bin/env bash
set -euo pipefail

PICO_VID_PID="2e8a:0009"
USBIPD="/mnt/c/Program Files/usbipd-win/usbipd.exe"

if [[ $# -lt 1 ]]; then
    echo "Usage: ./scripts/flash.sh <path/to/firmware.elf>"
    exit 1
fi

ELF="$1"

if [[ ! -f "$ELF" ]]; then
    echo "File not found: $ELF"
    exit 1
fi

openocd \
    -f interface/cmsis-dap.cfg \
    -f target/rp2350.cfg \
    -c "adapter speed 5000" \
    -c "program $ELF verify reset exit"

# After SWD reset the Pico's USB re-enumerates, but the WSL2 handle goes stale.
# Detach and reattach via usbipd to get a live /dev/ttyACM0.
BUSID=$("$USBIPD" list 2>/dev/null | grep "$PICO_VID_PID" | awk '{print $1}' | tr -d '\r') || true
if [[ -n "$BUSID" ]]; then
    echo "Re-attaching Pico USB (BUSID $BUSID)..."
    "$USBIPD" detach --busid "$BUSID" 2>/dev/null || true
    sleep 1
    "$USBIPD" attach --wsl --busid "$BUSID"
    sleep 2
else
    echo "Warning: could not find Pico USB device to reattach (VID:PID $PICO_VID_PID)"
fi

echo "Done. Run ./scripts/serial.sh to view output."
