    #include <stdio.h>  
    #include <pthread.h>  
    #include <semaphore.h> 
     #include <unistd.h> 
    #define   MAX     5  //队列长度  
      
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  
    sem_t  full;     //填充的个数  
    sem_t  empty;    //空槽的个数  

    int cnt=0;

    void* produce(void* arg)  
    {  
     
        while(1) 
        {  
            // printf("producer  %d is preparing data\n",*((int*)arg));  
            sem_wait(&empty);//若空槽个数低于0阻塞  
       
            pthread_mutex_lock(&mutex);              
            cnt = cnt+1;  
            printf("producer  %d is producing data\n",*((int*)arg));  
            printf("the number is  %d\n", cnt % MAX);  
      	   sleep(1);
             pthread_mutex_unlock(&mutex);  
              
             sem_post(&full);  
        }  
        return (void*)1;  
    }  
      
    void* consume(void* arg)  
    {  
     
        while(1)  
        {  
            // printf("consumer  %d is preparing data\n",*((int*)arg));  
            sem_wait(&full);//若填充个数低于0阻塞  
          
            pthread_mutex_lock(&mutex);  
            
           cnt= cnt-1 ;  
           printf("consumer %d is consuming data\n",*((int*)arg));
           printf("the number is %d\n", cnt % MAX);  
      	 sleep(1);
           pthread_mutex_unlock(&mutex);  
 
           sem_post(&empty);  
        }  
      
        return (void*)2;  
    }  
      
    int main(int argc, char *argv[])  
    {  
        pthread_t thid[10]; 
        int res[10];
        int tmp[10];
        sem_init(&full, 0, 0);  
        sem_init(&empty, 0, MAX);  
	
      for (int i = 0; i < 5; ++i)
       {
               	 tmp[i]=i+1;
               	 tmp[i+5]=i+1;
               	 pthread_create(&thid[i], NULL, produce, &tmp[i]);  
        		 pthread_create(&thid[i+5], NULL, consume, &tmp[i+5]);  
         }         

        for (int i = 0; i < 10; ++i)
        {
        	    pthread_join(thid[i], NULL);  
        }
        return 0;  
    }  