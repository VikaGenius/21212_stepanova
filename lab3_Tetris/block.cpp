#include "block.h"
#include <stdlib.h>
#include <time.h>

constexpr int sizeBlock = 4;

int block1[4][4] =  {{1, 0, 0, 0},
                    {1, 0, 0, 0},
                    {1, 0, 0, 0},
                    {1, 0, 0, 0}};
int block2[4][4] = {{2, 2, 0, 0},
                    {0, 2, 2, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}};
int block3[4][4] = {{3, 3, 3, 0},
                    {0, 3, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}};
int block4[4][4] = {{4, 4, 0, 0},
                    {4, 0, 0, 0},
                    {4, 0, 0, 0},
                    {0, 0, 0, 0}};
int block5[4][4] = {{5, 0, 0, 0},
                    {5, 0, 0, 0},
                    {5, 5, 0, 0},
                    {0, 0, 0, 0}};
int block6[4][4] = {{0, 6, 6, 0},
                    {6, 6, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}};
int block7[4][4] = {{7, 7, 0, 0},
                    {7, 7, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}};

Block::Block() {
    srand(time(NULL));
    CreateBlock(block);
}

void Block::CopyBlock(int dst[4][4], int src[4][4]) {
    for (int i = 0; i < sizeBlock; i++) {
        for (int j = 0; j < sizeBlock; j++) {
            block[i][j] = src[i][j];
        }
    }
}

void Block::CreateBlock(int dst[4][4]) {
    int type = rand()%7;
    switch (type) {
        case 0:
            CopyBlock(dst, block1);
            break;
        case 1:
            CopyBlock(dst, block2);
            break;
        case 2:
            CopyBlock(dst, block3);
            break;
        case 3:
            CopyBlock(dst, block4);
            break;
        case 4:
            CopyBlock(dst, block5);
            break;
        case 5:
            CopyBlock(dst, block6);
            break;
        case 6:
            CopyBlock(dst, block7);
            break;
    }
}

void Block::RestoreBlock() {
    CopyBlock(block, nextBlock);
    CreateBlock(nextBlock);
    curX = 4;
    curY = 0;
}

void Block::RotateBlock() {
    int tmp;
     for(int i = 0; i < sizeBlock / 2; i++) {
        for(int j = i; j < sizeBlock - 1 - i; j++) {
            tmp = block[i][j];
            block[i][j] = block[sizeBlock - j - 1][i];
            block[sizeBlock - j - 1][i] = block[sizeBlock - i - 1][sizeBlock - j - 1];
            block[sizeBlock - i - 1][sizeBlock - j - 1] = block[j][sizeBlock - i - 1];
            block[j][sizeBlock - i - 1] = tmp;
        }
     }
}



