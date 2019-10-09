#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define O_BINARY 0
// cp /dev/tty a
//ggggggggggggggggggggg
//ctrl-D

int fdin,fdout;
#define BUFMAX 10
char buf[BUFMAX];

int bytesread=0;


main()
{
fdin = open("a", O_RDONLY|O_BINARY, 0);
if (fdin == -1) return -1;

fdout = open("aa", O_WRONLY|O_BINARY|O_CREAT|O_TRUNC, 0x1ff);
if (fdout == -1) {
    close(fdin);
    return -1;
}	
bytesread=read(fdin, buf, 2100);

printf("DEBUG bytesread %i\n", bytesread);

if (bytesread == 0) return;
write(fdout, buf, 2100);
}

