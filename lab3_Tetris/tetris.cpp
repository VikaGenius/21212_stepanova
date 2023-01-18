#include "tetris.h"
#include <QDebug>

constexpr int sizeBlockMatrix = 4;

Tetris::Tetris(QWidget *parent): QWidget{parent} {
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            tetrisWindow[i][j] = 0;
        }
    }
}

bool Tetris::BlockSpawn() {
    if (status != TheEnd) {
        for (int i = 0; i < sizeBlockMatrix; i++) {
            for (int j = 0; j < sizeBlockMatrix; j++) {
                //проверка на право лево низ верх и наличие других блоков
                if (curBlock.block[i][j] > 0) {
                    if (curBlock.curX + j < 0 || curBlock.curX + j >= fieldWidth || curBlock.curY + i >= fieldHeight) {
                        return false;
                    }
                    if (tetrisWindow[curBlock.curY + i][curBlock.curX + j] > 0) {
                        return false;
                    }
                }
            }
        }
        for (int i = 0; i < sizeBlockMatrix; i++) {
            for (int j = 0; j < sizeBlockMatrix; j++) {
                if (curBlock.block[i][j] > 0) {
                    tetrisWindow[curBlock.curY + i][curBlock.curX + j] = curBlock.block[i][j];
                }
            }
        }
        return true;
    }
    return false;
}

void Tetris::RestoreBlock() {
    Block tmp;
    curBlock = nextBlock;
    nextBlock = tmp;
    if (BlockSpawn() == false) {
        status = TheEnd;
    }
}

void Tetris::clearBlockOnWindow() {
    for (int i = 0; i < sizeBlockMatrix; i++) {
        for (int j = 0; j < sizeBlockMatrix; j++) {
            if (curBlock.block[i][j] > 0) {
                tetrisWindow[curBlock.curY + i][curBlock.curX + j] = 0;
            }
        }
    }
}

bool Tetris::BlockMove(char where) {
    int y = 0;
    int x = 0;
    switch(where) {
        case 'd':
            clearBlockOnWindow();
            curBlock.curY++;
            if (!BlockSpawn()) {
                curBlock.curY--;
                BlockSpawn();
                FullLineOrColumn();
                RestoreBlock();
                return false;
            }
        break;
        case 'l':
            clearBlockOnWindow();
            curBlock.curX--;
            if (!BlockSpawn()) {
                curBlock.curX++;
                BlockSpawn();
            }
        break;
        case 'r':
            clearBlockOnWindow();
            curBlock.curX++;
            if (!BlockSpawn()) {
                curBlock.curX--;
                BlockSpawn();
            }
        break;
        case 'u':
            Block tmp(curBlock);
            clearBlockOnWindow();
            curBlock.RotateBlock();
            if (!(BlockSpawn())) {
                curBlock = tmp;
                BlockSpawn();
            }
        break;
    }
    return true;
}

void Tetris::FullLineOrColumn(){
    bool isFull = true;
    int i = fieldHeight - 1;
    while (i > 0) {
        for (int j = 0; j < fieldWidth; j++) {
            if (tetrisWindow[i][j] == 0) {
                isFull = false;
                i--;
                break;
            }
        }
        if (isFull) {
            for(int k = i; k > 0; k--) {
                for (int j = 0; j < fieldWidth; j++) {
                    tetrisWindow[k][j] = tetrisWindow[k - 1][j];
                }
            }
            //countOfLine++;
            if (score.CountOfScore(1) % 500 == 0) {
                level += 1;
            }
        }
        isFull = true;
    }
}
