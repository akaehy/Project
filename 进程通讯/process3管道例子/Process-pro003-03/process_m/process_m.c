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
    char *data = "Cmd 008"; 
    
    fifo_fd = open(FIFO_P, O_WRONLY|O_NONBLOCK);
    if(fifo_fd < 0)
    {
         printf("Open FIFO %s failure!!!\n", FIFO_P);
         return(-1); 
    }
    
    if(write(fifo_fd, data , 8) != -1)
    {
        printf("Send Data to FIFO sucessful\n");
    }
    
    close(fifo_fd);
    
    return(0);  
}
