#include "tetris.h"

GameController::GameController() : dropSpeed(50), dropCounter(0), paused(false) {}

void GameController::run() {
    while (!state.isGameOver()) {
        InputHandler::Key key = InputHandler::getKey();
        processInput(key);
        
        if (!paused) {
            update();
        }
        
        render();
        Sleep(20);
    }
    
    renderer.renderGameOver(state);
}

void GameController::processInput(InputHandler::Key key) {
    switch (key) {
        case InputHandler::UP:
            state.rotate();
            break;
        case InputHandler::LEFT:
            state.move(-1, 0);
            break;
        case InputHandler::RIGHT:
            state.move(1, 0);
            break;
        case InputHandler::DOWN:
            state.move(0, 1);
            break;
        case InputHandler::SPACE:
            state.drop();
            break;
        case InputHandler::P:
            paused = !paused;
            break;
        case InputHandler::ESC:
            exit(0);
        default:
            break;
    }
}

void GameController::update() {
    if (dropCounter >= dropSpeed) {
        if (state.canMove(0, 1)) {
            state.move(0, 1);
        } else {
            state.lockBlock();
            int lines = state.clearLines();
            if (lines > 0) {
                state.addScore(lines * 100);
                state.addLines(lines);
                
                // 更新等级和下落速度
                state.setLevel(state.getLines() / 10 + 1);
                dropSpeed = max(10, 50 - (state.getLevel() - 1) * 5);
            }
            
            state.generateNextBlock();
            if (!state.canMove(0, 0)) {
                state.setGameOver(true);
            }
        }
        dropCounter = 0;
    } else {
        dropCounter++;
    }
}

void GameController::render() const {
    renderer.renderBoard(state);
    renderer.renderNextBlock(state.getNextBlock());
    renderer.renderScore(state);
    
    if (paused) {
        renderer.setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        renderer.gotoxy(BOARD_WIDTH * 2 + 4, 10);
        cout << "游戏暂停";
        renderer.gotoxy(BOARD_WIDTH * 2 + 4, 11);
        cout << "按 P 继续";
    }
}    
