// 斗地主发牌。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// 一共54张牌，编码1~54
// 0 代表黑桃_A 1 代表黑桃_2 ....... 12 代表 黑桃_k
// 13代表红桃_A .................. 25 代表 红桃_k
// 26代表草花_A .................. 38 代表 草花_k
// 39代表方块_A .................. 51 代表 方块_k
struct card
{
    int id;
    char suits[20];
};

struct card cards[54];
char *suit[] = {"黑桃", "红桃", "草花", "方块"};
char *joker[] = {"小王", "大王"};
char *face[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
int flag[54] = {0};

void licensing()
{
    // 重置标志数组，表示所有牌都未使用
    for (int i = 0; i < 54; i++)
    {
        flag[i] = 0;
    }
    // 随机发牌
    for (int i = 0; i < 54; i++)
    {
        int x = rand() % 54;
        while (flag[x] != 0)
        {
            x = rand() % 54;
        }
        flag[x] = 1;
        cards[i].id = x;
        if (x / 13 < 4)
        {
            sprintf(cards[i].suits, "%s_%s", suit[x / 13], face[x % 13]);
        }
        else
        {
            strcpy(cards[i].suits, joker[x % 13]);
        }
    }
    // 打印发牌结果：三位玩家各17张牌，最后3张底牌
    for (int i = 0; i <= 53; i++)
    {
        if (i % 17 == 0 && i != 0)
        {
            printf("\n");
        }
        if (i % 17 == 0 && i / 17 != 3)
        {
            printf("玩家%d: ", i / 17 + 1);
        }
        else if (i / 17 == 3 && i % 17 == 0)
        {
            printf("底牌: ");
        }
        printf("%s ", cards[i].suits);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    int times;
    printf("请输入发牌次数：");
    scanf("%d", &times);
    for (int i = 0; i < times; i++)
    {
        printf("第%d次发牌:\n", i + 1);
        licensing();
    }
    return 0;
}