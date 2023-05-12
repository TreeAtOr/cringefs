#include "cringefs.h"

/*
/////////////////////////////////////READ THIS PLEASE///////////////////////////////////////
/////////////I HAD TO CHANGE SB TYPE FROM CFS_SUPER_BLOCK_PTR TO CFS_SUPER_BLOCK////////////
///////////////////////////////OTHERWISE READING ISN'T WORKING//////////////////////////////
/////////////////////////////////IT SAYS "SEGMENTATION FAULT"///////////////////////////////
*/

int* cfs_f_descriptor = -1;
cfs_super_block sb;
cfs_file_table ft;


int main(int argc, char* argv[]){

    // if not -> Houston, we have problems 
    assert(sizeof(cfs_meta) <= CFS_ONE_META_SIZE);


    // argv[1] это путь к файлу устройства(флешки) ( например "/dev/sda3" )

    printf("Debug: program starts\n");

    if (argc <= 1){
        //print argument with device path missed
        printf("There's no such argument\n");
        printf("Debug: program ends\n");
        return -1;
    }

    if (startup(argv[1]) == -1)
        printf("Debug: No startup\n");
    
    else
    {
        // some shit
        // поймать сигнал ctrl+c? дла корректного shutdown
        shutdown();
    }
    // parse_args()

    printf("Debug: program ends\n");
    return 0;
}

int startup(char* device_path){
    cfs_f_descriptor = open(device_path, O_RDWR);
    printf("Debug: in startup\n");
    if (cfs_f_descriptor == -1){
        perror("Error");
        return -1;
    }
    //start reading superblock
    read(cfs_f_descriptor, &(sb.sb_magic), (size_t)sizeof(int*));
    read(cfs_f_descriptor, &(sb.start_block_ptr), (size_t)sizeof(int*));
    read(cfs_f_descriptor, &(sb.free_space_ptr), (size_t)sizeof(int*));
    read(cfs_f_descriptor, &(sb.end_meta_ptr), (size_t)sizeof(int*));
    read(cfs_f_descriptor, &(sb.start_meta_ptr), (size_t)sizeof(int*));

    if (check_sb(sb) == -1)
    {
        while(1){
            printf("Superblock of file %s isn't %p, do you want to formate file system? (y/n) ", device_path, CFS_MAGIC);
            char* choice[2] = { NULL };
            scanf("%s", &choice);
            if (choice[0] == 'y' || choice[0] == 'Y')
            {
                format_fs();
                // if(format_fs == -1)
                //      return -1;
                break;
            }
            else if (choice[0] == 'n' || choice[0] == 'N')
            {
                printf("Well, goodbye\n");
                return -1;
            }
            else 
            {
                printf("Looks like it's wrong input, my friend :( \n");
            }
        }
    }
    else printf("Everything is OK\n");

    // if something bad return -1
}

int shutdown(){
    if (close(cfs_f_descriptor)){
        printf("Oh no, something very bad happened :(\n");
        return -1;
    }
    return 0;
    // if something bad return -1
}

int check_sb(cfs_super_block sb){
    // check magic
    if (sb.sb_magic != CFS_MAGIC)
        return -1;
    else return 0;
}

/*


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

    if (idx <= 0){
        printf("Block idx %i - wrong value\n", idx);
        return nullptr;
    }

    int result = 0;
    result = idx * CFS_ONE_BLOCK_SIZE + CFS_SUPERBLOCK_SIZE + CFS_STARTPOS; // + sizeof(cfs_super_block) ? + смещение суперлока на диске(CFS_STARTPOS)

    // check border ptrs
    if (result < sb->start_block_ptr - CFS_SUPERBLOCK_SIZE || result > sb->start_meta_ptr + CFS_ONE_META_SIZE){
        printf("Converted block idx %i -> %i out of borders\n", idx, result);
        return nullptr;
    }

    return result;
}

int disk_ptr_to_block_idx(int* ptr){
    //printf("TODO convertion from disk ptr to block idx");

    //int* idx = ((char*)ptr - CFS_STARTPOS - CFS_SUPERBLOCK_SIZE) / CFS_ONE_BLOCK_SIZE; // char* для того, чтобы смещение прибавлялось по байтам
}

int disk_ptr_to_meta_idx(int* ptr){

}

int* meta_idx_to_disc_ptr(int idx){

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

    }

    // if file already in table return 0
    // read file paths from disk until you find path
    // if path not found return -1
    // read file, add file to table
    
}
*/

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

/*
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
    int new_start_block_idx = dst_f_ptr->meta_ptr->start_block_idx; // save to not lose

    copy_meta(file_table_ptr->meta_ptr, dst_f_ptr->meta_ptr);

    dst_f_ptr->meta_ptr->start_block_idx = new_start_block_idx; // recover new adress

    // save new file
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
*/
int format_fs(){
    // clear table of opened files
    clear_table();
    printf("in format\n");

    // reset superblock
    sb.sb_magic = CFS_MAGIC;
    sb.start_block_ptr = CFS_STARTPOS + CFS_SUPERBLOCK_SIZE;
    sb.free_space_ptr = sb.start_block_ptr;

    sb.start_meta_ptr = CFS_ENDPOS;
    sb.end_meta_ptr = sb.start_meta_ptr;

    
    printf("%p, %p, %p, %p, %p\n",sb.sb_magic, sb.start_block_ptr, sb.free_space_ptr, sb.end_meta_ptr, sb.start_meta_ptr);

    // write sb
    lseek(cfs_f_descriptor, CFS_STARTPOS, SEEK_SET); // shift file pointer
    write(cfs_f_descriptor, &sb, sizeof(cfs_super_block)); // write
    //write(cfs_f_descriptor, &sb, CFS_SUPERBLOCK_SIZE);
}



int remove_from_table(char* path){
    // find and clear
}

int clear_table(){
    // clear all
}
/*
//return ptr if found file else nullptr
cfs_file_ptr find_file_table(char* path){
    // find in table
}

// return ptr if found file else nullptr
int* find_file_disk(char* path){
    // find on disk
}


int get_new_free_block_idx(){

    int new_block_idx = disk_ptr_to_block_idx(sb->free_space_ptr);

    // ckeck if new block overlaps meta
    if (sb->free_space_ptr + CFS_ONE_BLOCK_SIZE > sb->end_meta_ptr){
        printf("New block with index %i overlaps meta\n", new_block_idx);
        return -1;
    }

    // everything is ok
    sb->free_space_ptr += CFS_ONE_BLOCK_SIZE;
    return new_block_idx;

}

int copy_meta(cfs_meta_ptr src, cfs_meta_ptr dst){
    strcpy(dst->f_path, src->f_path);
    dst->start_block_idx = src->start_block_idx;
    dst->is_dir = src->is_dir;
    dst->cleared = src->cleared;
    dst->size = src->size;
}
*/