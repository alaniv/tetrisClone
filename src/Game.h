#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>  
#include <iostream>  

class Tetromino;
class Board;
class Background;

class Game {
public:
    static const unsigned int WINDOW_WIDTH = 800;
    static const unsigned int WINDOW_HEIGHT = 800;
    static const unsigned int FPS = 60;
    static const unsigned int FRAME_TIME = 1000/FPS;
    static int linesCleared;
    static Uint32 advanceTime;
    static SDL_Renderer *renderer;    
    Game();
    ~Game();
    void run();
    void initalize();
    void processInput();
    void update(Uint32 deltaTime);
    void render();
    void testCollisions();
    void finish();
    void onBoardCleanDone();
    int getCurrentLevel();
    int setSpeed();
private:
    bool isRunning;
    SDL_Window *window;
    Board* board;
    Tetromino* piece;
    Background* background;
    void ProcessGameOver();
    void ProcessNextLevel();
    void loadTexture();
};
#endif