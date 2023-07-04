package brainfuck;


public class DecrementPointer implements Command {
    /**Shifts to the left by one array cell*/
    public void Operation(ExecutionContext context) {
        context.InstructionPopFront();
        if (context.GetIndex() > 0) {
            context.DecreaseIndex();
        }
        else {
            throw new RuntimeException("Went abroad");
        }
    }
}
