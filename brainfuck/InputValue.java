package brainfuck;

import java.io.InputStreamReader;

public class InputValue implements Command {
    /** Takes a value from the input and puts it in the current cell of the array */
    public void Operation(ExecutionContext context) {
        context.InstructionPopFront();
        try { 
            InputStreamReader reader = new InputStreamReader(context.GetInputStream());
            context.ChangeCurrentValue(reader.read());
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
