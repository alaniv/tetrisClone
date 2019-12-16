#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>
#include <SDL2/SDL.h>

struct Position {
    int x;
    int y;
};

enum class PivotType {
    NO_ROTATION, SIMPLE_ROTATION, LINE_ROTATION_1, LINE_ROTATION_2
};

struct RotationPivot {
    int x;
    int y;
    PivotType type;
};

enum class TetrominoType {
    I, J, L, O, S, T, Z
};

class Tetromino {
    public:
        int color;
        std::array<Position, 4> pieces;
        bool mustCheckCollision;
        bool isPaused;
        Tetromino(int x, int y);
        ~Tetromino();
        void render();
        void moveDown();
        void moveLeft();
        void moveRight();
        void rotateClockwise();
        void update(Uint32 deltaTime);
        void newTetromino();
        void setTetrominoByType(int type);
        void revertState();
        void pause(){
            isPaused = true;
        }
        void start(){
            isPaused = false;
        }
        void setSpeedUp(bool isFaster);
    private:
        std::array<Position, 4> previousState;
        bool speedUp;
        int position_x;
        int position_y;
        RotationPivot pivot;
        RotationPivot previousPivot;
        Uint32 elapsedTime;
};

#endif