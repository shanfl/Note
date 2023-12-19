#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>		/* some systems still require this */
#include <sys/stat.h>
#include <sys/termios.h>	/* for winsize */
#if defined(MACOS) || !defined(TIOCGWINSZ)
#include <sys/ioctl.h>
#endif

#include <stdio.h>		/* for convenience */
#include <stdlib.h>		/* for convenience */
#include <stddef.h>		/* for offsetof */
#include <string.h>		/* for convenience */
#include <unistd.h>		/* for convenience */
#include <signal.h>		/* for SIG_ERR */
#define EUNDEF    0
#define ENOTFOUND 1
//#define EACCESS   2
#define ENOSPACE  3
#define EBADOP    4
#define EBADID    5
#define EEXISTS   6
#define ENOUSER   7

int main(int argc,char*argv[])
{
    fprintf(stderr,"EACCES: %s\n",strerror(EACCES));
    errno=ENOENT;
    perror(argv[0]);
    exit(0);
}