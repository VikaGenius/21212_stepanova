package brainfuck;

public interface Command {

    /** 
     * @param context Contains the state of the program
     */
    public void Operation(ExecutionContext context);
}
