package game;

import java.io.InputStream;
import java.util.HashMap;
import java.util.Scanner;

public class Game {
    public int cntBarrier = 0;
    public HashMap<String, Detail> gameWindow = new HashMap<>();
    public int gameStatus = 0; // 0 - play game, 1 - finish game
    public int steps = 0;

    public static final int QUANTITY_OF_CELL = 6;

    Game (InputStream level) {
        try(Scanner sc = new Scanner(level)) { 
            String s = sc.nextLine(); //skip first string
            while (sc.hasNext()) {
                s = sc.nextLine();
                String[] data = s.split(" ");
                LevelProcessing(data);
            }
        } 
    }

    public String GetKey(int a, int b) {
        String key = String.valueOf(a);
        key = key.concat(String.valueOf(b));
        return key;
    }

    //try catch не забудь дубина
    public void LevelProcessing(String[] data) {
        for (int i = 0; i < data.length; i++) {
            if (data[i].charAt(0) == 'm') {
                Detail mouse = new Detail('m', 2, Character.digit(data[i].charAt(1), 10), 2);
                gameWindow.put(GetKey(Character.digit(data[i].charAt(1), 10), 2), mouse);
                gameWindow.put(GetKey(Character.digit(data[i].charAt(1), 10) + 1, 2), mouse);

            }
            else if (data[i].charAt(0) == 'v') {
                Detail block = new Detail('v', Character.digit(data[i].charAt(3), 10), Character.digit(data[i].charAt(1), 10), Character.digit(data[i].charAt(2), 10));
                cntBarrier++;
                for(int j = 0; j < Character.digit(data[i].charAt(3), 10); j++) {
                    String key = GetKey(Character.digit(data[i].charAt(1), 10), Character.digit(data[i].charAt(2), 10) + j);
                    gameWindow.put(key, block);
                }
            }
            else if (data[i].charAt(0) == 'h') {
                Detail block = new Detail('h', Character.digit(data[i].charAt(3), 10), Character.digit(data[i].charAt(1), 10), Character.digit(data[i].charAt(2), 10));
                cntBarrier++;
                for(int j = 0; j < Character.digit(data[i].charAt(3), 10); j++) {
                    String key = GetKey(Character.digit(data[i].charAt(1), 10) + j, Character.digit(data[i].charAt(2), 10));
                    gameWindow.put(key, block);
                }
            }
        }
    }

    public void CheckGameStatus() {
        String key;
        boolean tmpStatus = true;
        for (int i = 0; i < QUANTITY_OF_CELL; i ++) {
            key = GetKey(i, 2);
            Detail det = gameWindow.get(key);
            if (det != null && det.orientation == 'm') {
                tmpStatus = false;
            }
        }
        if (tmpStatus) {
            gameStatus = 1;
        }
    }

    public void Moving (int x, int y, Detail det) {
        if (det == null) {
            return;
        }
        if (det.x0 != x || det.y0 != y) {
            if (det.orientation == 'v') {
                for (int i = 0; i < det.len; i++) {
                    gameWindow.remove(GetKey(det.x0, det.y0 + i));
                }
                det.y0 = y;
                det.y1 = y + det.len - 1;
                for (int i = 0; i < det.len; i++) {
                    gameWindow.put(GetKey(det.x0, det.y0 + i), det);
                }
            }
            if (det.orientation == 'h') {
                for (int i = 0; i < det.len; i++) {
                    gameWindow.remove(GetKey(det.x0 + i, det.y0));
                }
                det.x0 = x;
                det.x1 = x + det.len - 1;
                for (int i = 0; i < det.len; i++) {
                    gameWindow.put(GetKey(det.x0 + i, det.y0), det);
                }
            }
            if (det.orientation == 'm') {
                for (int i = 0; i < det.len; i++) {
                    gameWindow.remove(GetKey(det.x0 + i, det.y0));
                }
                det.x0 = x;
                det.x1 = x + 1;
                for (int i = 0; i < det.len; i++) {
                    gameWindow.put(GetKey(det.x0 + i, det.y0), det);
                }
            }
        }
        CheckGameStatus();
        steps++;
    }

    public boolean CheckBorder(int difX, int difY, Detail det) {
        if (difX > 0) {
            for (int i = 1; i <= difX; i++) {
                Detail det1 = gameWindow.get(GetKey(i + det.x1, det.y0));
                if (det1 != null) {
                    return false;
                }
            }
        }
        if (difX < 0) {
            for (int i = difX; i < 0; i++) {
                Detail det1 = gameWindow.get(GetKey(i + det.x0, det.y0));
                if (det1 != null) {
                    return false;
                }
            }
        }
        if (difY > 0) {
            for (int i = 1; i <= difY; i++) {
                Detail det1 = gameWindow.get(GetKey(det.x0, det.y1 + i));
                if (det1 != null) {
                    return false;
                }
            }
        }
        if (difY < 0) {
            for (int i = difY; i < 0; i++) {
                Detail det1 = gameWindow.get(GetKey(det.x0, det.y0 + i));
                if (det1 != null) {
                    return false;
                }
            }
        }
        return true;
    }


}
