#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct Node {
    char data;
    struct Node *left, *right;
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
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) exit(1);
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

void pushNode(NodeStack *s, Node *n) { s->items[++s->top] = n; }
Node *popNode(NodeStack *s) { return s->items[s->top--]; }

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

Node *buildExpressionTree(const char *postfix) {
    NodeStack s = {.top = -1};

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isspace((unsigned char)c)) continue;

        if (isdigit((unsigned char)c)) {
            pushNode(&s, createNode(c));
        } else if (isOperator(c)) {
            Node *right = popNode(&s);
            Node *left = popNode(&s);
            Node *op = createNode(c);
            op->left = left;
            op->right = right;
            pushNode(&s, op);
        }
    }
    return popNode(&s);
}

void preorder(Node *root) {
    if (!root) return;
    printf("%c ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}

void postorder(Node *root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->data);
}

void displayTree(Node *root, int level, char branch) {
    if (!root) return;

    for (int i = 0; i < level; i++) printf("    ");

    if (level == 0)
        printf("%c\n", root->data);
    else
        printf("%c-- %c\n", branch, root->data);

    displayTree(root->left, level + 1, 'L');
    displayTree(root->right, level + 1, 'R');
}

int applyOperator(int left, int right, char op) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        default: exit(1);
    }
}

int evaluatePostfix(const char *postfix) {
    IntStack s = {.top = -1};

    printf("\nStack-based postfix evaluation trace:\n");

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isspace((unsigned char)c)) continue;

        if (isdigit((unsigned char)c)) {
            int value = c - '0';
            s.items[++s.top] = value;
            printf("Read %c -> push %d\n", c, value);
        } else if (isOperator(c)) {
            int right = s.items[s.top--];
            int left = s.items[s.top--];
            int result = applyOperator(left, right, c);
            s.items[++s.top] = result;

            printf("Read %c -> %d %c %d = %d -> push %d\n",
                   c, left, c, right, result, result);
        }
    }
    return s.items[s.top];
}

int evaluateTree(Node *root) {
    if (!root) return 0;

    if (!isOperator(root->data))
        return root->data - '0';

    int left = evaluateTree(root->left);
    int right = evaluateTree(root->right);
    int result = applyOperator(left, right, root->data);

    printf("Tree evaluation: %d %c %d = %d\n",
           left, root->data, right, result);

    return result;
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    char postfix[MAX];

    if (!file) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }

    if (!fgets(postfix, sizeof(postfix), file)) {
        fclose(file);
        printf("Error: Empty input.\n");
        return 1;
    }
    fclose(file);

    printf("Expression Tree and Evaluation\n");
    printf("Postfix Expression: %s", postfix);

    Node *root = buildExpressionTree(postfix);

    printf("\nExpression Tree:\n");
    displayTree(root, 0, ' ');

    printf("\nTraversals:\n");
    printf("Preorder  : ");
    preorder(root);
    printf("\nInorder   : ");
    inorder(root);
    printf("\nPostorder : ");
    postorder(root);
    printf("\n");

    int postfixResult = evaluatePostfix(postfix);
    printf("Postfix evaluation result: %d\n", postfixResult);

    printf("\nExpression Tree evaluation trace:\n");
    int treeResult = evaluateTree(root);
    printf("Expression Tree evaluation result: %d\n", treeResult);

    printf("\nComparison:\n");
    printf("Postfix evaluation uses a stack.\n");
    printf("Expression Tree evaluation uses a binary tree and recursion.\n");
    printf("Both evaluations take O(n) time.\n");
    printf("Both require O(n) worst-case space.\n");
    printf("The Expression Tree preserves operand-operator relationships and supports\n");
    printf("prefix, infix, and postfix traversals, unlike direct postfix evaluation.\n");

    freeTree(root);
    return 0;
}
