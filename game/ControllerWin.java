package game;

import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class ControllerWin {

    @FXML
    private Label score;

    void setUserData(String name, int seconds) {
        score.setText(name + ": " + Integer.toString(seconds) + " секунд");
    }
    
}
