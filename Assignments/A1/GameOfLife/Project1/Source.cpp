#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a simple message box
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
        "Hello, World!",   // Title
        "This is a simple SDL message box.", // Message
        NULL);            // No parent window

    // Clean up and quit SDL
    SDL_Quit();

    return 0;
}
