// 舞伴配对问题
// 队列

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char name[20];
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
    int size;
} Queue;

Queue *initQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}
// 入队
void enqueue(Queue *q, const char *name)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}
// 出队
char *dequeue(Queue *q)
{
    if (q->front == NULL)
        return NULL;
    Node *temp = q->front;
    char *name = (char *)malloc(20);
    strcpy(name, temp->name);

    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    q->size--;
    return name;
}
// 查看队首元素
char *peek(Queue *q)
{
    if (q->front == NULL)
        return NULL;
    return q->front->name;
}

int isEmpty(Queue *q)
{
    return q->front == NULL;
}
// 输入舞者信息
Queue *inputDancers(const char *gender)
{
    Queue *q = initQueue();
    int count;
    char name[20];

    printf("%s队:\n输入跳舞者人数: ", gender);
    scanf("%d", &count);
    printf("输入跳舞者的姓名: ");
    for (int i = 0; i < count; i++)
    {
        scanf("%s", name);
        enqueue(q, name);
    }
    return q;
}

int main()
{
    Queue *maleQueue = inputDancers("男");
    Queue *femaleQueue = inputDancers("女");

    int rounds;
    printf("请输入舞会的轮数: ");
    scanf("%d", &rounds);

    for (int i = 0; i < rounds; i++)
    {
        printf("\n第%d轮舞会:\n", i + 1);

        int pairCount = (maleQueue->size < femaleQueue->size) ? maleQueue->size : femaleQueue->size;

        for (int j = 0; j < pairCount; j++)
        {
            char *maleDancer = dequeue(maleQueue);
            char *femaleDancer = dequeue(femaleQueue);

            printf("配对的舞者: %s 和 %s\n", maleDancer, femaleDancer);

            enqueue(maleQueue, maleDancer);
            enqueue(femaleQueue, femaleDancer);

            free(maleDancer);
            free(femaleDancer);
        }

        if (maleQueue->size > femaleQueue->size)
        {
            printf("第一个出场的未配对舞者的姓名：%s\n", peek(maleQueue));
        }
        else if (femaleQueue->size > maleQueue->size)
        {
            printf("第一个出场的未配对舞者的姓名：%s\n", peek(femaleQueue));
        }
    }

    while (!isEmpty(maleQueue))
        free(dequeue(maleQueue));
    while (!isEmpty(femaleQueue))
        free(dequeue(femaleQueue));
    free(maleQueue);
    free(femaleQueue);

    return 0;
}
