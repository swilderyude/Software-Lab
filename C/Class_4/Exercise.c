// 合并两个有序升序整数数组。
// 示例
// 输入：[4, 5,6]，[1,2,3]
// 返回值：[1,2,3,4,5,6]
// 输入：[1,2,3]，[2,5,6]
// 返回值：[1,2,2,3,5,6]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void merge(int *A, int m, int *B, int n)
{
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;
    while (i >= 0 && j >= 0)
    {
        if (A[i] > B[j])
        {
            A[k] = A[i];
            i--;
        }
        else
        {
            A[k] = B[j];
            j--;
        }
        k--;
    }
    while (j >= 0)
    {
        A[k] = B[j];
        j--;
        k--;
    }
}
// 输入形式转换为整数数组
int parseArray(const char *s, int *arr)
{
    int num = 0, sign = 1, inNumber = 0, count = 0; // sign表示数字符号
    for (int i = 0; s[i]; i++)
    {
        if (s[i] == '-')
        {
            sign = -1;
        }
        else if (isdigit((unsigned char)s[i]))
        {
            num = num * 10 + (s[i] - '0');
            inNumber = 1;
        }
        else if (inNumber)
        {
            arr[count++] = num * sign;
            num = 0;
            sign = 1;
            inNumber = 0;
        }
    }
    if (inNumber)
    {
        arr[count++] = num * sign;
    }
    return count;
}

int main()
{
    char input1[256], input2[256];
    int A[200], B[200];
    int m, n;

    printf("请输入第一个数组: ");
    scanf("%255s", input1);
    m = parseArray(input1, A);

    printf("请输入第二个数组: ");
    scanf("%255s", input2);
    n = parseArray(input2, B);

    for (int i = m; i < m + n; i++)
    {
        A[i] = 0;
    }
    merge(A, m, B, n);

    printf("合并结果: [");
    for (int i = 0; i < m + n; i++)
    {
        printf("%d", A[i]);
        if (i < m + n - 1)
            printf(", ");
    }
    printf("]\n");

    return 0;
}