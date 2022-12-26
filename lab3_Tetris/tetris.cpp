#include "tetris.h"
#include <QDebug>

constexpr int sizeBlockMatrix = 4;

Tetris::Tetris(QWidget *parent)
    : QWidget{parent}
{
}

bool Tetris::BlockSpawn(Block* curBlock) {
    for (int i = 0; i < sizeBlockMatrix; i++) {
        for (int j = 0; j < sizeBlockMatrix; j++) {
            if ((curBlock->block[i][j] > 0) && !(tetrisWindow[curBlock->curY + i][curBlock->curX + j] == 0)) {
                return false;
            }
        }
    }
    qDebug() << "2";
    for (int i = 0; i < sizeBlockMatrix; i++) {
        for (int j = 0; j < sizeBlockMatrix; j++) {
            if (curBlock->block[i][j] > 0) {
                tetrisWindow[curBlock->curY + i][curBlock->curX + j] = curBlock->block[i][j];
            }
        }
    }
    return true;
}

void Tetris::BlockMove(Block* curBlock, char where) {
    int y = 0;
    int x = 0;
    switch(where) {
        case 'd':
            for (int i = 0; i < sizeBlockMatrix; i++) {
                for (int j = 0; j < sizeBlockMatrix; j++) {
                    y = curBlock->curY + i + 1;
                    x = curBlock->curX + j;
                    if (!(y < fieldHeight && curBlock->block[i][j] > 0 && tetrisWindow[y][x] == 0)) {
                        return;
                    }
                }
            }
            BlockMoving(curBlock, 0, 1);
            curBlock->curY++;
        case 'l':
            for (int i = 0; i < sizeBlockMatrix; i++) {
                for (int j = 0; j < sizeBlockMatrix; j++) {
                    y = curBlock->curY + i;
                    x = curBlock->curX + j - 1;
                    if (!(x > 0 && curBlock->block[i][j] > 0 && tetrisWindow[y][x] == 0)) {
                        status = Waiting;
                        curBlock->RestoreBlock();
                        BlockSpawn(curBlock);
                        status = Motion;
                        return;
                    }
                }
            }
            BlockMoving(curBlock, -1, 0);
            curBlock->curX--;
        case 'r':
            for (int i = 0; i < sizeBlockMatrix; i++) {
                for (int j = 0; j < sizeBlockMatrix; j++) {
                    y = curBlock->curY + i;
                    x = curBlock->curX + j + 1;
                    if (!(x < fieldWidth && curBlock->block[i][j] > 0 && tetrisWindow[y][x] == 0)) {
                        return;
                    }
                }
            }
            BlockMoving(curBlock, 1, 0);
            curBlock->curX++;
        case 'u':
            curBlock->CopyBlock(curBlock->tmpBlock, curBlock->block);
            curBlock->RotateBlock();
            if (!(BlockSpawn(curBlock))) {
                curBlock->CopyBlock(curBlock->block, curBlock->tmpBlock);
            }
    }

    if (!FullLineOrColumn()) {
        status = TheEnd;
    }
}

void Tetris::BlockMoving(Block* curBlock, int x, int y) {
    for (int i = 0; i < sizeBlockMatrix; i++) {
        for (int j = 0; j < sizeBlockMatrix; j++) {
            if (curBlock->block[i][j] == 1) {
                tetrisWindow[curBlock->curX + i + x][curBlock->curY + j + y] = 1;
                tetrisWindow[curBlock->curX + i][curBlock->curY + j] = 0;

            }
        }
    }
}

bool Tetris::FullLineOrColumn(){
    bool isFull = true;
    for (int i = fieldHeight - 1; i > 0; i--) {
        for (int j = 0; j < fieldWidth; j++) {
            if (tetrisWindow[i][j] == 0) {
                isFull = false;
            }
        }
        if (isFull) {
            for(int k = i; k > 0; k--) {
                for (int j = 0; j < fieldWidth; j++) {
                    tetrisWindow[k][j] = tetrisWindow[k - 1][j];
                }
            }
            countOfLine++;
        }
    }

    for(int i = 0; i < fieldWidth; i++) {
        if (tetrisWindow[0][i] > 0) {
            return false;
        }
    }
    return true;
}

