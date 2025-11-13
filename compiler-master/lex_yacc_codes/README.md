# Compiler Lex/Yacc Projects

This repository contains several small compiler-related projects using Lex and Yacc. Each project includes build and run instructions, along with sample input.

---

## 1. Calculator (`calc`)

A simple calculator that evaluates basic arithmetic expressions.

**Build & Run:**
```bash
lex calc.l
yacc -d calc.y
gcc lex.yy.c y.tab.c -o calc
./calc
```

**Sample Input:**
```
3 + 5
```

---

## 2. Abstract Syntax Tree Builder (`ast`)

Builds and displays an Abstract Syntax Tree (AST) for a given arithmetic expression.

**Build & Run:**
```bash
lex ast.l
yacc -d ast.y
gcc lex.yy.c y.tab.c -o ast
./ast
```

**Sample Input:**
```
3+5*(10-4)
```

---

## 3. String Equality Checker (`neq`)

Checks if a string consists of an equal number of 'a's followed by an equal number of 'b's (e.g., `aabb`).

**Build & Run:**
```bash
lex neq.l
yacc -d neq.y
gcc lex.yy.c y.tab.c -o neq -ll
./neq
```

**Sample Input:**
```
aabb
abab
```

---

## 4. Pattern Recognizer (`pattern`)

Recognizes strings that follow the pattern `a*b+` (zero or more 'a's followed by one or more 'b's).

**Build & Run:**
```bash
lex pattern.l
yacc -d pattern.y
gcc lex.yy.c y.tab.c -o pattern
./pattern
```

**Sample Input:**
```
ab
aab
aaab
abbbaabba
```

---

## 5. Three-Address Code Generator (`three_addr_generator`)

Converts simple assignment statements into three-address code.

**Build & Run:**
```bash
yacc -d three_addr.y
lex three_addr.l
gcc y.tab.c lex.yy.c -o three_addr_generator
./three_addr_generator < input.txt
```

**Sample Input (`input.txt`):**
```
a = b + c * d;
x = a - e;
y = (a + b) * (c + d);
```

---

## 6. Simple Code Generator (`codegen`)

Generates simple assembly-like code from three-address code statements.

**Build & Run:**
```bash
yacc -d codegen.y
lex codegen.l
gcc y.tab.c lex.yy.c -o codegen
./codegen
```

**Sample Input:**
```
T1 := A + B
T2 := C * D
Result := T1 - T2
```
---
## 7. Optimizer (`optimizer`)

Implements basic optimization techniques for arithmetic expressions.
**Build & Run:**
```bash
yacc -d optimizer.y
lex optimizer.l
gcc y.tab.c lex.yy.c -o optimizer
./optimizer
```

**Sample Input:**
```
2 * 3 + b * 1  
a + 0
(b * 0) + (c + 0)
x+0
a*2
a/2
```