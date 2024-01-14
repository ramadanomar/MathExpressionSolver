# MathExpressionSolver In C++ Using STL And Classes

Features
- Can parse all types of expressions (* #(for sqrt) + - etc.)
- Respects parantheses & order of operations
- Shows messages for incorrect expressions and numbers.
- Saves all previous parsed expression results in a binary file (and in memory as a cache)
- Can be launched from the CLI (MathExpressionSolver.exe (expression) -i [input-file path] -o [output-file-path]
- Can read expressions from STDIN (keyboard) and from a file
- Can output result to STDOUT (console) or to a txt file
- Previous expressions can be referenced using $ variables. For example if the first expression we ran had an answer of 144 we can reference it using $0 in the next expression
- Has a menu to help the user navigate through some of the features.
