#include "TextureManager.h"
#include "Game.h"

SDL_Texture* TextureManager::coloredTiletexture;
SDL_Texture* TextureManager::backgroundTexture;
TTF_Font* TextureManager::font;


void TextureManager::loadTextures(){
    SDL_Surface* surface = IMG_Load(std::string("./assets/tileColors.png").c_str());
    if(surface == nullptr) 
        throw std::runtime_error(std::string("NULL surface:: ") + SDL_GetError());
    coloredTiletexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    if(coloredTiletexture == nullptr) 
        throw std::runtime_error(std::string("NULL Texture:: ") + SDL_GetError());
    SDL_FreeSurface(surface);

    surface = IMG_Load(std::string("./assets/background.png").c_str());
    if(surface == nullptr) 
        throw std::runtime_error(std::string("NULL surface:: ") + SDL_GetError());
    backgroundTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    if(backgroundTexture == nullptr) 
        throw std::runtime_error(std::string("NULL Texture:: ") + SDL_GetError());
    SDL_FreeSurface(surface);

    font = TTF_OpenFont(std::string("./assets/charriot.ttf").c_str(), 12);
     if( font == NULL )
        throw std::runtime_error(std::string("NULL font: ") + SDL_GetError());
}
constexpr SDL_Color COLOR_WHITE = { 0, 0, 0, 255 };
SDL_Texture* TextureManager::textTexture(std::string text){
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), COLOR_WHITE);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}