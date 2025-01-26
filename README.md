# Linux NTFS MBR Bootloader
; Custom MBR Bootloader for Linux from NTFS ; Based on Windows XP MBR but modified to support Linux bootloaders like GRUB2

# Linux NTFS MBR Bootloader

![License](https://img.shields.io/badge/license-MIT-blue.svg) ![Status](https://img.shields.io/badge/status-stable-green.svg)

## Overview
This project modifies the **Windows XP MBR bootloader** to allow **native Linux booting from an NTFS partition**. By replacing Windows-specific assumptions (`NTLDR`) with support for **Linux boot sectors**, this bootloader makes dual-booting, system recovery, and legacy hardware support significantly more powerful.

## Why Modify the XP Bootloader for Linux?
This modification **bridges the gap** between Microsoft's legacy boot infrastructure and Linux systems, enabling:

### 1. Native NTFS Boot for Linux
- ✅ Boot Linux **directly from an NTFS partition** without relying on GRUB.
- ✅ No need for an extra **boot partition** formatted in FAT32 or ext4.
- ✅ Great for **Windows-Linux hybrid environments**.

### 2. Cross-Booting Without GRUB
- ✅ Windows Boot Manager **fails? No problem.** Linux can still boot!
- ✅ Enables a **resilient dual-boot setup** without dependency on multiple bootloaders.
- ✅ Reduces **bootloader conflicts** between Windows and Linux.

### 3. Windows-Compatible Live Linux Distributions
- ✅ Boot a **Live Linux distro** directly from NTFS.
- ✅ No FAT32 **4GB file limit**, allowing **larger kernel images**.
- ✅ Security-focused distros (Kali, Tails) can now be **NTFS-native**.

### 4. Seamless Windows Recovery Integration
- ✅ A **Linux recovery system** can be embedded inside a Windows partition.
- ✅ System administrators can **repair Windows from within Linux**.
- ✅ Create **hidden NTFS Linux recovery partitions** for system repair.

### 5. Boot Linux on Legacy BIOS Systems Without UEFI
- ✅ Many **older BIOS-based PCs** lack support for modern Linux booting.
- ✅ Enables **Linux to boot on older hardware** without modifying partition tables.
- ✅ Great for **corporate legacy machines** that need NTFS-based system images.

### 6. AI-Powered System Recovery
- ✅ AI-based Linux diagnostics can **run from within an NTFS partition**.
- ✅ Enables **self-healing OS recovery tools**.
- ✅ **Cybersecurity monitoring** can operate inside Windows installations.

## Features
- 🚀 **Boots Linux natively from an NTFS partition**.
- 🚀 **No GRUB dependency required**.
- 🚀 **Works on BIOS-based systems (non-UEFI)**.
- 🚀 **Provides Windows recovery via embedded Linux rescue mode**.
- 🚀 **Compatible with GRUB2, Syslinux, and other Linux bootloaders**.

## Requirements
- A **BIOS-based system**.
- An **NTFS partition with a Linux bootloader installed**.
- `nasm` for compiling the bootloader.
- A tool like `dd` to write the MBR to disk.

## Installation
### Building the Bootloader
```sh
make
```
This generates `mbr.bin`, the bootloader binary.

### Installing to a Drive
⚠ **WARNING:** This writes directly to a disk. Use with caution!
```sh
sudo dd if=mbr.bin of=/dev/sdX bs=512 count=1
```
Replace `/dev/sdX` with your actual disk (e.g., `/dev/sda`).

### Verifying the Bootloader
Reboot your system and check if the bootloader correctly loads Linux from NTFS.

## Future Enhancements
- ✨ **Direct GRUB handoff** from the XP bootloader.
- ✨ **Custom Linux kernel booting from NTFS**.
- ✨ **Encrypted NTFS boot partition support**.

## Contributing
Contributions are welcome! Feel free to **fork the repository** and submit a pull request.

## License

This project is released under the **GNU GPL Open Source Licence**.

## Author

[King James](https://www.facebook.com/HRHKingJamesIXofScotland)

## Repository

[GitHub Repository](https://github.com/KingJamesIX/Linux_NTFS_MBR)

