/* process_s.c - by fqheda */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>  
#include <sys/msg.h> 
 
#define MSG_DATA_MAX 1024
#define MSG_KEY      1234

struct m_msg_t
{  
   int msg_type;
   char msg_data[MSG_DATA_MAX];  
};

//////////////////////////////////////////////////////////////////////////
/*************************************************************************
 * \brief main
 *************************************************************************/
int main(int argc, char* argv[])
{
    struct m_msg_t msg_q_s;
    int msg_id = -1;
    char dbuf[MSG_DATA_MAX]; 
    
    if((msg_id = msgget((key_t)MSG_KEY, 0777|IPC_CREAT)) == -1 )  
    {
        printf("msgget failure!!!\n"); 
        return (-1);  
    }
    
    printf("Please Enter Message to Send:");  
    fgets(dbuf, MSG_DATA_MAX, stdin);
    
    msg_q_s.msg_type = 1;
    
    strcpy(msg_q_s.msg_data, dbuf);  
    
    if((msgsnd(msg_id, (void *)&msg_q_s, sizeof(struct m_msg_t), 0)) == -1)//0表示非阻塞和msgrcv相反
    {
        printf("msgsnd failure!!!\n"); 
        return (-1);
    }
    
    return(0);  
}
