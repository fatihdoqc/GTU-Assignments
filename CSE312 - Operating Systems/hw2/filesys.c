#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "filesys.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stddef.h>

#define BLOCK_COUNT 4096 // 12 bit entry width, 2^12 blocks

uint32_t simple_hash(const char *str);
void set_password(DirectoryEntry *entry, const char *password);
int verify_password(const DirectoryEntry *entry, const char *password);
void initialize_superblock(superblock* sb, int block_size , int block_count, uint8_t* fat_first_addr, DirectoryEntry root);

int main(int argc, char *argv[]){

    if (argc != 3)
    {
        printf("Bad usage: Usage is makeFileSystem <block_size> mySystem.dat\n");
        return 1;
    }

    int BLOCK_SIZE;

    if (strcmp(argv[1], "0.5") == 0)
    {
        BLOCK_SIZE = 512;
    }
    else if (strcmp(argv[1], "1") == 0)
    {
        BLOCK_SIZE = 1024;
    }
    else{
        printf("Bad usage: Usage is makeFileSystem <block_size> mySystem.dat\n");
        return 1;
    }

    char file_system_name[32];
    strcpy(file_system_name,argv[2]);
    
    uint8_t *filesystem = (uint8_t *)malloc(BLOCK_SIZE * BLOCK_COUNT);
    if (filesystem == NULL) {
        perror("Error allocating memory");
        return 1;
    }

    // Two's complement representation of -2 in 8 bits is 254
    for (int i = 0; i < BLOCK_SIZE * BLOCK_COUNT; i++) {
        filesystem[i] = 254;
    }

    uint16_t *fat = (uint16_t *)malloc(BLOCK_COUNT * sizeof(uint16_t));
    if (fat == NULL) {
        perror("Error allocating memory");
        free(filesystem);
        return 1;
    }

    for ( uint16_t i = 0; i < BLOCK_COUNT; i++) {
        fat[i] = 65534;
    }
    
    uint8_t *fat_first_addr = (uint8_t *)(filesystem) + sizeof(superblock); // Put fat[0] the root address
    uint8_t *fat0_addr = fat_first_addr + BLOCK_COUNT * sizeof(uint16_t);
    *(uint8_t **)fat = fat0_addr;

    DirectoryEntry root;
    strcpy(root.filename, "root");
    root.size = 0;
    root.user_perm = 0;
    root.user_perm |= READ_PERM;
    root.user_perm |= WRITE_PERM;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(root.file_creation_date, "%02d:%02d:%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    sprintf(root.last_modification_date, "%02d:%02d:%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    root.first_block_addr = *(filesystem +  BLOCK_COUNT * sizeof(uint16_t) );

    memcpy(filesystem + sizeof(superblock) + BLOCK_COUNT * sizeof(uint16_t), &root, sizeof(DirectoryEntry));
    // put root block into filesystem + superblock + fat  

    superblock *sb = (superblock *)filesystem;

    initialize_superblock(sb, BLOCK_SIZE, BLOCK_COUNT, filesystem + sizeof(superblock) + 1, root);

    memcpy(filesystem + sizeof(superblock), fat, BLOCK_COUNT * sizeof(uint16_t));
    // put FAT into filesystem + superblock

    //printf("b : %d , %d\n",filesystem, filesystem + sizeof(superblock) + 1);
    
    int fd = open(file_system_name, O_CREAT | O_WRONLY, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    ssize_t bytes_written = write(fd, filesystem, BLOCK_SIZE * BLOCK_COUNT);
    if (bytes_written != BLOCK_SIZE * BLOCK_COUNT) {
        perror("Error writing to file");
        close(fd);
        free(filesystem);
        free(fat);
        return 1;
    }

    close(fd);

    free(filesystem);
    free(fat);


    /*char user_permissions = 0;
    user_permissions |= READ_PERM;
    user_permissions |= WRITE_PERM;

    if (user_permissions & READ_PERM)
    {
        printf("user can read\n");
    }
    if (user_permissions & WRITE_PERM)
    {
        printf("user can write\n");
    }
    if ((user_permissions & READ_PERM) && (user_permissions & WRITE_PERM))
    {
        printf("user has both\n");
    }*/
    
    
    return 0;
}

uint32_t simple_hash(const char *str) {
    uint32_t hash = 0;
    while (*str) {
        hash = hash * 31 + *str++;
    }
    return hash;
}

void set_password(DirectoryEntry *entry, const char *password) {
    uint32_t hash = simple_hash(password);
    snprintf(entry->password, sizeof(entry->password), "%08x", hash);
}

int verify_password(const DirectoryEntry *entry, const char *password) {
    uint32_t hash = simple_hash(password);
    char hash_str[9];
    snprintf(hash_str, sizeof(hash_str), "%08x", hash);
    return strcmp(entry->password, hash_str) == 0;
}
void initialize_superblock(superblock* sb, int block_size , int block_count, uint8_t* fat_first_addr, DirectoryEntry root){
    sb->block_size = block_size;
    sb->block_count = block_count;
    sb->fat_first_addr = fat_first_addr;
    sb->root = root;
}