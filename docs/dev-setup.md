# Development Environment Setup

Host: Windows + WSL2 Ubuntu 24.04  
Board: RP2350 (Pico 2 clone, Micro USB)  
Debug probe: Raspberry Pi Debug Probe (CMSIS-DAP v2)

## Prerequisites

- `usbipd-win` installed on Windows (for forwarding USB devices into WSL2)
- WSL2 Ubuntu 24.04

## 1. First-time USB setup

Run once per device (persists across reboots). Open an **Administrator PowerShell**.

First, find BUSIDs via `usbipd list` — look for `2e8a:0009` (Pico) and `2e8a:000c` (probe):

```powershell
usbipd bind --busid 1-3   # Pico USB CDC
usbipd bind --busid 1-4   # Debug probe
```

Replace `1-3` / `1-4` with your actual BUSIDs.

## 2. Per-session USB attach

Run at the start of each dev session from WSL2:

```bash
./scripts/attach.sh
```

This attaches both the Pico USB CDC and the debug probe into WSL2 by calling `usbipd.exe` directly — no PowerShell window needed. `scripts/flash.sh` automatically reattaches the Pico after each flash, so no manual re-running is needed during the session.

## 3. Serial monitor (picocom)

Add your user to `dialout` (one-time):

```bash
sudo usermod -aG dialout $USER
# Log out and back in, or: newgrp dialout
```

Connect:

```bash
./scripts/serial.sh
```
> **Debug probe firmware:** Stay on v1.x. Upgrading to v2.x caused OpenOCD to fail
> with "CMSIS-DAP command CMD_INFO failed" in this WSL2 setup. v1.1 is confirmed working.

## 4. OpenOCD setup (one-time build)

Ubuntu 24.04's packaged OpenOCD predates RP2350. Build the Raspberry Pi fork from source:

```bash
sudo apt install -y git build-essential autoconf automake libtool pkg-config \
    libusb-1.0-0-dev libhidapi-dev libjim-dev

cd ~/projects
git clone https://github.com/raspberrypi/openocd.git --depth=1
cd openocd
git submodule update --init
./bootstrap
./configure --enable-cmsis-dap
make -j$(nproc)
sudo make install
```

Set up udev rules so OpenOCD can access the probe without sudo:

```bash
sudo cp /usr/local/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo udevadm trigger
sudo usermod -aG plugdev $USER
newgrp plugdev
```

## 5. Flashing via SWD

No BOOTSEL button dance required. With the debug probe connected:

```bash
./scripts/flash.sh build/examples/timer/timer_example.elf
```

The script flashes, resets the target, and reattaches the Pico's USB CDC into WSL2
automatically. Then open serial to see output:

```bash
./scripts/serial.sh
```

## Full dev loop

```bash
# 1. Build
./examples/timer/build.sh

# 2. Flash
./scripts/flash.sh build/examples/timer/timer_example.elf

# 3. Monitor
./scripts/serial.sh
```
