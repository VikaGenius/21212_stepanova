#include "widget.h"
#include "ui_widget.h"
//#include "block.h"
#include "tetris.h"

#include <QPen>
#include <QBrush>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <QGraphicsView>
//#include <QMediaPlayer>

constexpr int fieldHeightG = 600;
constexpr int  fieldWidthG = 300;
constexpr int  sizeOfCell = 30;
constexpr int fieldNext = 210;

GameWidget::GameWidget(QWidget *parent): QWidget(parent), ui(new Ui::GameWidget) {
    ui->setupUi(this);

    gameScene = new QGraphicsScene();
    ui->graphicsView->setScene(gameScene);

    nextScene = new QGraphicsScene();
    ui->next->setScene(nextScene);

    //отключаем скролл бары и всякое
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->next->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->next->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->next->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    GameStart();
}

GameWidget::~GameWidget() {
    delete ui;
}

void GameWidget::GameStart() {
    tetris.status = Motion;
    timerGame = startTimer(speed);
    timerPainting = startTimer(update);
    tetris.BlockSpawn();

    /*QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl("game.qrc:/media/music/Eminem feat. Juice WRLD - Godzilla.mp3"));
    player->setVolume(50);
    player->play();*/
}

void GameWidget::LevelUp() {
    if (level < 7) {
        if (tetris.level > level) {
            level++;
            speed -= 110;
            killTimer(timerGame);
            timerGame = startTimer(speed);
        }
    }
}

void GameWidget::Painting() {
    gameScene->clear();
    nextScene->clear();

    QPen pen;
    pen.setBrush(Qt::darkGray);

    ui->lineEdit->setText(QString::number(tetris.score.CountOfScore(0)));

    //Рисуем клеточное поле
    for (size_t i = 0; i < fieldWidth; i++) {
        gameScene->addLine(i*sizeOfCell, 0, i*sizeOfCell, fieldHeightG, pen);
    }
    for (size_t i = 0; i < fieldHeight; i++) {
        gameScene->addLine(0, i*sizeOfCell, fieldWidthG, i*sizeOfCell, pen);
    }

    //Клеточное поле для след. элемента
    for (size_t i = 0; i < fieldNext; i++) {
        nextScene->addLine(i*sizeOfCell, 0, i*sizeOfCell, fieldNext, pen);
    }
    for (size_t i = 0; i < fieldNext; i++) {
        nextScene->addLine(0, i*sizeOfCell, fieldNext, i*sizeOfCell, pen);
    }

    //рисуем блоки на клеточном поле
    QColor color;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    pen.setBrush(Qt::darkGray);
    for (int i = 0; i < fieldWidth; i++) {
        for (int j = 0; j < fieldHeight; j++) {
            switch (tetris.tetrisWindow[j][i]) {
                case 0:
                    continue;
                case 1:
                    color = Qt::red;
                    break;
                case 2:
                    color = Qt::green;
                    break;
                case 3:
                    color = Qt::blue;
                    break;
                case 4:
                    color = Qt::cyan;
                    break;
                case 5:
                    color = Qt::magenta;
                    break;
                case 6:
                    color = Qt::yellow;
                    break;
                case 7:
                    color = Qt::darkMagenta;
                    break;
            }
            brush.setColor(color);
            gameScene->addRect(i * sizeOfCell, j * sizeOfCell, sizeOfCell, sizeOfCell, pen, brush);
        }
    }

    //рисуем спойлеры (след. блок)
    brush.setColor(Qt::black);
    for (int i = 0; i < sizeBlock; i++) {
        for (int j = 0; j < sizeBlock; j++) {
            if (tetris.nextBlock.block[i][j] > 0) {
                nextScene->addRect((i + 1) * sizeOfCell, (j + 1) * sizeOfCell, sizeOfCell, sizeOfCell, pen, brush);
            }
        }
    }
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    if(tetris.status == Motion) {
        switch (event->key()) {
            case Qt::Key_Up:
                tetris.BlockMove('u');
                break;
            case Qt::Key_Down:
                tetris.BlockMove('d');
                LevelUp();
                break;
            case Qt::Key_Right:
                tetris.BlockMove('r');
                break;
            case Qt::Key_Left:
                tetris.BlockMove('l');
                break;
        case Qt::Key_Space:
            while(tetris.BlockMove('d')) {}
            break;
        }
    }
}

void GameWidget::timerEvent(QTimerEvent* event) {
    if (event->timerId() == timerPainting && tetris.status == TheEnd) {
        GameOver();
    }
    if (event->timerId() == timerGame && tetris.status == Motion) {
        tetris.BlockMove('d');
        LevelUp();
    }
    if (event->timerId() == timerPainting) {
        Painting();
    }
}

void GameWidget::GameOver() {
    killTimer(timerGame);
    killTimer(timerPainting);
    QMessageBox::information(this, "Game Over", "Ты лох =)");
}



