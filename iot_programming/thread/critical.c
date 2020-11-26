#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t mutex;
int count;
int result; 

void *thread_main(void *arg){
    int i;
    for(i=0; i<100000; i++){
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }
    result = i;
    pthread_exit((void*)&result);
   // return (void*)&result;
    return NULL;
}

int main()
{
    pthread_t t_id1, t_id2, t_id3;
    int ret;

    pthread_mutex_init(&mutex, NULL);
    
    //mutex = PTHREAD_MUTEX_INITIALIZER;

    ret = pthread_create(&t_id1, NULL, thread_main, NULL);
    ret = pthread_create(&t_id2, NULL, thread_main, NULL);
    ret = pthread_create(&t_id3, NULL, thread_main, NULL);
    if(ret != 0){
        errno = ret;
        perror("thread_create");
        return 0;
    }
    ret=pthread_join(t_id1, NULL);
    ret=pthread_join(t_id2, NULL);
    ret=pthread_join(t_id3, NULL);
    printf("Count : %d\n", count);
    printf("End\n");

    pthread_mutex_destroy(&mutex);

    return 0;

}
