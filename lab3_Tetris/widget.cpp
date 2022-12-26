#include "widget.h"
#include "ui_widget.h"
#include "block.h"
#include "tetris.h"

#include <QPen>
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QKeyEvent>
#include <QMessageBox>

constexpr int fieldHeightG = 600;
constexpr int  fieldWidthG = 300;
constexpr int  sizeOfCell = 30;

GameWidget::GameWidget(QWidget *parent): QWidget(parent), ui(new Ui::GameWidget) {
    ui->setupUi(this);
    gameScene = new QGraphicsScene();
    ui->graphicsView->setScene(gameScene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    currentBlock = new Block();
    tetris = new Tetris();
    GameStart();
}

GameWidget::~GameWidget() {
    delete currentBlock;
    delete tetris;
    delete ui;
}

void GameWidget::GameStart() {
    tetris->status = Motion;
    timerGame = startTimer(speed);
    timerPainting = startTimer(update);
    currentBlock->CreateBlock(currentBlock->nextBlock);
    currentBlock->RestoreBlock();
    tetris->BlockSpawn(currentBlock);
}

void GameWidget::Painting() {
    gameScene->clear();

    QPen pen;
    pen.setBrush(Qt::darkGray);

    //Рисуем клеточное поле
    for (size_t i = 0; i < 10; i++) {
        gameScene->addLine(i*sizeOfCell, 0, i*sizeOfCell, fieldHeightG, pen);
    }
    for (size_t i = 0; i < 20; i++) {
        gameScene->addLine(0, i*sizeOfCell, fieldWidthG, i*sizeOfCell, pen);
    }

    QColor color;
    QBrush brush;
    pen.setBrush(Qt::gray);
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            switch (tetris->tetrisWindow[i][j]) {
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
            qDebug() << color;
            gameScene->addRect(i * sizeOfCell, j * sizeOfCell, sizeOfCell, sizeOfCell, pen, brush);
        }
    }

}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    if(tetris->status == Motion) {
        switch (event->key()) {
            case Qt::Key_Up:
                tetris->BlockMove(currentBlock, 'u');
                break;
            case Qt::Key_Down:
                tetris->BlockMove(currentBlock, 'd');
                if (tetris->status == TheEnd) {
                    GameOver();
                }
                break;
            case Qt::Key_Right:
                tetris->BlockMove(currentBlock, 'r');
                break;
            case Qt::Key_Left:
                tetris->BlockMove(currentBlock, 'l');
                break;
        }

    }
}

void GameWidget::timerEvent(QTimerEvent* event) {
    if (event->timerId() == timerGame && tetris->status != TheEnd) {
        tetris->BlockMove(currentBlock, 'd');
        if (tetris->status == TheEnd) {
            GameOver();
        }
    }
    if (event->timerId() == timerPainting) {
        Painting();
    }
}

void GameWidget::GameOver() {
    killTimer(timerGame);
    killTimer(timerPainting);
    QMessageBox::information(this, "failed", "game over");
}



