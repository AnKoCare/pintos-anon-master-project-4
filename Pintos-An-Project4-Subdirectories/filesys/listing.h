#ifndef FILESYS_LISTING_H
#define FILESYS_LISTING_H

#include <stdbool.h>
#include "filesys/directory.h"

/* File listing functions */
bool list_directory (const struct dir *dir);
bool list_file_info (const char *name, const struct inode *inode);
int get_file_count (const struct dir *dir);

#endif /* filesys/listing.h */