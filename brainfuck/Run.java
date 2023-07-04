package brainfuck;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.Scanner;


public class Run {
    /**
     * @param input stream input for program
     * @param read stream input for command ","(input value for current cell of array)
     * @param output stream of program output
     */
    Run(InputStream input, OutputStream output, InputStream read) { 
        ex = new Executor(read, output); 
        in = input;
    }
    /**Console is input and output */
    Run() {
        ex = new Executor();
        in = System.in;
    }
    /**
     * @param input stream input for program
     * @param output stream of program output
     */
    Run(InputStream input, OutputStream output) { 
        ex = new Executor(input, output); 
        in = input;
    }
    /** Reads a program into a queue for further processing */
    public void start() {
        String line;
        String tmp;
        try(Scanner sc = new Scanner(in)) {
            while (sc.hasNext()) {
                line = sc.nextLine();
                for (int i = 0; i < line.length(); i++) {
                    tmp = Character.toString(line.charAt(i));
                    ex.getContext().InstructionPushBack(tmp);
                }
                ex.Execute();
            }
        } catch (Exception  e) {
            System.err.println(e.getMessage());
            throw e;
        }
    }
    
    private Executor ex;    
    private InputStream in;
}
