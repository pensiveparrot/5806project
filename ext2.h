#ifndef _EXT2_H_
#define _EXT2_H_
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>
#include <cstddef>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "vdifile.h"
#include "partition.h"
struct ext2superblock
{
    uint32_t s_inodes_count; // num inodes
    uint32_t s_blocks_count; // Numblocks (guessing s for sum of count)
    uint32_t s_r_blocks_count; // Number of blocks reserved (guessing sum of count of reserved)
    uint32_t  s_free_blocks_count; // num free blocks (the sum of all free blocks of all BGs)
    uint32_t s_free_inodes_count; // sum of free inodes from all block groups.
    uint32_t s_first_data_block; // first data block
    uint32_t s_log_block_size; // block size == 1024*pow(2, s_log_block_size)
    uint32_t s_log_frag_size;//frag size? im guessing fragment?
    uint32_t s_blocks_per_group;//sum of blocks per group?
    uint32_t s_frags_per_group;//sum of frags per group?
    uint32_t s_inodes_per_group;// sum of inodes per group?
    uint32_t s_mtime;
    uint32_t s_wtime;
    uint16_t s_mnt_count;
    uint16_t s_max_mnt_count;
    uint16_t s_magic;
    uint16_t s_state;
    uint16_t s_errors;
    uint16_t s_minor_rev_level;
    uint32_t s_lastcheck;
    uint32_t s_checkinterval;
    uint32_t s_creator_os;
    uint32_t s_rev_level;
    uint16_t s_def_resuid;
    uint16_t s_def_resgid;
    uint32_t s_first_ino;//first inode per BG? sum?
    uint16_t s_inode_size;//size of inode? sum?
    uint16_t s_block_group_nr;
    uint32_t s_feature_compat;
    uint32_t s_feature_incompat;
    uint32_t s_feature_ro_compat;
    char s_uuid[16];
    uint8_t s_volume_name[16];
    uint8_t s_last_mounted[64];
    uint32_t s_algo_bitmap;
    uint8_t s_prealloc_blocks;
    uint8_t s_prealloc_dir_blocks;
    char s_journal_uuid[16];
    uint32_t s_journal_inum;
    uint32_t s_journal_dev;
    uint32_t s_last_orphan;
    uint32_t s_hash_seed[4];
    uint8_t s_def_hash_version;
    uint32_t s_default_mount_options;
    uint32_t s_first_meta_bg;
    uint8_t padding[760];

};
struct ext2blockgroupdescriptor
{
    uint32_t bg_block_bitmap;
    uint32_t bg_inode_bitmap;
    uint32_t bg_inode_table;
    uint16_t bg_free_blocks_count;
    uint16_t bg_free_inodes_count;
    uint16_t bg_used_dirs_count;
    uint16_t bg_pad;
    uint8_t bg_reserved[12];
};
struct ext2file
{
    struct ext2superblock *superblock;
    struct ext2blockgroupdescriptor *bgdt;
    struct VDIFile *vdi;
    struct PartitionFile *p;
    uint32_t blocksize = 1024 << superblock->s_log_block_size;
    uint32_t numBGs;
};
int32_t fetchsuperblock(struct ext2file *f, uint32_t blocknum, struct ext2superblock *sb);
struct ext2file *ext2open(char *fn, int32_t pNum);
void ext2close(struct ext2file *f);
int32_t fbff(struct ext2file *f, uint32_t blocknum, void *buf);
int32_t fetchblock(struct ext2file *f, uint32_t blocknum, void *buf);
int32_t writeblock(struct ext2file *f, uint32_t blocknum, void *buf);
int32_t writesuperblock(struct ext2file *f, uint32_t blocknum, struct ext2superblock *sb);
int32_t fetchBGDT(struct ext2file *f, uint32_t blocknum, struct ext2blockgroupdescriptor *bgdt);
int32_t writeBGDT(struct ext2file *f, uint32_t blocknum, struct ext2blockgroupdescriptor *bgdt);
#endif
