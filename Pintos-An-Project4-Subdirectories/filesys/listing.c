#include "filesys/listing.h"
#include <stdio.h>
#include <string.h>
#include "filesys/filesys.h"
#include "filesys/inode.h"
#include "filesys/directory.h"

/* Lists all files in the given directory */
bool 
list_directory (const struct dir *dir) 
{
    char name[NAME_MAX + 1];
    struct inode *inode;
    
    if (dir == NULL)
        return false;
        
    while (dir_readdir (dir, name)) {
        dir_lookup (dir, name, &inode);
        list_file_info (name, inode);
    }
    
    return true;
}

/* Print information about a single file */
bool
list_file_info (const char *name, const struct inode *inode)
{
    if (name == NULL || inode == NULL)
        return false;
        
    printf("%s: ", name);
    
    if (inode_get_type(inode) == 1)
        printf("DIR ");
    else if (inode_get_type(inode) == 2)
        printf("LINK ");
    else
        printf("FILE ");
        
    printf("size: %d\n", (int)inode_length(inode));
    return true;
}

/* Count number of files in directory */
int
get_file_count (const struct dir *dir)
{
    char name[NAME_MAX + 1];
    int count = 0;
    
    while (dir_readdir (dir, name))
        count++;
        
    return count;
}