# Linux NTFS MBR Bootloader
; Custom MBR Bootloader for Linux from NTFS ; Based on Windows XP MBR but modified to support Linux bootloaders like GRUB2

## Overview

This project is a **custom Master Boot Record (MBR) bootloader** designed to boot **Linux from an NTFS partition**. It is based on the **Windows XP MBR**, but has been modified to:

- Remove dependencies on Windows (`NTLDR`).
- Support **Linux bootloaders** like **GRUB2** from an **NTFS partition**.
- Provide **error handling** for missing bootloaders.
- Work with BIOS boot mode (legacy systems).

## Features

- **Supports NTFS** (`07h` partition type) natively in the bootloader.
- **Loads Linux boot sectors** from an active NTFS partition.
- **Fails gracefully** with error messages when no valid bootloader is found.
- **Compatible with GRUB2**, Syslinux, and other Linux boot sectors.

## Requirements

- A **BIOS-based system** (not UEFI-only machines).
- An **NTFS-formatted partition** with a Linux bootloader installed.
- A tool like `dd` or `fdisk` to install the MBR.
- **NASM assembler** to compile the MBR bootloader.

## Installation

### Building the MBR Bootloader

To compile the MBR bootloader, run:

```sh
make
```

This generates `mbr.bin`, the bootloader binary.

### Installing to a Drive

⚠ **WARNING:** This command writes directly to a disk. Use with caution!

```sh
sudo dd if=mbr.bin of=/dev/sdX bs=512 count=1
```

Replace `/dev/sdX` with your actual disk (e.g., `/dev/sda`).

### Verifying the Bootloader

After installation, reboot your system and check if the bootloader correctly loads your Linux bootloader from NTFS.

## Error Messages

| Message                          | Meaning                                                |
| -------------------------------- | ------------------------------------------------------ |
| `Invalid partition table`        | The MBR found an issue with the partition table.       |
| `Error loading operating system` | The partition boot sector could not be loaded.         |
| `Missing operating system`       | No valid bootloader was found on the active partition. |

## Contributing

If you’d like to improve this bootloader, feel free to **fork the repository** and submit a pull request. Contributions are welcome!

## License

This project is released under the **GNU GPL Open Source Licence**.

## Author

[King James](https://www.facebook.com/HRHKingJamesIXofScotland)

## Repository

[GitHub Repository](https://github.com/KingJamesIX/Linux_NTFS_MBR)

