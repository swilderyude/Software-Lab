// 拆除楼房
/*
现在有一排n个楼房，第i个楼房的高度为ai。
你每次可以选择一个连续的区间［l,r]， 满足任意i属于［l,r]， 有ai ＞0，
之后将区间里所有楼房的高度ai減去任意一个相同的值，过程中任意一个楼房的高度不能为负数。
请问你最少操作几次才能让所有楼房的高度变为0。并展示拆除过程。
*/
#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

typedef struct
{
    int l, r, val; 
} Operation;

int n;
int *arr;
Operation ops[10000]; 
int opCnt;            

// 递归函数：处理区间 [l, r)，返回最少操作次数
int solve(int l, int r)
{
    if (l >= r)
        return 0;

    int min = INF;
    for (int i = l; i < r; i++)
        if (arr[i] < min)
            min = arr[i];

    for (int i = l; i < r; i++)
        arr[i] -= min;
    // 记录本次削减操作    
    int curIdx = opCnt++;
    ops[curIdx].l = l;
    ops[curIdx].r = r - 1;
    ops[curIdx].val = min;

    int costs = 1;
    int i = l;
    while (i < r)
    {
        while (i < r && arr[i] == 0)
            i++;
        int j = i;
        while (j < r && arr[j] > 0)
            j++;
        if (i < r)
            costs += solve(i, j);
        i = j;
    }

    for (int i = l; i < r; i++)
        arr[i] += min;

    int cost = r - l; 

    if (cost < costs)
    {
        opCnt = curIdx;// 撤销
        return cost;
    }
    return costs;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");
    if (!fp)
    {
        printf("文件打开失败\n");
        return 1;
    }

    while (fscanf(fp, "%d", &n) == 1)
    {
        arr = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            fscanf(fp, "%d", &arr[i]);

        printf("n = %d\n", n);
        opCnt = 0;
        int ans = solve(0, n);
        printf("最少操作次数为%d\n", ans);

        printf("初始高度:\n ");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        for (int k = 0; k < opCnt; k++)
        {
            printf("操作%d:区间[%d,%d]减去%d\n",
                   k + 1, ops[k].l + 1, ops[k].r + 1, ops[k].val);
        }
        printf("\n");

        free(arr);
    }

    fclose(fp);
    return 0;
}
