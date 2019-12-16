#include "Background.h"
#include "TextureManager.h"
#include "Game.h"

void Background::render(){
    SDL_RenderCopy(Game::renderer, TextureManager::backgroundTexture, NULL, NULL);
    SDL_Texture* textTexture = TextureManager::textTexture("Lines: " + std::to_string(Game::linesCleared));
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &texW, &texH);
    SDL_Rect textRectDest = { 25, 25, 2*texW, 2*texH };
    SDL_RenderCopy(Game::renderer, textTexture, NULL, &textRectDest ); 
}
