# Semester-Project

REPL calls interpreter.run(tree)
execute(BlockNode)
execute(AssignNode) ← x = 5 + 3
evaluate(BinOpNode +)
evaluate(NumberNode 5) → 5.0
evaluate(NumberNode 3) → 3.0
returns 5.0 + 3.0 = 8.0
env.set("x", 8.0) ← stored in notebook

        execute(PrintNode)           ← dikhao x
            evaluate(IdentifyingNode "x")
                env.get("x")         → returns 8.0
            cout << 8.0              ← prints 8
