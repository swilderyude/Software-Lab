// 验证输入的字符串是否是有效的IPv4 / IPV6 / MAC地址，并指出具体哪位数存在问题。

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_valid_ipv4(const char *ip, char *error)
{
    char buf[100];
    strcpy(buf, ip);
    char *token = strtok(buf, ".");
    int count = 0;

    while (token)
    {
        count++;
        for (int i = 0; token[i]; i++)
        {
            if (!isdigit(token[i]))
            {
                sprintf(error, "IPv4第%d段含有非数字字符", count);
                return 0;
            }
        }
        if (strlen(token) > 1 && token[0] == '0')
        {
            sprintf(error, "IPv4第%d段有前导0", count);
            return 0;
        }
        int val = atoi(token);
        if (val < 0 || val > 255)
        {
            sprintf(error, "IPv4第%d段超出范围0-255", count);
            return 0;
        }
        token = strtok(NULL, ".");
    }
    if (count != 4)
    {
        sprintf(error, "IPv4段数错误，应为4段");
        return 0;
    }
    return 1;
}
// 判断16进制
int is_hex(char c)
{
    return isdigit(c) || (tolower(c) >= 'a' && tolower(c) <= 'f');
}

int is_valid_ipv6(const char *ip, char *error)
{
    char buf[200];
    strcpy(buf, ip);
    char *token = strtok(buf, ":");
    int count = 0;

    while (token)
    {
        count++;
        int len = strlen(token);
        if (len < 1 || len > 4)
        {
            sprintf(error, "IPv6第%d组长度错误", count);
            return 0;
        }
        for (int i = 0; i < len; i++)
        {
            if (!is_hex(token[i]))
            {
                sprintf(error, "IPv6第%d组含有非法字符", count);
                return 0;
            }
        }
        token = strtok(NULL, ":");
    }
    if (count != 8)
    {
        sprintf(error, "IPv6组数错误，应为8组");
        return 0;
    }
    return 1;
}

int is_valid_mac(const char *mac, char *error)
{
    char buf[200];
    strcpy(buf, mac);

    char *token;
    char sep = strchr(mac, '-') ? '-' : ':';

    token = strtok(buf, &sep);
    int count = 0;
    while (token)
    {
        count++;
        if (strlen(token) != 2)
        {
            sprintf(error, "MAC第%d组长度错误，应为2位", count);
            return 0;
        }
        for (int i = 0; i < 2; i++)
        {
            if (!is_hex(token[i]))
            {
                sprintf(error, "MAC第%d组含有非法字符", count);
                return 0;
            }
        }
        token = strtok(NULL, &sep);
    }
    if (count != 6)
    {
        sprintf(error, "MAC组数错误，应为6组");
        return 0;
    }
    return 1;
}

const char *validate_address(const char *input)
{
    static char error[200];
    char tmp[200];

    if (is_valid_ipv4(input, error))
        return "IPv4";
    strcpy(tmp, error);

    if (is_valid_ipv6(input, error))
        return "IPv6";
    if (strcmp(error, "") != 0)
        strcpy(tmp, error);

    if (is_valid_mac(input, error))
        return "MAC";
    if (strcmp(error, "") != 0)
        strcpy(tmp, error);

    // 都不合法，返回 Neither + 错误原因
    static char result[300];
    sprintf(result, "Neither，%s", tmp);
    return result;
}

int main()
{
    char input[200];
    printf("请输入地址: ");
    scanf("%199s", input);

    const char *result = validate_address(input);
    printf("返回值: %s\n", result);
    return 0;
}