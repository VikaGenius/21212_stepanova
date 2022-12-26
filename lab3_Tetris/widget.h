#ifndef WIDGET_H
#define WIDGET_H

#include "block.h"
#include "tetris.h"

#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>



QT_BEGIN_NAMESPACE
namespace Ui { class GameWidget; }
QT_END_NAMESPACE

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
    void GameStart();
    void Painting();
    void GameOver();

public slots:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent* event) override;


private:
    Ui::GameWidget *ui;
    QGraphicsScene *gameScene = nullptr;
    Tetris* tetris = nullptr;
    Block* currentBlock = nullptr;
    QGraphicsItemGroup* blockGroup = nullptr;
    int timerGame;
    int timerPainting;
    int speed = 800;
    int update = 3;
    int score = 0;
    //задать количество очков, следующий элемент
};
#endif // WIDGET_H
