package brainfuck;

public class ValueIncrement implements Command {
    /** Increase value in array cell  */
    public void Operation(ExecutionContext context) {
        context.InstructionPopFront();
        context.IncreaseCurrentValue();
    }
}
