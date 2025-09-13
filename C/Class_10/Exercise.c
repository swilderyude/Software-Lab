// 看电影最少花费。
// 带权无向图，路费仅记一次
// 最短路径，Floyd算法

#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int main()
{
    int n, m;
    printf("请输入城市和公路个数：");
    scanf("%d %d", &n, &m);

    int ticket[n];
    printf("请输入各城市票价：");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ticket[i]);
    }

    int dist[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = (i == j) ? 0 : INF;

    printf("请输入公路和相应过路费：\n");
    for (int k = 0; k < m; k++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--;
        v--;
        if (w < dist[u][v])
        {
            dist[u][v] = w;
            dist[v][u] = w;
        }
    }
    // Floyd 算法
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    // 计算每个城市最少花费
    for (int i = 0; i < n; i++)
    {
        int minCost = INF;
        for (int j = 0; j < n; j++)
        {
            int cost = dist[i][j] + ticket[j];
            if (cost < minCost)
                minCost = cost;
        }
        printf("城市 %d 最少花费: %d\n", i + 1, minCost);
    }
    return 0;
}
