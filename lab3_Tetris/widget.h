#ifndef WIDGET_H
#define WIDGET_H

#include "tetris.h"

#include <QGraphicsItem>
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

private slots:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent* event) override;


private:
    Ui::GameWidget* ui;
    QGraphicsScene* gameScene = nullptr;
    QGraphicsScene* nextScene = nullptr;
    Tetris tetris;
    int timerGame;
    int timerPainting;
    int speed = 800;
    int update = 3;
    int level = 0;

    void GameStart();
    void Painting();
    void GameOver();
    void LevelUp();

};
#endif // WIDGET_H
