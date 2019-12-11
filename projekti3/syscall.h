//Lähteet:
//https://pdos.csail.mit.edu/6.828/2014/xv6.html
//https://medium.com/@viduniwickramarachchi/add-a-new-system-call-in-xv6-5486c2437573
//https://ampleux.wordpress.com/2018/02/22/how-to-add-a-user-program-to-xv6/
// System call numbers
#define SYS_fork    1
#define SYS_exit    2
#define SYS_wait    3
#define SYS_pipe    4
//read() system call
#define SYS_read    5
#define SYS_kill    6
#define SYS_exec    7
#define SYS_fstat   8
#define SYS_chdir   9
#define SYS_dup    10
#define SYS_getpid 11
#define SYS_sbrk   12
#define SYS_sleep  13
#define SYS_uptime 14
#define SYS_open   15
#define SYS_write  16
#define SYS_mknod  17
#define SYS_unlink 18
#define SYS_link   19
#define SYS_mkdir  20
#define SYS_close  21
//readcount system call
#define SYS_readcount  22
