I implemented a parser and lexical analyzer in C++!

For the language, I defined keywords and identifiers, variables and let declarations, blocks, statements (print, if, while, assignment, and return statements), and expressions. I provided operator precedence, with multiplication/division operators at the highest level, then addition/subtraction, then greater than or less than, and finally equality. I used left recursion for my grammar, which provides left-associativity.

Firstly, I built a node which tracks all the statements in the program; each program is a series of statements, and this node holds all of them. Second, I used expression nodes for integers, floats, booleans, identifiers, binary and unary operations, and function calls. Third, I used declaration nodes to track whether declarations are immutable, and function name declarations to keep track of the function names, return types, and bodies. Lastly, I used statement nodes for return, print, if, and while statements. 

The primary challenge was scope tracking for semantic validation due to Bison's bottom-up parsing. I learned that parameters are parsed before function bodies, and this makes it impossible to detect parameter-variable name conflicts. I also had a difficult time with identifying the exact line and column of errors. I was able to fix this by tracking the last valid token's position and using that for EOF errors, adding 1 to point where the semicolon should be.

Although I had a hard time learning flex to begin with, I thought it was a great lexer. It was a fantastic tool which had automatic tokenization, which enabled me to focus entirely on abstract syntax tree generation and parsing. I appreciated how it worked together with Bison and how its column and line tracking allowed for easy parsing error tracing.

During this assignment I learned the practical parts of how a compiler creates a grammar specification from a language and uses it to parse code. This provided a good complement to the written homeworks, where we learned how to construct parsing trees from grammars. The programming assignment gave insight into how compilers go from a tokenized language to a semantic analysis, using abstract syntax trees. I also learned two new tools, flex and bison, and it was interesting to understand how they form lexemes and provide the basis for effective parsing.

I tested my code by checking for several invalid declaration statements and semantic errors, using the wrong operators, missing semicolons, and missing colons. Here are three of the tests I checked against:

a.
var x : int = 5; # invalid; using = instead of :=

b.
func test() : int {
    print(5)
    return 0;
} # invalid; missing a semicolon after a statement

c.
var x int := 5; # invalid; missing a colon before the type
