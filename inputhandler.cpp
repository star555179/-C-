#include "tetris.h"

InputHandler::Key InputHandler::getKey() {
    if (_kbhit()) {
        char key = _getch();
        
        if (key == 224) {  // 功能键前缀
            key = _getch();
            switch (key) {
                case 72: return UP;
                case 75: return LEFT;
                case 77: return RIGHT;
                case 80: return DOWN;
                default: return NONE;
            }
        } else {
            switch (key) {
                case 32: return SPACE;
                case 27: return ESC;
                case 'p': case 'P': return P;
                default: return NONE;
            }
        }
    }
    
    return NONE;
}    
