// change git test

#include "stdio.h"
#include "string.h"

#define CFS_STARTPOS 0xffff // for formating system

#define CFS_MAGIC 0x69A4

#define CFS_FILE_PATH_LEN 256

typedef struct cfs_super_block_t{
    int sb_magic;
    /* data */

} cfs_super_block, *cfs_super_block_ptr;

typedef struct cfs_meta_t{

    char f_path[CFS_FILE_PATH_LEN];

    // char is_dir = 0/1
    // ptr to start block
    // amount blocks
    /* data */

} cfs_meta;

typedef struct cfs_file_table_t{
    // array/list of loaded files

    // amount?
    /* data */

} cfs_file_table;


typedef struct �fs_file_t {
    // ptr to meta
    // ptr to blocks

} �fs_file, *�fs_file_ptr;

// need?
typedef struct cfs_block_t{
    // ptr to block?
} cfs_block;

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



int open_file(char* path); // load to table

int close_file(char* path); // unload from table

int show_file(char* path); // show on screen

int write_file(char* path); // save to disk

int extend_file(char* path); // move? file and add free blocks

int shrink_file(char* path); // remove blocks

int copy_file(char* path, char* dst_path); // copy file from path to dst_path

int move_file(char* path, char* dst_path); // move file from path to dst_path

int delete_file(char* path); // delete from disk

struct cfs_file* find_file_table(char* path); // returns ptr to file

int* find_file_disk(char* path); // returns ptr to file on disk



int sort_meta();

int pack_fs();

int format_fs();




int add_to_table(�fs_file_ptr file);

int remove_from_table(char* path);

int clear_table();

//read_block ?
// write block ? 
