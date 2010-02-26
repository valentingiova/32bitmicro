/*
 * 32bitmicro libc stat
 * $URL$
 * $ID$

Copyright (c) 2010, 32bitmicro
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.
Neither the name of the 32bitmicro nor the names of its contributors may be used to endorse or promote products derived from this software without 
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef	_SYS_STAT_H_
#define	_SYS_STAT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <sys/types.h>

struct	stat {
	dev_t     st_dev;     /* device ID */ 
	ino_t     st_ino;     /* file serial number */
	mode_t    st_mode;    /* file mode */
	nlink_t   st_nlink;   /* number of hard links to the file */
	uid_t     st_uid;     /* user ID */
	gid_t     st_gid;     /* group ID */
	dev_t     st_rdev;    /* device ID if special: block, character, fifo or device */
	off_t     st_size;    /* file size in bytes */
	time_t    st_atime;   /* time of last access */
	time_t    st_mtime;   /* time of last data modification */
	time_t    st_ctime;   /* time of last status change */
	blksize_t st_blksize; /* file system preferred I/O block size */
	blkcnt_t  st_blocks;  /* number of blocks allocated for this file */
};

/* file type bits */
#define S_IFMT   0x00017000  /* file type        */
#define S_IFREG  0x00001000  /* regular           */
#define S_IFDIR  0x00002000  /* directory         */
#define S_IFLNK  0x00004000  /* symbolic link     */
#define S_IFSOCK 0x00008000  /* socket            */
#define S_IFBLK  0x00011000  /* block special     */
#define S_IFCHR  0x00012000  /* character special */
#define S_IFIFO  0x00014000  /* FIFO special      */
#define S_IFDEV  0x00018000  /* DEVICE special    */

/* file mode bits */
#define S_IRWXU  0x00000700  /* RWX------ user    */
#define S_IRUSR  0x00000400  /* R-------- user    */
#define S_IWUSR  0x00000200  /* -W------- user    */
#define S_IXUSR  0x00000100  /* --X------ user    */
#define S_IRWXG  0x00000070  /* ---RWX--- group   */
#define S_IRGRP  0x00000040  /* ---R----- group   */
#define S_IWGRP  0x00000020  /* ----W---- group   */
#define S_IXGRP  0x00000010  /* -----X--- group   */
#define S_IRWXO  0x00000007  /* ------RWX other   */
#define S_IROTH  0x00000004  /* ------R-- other   */
#define S_IWOTH  0x00000002  /* -------W- other   */
#define S_IXOTH  0x00000001  /* --------X other   */

/* file type macros */
#define S_ISREG(m)  ((m & S_IFMT) == S_IFREG)
#define S_ISDIR(m)  ((m & S_IFMT) == S_IFDIR)
#define S_ISLNK(m)  ((m & S_IFMT) == S_IFLNK)
#define S_ISSOCK(m) ((m & S_IFMT) == S_IFSOCK)
#define S_ISBLK(m)  ((m & S_IFMT) == S_IFBLK)
#define S_ISCHR(m)  ((m & S_IFMT) == S_IFCHR)
#define S_ISFIFO(m) ((m & S_IFMT) == S_IFIFO)
#define S_ISDEV(m)  ((m & S_IFMT) == S_IFDEV)

#ifdef __cplusplus
}
#endif

#endif