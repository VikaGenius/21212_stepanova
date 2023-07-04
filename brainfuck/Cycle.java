package brainfuck;

import java.util.ArrayList;
import java.util.Iterator;

public class Cycle implements Command {
    /** Operation [], do while currentValue > 0
     * @param context consist // in nterface
     * 
     */
    public void Operation(ExecutionContext context) {
        int countCycle = 0;
        ArrayList<String> cycle;
        if (context.GetCurrentValue().equals((char)0)) {
            context.InstructionPopFront();
            String tmp = context.GetInstruction();
            while (tmp.equals("]") == false || countCycle != 0) {
                if (tmp.equals("[")) {
                    countCycle++; 
                }
                if (tmp.equals("]")) {
                    countCycle--;
                }
                context.InstructionPopFront();
                tmp = context.GetInstruction();
            }
            context.InstructionPopFront();
            return;
        }
        else {
            cycle = new ArrayList<String>();
            Iterator<String> iter = context.IteratorForInstruction();
            String tmp;
            iter.next(); // пропустим скобочку [
            while(iter.hasNext()) {
                tmp = iter.next();
                if (tmp.equals("[")) {
                    countCycle++;
                }
                if (tmp.equals("]")) {
                    if (countCycle == 0) {
                        while (cycle.isEmpty() == false) {
                            context.InstructionPushFront(cycle.get(cycle.size() - 1));
                            cycle.remove(cycle.size() - 1);
                        }
                        return;
                    } else {
                        countCycle--;
                    }
                }
                cycle.add(tmp);
            }
        }
        if (cycle.isEmpty() == false) {
            throw new RuntimeException("Lost closing bracket");
        }
    }
}
