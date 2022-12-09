#include <pthread.h>
#include <stdio.h>

pthread_t p2;
int nums [32];

void* thread2_start(void *arg)
{
    for (int i =0; i<100; i++)
    {
        int tmp = 0;
        for (int j = 0; j < 5000; j++)
        {
            tmp = tmp + 1;
        }

        int cur = 0;
        for (int l = 0; l < 32; l++)
        {
             cur = nums[l];
        }
    }
}

int main(void)
{
    if (pthread_create(&p2, NULL, &thread2_start, NULL)!= 0)
    {
        printf("create p2 error\n");
        return 1;
    }

    for (int i =0; i<100; i++)
    {
        for (int l = 0; l < 32; l++)
        {
            nums[l] = nums[l] + 1;
        }
        int tmp = 0;
        for (int j = 0; j < 5000; j++)
        {
            tmp = tmp + 1;
        }
    }
    
    pthread_join(p2, NULL);
    return 0;
}
