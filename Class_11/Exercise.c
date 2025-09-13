// 飞机制造存储成本之和最小
// 贪心：从m+1天卖成本最高的
// 大根堆
#include <stdio.h>
#include <stdlib.h>
// 大根堆
void heap_push(int heap[], int *hsz, int idx, int cost[])
{
    heap[++(*hsz)] = idx;
    int i = *hsz;
    while (i > 1)
    {
        int p = i / 2;
        if (cost[heap[p]] >= cost[heap[i]])
            break;
        int tmp = heap[p];
        heap[p] = heap[i];
        heap[i] = tmp;
        i = p;
    }
}

int heap_pop(int heap[], int *hsz, int cost[])
{
    int res = heap[1];
    heap[1] = heap[*hsz];
    (*hsz)--;
    int i = 1;
    while (1)
    {
        int l = i * 2, r = l + 1, largest = i;
        if (l <= *hsz && cost[heap[l]] > cost[heap[largest]])
            largest = l;
        if (r <= *hsz && cost[heap[r]] > cost[heap[largest]])
            largest = r;
        if (largest == i)
            break;
        int tmp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = tmp;
        i = largest;
    }
    return res;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");
    if (!fp)
    {
        perror("无法打开 input.txt");
        return 1;
    }

    int n, m;
    while (fscanf(fp, "%d %d", &n, &m) == 2)
    {
        int *cost = (int *)malloc((n + 1) * sizeof(int)); // 1..n
        for (int i = 1; i <= n; ++i)
        {
            if (fscanf(fp, "%d", &cost[i]) != 1)
            {
                fprintf(stderr, "输入格式错误或提前结束\n");
                free(cost);
                fclose(fp);
                return 1;
            }
        }

        int *heap = (int *)malloc((n + 5) * sizeof(int));
        int hsz = 0;
        long long total = 0LL;
        int next_prod = 1;

        for (int t = m + 1; t <= m + n; ++t)
        {
            while (next_prod <= n && next_prod <= t)
            {
                heap_push(heap, &hsz, next_prod, cost);
                ++next_prod;
            }
            int idx = heap_pop(heap, &hsz, cost);
            long long stay = (long long)t - (long long)idx;
            if (stay < 0)
                stay = 0;
            total += stay * (long long)cost[idx];
        }
        printf("%lld\n", total);
        free(cost);
        free(heap);
    }
    fclose(fp);
    return 0;
}
