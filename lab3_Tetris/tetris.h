#ifndef TETRIS_H
#define TETRIS_H

#include "block.h"
#include "score.h"

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
    bool BlockMove(char where);
    bool BlockSpawn();

    int tetrisWindow[fieldHeight][fieldWidth];
    Block nextBlock;
    GameStatus status;
    Score score;
    int level = 0;

private:
    void clearBlockOnWindow();
    void FullLineOrColumn();
    void RestoreBlock();
    Block curBlock;
};

#endif // TETRIS_H
