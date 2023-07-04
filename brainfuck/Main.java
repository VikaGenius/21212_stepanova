package brainfuck;

import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;

public class Main {
    public static void main(String[] args)  {
        Run run;
        InputStream read = System.in;
        if (args.length == 0) {
            run = new Run();
            run.start();
        } else {
            try {
                InputStream input = new FileInputStream(args[0]);
                OutputStream output = System.out;
                run = new Run(input, output, read);
                run.start();
            } catch (Exception e) {
                System.err.println(e.getMessage());
                return;
            }
        }
    }
}
