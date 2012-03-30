/* process_p.c - by fqheda */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

//////////////////////////////////////////////////////////////////////////
/*************************************************************************
 * \brief main
 *************************************************************************/
int main(int argc, char* argv[])
{
    pid_t pid;
    int pipe_fd[2] = {-1, -1};    
    int pipe_fd_2[2] = {-1, -1};
    char dbuf[1024];
    char dbuf_2[1024];

    if(pipe(pipe_fd) < 0)
    {
        printf("Create PIPE failure!!!\n");
        return (-1);	
    }
    
    if(pipe(pipe_fd_2) < 0)
    {
        printf("Create PIPE failure!!!\n");
        return (-1);	
    }
     
    pid = fork();
    
    if (pid > 0)
    {
         close(pipe_fd[1]);
         close(pipe_fd_2[0]);

         for(;;)
          {
    	      printf("Parent process\n");

              write(pipe_fd_2[1], "Cmd 00a", 8);

    	      memset(dbuf, 0x00, sizeof(dbuf));
               
             if(read(pipe_fd[0], dbuf, sizeof(dbuf)) > 0)
               {
                    printf("Parent Receive Cmd is %s\n", dbuf);  
               }
    	      sleep(1);
          }
    }
    else
    {
    	  close(pipe_fd[0]);
    	  close(pipe_fd_2[1]);
          
         for(;;)
          {
    	      printf("Child process\n");
    	      
             write(pipe_fd[1], "Cmd 006", 8);

             memset(dbuf_2, 0x00, sizeof(dbuf_2));
               
             if(read(pipe_fd_2[0], dbuf_2, sizeof(dbuf_2)) > 0)
               {
                    printf("Child Receive Cmd is %s\n", dbuf_2);  
               }
             
             sleep(2);
          }
    }
    
    return 0;
}
