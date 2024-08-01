#ifndef FILESYS_H
#define FILESYS_H


#include <time.h>
#include <stdint.h>

#define DATE_LENGTH 20 // dd:mm:yyyy hh:mm:ss\0
#define READ_PERM 0x01  // 0001
#define WRITE_PERM 0x04 // 0100

typedef struct __attribute__ ((packed)){
    char filename[32]; // 32 byte name
    int size;
    char user_perm; // Should be initialized to 0.
    char last_modification_date[DATE_LENGTH];
    char file_creation_date[DATE_LENGTH];
    uint32_t first_block_addr;
    char password[9];

} DirectoryEntry; // 90 byte

typedef struct __attribute__ ((packed)){ 
    int block_size;
    int block_count;
    uint8_t* fat_first_addr;
    DirectoryEntry root;
} superblock; // 99 byte


#endif 