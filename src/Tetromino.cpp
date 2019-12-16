#include "Tetromino.h"
#include "TextureManager.h"
#include "Game.h"

#include <cstdlib>
#include <ctime>

Tetromino::Tetromino(int x, int y) 
    : position_x(x), position_y(y), elapsedTime(0) {
    std::srand(std::time(nullptr));
    newTetromino();
    isPaused = false;
    speedUp = false;
}

Tetromino::~Tetromino(){   
}

void Tetromino::render(){
    if(isPaused) return;
    SDL_Rect blackSrc = {0, 0, TextureManager::TILE_SIZE, TextureManager::TILE_SIZE};
    for(auto& piece : pieces ){
        SDL_Rect destination = {position_x + static_cast<int>(piece.x)*TextureManager::TILE_SIZE,
             position_y + static_cast<int>(20 - piece.y)*TextureManager::TILE_SIZE,
             TextureManager::TILE_SIZE,TextureManager::TILE_SIZE};
        blackSrc.x = TextureManager::TILE_SIZE*color;
        SDL_RenderCopy(Game::renderer, TextureManager::coloredTiletexture, &blackSrc, &destination);
    }
}

void Tetromino::revertState(){
    pieces = previousState;
    pivot = previousPivot;
}

void Tetromino::setSpeedUp(bool isFaster){
    speedUp = isFaster;
}

void Tetromino::moveDown(){
    mustCheckCollision = true;
    previousState = pieces;
    previousPivot = pivot;
    for(auto& piece : pieces)
        piece.y--;
    pivot.y--;
}

void Tetromino::moveLeft(){
    previousState = pieces;
    previousPivot = pivot;
    for(auto& piece : pieces)
        piece.x--;
    pivot.x--;
}

void Tetromino::moveRight(){
    previousState = pieces;
    previousPivot = pivot;
    for(auto& piece : pieces)
        piece.x++;
    pivot.x++;
}

void Tetromino::rotateClockwise(){
    previousState = pieces;
    previousPivot = pivot;
    if(pivot.type != PivotType::NO_ROTATION){
        for(auto& piece : pieces){
            int delta_x = piece.x - pivot.x;  
            int delta_y = piece.y - pivot.y;
            // rotation
            piece.y = pivot.y - delta_x; 
            piece.x = pivot.x + delta_y; 
        }
        if(pivot.type == PivotType::LINE_ROTATION_1){
            pivot.x++;
            pivot.type = PivotType::LINE_ROTATION_2;
        }
        if(pivot.type == PivotType::LINE_ROTATION_2){
            pivot.x--;
            pivot.type = PivotType::LINE_ROTATION_1;
        }
    }
}

void Tetromino::update(Uint32 deltaTime){
    if(isPaused) return;
    elapsedTime += deltaTime;
    if(elapsedTime > (speedUp ?  32 : Game::advanceTime)){
        elapsedTime -= (speedUp ? 32 : Game::advanceTime);
        moveDown();
    }
}

void Tetromino::newTetromino(){
    mustCheckCollision = false;
    //speedUp = false;
    isPaused = false;
    int random_variable = std::rand();
    color = 1 + random_variable % 18; // 0 is background!
    setTetrominoByType(random_variable % 7);
}

void Tetromino::setTetrominoByType(int type){ //     I, J, L, O, S, Z, T
    switch(type){
        case 0:
            pieces = {Position{3,19},Position{3,18},Position{3,17},Position{3,16}};
            pivot = {3, 18, PivotType::LINE_ROTATION_1};
        break;
        case 1:
            pieces = {Position{3,19},Position{3,18},Position{3,17},Position{2,17}};
            pivot = {3, 18, PivotType::SIMPLE_ROTATION};
        break;
        case 2:
            pieces = {Position{3,19},Position{3,18},Position{3,17},Position{4,17}};
            pivot = {3, 18, PivotType::SIMPLE_ROTATION};
        break;
        case 3:
            pieces = {Position{3,19},Position{3,18},Position{4,19},Position{4,18}};
            pivot = {3, 18, PivotType::NO_ROTATION};
        break;
        case 4:
            pieces = {Position{3,19},Position{3,18},Position{4,18},Position{4,17}};
            pivot = {4, 18, PivotType::SIMPLE_ROTATION};
        break;
        case 5:
            pieces = {Position{4,19},Position{4,18},Position{3,18},Position{3,17}};
            pivot = {4, 18, PivotType::SIMPLE_ROTATION};
        break;
        case 6:
            pieces = {Position{4,19},Position{4,18},Position{4,17},Position{3,18}};
            pivot = {4, 18, PivotType::SIMPLE_ROTATION};
        break;        
    }
}