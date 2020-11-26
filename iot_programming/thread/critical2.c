#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
int count;
int result; 

void *thread_main1(void *arg){
    int id=*(int*)arg;
    int i;
    for(i=1; i<=20; i+=2){
        pthread_mutex_lock(&mutex1);
        printf("id : %d, i = %d\n", id, i);
        pthread_mutex_unlock(&mutex2);
    }
    result = i;
    pthread_exit((void*)&result);
   // return (void*)&result;
    return NULL;
}
void *thread_main2(void *arg){
    int id =*(int*)arg;
    int i;
    for(i=2; i<=20; i+=2){
        pthread_mutex_lock(&mutex2);
        printf("id : %d, i = %d\n", id, i);
        pthread_mutex_unlock(&mutex1);
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

    int a=1, b=2;
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    
    //mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mutex2);
    ret = pthread_create(&t_id1, NULL, thread_main1, &a);
    ret = pthread_create(&t_id2, NULL, thread_main2, &b);
    if(ret != 0){
        errno = ret;
        perror("thread_create");
        return 0;
    }
    ret=pthread_join(t_id1, NULL);
    ret=pthread_join(t_id2, NULL);
    printf("Count : %d\n", count);
    printf("End\n");

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;

}
