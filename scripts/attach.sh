#!/usr/bin/env bash
set -euo pipefail

USBIPD="/mnt/c/Program Files/usbipd-win/usbipd.exe"

PICO_VID_PID="2e8a:0009"
PROBE_VID_PID="2e8a:000c"

attach_device() {
    local name="$1"
    local vid_pid="$2"

    local busid
    busid=$("$USBIPD" list 2>/dev/null | grep "$vid_pid" | awk '{print $1}' | tr -d '\r') || true

    if [[ -z "$busid" ]]; then
        echo "Warning: $name ($vid_pid) not found — is it plugged in?"
        return
    fi

    echo "Attaching $name (BUSID $busid)..."
    "$USBIPD" detach --busid "$busid" 2>/dev/null || true
    sleep 1
    "$USBIPD" attach --wsl --busid "$busid"
    echo "  Done."
}

attach_device "Pico USB CDC"  "$PICO_VID_PID"
attach_device "Debug probe"   "$PROBE_VID_PID"

echo ""
echo "Verify with: lsusb | grep 2e8a"
