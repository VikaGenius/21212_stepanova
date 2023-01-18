#ifndef BLOCK_H
#define BLOCK_H

#include <QColor>

constexpr int sizeBlock = 4;

class Block
{
public:
    int curX = 4;
    int curY = 0;
    int block[4][4];

    explicit Block();
    Block(const Block& other) noexcept;
    Block& operator=(const Block& other);
    void RotateBlock();
};

#endif // BLOCK_H
