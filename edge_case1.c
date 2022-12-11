#include <pthread.h>
#include <stdio.h>

pthread_t p2;
pthread_mutex_t m0;

typedef struct {
    int foo;
    char bar;
    void* zero;
} Element;

Element arr [32];

void* thread2_start(void *arg)
{
    for (int i =0; i<50; i++)
    {
        int tmp = 0;
        for (int j = 0; j < 5000; j++)
        {
            tmp = tmp + 1;
        }
        pthread_mutex_lock(&m0);
        for (int l = 0; l < 32; l++)
        {
            arr[l].foo += 1;
            arr[l].bar += 1;
            arr[l].zero = 0;
        }
        pthread_mutex_unlock(&m0);
    }
    for (int i =0; i<4950; i++)
    {
        int tmp = 0;
        for (int j = 0; j < 5000; j++)
        {
            tmp = tmp + 1;
        }
        for (int l = 0; l < 32; l++)
        {
            int x = arr[l].foo;
            x += 1;
            char y = arr[l].bar;
            y += 1;
            void* z = arr[l].zero;
        }
    }
}

int main(void)
{
    if (pthread_mutex_init(&m0, NULL) != 0)
    {
        printf("mutex init error\n");
        return 1;
    }
    if (pthread_create(&p2, NULL, &thread2_start, NULL)!= 0)
    {
        printf("create p2 error\n");
        return 1;
    }

    for (int i =0; i<50; i++)
    {
        pthread_mutex_lock(&m0);
        for (int l = 0; l < 32; l++)
        {
            arr[l].foo -= 1;
            arr[l].bar -= 1;
            arr[l].zero = 1;
        }
        pthread_mutex_unlock(&m0);
        int tmp = 0;
        for (int j = 0; j < 5000; j++)
        {
            tmp = tmp + 1;
        }
    }
    for (int i =0; i<4950; i++)
    {
        for (int l = 0; l < 32; l++)
        {
            int x = arr[l].foo;
            x -= 1;
            char y = arr[l].bar;
            y -= 1;
            void* z = arr[l].zero;
        }
        int tmp = 0;
        for (int j = 0; j < 5000; j++)
        {
            tmp = tmp + 1;
        }
    }
    
    pthread_join(p2, NULL);
    pthread_mutex_destroy(&m0);
    printf("5 done\n");
    return 0;
}
