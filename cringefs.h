// change git test

#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h" // calloc
#include "stdint.h" // uintptr_t
#include <unistd.h> // read
#include "fcntl.h"

#define DEBUG 1

#define CFS_STARTPOS 0xffff // for formating system
#define CFS_ENDPOS 0x5ffff

#define CFS_MAGIC 0x69A4

#define CFS_FILE_PATH_LEN 256
#define CFS_ONE_BLOCK_SIZE 4096
#define CFS_SUPERBLOCK_SIZE CFS_ONE_BLOCK_SIZE
#define CFS_ONE_META_SIZE 512

#ifdef __linux__
#define nullptr 0
#endif

typedef struct cfs_super_block_t{
    int sb_magic;
    int* start_block_ptr;
    int* free_space_ptr;
    int* end_meta_ptr;
    int* start_meta_ptr;
} cfs_super_block, *cfs_super_block_ptr;

typedef struct cfs_meta_t{

    char f_path[CFS_FILE_PATH_LEN];
    int start_block_idx;
    //int* start_block_ptr; 
    int size; // in bytes
    char is_dir;
    char cleared;

} cfs_meta, *cfs_meta_ptr;

// need?
typedef struct cfs_block_t {
    // ptr to block?
} cfs_block;



typedef struct cfs_file_t {
    cfs_meta_ptr meta_ptr;
    char* content;


} cfs_file, * cfs_file_ptr;



typedef struct cfs_file_table_t{

    int table_size; // ���������� � �������
    cfs_file_ptr* table; // ���� �������, ������ ���������� 
    // ������ * !??

} cfs_file_table;




typedef enum cfs_command_type_t{
    OPEN,     // open  /text.txt
    CLOSE,    // close /text.txt
    SHOW,     // cat   /text.txt
    DELETE,   // rm    /text.txt
    CREATE,   // touch /text.txt
    COPY,     // cp    /text.txt /text2.txt
    MOVE,     // mv    /text.txt /dir/text.txt
    CREATEDIR,// mkdir /dir
    FORMAT,   // format
    EXTEND,   // command is needed or it is inner function?
    SHRINK,   // command is needed or it is inner function?
    EXIT      // exit
    // etc.
} cfs_command_type;

typedef struct cfs_command_t{
    cfs_command_type command_type;
    char num_args;
    char* arg1;
    char* arg2;
    //char* arg3;
    //char* arg4;
} cfs_command, *cfs_command_ptr;



int startup(char* device_path);

int shutdown();

int check_sb(cfs_super_block sb);



void parse_args();

int exec_command(cfs_command command);



int cfs_fopen(char* path); // load to table

int close_file(char* path); // unload from table

int show_file(char* path); // show on screen

// use during creation of new file to save it on disk
int write_file(cfs_file_ptr file_ptr); // save to disk // not needed 11.05.23 15:36 thinking

int save_file(char* path); // save file from table to disk (if needed)

int extend_file(char* path); // move? file and add free blocks

int shrink_file(char* path); // remove blocks

int copy_file(char* path, char* dst_path); // copy file from path to dst_path

int move_file(char* path, char* dst_path); // move file from path to dst_path

int delete_file(char* path); // delete from disk

// creates only on disk
int create_file(char* path); // create on disk

cfs_file_ptr find_file_table(char* path); // returns ptr to file

int* find_file_disk(char* path); // returns ptr to file on disk



int sort_meta();

int pack_fs();

// return index of first block
// requesting <minimum_blocks_num> blocks
// if not found return nullptr
int find_empty_space_in_meta(int minimum_blocks_num);

int format_fs();




int add_to_table(cfs_file_ptr file);

int remove_from_table(char* path);

int clear_table();



int disk_ptr_to_block_idx(int* ptr);

int* block_idx_to_disc_ptr(int idx);

int disk_ptr_to_meta_idx(int* ptr);

int* meta_idx_to_disc_ptr(int idx);

// get free block from end of blocks in fs, return index
int get_new_free_block_idx();



int copy_meta(cfs_meta_ptr src, cfs_meta_ptr dst);


void debug_print(char* str);