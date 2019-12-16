#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Tetromino;

class Board {
    public:
        Board(int x, int y);
        ~Board();
        void render();
        bool ifCollisionMergeWithBoard(Tetromino* tetro);
        bool isColliding(Tetromino* tetro) const;
        void ifCollisionRevert(Tetromino* tetro);
        int cleanFilledRows();
        void update(Uint32 deltaTime);
        bool areRowsFalling;
    private:
        std::vector<std::vector<int> > board;
        void addTetroToBoard(Tetromino* tetro);
        int draw_origin_x;
        int draw_origin_y;
        bool isRowFilled(size_t rowNumber) const;
        bool isRowEmpty(size_t rowNum) const;
        void cleanRow(size_t rowNumber);
        Uint32 elapsedTime;
        Uint32 advanceTime;
        bool canRowFall(size_t rowNum) const;
        void doRowFall(size_t rowNum);
        bool fallRows();
};

#endif