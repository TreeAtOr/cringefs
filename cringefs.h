// change git test

#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h" // calloc
#include "stdint.h" // uintptr_t
#include <unistd.h> // read
#include "fcntl.h"

#define DEBUG_ON 1

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
    int* end_meta_ptr; // last meta; if == CFS_CFS_ENDPOS then no files in fs :)
    int* start_meta_ptr;
} cfs_super_block, *cfs_super_block_ptr;

typedef struct cfs_meta_t{

    char f_path[CFS_FILE_PATH_LEN];
    int start_block_idx;
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

    size_t table_size; // size of table
    cfs_file_ptr* files; // table of opened files
    size_t count_opened_files;
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
    EXIT,     // exit
    DEBUG
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
// save superblock on disk
void save_sb();



void parse_args();

int exec_command(cfs_command command);



int cfs_fopen(char* path); // load to table

int close_file(cfs_file_ptr file); // unload from table

int show_file(char* path); // show on screen

// use during creation of new file to save it on disk
int write_file(cfs_file_ptr file_ptr, int meta_idx); // save to disk // not needed 11.05.23 15:36 thinking

int save_file(cfs_file_ptr file); // save file from table to disk (if needed)

int extend_file(cfs_meta_ptr _meta, int _nsize); // move? file and add free blocks

int shrink_file(cfs_meta_ptr _meta, int _nsize); // remove blocks

int copy_file(char* path, char* dst_path); // copy file from path to dst_path

int move_file(char* path, char* dst_path); // move file from path to dst_path

int delete_file(char* path); // delete from disk

// creates only on disk
int create_file(char* path); // create on disk

cfs_meta_ptr find_file_disk(char* path);



int sort_meta();

int pack_fs();

// return index of first block
// requesting <minimum_blocks_num> blocks
// if not found return nullptr
int find_empty_space_in_meta(int minimum_blocks_num);

int format_fs();




void init_file_table();

void destroy_table();

cfs_file_ptr find_file_table(char* path); // returns ptr to file

int add_to_table(cfs_file_ptr file);

int remove_from_table(char* path);

int clear_table();

void resize_file_table();

void shift_array_of_files(int start_index);



int disk_ptr_to_block_idx(int* ptr);

int* block_idx_to_disc_ptr(int idx);

int disk_ptr_to_meta_idx(int* ptr);

int* meta_idx_to_disc_ptr(int idx);

// get free block from end of blocks in fs, return index
int get_new_free_block_idx();

// add get_new_free_meta_idx



int copy_meta(cfs_meta_ptr src, cfs_meta_ptr dst);
// zero fill of meta
//void init_meta();

//  read meta from disk starting from disk_meta_ptr address
void read_meta(int* disk_meta_ptr, cfs_meta_ptr dst_meta);

// write meta to disk starting from disk_meta_ptr address
void write_meta(int* disk_meta_ptr, cfs_meta_ptr meta);


void debug_print(char* str);

// show all names of files on disk
void debug_print_files_meta_on_disk();


