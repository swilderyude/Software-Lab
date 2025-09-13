// 有向图，邻接表。
// 图的建立、深度优先搜索与广度优先搜索。
// 头插法
/*
请输入顶点数: 5
请输入顶点: A B C D E
请输入边数: 6
请输入边(格式: 起点 终点): 
A B
A C
B D
C D
C E
D E
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    struct node *next;
    char val[20]; 
} LinkList;

LinkList **head; 
int *visited;    
int x, t;        

LinkList *init(char val[])
{
    LinkList *node = (LinkList *)malloc(sizeof(LinkList));
    strcpy(node->val, val);
    node->next = NULL;
    return node;
}

int find(char val[])
{
    for (int i = 0; i < x; i++)
    {
        if (!strcmp(head[i]->val, val))
        {
            return i;
        }
    }
    return -1;
}

// 添加边 (头插法) 
void add(char from[], char to[])
{
    int idx = find(from);
    LinkList *node = init(to);
    node->next = head[idx]->next;
    head[idx]->next = node;
}
// 深度优先搜索
void dfs(LinkList *v)
{
    int idx = find(v->val);
    visited[idx] = 1;
    printf("%s ", v->val);

    for (LinkList *p = head[idx]->next; p; p = p->next)
    {
        int nextIdx = find(p->val);
        if (!visited[nextIdx])
        {
            dfs(p);
        }
    }
}
// 广度优先搜索
void bfs(LinkList *start)
{
    int front = 0, rear = 0;
    LinkList **queue = (LinkList **)malloc(sizeof(LinkList *) * x);

    queue[rear++] = start;
    visited[find(start->val)] = 1;

    while (front < rear)
    {
        LinkList *cur = queue[front++];
        printf("%s ", cur->val);

        int idx = find(cur->val);
        for (LinkList *p = head[idx]->next; p; p = p->next)
        {
            int nextIdx = find(p->val);
            if (!visited[nextIdx])
            {
                visited[nextIdx] = 1;
                queue[rear++] = head[nextIdx];
            }
        }
    }
    free(queue);
}

int main()
{
    printf("请输入顶点数: ");
    scanf("%d", &x);
    head = (LinkList **)malloc(sizeof(LinkList *) * x);
    visited = (int *)malloc(sizeof(int) * x);

    printf("请输入顶点: ");
    for (int i = 0; i < x; i++)
    {
        char str[20];
        scanf("%s", str);
        head[i] = init(str);
    }

    printf("请输入边数: ");
    scanf("%d", &t);
    printf("请输入边(格式: 起点 终点): \n");
    for (int i = 0; i < t; i++)
    {
        char a[20], b[20];
        scanf("%s %s", a, b);
        add(a, b); // 有向图只加一次
    }

    memset(visited, 0, sizeof(int) * x);
    printf("广度优先搜索的结果为: ");
    bfs(head[0]);

    memset(visited, 0, sizeof(int) * x);
    printf("\n深度优先搜索的结果为: ");
    dfs(head[0]);

    printf("\n");
    return 0;
}
