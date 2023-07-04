package game;

public class Detail {
    public char orientation; //vertical or horizontal
    public int len;
    public int x0; 
    public int y0;
    public int x1;
    public int y1;
    public int move = 0;

    Detail(char orient, int length, int x, int y) {
        orientation = orient;
        len = length;
        if (orientation == 'v') {
            y0 = y;
            y1 = y + len - 1;
            x0 = x;
            x1 = x;
        } else if (orientation == 'h') {
            y0 = y;
            y1 = y;
            x0 = x;
            x1 = x + len - 1;
        } else if (orientation == 'm') {
            y0 = y;
            y1 = y;
            x0 = x;
            x1 = x + 1;
        }
    }
    
}
