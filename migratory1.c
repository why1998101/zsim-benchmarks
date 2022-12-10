#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t p2;
pthread_mutex_t m0;

typedef struct Node {
    int value;
    struct Node* next;
} Node_t;

Node_t* head;

void* thread2_start(void *arg)
{
    for (int i =0; i<5000; i++)
    {
        int tmp = 0;
        for (int j = 0; j < 5000; j++)
        {
            tmp = tmp + 1;
        }
        pthread_mutex_lock(&m0);
        Node_t* curr = head;
        for (int l = 0; l < 16; l++)
        {
            curr->value += 1;
            curr = curr->next;
        }
        pthread_mutex_unlock(&m0);
    }
}

int main(void)
{
    head = (Node_t*) malloc(sizeof(Node_t));
    if (head == NULL)
    {
        printf("malloc error\n");
        return 1;
    }
    Node_t* curr = head;
    for (int i = 0; i < 15; i++)
    {
        Node_t* tmp = (Node_t*) malloc(sizeof(Node_t));
        if (tmp == NULL)
        {
            printf("malloc error\n");
            return 1;
        }
        curr->next = tmp;
        curr = tmp;
    }
    curr-> next = NULL;

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

    for (int i =0; i<5000; i++)
    {
        pthread_mutex_lock(&m0);
        Node_t* curr = head;
        for (int l = 0; l < 16; l++)
        {
            curr->value -= 1;
            curr = curr->next;
        }
        pthread_mutex_unlock(&m0);
        int tmp = 0;
        for (int j = 0; j < 5000; j++)
        {
            tmp = tmp + 1;
        }
    }
    
    pthread_join(p2, NULL);
    pthread_mutex_destroy(&m0);
    printf("2 done\n");
    return 0;
}
