#ifndef BLOCK_H
#define BLOCK_H

#include <QColor>

class Block
{
public:
    int curX = 4;
    int curY = 0;

    explicit Block();
    void RotateBlock();
    void CopyBlock(int dst[4][4], int src[4][4]);
    void CreateBlock(int dst[4][4]);
    void RestoreBlock();

signals:


private:

public:
    int block[4][4];
    int nextBlock[4][4];
    int tmpBlock[4][4];
};

#endif // BLOCK_H
