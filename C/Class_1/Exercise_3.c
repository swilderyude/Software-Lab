// 杨辉三角。

#include <stdio.h>
#include <stdlib.h>
// 生成杨辉三角的下一行的内容
int *generateRow(int *preRow, int currentRow)
{
    int *newRow = (int *)malloc((currentRow + 1) * sizeof(int));
    if (newRow == NULL)
    {
        printf("内存分配失败。\n");
        exit(1);
    }
    newRow[0] = 1;
    newRow[currentRow] = 1;
    if (currentRow > 1)
    {
        for (int i = 1; i < currentRow; i++)
        {
            newRow[i] = preRow[i - 1] + preRow[i];
        }
    }
    return newRow;
}
// 打印函数
void printTriangle(int n)
{
    int *preRow = NULL;
    int *currentRow = NULL;
    for (int i = 0; i < n; i++)
    {
        currentRow = generateRow(preRow, i);
        for (int j = 0; j <= i; j++)
        {
            printf("%d ", currentRow[j]);
        }
        printf("\n");
        if (preRow != NULL)
        {
            free(preRow);
        }
        preRow = currentRow;
    }
    if (preRow != NULL)
    {
        free(preRow);
    }
}

int main()
{
    int n;
    printf("请输入杨辉三角的行数: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("行数必须为正整数。\n");
        return 1;
    }
    printTriangle(n);
    return 0;
}
