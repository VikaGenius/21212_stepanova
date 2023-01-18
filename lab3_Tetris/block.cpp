#include "block.h"
#include <stdlib.h>
#include <time.h>

const int block1[4][4] =  {{0, 1, 0, 0},
                           {0, 1, 0, 0},
                           {0, 1, 0, 0},
                           {0, 1, 0, 0}};
const int block2[4][4] = {{0, 0, 0, 0},
                          {0, 2, 2, 0},
                          {0, 0, 2, 2},
                          {0, 0, 0, 0}};
const int block3[4][4] = {{0, 0, 0, 0},
                          {0, 3, 3, 3},
                          {0, 0, 3, 0},
                          {0, 0, 0, 0}};
const int block4[4][4] = {{0, 4, 4, 0},
                          {0, 4, 0, 0},
                          {0, 4, 0, 0},
                          {0, 0, 0, 0}};
const int block5[4][4] = {{0, 5, 0, 0},
                          {0, 5, 0, 0},
                          {0, 5, 5, 0},
                          {0, 0, 0, 0}};
const int block6[4][4] = {{0, 0, 6, 6},
                          {0, 6, 6, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0}};
const int block7[4][4] = {{0, 0, 0, 0},
                          {0, 7, 7, 0},
                          {0, 7, 7, 0},
                          {0, 0, 0, 0}};


Block::Block() {
    srand(time(NULL));
    int type = rand()%7;
    switch (type) {
    case 0:
        std::copy(*block1, *block1 + sizeBlock * sizeBlock, *block);
        break;
    case 1:
        std::copy(*block2, *block2 + sizeBlock * sizeBlock, *block);
        break;
    case 2:
        std::copy(*block3, *block3 + sizeBlock * sizeBlock, *block);
        break;
    case 3:
        std::copy(*block4, *block4 + sizeBlock * sizeBlock, *block);
        break;
    case 4:
        std::copy(*block5, *block5 + sizeBlock * sizeBlock, *block);
        break;
    case 5:
        std::copy(*block6, *block6 + sizeBlock * sizeBlock, *block);
        break;
    case 6:
        std::copy(*block7, *block7 + sizeBlock * sizeBlock, *block);
        break;
    default:
        break;
    }
}

Block::Block(const Block& other) noexcept : curX(other.curX), curY(other.curY) {
    std::copy(*(other.block), *(other.block) + sizeBlock * sizeBlock, *block);
}

Block& Block::operator=(const Block& other) {
    if (this != &other) {
        curX = other.curX;
        curY = other.curY;
        std::copy(*(other.block), *(other.block) + sizeBlock * sizeBlock, *block);
    }
    return *this;
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



