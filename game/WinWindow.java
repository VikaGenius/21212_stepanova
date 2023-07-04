package game;

import java.io.IOException;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class WinWindow {
    public void showWinWindow(String name, int score) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/win.fxml"));
        Parent root = loader.load();
        Stage stage = new Stage();
        ControllerWin control = loader.getController();
        control.setUserData(name, score);
        loader.setController(control);
        stage.setScene(new Scene(root, 500, 500));
        stage.setResizable(false);
        stage.show();
    }
}
