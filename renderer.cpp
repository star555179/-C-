#include "tetris.h"

Renderer::Renderer() {
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // 隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

void Renderer::clearScreen() const {
    system("cls");
}

void Renderer::setColor(int color) const {
    SetConsoleTextAttribute(hOut, color);
}

void Renderer::gotoxy(int x, int y) const {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hOut, coord);
}

void Renderer::renderBoard(const GameState& state) const {
    clearScreen();
    
    // 绘制边框
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            gotoxy(j * 2, i);
            if (state.getBoardValue(i, j) == 1) {
                cout << "■";
            } else {
                cout << "  ";
            }
        }
    }
    
    // 绘制当前方块
    const Block* current = state.getCurrentBlock();
    setColor(static_cast<int>(current->getColor()));
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (current->getShape(i, j) != 0) {
                int x = (state.getBlockX() + j) * 2;
                int y = state.getBlockY() + i;
                
                if (y >= 0) {
                    gotoxy(x, y);
                    cout << "■";
                }
            }
        }
    }
    
    // 绘制游戏信息
    renderScore(state);
}

// 其他方法实现（略）    
