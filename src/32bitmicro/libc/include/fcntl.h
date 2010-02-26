#ifndef	_FCNTL_H_
#define	_FCNTL_H_
#ifdef __cplusplus
extern "C" {
#endif


#define	_FREAD		0x0001	/* read enabled */
#define	_FWRITE		0x0002	/* write enabled */
#define	_FAPPEND	0x0004	/* append (writes guaranteed at the end) */
#define	_FCREAT		0x0008	/* open with file create */
#define	_FTRUNC		0x0010	/* open with truncation */
#define	_FEXCL		0x0020	/* error on open if file exists */
#define	_FNONBLOCK	0x0040	/* non blocking I/O (POSIX style) */
#define	_FTXTMODE	0x8000	/* text mode */


#define	O_RDONLY	0
#define	O_WRONLY	1
#define	O_RDWR		2
#define	O_BINARY	0
#define O_TEXT      _FTXTMODE
#define	O_APPEND	_FAPPEND
#define	O_CREAT		_FCREAT
#define	O_TRUNC		_FTRUNC
#define	O_EXCL		_FEXCL
#define	O_NONBLOCK	_FNONBLOCK

#define	O_ACCMODE	(O_RDONLY|O_WRONLY|O_RDWR)

#include <sys/types.h>
#include <sys/stat.h>


#ifdef __cplusplus
}
#endif

#endif

