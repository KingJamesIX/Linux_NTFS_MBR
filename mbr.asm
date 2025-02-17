; Custom MBR Bootloader for Linux from NTFS
; Based on Windows XP MBR but modified to support Linux bootloaders like GRUB2
; Removes Windows-specific assumptions (NTLDR) and replaces with Linux boot sector execution
;
; Author: King James
; License: GNU GPL Open Source Licence
; Repository: https://github.com/KingJamesIX/Linux_NTFS_MBR
;
; Assembly: NASM
; Install: dd if=mbr.bin of=/dev/sdX bs=512 count=1
;
;-------------------------------------------------------------------------------

VOLBOOT_ORG             EQU 0x7C00
SIZE_SECTOR             EQU 512
PART_IFS                EQU 0x07    ; NTFS Partition Type
PART_FAT32              EQU 0x0B
PART_FAT32_XINT13       EQU 0x0C
PART_XINT13             EQU 0x0E
BOOTSECTRAILSIGH        EQU 0xAA55

RELOCATION_ORG          EQU 0x0600
READ_RETRY_CNT          EQU 5

section .text
org VOLBOOT_ORG

;-------------------------------------------------------------------------------
; Entry point: Start execution in BIOS boot mode (Real Mode, 16-bit)
;-------------------------------------------------------------------------------

start:
        xor     ax, ax
        mov     ss, ax
        mov     sp, VOLBOOT_ORG    ; Setup stack
        sti
        cld

        ; Relocate MBR to 0x600
        mov     si, VOLBOOT_ORG
        mov     di, RELOCATION_ORG
        mov     cx, SIZE_SECTOR
        rep     movsb
        jmp     relocate_done

relocate_done:

;-------------------------------------------------------------------------------
; Locate the active partition in the partition table.
;-------------------------------------------------------------------------------

        mov     bp, tab   ; Fixed: Removed `offset`
        mov     cl, 4    ; Four partition entries to check

active_loop:
        cmp     byte [bp], 0x80  ; Check for active partition
        jne     check_inactive
        jmp     StartLoad

check_inactive:
        add     bp, 16  ; Move to next partition entry
        loop    active_loop
        int     18h     ; No active partition, boot ROM BASIC

;-------------------------------------------------------------------------------
; Load the first sector of the active partition and execute it.
;-------------------------------------------------------------------------------

StartLoad:
        call    ReadSector
        jnc     CheckPbr

        ; If failed, check for backup boot sector
        cmp     byte [bp+4], PART_IFS
        je      trybackup
        jmp     display_error

trybackup:
        add     word [bp+8], 6
        call    ReadSector
        jnc     CheckPbr
        jmp     display_error

CheckPbr:
        cmp     word [VOLBOOT_ORG + SIZE_SECTOR - 2], BOOTSECTRAILSIGH
        je      done
        jmp     display_error

;-------------------------------------------------------------------------------
; Jump to Linux bootloader
;-------------------------------------------------------------------------------

done:
        mov     si, bp  ; Pass partition table entry to bootloader
        push    ds
        push    si
        retf  ; Fixed: Corrected label issue

;-------------------------------------------------------------------------------
; Display an error message if boot fails
;-------------------------------------------------------------------------------

display_error:
        mov     si, error_msg
        call    print_string
        jmp     $

print_string:
        lodsb
        test    al, al
        jz      $
        mov     ah, 0Eh
        int     10h
        jmp     print_string

section .data
error_msg db 'Error booting Linux from NTFS', 0
signa:  dw BOOTSECTRAILSIGH  ; ✅ Fix: moved from .bss to .data

;-------------------------------------------------------------------------------
; Partition table placeholder
;-------------------------------------------------------------------------------

section .bss
align 512

tab:    resb 64  ; Reserved space for partition table

section .text
ReadSector:
        ; Placeholder for BIOS read sector function
        ret
