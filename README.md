# Expression Tree and Postfix Evaluation

## Assignment Question

Consider the postfix expression:

`8 3 2 * + 6 2 / -`

### (a) Implement an Expression Tree using the postfix expression. Display the tree and its traversal results.

The expression represented is:

`(8 + (3 * 2)) - (6 / 2)`

**Expression Tree:**

```text
             -
           /   \
          +     /
         / \   / \
        8   * 6   2
           / \
          3   2
```

**Traversal results**

- **Preorder (Root, Left, Right):** `- + 8 * 3 2 / 6 2`
- **Inorder (Left, Root, Right):** `((8+(3*2))-(6/2))`
- **Postorder (Left, Right, Root):** `8 3 2 * + 6 2 / -`

### (b) Evaluate the expression using stack-based postfix evaluation and Expression Tree evaluation. Prepare a trace showing the important intermediate operations.

#### 1. Stack-Based Postfix Evaluation

| Step | Token | Operation | Stack after operation |
|---:|:---:|---|---|
| 1 | 8 | Push 8 | [8] |
| 2 | 3 | Push 3 | [8, 3] |
| 3 | 2 | Push 2 | [8, 3, 2] |
| 4 | * | 3 × 2 = 6 | [8, 6] |
| 5 | + | 8 + 6 = 14 | [14] |
| 6 | 6 | Push 6 | [14, 6] |
| 7 | 2 | Push 2 | [14, 6, 2] |
| 8 | / | 6 ÷ 2 = 3 | [14, 3] |
| 9 | - | 14 − 3 = 11 | [11] |

**Final result = 11**

#### 2. Expression Tree Evaluation

Evaluation is performed from the leaf nodes upward.

| Step | Sub-expression | Operation | Result |
|---:|---|---|---:|
| 1 | 3 * 2 | 3 × 2 | 6 |
| 2 | 8 + (3 * 2) | 8 + 6 | 14 |
| 3 | 6 / 2 | 6 ÷ 2 | 3 |
| 4 | (8 + 6) - 3 | 14 − 3 | 11 |

**Final result = 11**

Both methods produce the same result: **11**.

### (c) Compare the approaches and explain the structural information provided by an Expression Tree.

| Criterion | Stack-Based Postfix Evaluation | Expression Tree Evaluation |
|---|---|---|
| Number of arithmetic operations | 4 | 4 |
| Data structure | Stack | Binary tree and recursion stack |
| Time complexity | O(n) | O(n) for evaluation; O(n) additional to build the tree |
| Space requirements | O(n) worst case for the stack | O(n) for the tree; O(h) recursion space during evaluation |
| Main advantage | Simple direct evaluation | Preserves the structure of the expression |

Here, **n** is the number of tokens/nodes and **h** is the height of the tree.

#### Why does the Expression Tree provide additional structural information?

Direct postfix evaluation uses a stack to calculate the answer. It does not retain the complete expression hierarchy after the evaluation.

An Expression Tree preserves the operator-operand relationships:

- `3 * 2` is a sub-expression.
- `8 + (3 * 2)` is another sub-expression.
- `6 / 2` is another sub-expression.
- The subtraction operator combines the results of the two main sub-expressions.

The tree also supports preorder, inorder, and postorder traversals. Therefore, it is useful for understanding, displaying, and analysing the expression, while stack-based postfix evaluation is simpler when only the final result is needed.

## Files

- `main.c` — C source code for tree construction, traversals, both evaluation methods, and comparison.
- `Makefile` — GCC build and run commands.
- `README.md` — Assignment answers, trace tables, comparison, and complexity analysis.

## Compile and Run

With GCC and Make installed, run:

```bash
make
./expression_tree
```

On Windows, run the generated executable as `expression_tree.exe`. If Make is unavailable, compile directly:

```bash
gcc -std=c11 -Wall -Wextra main.c -o expression_tree
```

The program uses the given expression directly in `main.c`.
