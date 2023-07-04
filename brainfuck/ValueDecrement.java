package brainfuck;

public class ValueDecrement implements Command {
    /** Decrease value in array cell  */
    public void Operation(ExecutionContext context) {
        context.InstructionPopFront();
        context.DecreaseCurrentValue();
    }
}
