#include "tetris.h"

GameState::GameState() : currentBlock(nullptr), nextBlock(nullptr) {
    initialize();
}

GameState::~GameState() {
    delete currentBlock;
    delete nextBlock;
}

void GameState::initialize() {
    // 初始化地图
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (j == 0 || j == BOARD_WIDTH - 1 || i == BOARD_HEIGHT - 1) {
                board[i][j] = 1;  // 边界
            } else {
                board[i][j] = 0;  // 空白
            }
        }
    }
    
    score = 0;
    level = 1;
    lines = 0;
    gameOver = false;
    
    // 生成初始方块
    generateNextBlock();
    generateNextBlock(); // 生成两个方块，一个当前，一个下一个
    blockX = BOARD_WIDTH / 2 - 2;
    blockY = 0;
}

bool GameState::canMove(int dx, int dy) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentBlock->getShape(i, j) != 0) {
                int x = blockX + j + dx;
                int y = blockY + i + dy;
                
                if (x < 0 || x >= BOARD_WIDTH || y >= BOARD_HEIGHT || 
                    (y >= 0 && board[y][x] != 0)) {
                    return false;
                }
            }
        }
    }
    return true;
}

// 其他方法实现（略）    
