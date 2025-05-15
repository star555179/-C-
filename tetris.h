#ifndef TETRIS_H
#define TETRIS_H

#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

// 游戏常量
const int BOARD_WIDTH = 12;
const int BOARD_HEIGHT = 20;
const int NEXT_BLOCK_X = 26;
const int NEXT_BLOCK_Y = 5;

// 方块类型枚举
enum BlockType {
    BLOCK_I, BLOCK_J, BLOCK_L, BLOCK_O, BLOCK_S, BLOCK_T, BLOCK_Z
};

// 颜色枚举
enum BlockColor {
    CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    ORANGE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    PURPLE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    RED = FOREGROUND_RED | FOREGROUND_INTENSITY
};

// 方块类
class Block {
private:
    BlockType type;
    int shape[4][4];
    BlockColor color;

public:
    Block(BlockType t);
    BlockType getType() const;
    int getShape(int x, int y) const;
    BlockColor getColor() const;
    void rotate();
};

// 游戏状态类
class GameState {
private:
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    Block* currentBlock;
    Block* nextBlock;
    int blockX, blockY;
    int score;
    int level;
    int lines;
    bool gameOver;

public:
    GameState();
    ~GameState();
    void initialize();
    bool canMove(int dx, int dy) const;
    bool canRotate() const;
    void move(int dx, int dy);
    void rotate();
    void drop();
    void lockBlock();
    int clearLines();
    void generateNextBlock();
    bool isGameOver() const;
    int getScore() const;
    int getLevel() const;
    int getLines() const;
    const Block* getCurrentBlock() const;
    const Block* getNextBlock() const;
    int getBoardValue(int x, int y) const;
};

// 渲染类
class Renderer {
private:
    HANDLE hOut;

public:
    Renderer();
    void clearScreen() const;
    void setColor(int color) const;
    void gotoxy(int x, int y) const;
    void renderBoard(const GameState& state) const;
    void renderNextBlock(const Block* block) const;
    void renderScore(const GameState& state) const;
    void renderGameOver(const GameState& state) const;
};

// 输入处理类
class InputHandler {
public:
    enum Key {
        NONE, UP, DOWN, LEFT, RIGHT, SPACE, ESC, P
    };
    static Key getKey();
};

// 游戏控制器类
class GameController {
private:
    GameState state;
    Renderer renderer;
    int dropSpeed;
    int dropCounter;
    bool paused;

public:
    GameController();
    void run();
    void processInput(InputHandler::Key key);
    void update();
    void render() const;
};

#endif // TETRIS_H    
