package game;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.stage.Stage;
import javafx.util.Duration;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;


public class ControllerGame {
    private static final int SHIFT = 25; //смещение клеточного поля относительно игрового экрана
    private static final int SIZE_OF_CELL = 100;
    private int MAX_SHIFT;

    public void StartGame(InputStream lvl, ControllerLvls cLvls) throws FileNotFoundException {
        nickname = cLvls.userName;
        try {
            window = new Image(new FileInputStream("/home/kesha/oop/game/app/src/main/resources/поле2.png"));
        } catch (FileNotFoundException e) {
            System.err.println(e.getMessage());;
        }

        game = new Game(lvl);

        primaryStage = new Stage();
        primaryStage.setTitle("BestGameOfTheWorld");
         
        StartTime();

        stepsLabel = new Label("0 шагов");
        stepsLabel.setLayoutX(730);
        stepsLabel.setLayoutY(300);
        stepsLabel.setStyle("-fx-font-size: 24pt;"); // настройка размера шрифта
        
        // Создание Canvas
        canvas = new Canvas(1000, 650);

        // Получение контекста графики
        gc = canvas.getGraphicsContext2D();
    
        Draw();

        // Добавление обработчиков событий мыши
        canvas.setOnMousePressed(event -> {
            try {
                HandleMousePressed(event);
            } catch (FileNotFoundException e) {
                System.err.println(e.getMessage());
            }
        });

        canvas.setOnMouseDragged(event -> {
            try {
                HandleMouseDragged(event);
            } catch (FileNotFoundException e) {
                System.err.println(e.getMessage());
            }
        });

        canvas.setOnMouseReleased(event -> {
            try {
                HandleMouseReleased(event);
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }
        });

        // Создание сцены
        Pane root = new Pane(canvas);
        root.getChildren().addAll(timeLabel, stepsLabel);
        Scene scene = new Scene(root, 1000, 650);

        // Отображение сцены
        primaryStage.setScene(scene);
        primaryStage.show();

        primaryStage.setOnCloseRequest(event -> {
            cLvls.isWindowOpen = false;
        });

        primaryStage.setResizable(false);
    }

    private void StartTime() {
        timeLabel = new Label("0 секунд");
        timeLabel.setLayoutX(730);
        timeLabel.setLayoutY(150);
        timeLabel.setStyle("-fx-font-size: 24pt;"); // настройка размера шрифта

        timeline = new Timeline(
            new KeyFrame(Duration.seconds(1), e -> {
                secondsPassed++;
                timeLabel.setText(Integer.toString(secondsPassed).concat(" секунд"));
            })
        );
        timeline.setCycleCount(Animation.INDEFINITE); // запускаем бесконечный цикл анимации
        timeline.play();
    }

    private int newCoord(double a) {
        return (int)(a - SHIFT) / SIZE_OF_CELL;
    }

    private int newCoord1(double a) {
        return (int)Math.round((a - SHIFT) / SIZE_OF_CELL);
    }

    private int ShiftX(double a) {
        double shift = a - (detail.x0 * SIZE_OF_CELL + SHIFT);
        double sig = Math.signum(shift);
        shift = Math.abs(shift);
        return (int)(Math.ceil(shift / SIZE_OF_CELL) * sig);
    }
    private int ShiftY(double a) {
        double shift = a - (detail.y0 * SIZE_OF_CELL + SHIFT);
        double sig = Math.signum(shift);
        shift = Math.abs(shift);
        return (int)(Math.ceil(shift / SIZE_OF_CELL) * sig);
    }

    private void HandleMousePressed(MouseEvent event) throws FileNotFoundException {
        //Запоминание начальной позиции мыши
        mouseX = event.getSceneX();
        mouseY = event.getSceneY();
        int x = newCoord(mouseX);
        int y = newCoord(mouseY);
        String key = game.GetKey(x, y);
        detail = game.gameWindow.get(key);
        if (detail != null) {
            image = GetImage(detail);
            imageX = SHIFT + detail.x0 * SIZE_OF_CELL;
            imageY = SHIFT + detail.y0 * SIZE_OF_CELL;
            
            MAX_SHIFT = (Game.QUANTITY_OF_CELL - detail.len) * SIZE_OF_CELL + SHIFT;
        }
    }

