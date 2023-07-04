package game;

import java.io.IOException;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class LevelChoice {
    public void showLevelChoiceWindow(Controller controller) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/lvls.fxml"));
        Parent root = loader.load();
        ControllerLvls controllerLvls = loader.getController();
        controllerLvls.setUserName(controller.name);
        loader.setController(controllerLvls);
        Scene scene = new Scene(root, 400, 600);
        scene.setUserAgentStylesheet(null);

        Stage stage = new Stage();
        stage.setScene(scene);

        stage.setFullScreen(false);
        stage.setResizable(false);
        stage.show();

        stage.setOnCloseRequest(event -> {
            controller.isWindowOpen = false;
        });
    }
}
