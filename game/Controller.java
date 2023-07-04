package game;

import java.io.IOException;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextInputDialog;
import javafx.scene.control.Alert.AlertType;

public class Controller {
    public String name;

    @FXML
    private Button myButton;
    @FXML
    private Button myButton1;
    public boolean isWindowOpen = false;

    @FXML
    public void initialize(){
        myButton.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    TextInputDialog dialog = new TextInputDialog();
                    dialog.setTitle("Enter your nickname");
                    dialog.setHeaderText(null);
                    dialog.setContentText("Nickname:");
                    
            
                    java.util.Optional<String> result = dialog.showAndWait();
                    if (result.isPresent()) {
                        name = result.get();
                        isWindowOpen = true;
                        LevelChoice lvls = new LevelChoice();
                        lvls.showLevelChoiceWindow(this);
                    }
                }
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }
        });
        
        myButton1.setOnAction(event -> {
            Alert alert = new Alert(AlertType.INFORMATION);
            alert.setTitle("Game rules");
            alert.setHeaderText("Как играть?");
            alert.setContentText("Тебе нужно вывести хомяка из поля вправо, расчистив строку. Для этого передвигай кукурузины: вертикальные вверх и вниз, горизонтальные - влево и вправо. Ты справишься!");
            alert.showAndWait();
        });
    }
}
