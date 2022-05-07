#include "message_buffer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int shmid;
void *memory_segment=NULL;

int init_buffer(MessageBuffer **buffer) {
    /*---------------------------------------*/
    /* TODO 1 : init buffer                  */

    if((shmid = shmget(KEY, sizeof(MessageBuffer), IPC_CREAT|0666))==-1) return -1;
    printf("shmid : %d\n", shmid);
    attach_buffer(buffer);
    (*buffer)->is_empty = 1;
    (*buffer)->account_id = -1;

    /* TODO 1 : END                          */
    /*---------------------------------------*/

    printf("init buffer\n");
    return 0;
}

int attach_buffer(MessageBuffer **buffer) {
    /*---------------------------------------*/
    /* TODO 2 : attach buffer                */
    /* do not consider "no buffer situation" */
   
    if((shmid=shmget(KEY,sizeof(int), IPC_CREAT|0666))==-1) return -1;
    printf("Attaching to shmid: %d\n", shmid);
    if((memory_segment = shmat(shmid, NULL, 0)) == (void*)-1) return -1;
    (*buffer) = (MessageBuffer*)memory_segment;

    /* TODO 2 : END                          */
    /*---------------------------------------*/

    printf("attach buffer\n");
    printf("\n");
    return 0;
}

int detach_buffer() {
    if (shmdt(memory_segment) == -1) {
        printf("shmdt error!\n\n");
        return -1;
    }

    printf("detach buffer\n\n");
    return 0;
}

int destroy_buffer() {
    if(shmctl(shmid, IPC_RMID, NULL) == -1) {
        printf("shmctl error!\n\n");
        return -1;
    }

    printf("destroy shared_memory\n\n");
    return 0;
}

int produce(MessageBuffer **buffer, int sender_id, int data, int account_id) {

    /*---------------------------------------*/
    /* TODO 3 : produce message              */
   
    if((account_id<0) || (account_id>=BUFFER_SIZE)){
    	printf("Account ID must be in range [0,%d].\n", BUFFER_SIZE-1);
	return -1;
    }
    else if((*buffer)->messages[account_id].data+data<0){
    	printf("Balance cannot be negative.\n");
	return -1;
    }    
    else{
    	(*buffer)->account_id = account_id;
   	(*buffer)->messages[account_id].sender_id = sender_id;
   	(*buffer)->messages[account_id].data += data;
    	(*buffer)->is_empty--;
    }


    /* TODO 3 : END                          */
    /*---------------------------------------*/

    printf("produce message\n");

    return 0;
}

int consume(MessageBuffer **buffer, Message **message) {
    if((*buffer)->is_empty)
	    return -1;

    /*---------------------------------------*/
    /* TODO 4 : consume message              */

    (*message) = &((*buffer)->messages[(*buffer)->account_id]);
    (*buffer)->is_empty++; 

    /* TODO 4 : END                          */
    /*---------------------------------------*/

    return 0;
}
