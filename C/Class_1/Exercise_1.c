// 兔子生崽问题。

#include <stdio.h>
// 递归，第一个月末有1对成兔，0对小兔；第二个月末有1对成兔，1对小兔；以此类推。
int fun(int n)
{
    if (n == 1)
    {
        return 1;
    }
    if (n == 2)
    {
        return 2;
    }
    else
    {
        return fun(n - 1) + fun(n - 2);
    }
}
// 求一年后的月末兔子对数
int main()
{
    int a = fun(12);
    printf("一年以后有%d对兔子\n", a);
    return 0;
}