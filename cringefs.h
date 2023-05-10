// change git test

#include "stdio.h"
#include "string.h"
#include "stdlib.h" // calloc
#include <unistd.h> // read

#define CFS_STARTPOS 0xffff // for formating system

#define CFS_MAGIC 0x69A4

#define CFS_FILE_PATH_LEN 256
#define CFS_ONE_BLOCK_SIZE 2048 // random

typedef struct cfs_super_block_t{
    int sb_magic;

    /* data */

} cfs_super_block, *cfs_super_block_ptr;

typedef struct cfs_meta_t{

    char f_path[CFS_FILE_PATH_LEN];
    int start_block_idx;
    //int* start_block_ptr; 
    int size; // in bytes

    // char is_dir = 0/1

} cfs_meta, *cfs_meta_ptr;

// need?
typedef struct cfs_block_t {
    // ptr to block?
} cfs_block;



typedef struct сfs_file_t {
    cfs_meta_ptr meta_ptr;
    char* content;


} сfs_file, * сfs_file_ptr;



typedef struct cfs_file_table_t{

    int table_size; // количество в таблице
    cfs_file_ptr* table; // сама таблица, массив указателей 
    // убрать * !??

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
    EXTEND,   // need command or it is inner function?
    SHRINK,   // need_command or it is inner function?
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



int startup(char* device_path, cfs_super_block_ptr sb);

int shutdown();

int check_sb(cfs_super_block_ptr sb);



void parse_args();

int parse_str(char* str, cfs_command_ptr dst_command);

int exec_command(cfs_command_ptr command);



int cfs_fopen(char* path); // load to table

int close_file(char* path); // unload from table

int show_file(char* path); // show on screen

int write_file(char* path); // save to disk

int extend_file(char* path); // move? file and add free blocks

int shrink_file(char* path); // remove blocks

int copy_file(char* path, char* dst_path); // copy file from path to dst_path

int move_file(char* path, char* dst_path); // move file from path to dst_path

int delete_file(char* path); // delete from disk

cfs_file_ptr find_file_table(char* path); // returns ptr to file

int* find_file_disk(char* path); // returns ptr to file on disk



int sort_meta();

int pack_fs();

int format_fs();




int add_to_table(сfs_file_ptr file);

int remove_from_table(char* path);

int clear_table();

//read_block ?
// write block ? 
