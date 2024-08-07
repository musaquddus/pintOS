#ifndef FILESYS_DIRECTORY_H
#define FILESYS_DIRECTORY_H

#include <stdbool.h>
#include <stddef.h>
#include "devices/block.h"

/* Maximum length of a file name component.
   This is the traditional UNIX maximum length.
   After directories are implemented, this maximum length may be
   retained, but much longer full path names must be allowed. */
#define NAME_MAX 14

struct inode;

/* Opening and closing directories. */
bool dir_create(block_sector_t sector, size_t entry_cnt);
struct dir* dir_open(struct inode*);
struct dir* dir_open_root(void);
struct dir* dir_reopen(struct dir*);
void dir_close(struct dir*);
struct inode* dir_get_inode(struct dir*);

/* Reading and writing. */
bool dir_lookup(const struct dir*, const char* name, struct inode**);
bool dir_add(struct dir*, const char* name, block_sector_t);
bool dir_remove(struct dir*, const char* name);
bool dir_readdir(struct dir*, char name[NAME_MAX + 1]);
static int get_next_part(char*, const char**);
bool mk_dir(const char*, struct dir*);
char* get_file_at_path(const char* path);
struct dir* get_dir_at_path(const char* dir, struct dir* cwd);
struct dir* ch_dir(const char*, struct dir*);
struct dir* get_dir_at_filepath(const char*, struct dir*);
bool filesys_remove(const char* name);
struct inode* get_dir_entry_inode(struct dir* dir, char* name);

#endif /* filesys/directory.h */
