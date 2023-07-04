package brainfuck;

import java.io.PrintStream;

public class OutputValue implements Command {
    /** Prints the value of the current array cell */
    public void Operation(ExecutionContext context) {
        context.InstructionPopFront();
        PrintStream print = new PrintStream(context.GetOutputStream());
        print.print(context.GetCurrentValue());
    }
}
