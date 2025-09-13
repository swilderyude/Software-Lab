// 逆波兰表达式求值。逆波兰表达式，即后缀表示法。
// 用栈计算逆波兰表达式，栈的链式实现相当于头插法。
// 需要给出中缀表达式，用树结构（数字节点，运算符节点）
// 输入用例至少5个操作符

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

typedef struct TreeNode
{
    char *expression;
    int value;
    char op;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct StackNode
{
    TreeNode *treeNode;
    struct StackNode *next;
} StackNode;

TreeNode *createTreeNode(int value, const char *expr, char op)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->value = value;
    node->expression = (char *)malloc(strlen(expr) + 1);
    strcpy(node->expression, expr);
    node->op = op;
    node->left = NULL;
    node->right = NULL;
    return node;
}
// 数字节点
TreeNode *createNumberNode(int value)
{
    char expr[20];
    sprintf(expr, "%d", value);
    return createTreeNode(value, expr, '\0');
}
// 运算符优先级
int getPriority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}
// 为表达式添加括号
int needParentheses(TreeNode *child, char parentOp, int isLeft)
{
    if (child->op == '\0')
        return 0;

    int childPriority = getPriority(child->op);
    int parentPriority = getPriority(parentOp);

    if (childPriority < parentPriority)
        return 1;

    if (childPriority == parentPriority)
    {
        if (parentOp == '-' && !isLeft) // a - (b - c)
            return 1;
        if (parentOp == '/' && !isLeft) // a / (b / c)
            return 1;
    }
    return 0;
}
// 运算符节点
TreeNode *createOperatorNode(char op, TreeNode *left, TreeNode *right)
{
    int result;
    switch (op)
    {
    case '+':
        result = left->value + right->value;
        break;
    case '-':
        result = left->value - right->value;
        break;
    case '*':
        result = left->value * right->value;
        break;
    case '/':
        result = left->value / right->value;
        break;
    default:
        result = 0;
    }

    // 构建中缀表达式
    char expr[200] = "";
    int leftNeedParen = needParentheses(left, op, 1);
    int rightNeedParen = needParentheses(right, op, 0);

    if (leftNeedParen)
    {
        strcat(expr, "(");
        strcat(expr, left->expression);
        strcat(expr, ")");
    }
    else
    {
        strcat(expr, left->expression);
    }

    char opStr[2] = {op, '\0'};
    strcat(expr, opStr);

    if (rightNeedParen)
    {
        strcat(expr, "(");
        strcat(expr, right->expression);
        strcat(expr, ")");
    }
    else
    {
        strcat(expr, right->expression);
    }

    return createTreeNode(result, expr, op);
}

void push(StackNode **top, TreeNode *treeNode)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->treeNode = treeNode;
    newNode->next = *top;
    *top = newNode;
}

TreeNode *pop(StackNode **top)
{
    if (*top == NULL)
        return NULL;
    StackNode *temp = *top;
    TreeNode *treeNode = temp->treeNode;
    *top = (*top)->next;
    free(temp);
    return treeNode;
}

int isEmpty(StackNode *top)
{
    return top == NULL;
}

int calculateRPN(char *expression)
{
    StackNode *stack = NULL;
    int i = 0;

    while (expression[i] != '\0')
    {
        if (isspace(expression[i]))
        {
            i++;
            continue;
        }

        if (isdigit(expression[i]))
        {
            int num = 0;
            while (isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            push(&stack, createNumberNode(num));
        }
        else if (expression[i] == '+' || expression[i] == '-' ||
                 expression[i] == '*' || expression[i] == '/')
        {
            if (isEmpty(stack) || stack->next == NULL)
            {
                printf("错误：表达式格式不正确\n");
                return 0;
            }

            TreeNode *right = pop(&stack);
            TreeNode *left = pop(&stack);
            TreeNode *operatorNode = createOperatorNode(expression[i], left, right);
            push(&stack, operatorNode);
            i++;
        }
        else
        {
            printf("错误：无效字符 '%c'\n", expression[i]);
            return 0;
        }
    }

    if (isEmpty(stack) || stack->next != NULL)
    {
        printf("错误：表达式格式不正确\n");
        return 0;
    }

    TreeNode *finalNode = pop(&stack);
    printf("中缀表达式: %s\n", finalNode->expression);
    printf("计算结果: %d\n", finalNode->value);

    int result = finalNode->value;
    free(finalNode->expression);
    free(finalNode);

    return result;
}

int main()
{
    char expression[MAX_LENGTH];

    printf("请输入逆波兰表达式（至少包含5个操作符）:\n");
    fgets(expression, MAX_LENGTH, stdin);
    expression[strcspn(expression, "\n")] = '\0';

    calculateRPN(expression);

    return 0;
}
