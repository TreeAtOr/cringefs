// change git test

#include "stdio.h"
#include "string.h"

#define CRINGEFS_STARTPOS 0xffff // for formating system

#define CRINGEFS_MAGIC 0x69A4

#define CRINGEFS_FILE_PATH_LEN 256

struct cringefs_super_block{
    int sb_magic;
    /* data */
};

struct cringefs_meta{
    char f_path[CRINGEFS_FILE_PATH_LEN];
    // char is_dir = 0/1
    // ptr to start block
    // amount blocks
    /* data */
};

struct cringefs_file_table{
    // array/list of loaded files
    // amount?
    /* data */
};

struct cringefs_file{
    // ptr to meta
    // ptr to blocks
};

// need?
struct cringefs_block{
    // ptr to block?
};

enum cringefs_command_types{
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
};

struct cringefs_command{
    enum cringefs_command_types command_type;
    char num_args;
    char* arg1;
    char* arg2;
    //char* arg3;
    //char* arg4;
};

int startup(char* device_path, struct cringefs_super_block* sb);
int shutdown();
int check_sb(struct cringefs_super_block* sb);

void parse_args();
int parse_str(char * str, struct cringefs_command* dst_command);
int exec_command(struct cringefs_command* command);

int open_file(char* path); // aka load to table
int close_file(char* path); // aka unload from table
int show_file(char* path); // show on screen
int write_file(char* path); // save to disk
int extend_file(char* path); // move? file and add free blocks
int shrink_file(char* path); // remove blocks
int copy_file(char* path, char* dst_path); // copy file from path to dst_path
int move_file(char* path, char* dst_path); // move file from path to dst path
int delete_file(char* path); // delete from disk
struct cringefs_file* find_file_table(char* path); // returns ptr to file
int* find_file_disk(char* path); // returns ptr to file on disk

int sort_meta();
int pack_fs();

int format_fs();

int add_to_table(struct cringefs_file* file);
int remove_from_table(char* path);
int clear_table();

//read_block ?
// write block ? 
