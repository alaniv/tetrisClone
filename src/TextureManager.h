#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>  
#include <string>

class TextureManager {
    public:
        static const int TILE_SIZE = 32;
        static SDL_Texture* coloredTiletexture;  //teture range 0 - 18
        static SDL_Texture* backgroundTexture;  //teture range 0 - 18
        static void loadTextures();
        static SDL_Texture* textTexture(std::string text);
    private:
        static TTF_Font* font;
};

#endif