#include "Game.h"
#include "Tetromino.h"
#include "Board.h"
#include "TextureManager.h"
#include "Background.h"

SDL_Renderer* Game::renderer;
int Game::linesCleared;
Uint32 Game::advanceTime;

Game::Game() : isRunning{false} {}

Game::~Game() {
    delete board;
    delete piece;
    delete background;
}

void Game::run() {
    initalize();
    Uint32 last_time = SDL_GetTicks();
    while(isRunning){
        processInput();
        Uint32 current_time = SDL_GetTicks();
        update(current_time - last_time);
        last_time = current_time;
        render();
        SDL_Delay(FRAME_TIME);
    }
    finish();
}

void Game::initalize(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw std::runtime_error(std::string("SDL_INIT error: ") + SDL_GetError());
    if(TTF_Init()==-1)
        throw std::runtime_error(std::string("SDL_INIT error: ") + TTF_GetError());
    window = SDL_CreateWindow( "Game", 
       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS
    );    
    if(window == nullptr)
        throw std::runtime_error(std::string("SDL_CreateWindow error: ") + SDL_GetError());
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr)
        throw std::runtime_error(std::string("SDL_CreateRenderer error: ") + SDL_GetError());
    TextureManager::loadTextures();
    board = new Board((800-320)/2, (800-640)/2);
    piece = new Tetromino((800-320)/2, (800-640)/2);
    background = new Background();
    isRunning = true;
    linesCleared = 0;
    advanceTime = 800;
}

void Game::finish(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::processInput(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:{
                std::cout << "bye" << std::endl;
                isRunning = false;
                break;
            }
            case SDL_KEYDOWN:{
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    std::cout << "bye" << std::endl;
                    isRunning = false;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    piece->moveLeft();
                    board->ifCollisionRevert(piece);
                }
                if(event.key.keysym.sym == SDLK_RIGHT){
                    piece->moveRight();
                    board->ifCollisionRevert(piece);
                }
                if(event.key.keysym.sym == SDLK_DOWN){
                    piece->setSpeedUp(true);
                }
                if(event.key.keysym.sym == SDLK_SPACE){
                    piece->rotateClockwise();
                    board->ifCollisionRevert(piece);
                }
                break;
            }
            case SDL_KEYUP:{
                if(event.key.keysym.sym == SDLK_DOWN){
                    piece->setSpeedUp(false);
                }
            }
        }
    }
}

void Game::update(Uint32 deltaTime){
    piece->update(deltaTime);
    if(piece->mustCheckCollision)
        testCollisions();
    if(piece->isPaused){
        board->update(deltaTime);
        if(!board->areRowsFalling)
            onBoardCleanDone();
    }
}

void Game::testCollisions(){
    bool wasMerged = board->ifCollisionMergeWithBoard(piece);
    if(wasMerged){
        piece->newTetromino();
        piece->pause();
        board->areRowsFalling = true;
        if(board->cleanFilledRows() == 0)
            onBoardCleanDone();
    }
}

void Game::onBoardCleanDone(){
    piece->start();
    if(board->isColliding(piece)){ // if new piece is colliding at top, then its game over...
        std::cout << "GameOver" << std::endl;
        isRunning = false;
    }
    advanceTime = static_cast<Uint32>( 800 - 50*(linesCleared/10) );
}

void Game::render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    background->render();
    board->render();
    piece->render();
    SDL_RenderPresent(renderer);
}