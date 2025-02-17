#ifndef MBR_H
#define MBR_H

#include <stdint.h>

#define MBR_SIZE 512
#define PARTITION_ENTRY_SIZE 16
#define NUM_PARTITIONS 4
#define BOOT_SIGNATURE 0xAA55

// Partition types
#define PART_TYPE_NTFS 0x07
#define PART_TYPE_FAT32 0x0B
#define PART_TYPE_FAT32_LBA 0x0C
#define PART_TYPE_LBA 0x0E

// Bootloader code size
define X86BOOTCODE_SIZE 512

// MBR Partition Table Entry Structure
typedef struct {
    uint8_t boot_flag;        // Boot indicator (0x80 = bootable, 0x00 = non-bootable)
    uint8_t start_head;       // Starting head
    uint8_t start_sector;     // Starting sector (bits 0-5), starting cylinder (bits 6-7)
    uint8_t start_cylinder;
    uint8_t partition_type;   // Partition type code
    uint8_t end_head;         // Ending head
    uint8_t end_sector;       // Ending sector (bits 0-5), ending cylinder (bits 6-7)
    uint8_t end_cylinder;
    uint32_t start_lba;       // Starting LBA sector
    uint32_t total_sectors;   // Total sectors in partition
} __attribute__((packed)) partition_entry_t;

// MBR Structure
typedef struct {
    uint8_t bootloader[446];                // Bootloader code
    partition_entry_t partitions[NUM_PARTITIONS];  // Partition table entries
    uint16_t signature;                     // Boot signature (0xAA55)
} __attribute__((packed)) mbr_t;

// Bootloader binary code
static const unsigned char x86BootCode[X86BOOTCODE_SIZE] = {
    51,192,142,208,188,0,124,251,80,7,80,31,252,190,27,124,
    191,27,6,80,87,185,229,1,243,164,203,189,190,7,177,4,
    56,110,0,124,9,117,19,131,197,16,226,244,205,24,139,245,
    131,198,16,73,116,25,56,44,116,246,160,181,7,180,7,139,
    240,172,60,0,116,252,187,7,0,180,14,205,16,235,242,136,
    78,16,232,70,0,115,42,254,70,16,128,126,4,11,116,11,
    128,126,4,12,116,5,160,182,7,117,210,128,70,2,6,131,
    70,8,6,131,86,10,0,232,33,0,115,5,160,182,7,235,
    188,129,62,254,125,85,170,116,11,128,126,16,0,116,200,160,
    183,7,235,169,139,252,30,87,139,245,203,191,5,0,138,86,
    0,180,8,205,19,114,35,138,193,36,63,152,138,222,138,252,
    67,247,227,139,209,134,214,177,6,210,238,66,247,226,57,86,
    10,119,35,114,5,57,70,8,115,28,184,1,2,187,0,124,
    139,78,2,139,86,0,205,19,115,81,79,116,78,50,228,138,
    86,0,205,19,235,228,138,86,0,96,187,170,85,180,65,205,
    19,114,54,129,251,85,170,117,48,246,193,1,116,43,97,96,
    106,0,106,0,255,118,10,255,118,8,106,0,104,0,124,106,
    1,106,16,180,66,139,244,205,19,97,97,115,14,79,116,11,
    50,228,138,86,0,205,19,235,214,97,249,195,73,110,118,97,
    108,105,100,32,112,97,114,116,105,116,105,111,110,32,116,97,
    98,108,101,0,69,114,114,111,114,32,108,111,97,100,105,110,
    103,32,111,112,101,114,97,116,105,110,103,32,115,121,115,116,
    101,109,0,77,105,115,115,105,110,103,32,111,112,101,114,97,
    116,105,110,103,32,115,121,115,116,101,109,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,44,68,99,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,170
};

#endif // MBR_H
