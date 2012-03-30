/* process_n.c - by fqheda */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_P "/tmp/fifo_p"

//////////////////////////////////////////////////////////////////////////
/*************************************************************************
 * \brief main
 *************************************************************************/
int main(int argc, char* argv[])
{
    int fifo_fd = -1;
    char dbuf[1024];
    
    unlink(FIFO_P);
    
   if(mkfifo(FIFO_P, O_CREAT|O_EXCL) < 0)
    {
         printf("Create FIFO %s failure!!!\n", FIFO_P);
         unlink(FIFO_P);
         return(-1);
    }
    
    fifo_fd = open(FIFO_P, O_RDONLY);
    if(fifo_fd < 0)
    {
         printf("Open FIFO %s failure!!!\n", FIFO_P);
         unlink(FIFO_P);         
         return(-1);
    }
    
    for(;;) 
    {
        memset(dbuf, 0x00, sizeof(dbuf));
        
        if(read(fifo_fd, dbuf, sizeof(dbuf)) > 0)
        {
            printf("Get Cmd is :%s\n", dbuf); 
        }

        if(strcmp((char*)dbuf, "run") == 0)
        {
             system("../process_p_p/process_p");
        }

        printf("Runing...\n");
        sleep(1);
    } 
    
    close(fifo_fd);
    unlink(FIFO_P);
    
    return(0);  
}
