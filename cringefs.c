#include "cringefs.h"

int cfs_f_descriptor = -1;
cfs_super_block_ptr sb;
cfs_file_table ft;


int main(int argc, char* argv[]){

    // if not -> Houston, we have problems 
    assert(sizeof(cfs_meta) <= CFS_ONE_META_SIZE);


    // argv[1] это путь к файлу устройства(флешки) ( например "/dev/sda3" )

    printf("Debug: program starts\n");

    if (argc <= 1){
        //print argument with device path missed
        printf("Debug: program ends\n");
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
    printf("Debug: program ends\n");
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

    // Для Глеба:
    // Список команд указан в комментариях к энуму cfs_command_type_t
    // Задача: отпарсить пользовательский ввод и запихать аргументы в структуру cfs_command_t
    // На основе этой структуры будет выполняться команда в файловой системе
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
        // open file with path <arg1>
        cfs_fopen(command->arg1);
        break;
    case CLOSE:
        // close file with path <arg1>
        close_file(command->arg1);
        break;
    case SHOW:
        // show file with path <arg1>
        show_file(command->arg1);
        break;
    case DELETE:
        // delete file with path <arg1>
        delete_file(command->arg1);
        break;
    case CREATE:
        // create file with path <arg1>
        create_file(command->arg1);
        break;
    case COPY:
        // copy from <arg1>(path) to <arg2>(destination path) 
        copy_file(command->arg1, command->arg2);
        break;
    case MOVE:
        // move from <arg1>(path) to <arg2>(destination path) 
        move_file(command->arg1, command->arg2);
        break;
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
    result = idx * CFS_ONE_BLOCK_SIZE; // + sizeof(cfs_super_block) ? + смещение суперлока на диске(CFS_STARTPOS)
}

int disk_ptr_to_block_idx(int* ptr){
    printf("TODO convertion from disk ptr to block idx");
}

int cfs_fopen(char* path){


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
/*
        int* to_disc_ptr = block_idx_to_disc_ptr(meta_ptr->start_block_idx);

        if (to_disc_ptr == nullptr)
        {
            return -1; // error
        }

        int file_size = meta_ptr->size;

        char* buf = calloc(file_size, sizeof(char));
        if (buf == nullptr)
        {
            return -1; // error
        }

        read(to_disc_ptr, buf, )
*/
    }

    // if file already in table return 0
    // read file paths from disk until you find path
    // if path not found return -1
    // read file, add file to table
    
}

int close_file(char* path){
    // read table until you find file with path
    // save it
    // delete it from table
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

int write_file(cfs_file_ptr file_ptr){
    // calculate shift on disk of meta and block
    // write meta -> disk
    // write content of block -> disk
}

int save_file(char* path){
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
    cfs_file_ptr file_table_ptr = find_file_table(path);
    int* file_disk_ptr = nullptr;

    // not found in table -> search on disk
    if (file_table_ptr == nullptr){
        file_disk_ptr = find_file_disk(path);
    }

    // not found on disk and in table
    if (file_table_ptr == nullptr && file_disk_ptr == nullptr){
        printf("File %s not found\n", path);
        return -1;
    }

    // not found in table but found on disk -> open file
    if (file_table_ptr == nullptr){
        cfs_fopen(path);
        file_table_ptr = find_file_table(path);
    }

    // check if file with dst_path alreay exists
    int* file_with_dst_path = find_file_disk(dst_path);

    // file already exists
    if (file_with_dst_path != nullptr){
        printf("File %s already exists\n", dst_path);
        return -1;
    }

    // everything is ok
    // create new file, replace data in meta and content
    create_file(dst_path);
    // resize_file
    printf("TODO add resizing file to copy_file()\n");
    cfs_fopen(dst_path);
    cfs_file_ptr dst_f_ptr = find_file_table(dst_path);

    //free content
    free(dst_f_ptr->content);
    // create new content, copy from first file
    dst_f_ptr->content = malloc(file_table_ptr->meta_ptr->size);
    strcpy(dst_f_ptr->content, file_table_ptr->content);
    // copy data to meta
    strcpy(dst_f_ptr->meta_ptr->f_path, file_table_ptr->meta_ptr->f_path);
    dst_f_ptr->meta_ptr->size = file_table_ptr->meta_ptr->size;
    dst_f_ptr->meta_ptr->start_block_idx = file_table_ptr->meta_ptr->start_block_idx;
    dst_f_ptr->meta_ptr->is_dir = file_table_ptr->meta_ptr->is_dir;
    dst_f_ptr->meta_ptr->cleared = file_table_ptr->meta_ptr->cleared;

    save_file(dst_f_ptr->meta_ptr->f_path);

    return 0;

}

int move_file(char* path, char* dst_path){

    copy_file(path, dst_path);
    delete_file(path);

    return 0;
}

int delete_file(char* path){

    // find in table
    cfs_file_ptr file_table_ptr = find_file_table(path);

    // if not found open
    if (file_table_ptr == nullptr)
        cfs_fopen(path);

    // search once again
    file_table_ptr = find_file_table(path);

    // still not found - no such file. No file - no problems
    if (file_table_ptr == nullptr){
        printf("No file %s found\n", path);
        return -1;
    }    

    // if found set file cleared
    file_table_ptr->meta_ptr->cleared = 1;
    // close file(with save)
    close_file(path);

    return 0;

}

int create_file(char* path){

    // search file on disk(if already exists)
    int* file_disc_ptr = find_file_disk(path);
    // if exists
    if (file_disc_ptr != nullptr){
        printf("File %s already exists\n", path);
        return -1;
    }

    int block_idx = find_empty_space_in_meta(1);
    int flag_packed = 0; // to know if packing happens

    // if not found free blocks in meta
    if (block_idx == nullptr){
        // get free block from end of blocks in fs
        block_idx = get_new_free_block_idx();
        if (block_idx == 0){
            // no free space in fs, try to pack it
            pack_fs();
            flag_packed = 1;
        }
    }

    // if flag_packed then try to get_new_free_block again
    if (flag_packed){
        block_idx = get_new_free_block_idx();
        // nothing to be done, no space
        if (block_idx == 0){
            printf("Not enough space to create file in file system\n");
            return -1;
        }
    }

    // enough space, we have free block
    // create new meta and write on disk
    cfs_meta meta;
    strcpy(meta.f_path, path);
    meta.size = 1 * CFS_ONE_BLOCK_SIZE;
    meta.start_block_idx = block_idx;

    char content[CFS_ONE_BLOCK_SIZE];
    // remember that this file deletes after exiting function
    cfs_file new_file;
    new_file.meta_ptr = &meta;
    new_file.content = content;

    write_file(&new_file);
        
    return 0;
}


int sort_meta(){
    // hardcore
}

int find_empty_space_in_meta(int minimum_blocks_num){

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


int get_new_free_block_idx(){
    // new_block_idx = superblock.last_idx_block
    // ckeck if new block does not overlap with meta
    // if overlaps return 0
    // if not increase superblock.last_idx_block, return new_block_idx
}
