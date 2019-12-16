#include "Board.h"
#include "Game.h"
#include "TextureManager.h"
#include "Tetromino.h"

Board::Board(int x, int y)
: draw_origin_x(x), draw_origin_y(y)
{
    board = std::vector<std::vector<int>>(20, std::vector<int>(10, 0)); //teture range 0 - 18
    elapsedTime = 0;
    advanceTime = 100;
    areRowsFalling = false;
}

Board::~Board(){}

void Board::render(){
    SDL_Rect blackSrc = {0, TextureManager::TILE_SIZE, TextureManager::TILE_SIZE, TextureManager::TILE_SIZE};
    for(size_t i=0; i< 20; i++){
        for(size_t j=0; j< 10; j++){
            SDL_Rect destination = {draw_origin_x + static_cast<int>(j)*TextureManager::TILE_SIZE,
                draw_origin_y + static_cast<int>(20 - i)*TextureManager::TILE_SIZE,
                TextureManager::TILE_SIZE,TextureManager::TILE_SIZE};
            blackSrc.x = TextureManager::TILE_SIZE*board[i][j];
            SDL_RenderCopy(Game::renderer, TextureManager::coloredTiletexture, &blackSrc, &destination);
        }
    }
}

bool Board::ifCollisionMergeWithBoard(Tetromino* tetro){
    if(isColliding(tetro)){
        tetro->revertState();
        addTetroToBoard(tetro);
        return true;
    }
    return false;
}

bool Board::isColliding(Tetromino* tetro) const {
    for(auto& piece : tetro->pieces)
        if(piece.y < 0 || board[piece.y][piece.x] != 0 )
            return true;
    return false;
}

void Board::update(Uint32 deltaTime){
    elapsedTime += deltaTime;
    while(elapsedTime > advanceTime){
        elapsedTime -= advanceTime;
        areRowsFalling = fallRows();
    }
}

void Board::addTetroToBoard(Tetromino* tetro){
    for(auto& piece : tetro->pieces)
        board[piece.y][piece.x] = tetro->color;
}

void Board::ifCollisionRevert(Tetromino* tetro){
    for(auto& piece : tetro->pieces){
        if(piece.x < 0 || piece.x >= 20 || board[piece.y][piece.x] != 0 ){
            tetro->revertState();
            break;
        }
    }
}

int Board::cleanFilledRows(){
    int lines = 0;
    for(size_t i=0; i< 20; i++){
        if(isRowFilled(i)){
            cleanRow(i);
            lines++;
        }
    }
    Game::linesCleared += lines; // not good design... :(
    return lines;
}

bool Board::isRowFilled(size_t rowNumber) const {
    for(size_t j=0;j<10;j++){
        if(board[rowNumber][j] == 0)
            return false;
    }
    return true;
}

void Board::cleanRow(size_t rowNumber){
    for(size_t j=0;j<10;j++)
        board[rowNumber][j] = 0;
}

bool Board::isRowEmpty(size_t rowNum) const {
    for(size_t j=0;j<10;j++){
        if(board[rowNum][j] != 0)
            return false;
    }
    return true;
}

bool Board::canRowFall(size_t rowNum) const {
    for(size_t j=0; j<10; j++){
        if(board[rowNum][j] != 0 && board[rowNum+1][j] != 0)
            return false;
    }
    return true;
}

void Board::doRowFall(size_t rowNum){
    for(size_t j=0;j<10;j++){
        if(board[rowNum][j] == 0){
            board[rowNum][j] = board[rowNum+1][j];
            board[rowNum+1][j] = 0;
        }
    }   
}

bool Board::fallRows(){
    bool anyRowFalled = false;
    for(size_t i=0; i< 19; i++){
        if(isRowEmpty(i+1)) 
            continue;
        if(canRowFall(i)){
            doRowFall(i);
            anyRowFalled = true;
        }
    }
    return anyRowFalled;
}