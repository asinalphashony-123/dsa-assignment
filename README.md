# Expression Tree Evaluation

## Problem

Consider the postfix expression:

8 3 2 * + 6 2 / -

The program builds an Expression Tree, displays the tree and traversals, evaluates the expression using both stack-based postfix evaluation and Expression Tree evaluation, and compares the two approaches.

## Expression Tree

The expression is equivalent to:

8 + (3 * 2) - (6 / 2)

Tree structure:

-
|-- +
|   |-- 8
|   |-- *
|       |-- 3
|       |-- 2
|-- /
    |-- 6
    |-- 2

## Traversals

Preorder: - + 8 * 3 2 / 6 2

Inorder: 8 + 3 * 2 - 6 / 2

Postorder: 8 3 2 * + 6 2 / -

## Evaluation

### Stack-based postfix evaluation

The expression is scanned from left to right. Operands are pushed onto a stack. When an operator is found, the required operands are popped, the operation is performed, and the result is pushed back.

Important operations:

1. 3 * 2 = 6
2. 8 + 6 = 14
3. 6 / 2 = 3
4. 14 - 3 = 11

Final result: 11

### Expression Tree evaluation

The tree is evaluated recursively from the leaves upward:

1. 3 * 2 = 6
2. 8 + 6 = 14
3. 6 / 2 = 3
4. 14 - 3 = 11

Final result: 11

## Comparison

| Feature | Postfix Evaluation | Expression Tree |
|---|---|---|
| Data structure | Stack | Binary tree |
| Evaluation time | O(n) | O(n) |
| Construction | Not required | O(n) |
| Space | O(n) worst case | O(n) tree + O(h) recursion |
| Main output | Numerical result | Result plus structure |
| Traversals | Not stored | Prefix, infix, postfix |
| Modification | Less convenient | Convenient |

## Structural Information

Direct postfix evaluation mainly calculates the final value and does not retain the complete expression structure after evaluation.

The Expression Tree stores every operand-operator relationship as parent-child links. Therefore, it shows the order of operations and individual subexpressions. It can also be traversed to produce prefix, infix, and postfix forms.

This makes Expression Trees useful for expression analysis, modification, and further processing.

## Files

- expression_tree.c: C implementation
- input.txt: given postfix expression
- output.txt: expected output and trace
- README.md: documentation

## Compile and Run

Using GCC:

gcc expression_tree.c -o expression_tree

./expression_tree

On Windows:

gcc expression_tree.c -o expression_tree.exe

expression_tree.exe

Make sure input.txt is in the same folder.

## Expected Result

Postfix evaluation result: 11

Expression Tree evaluation result: 11
