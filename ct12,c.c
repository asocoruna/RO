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
char buf[BUFMAX];//="nothig";

int bytesread=0;


#include <pthread.h> 
pthread_t td, td2, tdc[10]; 
//int done=0;

f()
{
//usleep(0); //please dont do this, does not work!!!!
//done=1;
bytesread=read(fdin, buf, 2100);
//done=1;
}

fw()
{
//usleep(0); //please dont do this, does not work!!!!
//done=1;
bytesread=write(fdin, buf, 2100);
//done=1;
}

void *in;
void *out;
(void *) process();
void *q_remove(in)
{
	void *res;
	
	pthread_mutex_lock(&in->mutex);
	res=in->bufarray[in->dondevoy];
	//usleep(0);
	dondevoy++;
	pthread_mutex_unlock(&in->mutex);
	}
void *q_remove(b)
{
    void *res;
    
    pthread_mutex_lock(&b->mutex);
    while(b->validdata == 0) continue;
       //pthread_cond_wait(&b->more, &b->mutex);

    res = b->buf[b->dondevoy];
    b->dondevoy++ %= BSIZE;
    b->validdata--;
    
    //pthread_cond_signal(&b->less);
    pthread_mutex_unlock(&b->mutex);
    return(res);
}
void *q_insert(b,resc)
{
	void *res;
	
	pthread_mutex_lock(&b->mutex);
	b->bufarray[b->dondevoy]=resc;
	//usleep(0);
	b->dondevoy++;
	b->validdata++;
	pthread_mutex_unlock(&b->mutex);
	}
worker(in, out, process)
{
	void *res;
	res=q_remove(in);
	//usleep(0);
	resc=(*process)(res);
	q_insert(out,resc);
	}

fc()
{
//usleep(0); //please dont do this, does not work!!!!
//done=1;
//compress(buf, buf2, 2100);
worker(in, out, process);
//done=1;
}

main()
{
fdin = open("a", O_RDONLY|O_BINARY, 0);
if (fdin == -1) return -1;
fdout = open("aa", O_WRONLY|O_BINARY|O_CREAT|O_TRUNC, 0x1ff);
if (fdout == -1) {
    close(fdin);
    return -1;
}	
//bytesread=read(fdin, buf, 2100);
pthread_create(&td, NULL, f, NULL); 

printf("DEBUG bytesread %i\n", bytesread);

//worker(in, out, process);
for (int i=0 ;i<10;i++)
pthread_create(&tdc[i], NULL, fc, NULL); 

//if (bytesread == 0) return;
//while (!done) //
//     ;
//write(fdout, buf, 2100);
pthread_create(&td2, NULL, fw, NULL);
pthread_join(&td2, NULL); 

}

