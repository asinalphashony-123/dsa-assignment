#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *items[MAX];
    int top;
} NodeStack;

typedef struct {
    int items[MAX];
    int top;
} IntStack;

Node *createNode(char data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void pushNode(NodeStack *stack, Node *node) {
    if (stack->top >= MAX - 1) {
        fprintf(stderr, "Expression is too large.\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = node;
}

Node *popNode(NodeStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Invalid postfix expression.\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

void pushInt(IntStack *stack, int value) {
    if (stack->top >= MAX - 1) {
        fprintf(stderr, "Expression is too large.\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = value;
}

int popInt(IntStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Invalid postfix expression.\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

Node *buildTree(const char *postfix) {
    NodeStack stack = { .top = -1 };

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isspace((unsigned char)ch)) {
            continue;
        }

        if (!isdigit((unsigned char)ch) && !isOperator(ch)) {
            fprintf(stderr, "Invalid character in expression: %c\n", ch);
            exit(EXIT_FAILURE);
        }

        Node *node = createNode(ch);

        if (isOperator(ch)) {
            node->right = popNode(&stack);
            node->left = popNode(&stack);
        }

        pushNode(&stack, node);
    }

    if (stack.top != 0) {
        fprintf(stderr, "Invalid postfix expression.\n");
        exit(EXIT_FAILURE);
    }

    return popNode(&stack);
}

void printTreeBranches(Node *root, const char *prefix, int isLast) {
    if (root == NULL) {
        return;
    }

    printf("%s%s%c\n", prefix, isLast ? "`-- " : "|-- ", root->data);

    char nextPrefix[256];
    snprintf(nextPrefix, sizeof(nextPrefix), "%s%s",
             prefix, isLast ? "    " : "|   ");

    if (root->left != NULL && root->right != NULL) {
        printTreeBranches(root->left, nextPrefix, 0);
        printTreeBranches(root->right, nextPrefix, 1);
    } else if (root->left != NULL) {
        printTreeBranches(root->left, nextPrefix, 1);
    } else if (root->right != NULL) {
        printTreeBranches(root->right, nextPrefix, 1);
    }
}

void printTree(Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%c\n", root->data);
    if (root->left != NULL && root->right != NULL) {
        printTreeBranches(root->left, "", 0);
        printTreeBranches(root->right, "", 1);
    } else if (root->left != NULL) {
        printTreeBranches(root->left, "", 1);
    } else if (root->right != NULL) {
        printTreeBranches(root->right, "", 1);
    }
}

void preorder(Node *root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root) {
    if (root == NULL) return;

    if (isOperator(root->data)) printf("(");
    inorder(root->left);
    printf("%c", root->data);
    inorder(root->right);
    if (isOperator(root->data)) printf(")");
}

void postorder(Node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->data);
}

int calculate(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                fprintf(stderr, "Division by zero.\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
        default:
            fprintf(stderr, "Unknown operator.\n");
            exit(EXIT_FAILURE);
    }
}

int evaluatePostfix(const char *postfix) {
    IntStack stack = { .top = -1 };

    printf("Stack-based postfix evaluation trace:\n");

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isspace((unsigned char)ch)) continue;

        if (isdigit((unsigned char)ch)) {
            pushInt(&stack, ch - '0');
        } else if (isOperator(ch)) {
            int b = popInt(&stack);
            int a = popInt(&stack);
            int result = calculate(ch, a, b);
            printf("%d %c %d = %d\n", a, ch, b, result);
            pushInt(&stack, result);
        }
    }

    if (stack.top != 0) {
        fprintf(stderr, "Invalid postfix expression.\n");
        exit(EXIT_FAILURE);
    }

    return popInt(&stack);
}

int evaluateTree(Node *root) {
    if (root == NULL) return 0;

    if (isdigit((unsigned char)root->data)) {
        return root->data - '0';
    }

    int leftValue = evaluateTree(root->left);
    int rightValue = evaluateTree(root->right);
    int result = calculate(root->data, leftValue, rightValue);

    printf("%d %c %d = %d\n",
           leftValue, root->data, rightValue, result);

    return result;
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    const char *postfix = "8 3 2 * + 6 2 / -";

    printf("Postfix expression: %s\n\n", postfix);

    Node *root = buildTree(postfix);

    printf("a) Expression Tree:\n");
    printTree(root);

    printf("\nPreorder: ");
    preorder(root);

    printf("\nInorder: ");
    inorder(root);

    printf("\nPostorder: ");
    postorder(root);
    printf("\n");

    printf("\nb) Stack-based postfix evaluation:\n");
    int postfixResult = evaluatePostfix(postfix);
    printf("Result = %d\n", postfixResult);

    printf("\nExpression Tree evaluation trace:\n");
    int treeResult = evaluateTree(root);
    printf("Result = %d\n", treeResult);

    printf("\nc) Comparison:\n");
    printf("Arithmetic operations: 4 in each method.\n");
    printf("Data structures: stack for postfix; binary tree and recursion for tree evaluation.\n");
    printf("Time: O(n) for postfix evaluation; O(n) to build and O(n) to evaluate the tree.\n");
    printf("Space: O(n) worst-case stack; O(n) for the tree plus O(h) recursion space.\n");
    printf("The tree preserves operator-operand relationships and supports traversals.\n");

    freeTree(root);
    return 0;
}
