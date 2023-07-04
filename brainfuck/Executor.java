package brainfuck;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

 /** The executor class contains a factory for creating and receiving commands, as well as instructions for executing */
public class Executor {
    public Executor () {
        context = new ExecutionContext();
    }

    public Executor(InputStream in, OutputStream out) {
        context = new ExecutionContext(in, out);
    }
    
    /** The function runs each user program instruction in turn. */
    public void Execute() {
        if (factoryCommands != null) {
            while (context.InstructionIsEmpty() == false) { //instruction is empty
                Command comm = factoryCommands.GetCommand(context.GetInstruction());
                comm.Operation(context);
            }
        }  
    }

    public ExecutionContext getContext() {
        return context;
    }


    private ExecutionContext context;
    private Factory factoryCommands;
    {
        try { factoryCommands = new Factory(); }
        catch(IOException e) {
            e.printStackTrace();
        }
    }
}
