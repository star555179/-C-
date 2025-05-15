#include "tetris.h"

// 方块形状定义
const int BLOCK_SHAPES[7][4][4] = {
    // I型
    { {0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0} },
    // J型
    { {1,0,0}, {1,1,1}, {0,0,0} },
    // L型
    { {0,0,1}, {1,1,1}, {0,0,0} },
    // O型
    { {0,1,1}, {0,1,1}, {0,0,0} },
    // S型
    { {0,1,1}, {1,1,0}, {0,0,0} },
    // T型
    { {0,1,0}, {1,1,1}, {0,0,0} },
    // Z型
    { {1,1,0}, {0,1,1}, {0,0,0} }
};

// 方块颜色映射
const BlockColor BLOCK_COLORS[7] = {
    CYAN, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED
};

Block::Block(BlockType t) : type(t) {
    // 初始化形状
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i < 3 && j < 3) {
                shape[i][j] = BLOCK_SHAPES[static_cast<int>(t)][i][j];
            } else {
                shape[i][j] = 0;
            }
        }
    }
    
    // 设置颜色
    color = BLOCK_COLORS[static_cast<int>(t)];
}

BlockType Block::getType() const {
    return type;
}

int Block::getShape(int x, int y) const {
    return shape[x][y];
}

BlockColor Block::getColor() const {
    return color;
}

void Block::rotate() {
    int temp[4][4];
    
    // 复制原形状
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = shape[i][j];
        }
    }
    
    // 旋转（转置并翻转）
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            shape[i][j] = temp[3 - j][i];
        }
    }
}    
