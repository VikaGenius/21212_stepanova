package game;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
//import javafx.scene.media.Media;
//import javafx.scene.media.MediaPlayer;

public class ControllerLvls {
    @FXML
    private Button button1;
    @FXML
    private Button button2;
    @FXML
    private Button button3;
    @FXML
    private Button button4;
    @FXML
    private Button button5;
    @FXML
    private Button button6;
    @FXML
    private Button button7;
    @FXML
    private Button button8;
    @FXML
    private Button button9;
    @FXML
    private Button button10;

    public void setUserName(String name) {
        userName = name;
    }

    @FXML
    public void initialize() {
        button1.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    isWindowOpen = true;
                    /*Media music1 = new Media("file:///home/kesha/music/Not_afraid.wav");
                    soundPlayer = new MediaPlayer(music1);
                    soundPlayer.play();*/
                    lvlData = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/lvl1.txt");
                    ControllerGame lvl1 = new ControllerGame();
                    lvl1.StartGame(lvlData, this);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        button2.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    isWindowOpen = true;
                    lvlData = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/lvl2.txt");
                    ControllerGame lvl2 = new ControllerGame();
                    lvl2.StartGame(lvlData, this);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        button3.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    isWindowOpen = true;
                    lvlData = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/lvl3.txt");
                    ControllerGame lvl3 = new ControllerGame();
                    lvl3.StartGame(lvlData, this);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        button4.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    isWindowOpen = true;
                    lvlData = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/lvl4.txt");
                    ControllerGame lvl4 = new ControllerGame();
                    lvl4.StartGame(lvlData, this);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        button5.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    isWindowOpen = true;
                    lvlData = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/lvl5.txt");
                    ControllerGame lvl5 = new ControllerGame();
                    lvl5.StartGame(lvlData, this);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        button6.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    isWindowOpen = true;
                    lvlData = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/lvl6.txt");
                    ControllerGame lvl6 = new ControllerGame();
                    lvl6.StartGame(lvlData, this);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        button7.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    isWindowOpen = true;
                    lvlData = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/lvl7.txt");
                    ControllerGame lvl7 = new ControllerGame();
                    lvl7.StartGame(lvlData, this);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        button8.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    isWindowOpen = true;
                    lvlData = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/lvl8.txt");
                    ControllerGame lvl8 = new ControllerGame();
                    lvl8.StartGame(lvlData, this);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        button9.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    isWindowOpen = true;
                    lvlData = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/lvl9.txt");
                    ControllerGame lvl9 = new ControllerGame();
                    lvl9.StartGame(lvlData, this);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        button10.setOnAction(event -> {
            try {
                if (!isWindowOpen) {
                    isWindowOpen = true;
                    lvlData = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/lvl10.txt");
                    ControllerGame lvl10 = new ControllerGame();
                    lvl10.StartGame(lvlData, this);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }); 
    }

    public boolean isWindowOpen = false;
    public InputStream lvlData;
    public String userName;

    //private MediaPlayer soundPlayer = null;
}