    private void HandleMouseDragged(MouseEvent event) throws FileNotFoundException {
        if (detail == null) {
            return;
        }
        double imgX0 = 0; 
        double imgY0 = 0;
        // Вычисление новой позиции изображения
        if (detail.orientation == 'h') {
            if (imageX + event.getSceneX() - mouseX >= SHIFT && imageX + event.getSceneX() - mouseX <= MAX_SHIFT) {
                imgX0 = imageX + event.getSceneX() - mouseX;
                int difX = ShiftX(imgX0);
                int difY = 0;
                if (game.CheckBorder(difX, difY, detail) == true) {
                    imageX = imgX0;
                }
            }
            mouseX = event.getSceneX();
        } else if (detail.orientation == 'v') {
            if (imageY + event.getSceneY() - mouseY >= SHIFT && imageY + event.getSceneY() - mouseY <= MAX_SHIFT) {
                imgY0 = imageY + event.getSceneY() - mouseY;
                int difX = 0;
                int difY = ShiftY(imgY0);
                if (game.CheckBorder(difX, difY, detail) == true) {
                    imageY = imgY0;
                }
            }
            mouseY = event.getSceneY();
        } else if (detail.orientation == 'm') {
            if (imageX + event.getSceneX() - mouseX >= SHIFT && imageX + event.getSceneX() - mouseX <= MAX_SHIFT + detail.len * SIZE_OF_CELL) {
                imgX0 = imageX + event.getSceneX() - mouseX;
                int difX = ShiftX(imgX0);
                int difY = 0;
                if (game.CheckBorder(difX, difY, detail) == true) {
                    imageX = imgX0;
                }
            }
            mouseX = event.getSceneX(); //сохранение новой позиции мыши
        }
        detail.move = 1;
        
        // Очистка Canvas и перерисовка изображения
        gc.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
        Draw();
        gc.drawImage(image, imageX, imageY);
        detail.move = 0;
    }

    private void HandleMouseReleased(MouseEvent event) throws IOException  {
        int x = newCoord1(imageX);
        int y = newCoord1(imageY);
        game.Moving(x, y, detail);
        stepsLabel.setText(Integer.toString(game.steps).concat(" шагов"));
        try {            
            Draw();
        } catch (IOException e) {
            System.err.println(e.getMessage());;
        }
        if (game.gameStatus == 1) {
            timeline.stop();
            WinWindow winWindow = new WinWindow();
            winWindow.showWinWindow(nickname, secondsPassed);
        }

    }

    private void Draw() throws FileNotFoundException {
        gc.drawImage(window, 0, 0);
        for (int i = 0; i < 7; i++) {
            gc.strokeLine(SIZE_OF_CELL * i + SHIFT, SHIFT, SIZE_OF_CELL * i + SHIFT, SIZE_OF_CELL * 6 + SHIFT);
            gc.strokeLine(SHIFT, SIZE_OF_CELL * i + SHIFT, SIZE_OF_CELL * 6 + SHIFT, SIZE_OF_CELL * i + SHIFT);
        }
        String key;
        Detail det;
        for(int i = 0; i < Game.QUANTITY_OF_CELL; i++) {
            for (int j = 0; j < Game.QUANTITY_OF_CELL; j++) {
                key = String.valueOf(i) + String.valueOf(j);
                det = game.gameWindow.get(key);
                if (det != null && det.move == 0) { 
                    if (i == det.x0 && j == det.y0) {
                        Image currentImage = GetImage(det);
                        gc.drawImage(currentImage, SHIFT + SIZE_OF_CELL * det.x0, SHIFT + SIZE_OF_CELL * det.y0);
                    }
                    if (det.orientation == 'v') {
                        j = det.y1; 
                    }
                }
            }
        }
    }
    
    Image GetImage(Detail detail) throws FileNotFoundException {
        if (detail.orientation == 'v' && detail.len == 3) {
            try (FileInputStream fileImage = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/кукуруза3в.png")) {
                return new Image(fileImage); 
            } catch (IOException e) {
                throw new FileNotFoundException(e.getMessage());
            }
        } else if (detail.orientation == 'v' && detail.len == 2) {
            try (FileInputStream fileImage = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/кукуруза2в.png")) {
                return new Image(fileImage); 
            } catch (IOException e) {
                throw new FileNotFoundException(e.getMessage());
            }
        } else if (detail.orientation == 'h' && detail.len == 3) {
            try (FileInputStream fileImage = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/кукуруза3г.png")) {
                return new Image(fileImage); 
            } catch (IOException e) {
                throw new FileNotFoundException(e.getMessage());
            }
        } else if (detail.orientation == 'h' && detail.len == 2) {
            try (FileInputStream fileImage = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/кукуруза2г.png")) {
                return new Image(fileImage); 
            } catch (IOException e) {
                throw new FileNotFoundException(e.getMessage());
            }
        } else if (detail.orientation == 'm') {
            try (FileInputStream fileImage = new FileInputStream("/home/kesha/oop/game/app/src/main/resources/хомяк.png")) {
                return new Image(fileImage); 
            } catch (IOException e) {
                throw new FileNotFoundException(e.getMessage());
            }
        }
        return null;
    }

    private double mouseX, mouseY;
    private double imageX, imageY;
    private Image image; //текущее изображение, которое двигаем
    private Image window;
    private Canvas canvas;
    private GraphicsContext gc;
    private int secondsPassed = 0;

    private Timeline timeline;
    private Stage primaryStage;
    private Game game;
    private Detail detail; //текущая деталь
    private Label stepsLabel;
    private Label timeLabel;

    public String nickname;
}

