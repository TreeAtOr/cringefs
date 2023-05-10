#include "cringefs.h"

int cfs_f_descriptor = -1;
cfs_super_block_ptr sb;
cfs_file_table_ptr ft;


int main(int argc, char* argv[]){
    // argv[1] это путь к файлу устройства(флешки) ( например "/dev/sda3" )

    if (argc <= 1){
        //print argument with device path missed
        return -1;
    }
    // startup(argv[1])

    //if(check_sb() == -1){
    // print super block corrupted / no fs on device
    // ask to continue
    //}

    
    // parse_args()

    // поймать сигнал ctrl+c? дла корректного shutdown
    // shutdown()

    return 0;
}

int startup(char* device_path, cfs_super_block_ptr sb){
    // cfs_f_descriptor = open(device_path)  // гуглите функцию open()
    // read sb
    check_sb(sb);
    // if something bad return -1
}

int shutdown(){
    // close(cfs_f_descriptor) ??? 
    // if something bad return -1
}

int check_sb(cfs_super_block_ptr sb){
    // check magic
    // if != CFS_MAGIC return -1
}




void parse_args(){

    //while (1)
    //{
        // read str, parse_str(char* str, ...);
        // if bad str, message
        // if good, exec_command() (use switch and cfs_command_type)
        // if exit return
    //}
    
}

// parse str, put command in dst_command. If something goes wrong return -1
int parse_str(char * str, cfs_command_ptr dst_command){
    // check str if it is command and it has correct arguments
    //fill dst_command struct
    
}

int exec_command(cfs_command_ptr command){

    switch (command->command_type)
    {
    case OPEN:
        open_file(command->arg1);
        break;
    case CLOSE:
        close_file(command->arg1);
        break;
    case SHOW:
        show_file(command->arg1);
        break;
    case DELETE:
        
    case EXIT:
        return 0;
    default:
        // print err
        break;
    }
}


cfs_meta_ptr find_meta_by_name(char* path)
{
    // if file at path not found, return nullptr
    // else return meta_ptr
}

int* block_idx_to_disc_ptr(int idx)
{
    // if invalid return nullptr

    int result = 0;
    result = idx * CFS_ONE_BLOCK_SIZE; // + sizeof(cfs_super_block) ?
}

int open_file(char* path){


    if (find_file_table(path) != nullptr) // already opened
    {
        return 0;
    }
    
    cfs_meta_ptr meta_ptr = find_meta_by_name(path);

    if (meta_ptr == nullptr) // not found on disc
    {
        return -1;
    }
    else
    {

        int* to_disc_ptr = block_idx_to_disc_ptr(meta_ptr->start_block_idx);

        if (to_disc_ptr == nullptr)
        {
            return -1; // error
        }

        int file_size = meta_ptr->size;


    }

    // if file already in table return 0
    // read file paths from disk until you find path
    // if path not found return -1
    // read file, add file to table
    
}

int close_file(char* path){
    // read table until you find file with path
    // if file has been modified save it
    // clear it
}

int show_file(char* path){

    // find file with path in table
    // show on screen
    // if not found
    // find file on disk
    // show on screen
    // if not foud
    // print no such file
}

int write_file(char* path){
    // find file with path in table
    // if not found return -1
    // else just write to disk
}

int extend_file(char* path){
    // think 
}

int shrink_file(char* path){
    // think
}

int copy_file(char* path, char* dst_path){
    // find file by path in table/disk
    // if not found print, return -1 
    // check existance of dst_path
    // if exists print, return -1
    // create new meta, blocks
    // copy data
}

int move_file(char* path, char* dst_path){

    // copy_file()
    // delete file with path
}

int delete_file(char* path){
    // find file in table
    // unload()
    // find file on disk
    // set meta cleared
}


int sort_meta(){
    // hardcore
}
int pack_fs(){
    // hardcore
}

int format_fs(){
    // clear table
    // reset superblock
    // write sb
}

int remove_from_table(char* path){
    // find and clear
}

int clear_table(){
    // clear all
}

//return ptr if found file else nullptr
cfs_file_ptr find_file_table(char* path){
    // find in table
}

// return ptr if found file else nullptr
int* find_file_disk(char* path){
    // find on disk
}
