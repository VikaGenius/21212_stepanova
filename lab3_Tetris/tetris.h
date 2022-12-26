#ifndef TETRIS_H
#define TETRIS_H

#include "block.h"
#include <QWidget>

constexpr int fieldWidth = 10;
constexpr int fieldHeight = 20;

enum GameStatus {
    Motion,
    Waiting,
    TheEnd
};

class Tetris : public QWidget
{
    Q_OBJECT
public:
    explicit Tetris(QWidget *parent = nullptr);
    void Game();
    bool BlockSpawn(Block* curBlock);
    void BlockMove(Block* curBlock, char where);
    void BlockMoving(Block* curBlock, int x, int y);
    bool FullLineOrColumn();
    int tetrisWindow[fieldWidth][fieldHeight] = {0};
    int countOfLine = 0;
    GameStatus status;
signals:

private:

    //const static int fieldWidth = 10;
    //const static int fieldHeight = 20;
    //int tetrisWindow[fieldWidth][fieldHeight] = {0};

};

#endif // TETRIS_H
