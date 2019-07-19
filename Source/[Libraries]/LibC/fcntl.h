#ifndef _LIBC_FCNTL_H_
#define	_LIBC_FCNTL_H_

// Macros

#define	O_RDONLY	0x0000 // open for reading only */
#define	O_WRONLY	0x0001 // open for writing only */
#define	O_RDWR		0x0002 // open for reading and writing */
#define	O_ACCMODE	0x0003 // mask for above modes */
#define	O_NONBLOCK	0x0004 // no delay */
#define	O_APPEND	0x0008 // set append mode */
#define	O_SHLOCK	0x0010 // open with shared file lock */
#define	O_EXLOCK	0x0020 // open with exclusive file lock */
#define	O_ASYNC		0x0040 // signal pgrp when data ready */
#define	O_FSYNC		0x0080 // synchronous writes */
#define	O_CREAT		0x0200 // create if nonexistant */
#define	O_TRUNC		0x0400 // truncate to zero length */
#define	O_EXCL		0x0800 // error if already exists */
#define	O_NOCTTY	0	   // don't assign controlling terminal */
#define	F_DUPFD		0	   // duplicate file descriptor */
#define	F_GETFD		1	   // get file descriptor flags */
#define	F_SETFD		2	   // set file descriptor flags */
#define	F_GETFL		3	   // get file status flags */
#define	F_SETFL		4	   // set file status flags */
#define	F_GETOWN	5	   // get SIGIO/SIGURG proc/pgrp */
#define F_SETOWN	6	   // set SIGIO/SIGURG proc/pgrp */
#define	F_GETLK		7	   // get record locking information */
#define	F_SETLK		8	   // set record locking information */
#define	F_SETLKW	9	   // F_SETLK; wait if blocked */
#define	FD_CLOEXEC	1		/* close-on-exec flag */
#define	F_RDLCK		1		/* shared or read lock */
#define	F_UNLCK		2		/* unlock */
#define	F_WRLCK		3		/* exclusive or write lock */

struct flock
{
    short	l_type;		/* lock type: read/write, etc. */
    short	l_whence;	/* type of l_start */
    //off_t	l_start;	/* starting offset */
    //off_t	l_len;		/* len = 0 means until end of file */
    //pid_t	l_pid;		/* lock owner */
};

#endif