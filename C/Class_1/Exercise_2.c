// 大数存储问题。求1-40阶乘。

#include <stdio.h>
#include <string.h>
#define N 1000

int result[N];
int len;
// 大数乘法函数
void multiply(int multiplier)
{
    int carry = 0;
    for (int i = 0; i < len; i++)
    {
        int product = result[i] * multiplier + carry;
        result[i] = product % 10;
        carry = product / 10;
    }
    while (carry)
    {
        result[len] = carry % 10;
        carry /= 10;
        len++;
    }
}
int main()
{
    int n;
    printf("请在1到40内选择所求阶乘的数字:");
    scanf("%d", &n);
    if (n < 1 || n > 40)
    {
        printf("输入超出范围！\n");
        return 1;
    }
    memset(result, 0, sizeof(result));
    result[0] = 1;
    len = 1;
    for (int i = 2; i <= n; i++)
    {
        multiply(i);
    }
    printf("该数阶乘为:");
    for (int i = len - 1; i >= 0; i--)
    {
        printf("%d", result[i]);
    }
    printf("\n");
    return 0;
}