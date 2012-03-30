/*消息队列*/
/* process_r.c - by fqheda */
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
	  struct m_msg_t msg_q_r;
    int msg_id = -1;
    int msg_rx = 0;
    
    if((msg_id = msgget((key_t)MSG_KEY, 0777|IPC_CREAT)) == -1 )  //msgget消息队列的创建
    {
        printf("msgget failure!!!\n"); 
        return (-1);  
    }
     
    for(;;)
    {
        if(msgrcv(msg_id,(void *)&msg_q_r, sizeof(struct m_msg_t), msg_rx, 0) == -1)  
//    	int msgrcv ( int msqid, struct msgbuf *msgp, int msgsz, long mtype, int msgflg )
	
//	第4个参数指定函数从队列中所取消息的类型, 最后一个为0，阻塞模式
        {
            printf("msgrcv failure!!!\n"); 
        }  
        
        printf("Receive Message Type is : %d\n", msg_q_r.msg_type);
        printf("Receive Message Date is : %s\n", msg_q_r.msg_data);
        
        sleep(1);
    }
    
    return(0);  
}
