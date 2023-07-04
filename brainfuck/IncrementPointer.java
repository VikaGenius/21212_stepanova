package brainfuck;

class IncrementPointer implements Command {
    /** Shifts to the right by one array cell */
    public void Operation (ExecutionContext context) {
        context.InstructionPopFront();
        if (context.GetIndex() < ExecutionContext.MAX_IND) {
            context.IncreaseIndex();
        }
        else {
            throw new RuntimeException("Overflow in array");
        }
    }
}
