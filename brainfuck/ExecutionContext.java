package brainfuck;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayDeque;
import java.util.Iterator;
 
/** A class that stores the context for executing each interpreter command. Instructions, input and output streams, array and current cell number. */
public class ExecutionContext {
    public ExecutionContext() {
        for (int i = 0; i < MAX_IND; i++) {
            array[i] = 0;
        }
        input = System.in;
        output = System.out;
    }

    public ExecutionContext(InputStream in, OutputStream out) { 
        for (int i = 0; i < MAX_IND; i++) {
            array[i] = 0;
        }
        input = in;
        output = out;
    };
    
    public void IncreaseIndex() {
        index++;
    }

    public void DecreaseIndex() {
        index--;
    }

    public int GetIndex() {
        return index;
    }

    public void NewIndex(int ind) {
        index = ind;
    }

    public Character GetCurrentValue() {
        return array[index];
    }

    public void IncreaseCurrentValue() {
        array[index]++;
    }

    public void DecreaseCurrentValue() {
        array[index]--;
    }

    public void ChangeCurrentValue(int a) {
        array[index] = (char)a;
    }

    public OutputStream GetOutputStream() {
        return output;
    }

    public InputStream GetInputStream() {
        return input;
    }

    public void InstructionPushBack(String command) {
        instruction.offerLast(command);
    }

    public String InstructionPopFront() {
        return instruction.pop();
    }

    public String GetInstruction() {
        return instruction.peek();
    }

    public boolean InstructionIsEmpty() {
        return instruction.isEmpty();
    }

    Iterator<String> IteratorForInstruction() {
        Iterator<String> itr = instruction.iterator();
        return itr;
    }

    void InstructionPushFront(String val) {
        instruction.addFirst(val);
    }

    private Character[] array = new Character[MAX_IND]; ; 
    private int index = 0;
    public static final int MAX_IND = 30000;
    private InputStream input;
    private OutputStream output;
    ArrayDeque<String> instruction = new ArrayDeque<String>();;
}