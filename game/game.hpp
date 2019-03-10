#ifndef GAME_HPP_
#define GAME_HPP_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "../ship/ship.hpp"
#include "../asteroids/asteroid.hpp"

class Game {

  public:
    Game(); // initialize new game
    ~Game(); // destructor
    void quitGame(); // quit the game
    bool isInitSuccessful(); // check if init was successful (true/false)
    void clearViewPort(); // clear the ViewPort
    char getPlayerInput(); // get keyboard input
    bool setupShipSprites(); // setup ship sprites
    bool setupAsteroidSprites();
    bool createAsteroids();
    void renderAsteroids();
    void renderShip();
    void updateScreen();
    void stepForward();
    void stepBackward();
    void stepRight();
    void stepLeft();
    void checkIfShipReachedAsteroid();
    bool isShipAtAsteroid();
    void clearDashboard();
    void coasting();
    void setLastKey(char k);
    void rotateShip(int rotationAngle);

  private:

    char lastKey;
    // game parameters
    const int limitWidth = 5000; // map limits
    const int limitHeight = 5000; // map limits
    const int screenWidth = 1280; // screen width for game
    const int screenHeight = 640; // screen height for game
    SDL_Window* window = NULL; // window pointer
    SDL_Renderer* renderer = NULL; // renderer pointer
    bool initSuccess = true; // successful initiation (flag)
    SDL_Event event; // event handler

    // text for display
    TTF_Font * font = NULL;
    SDL_Texture * display_text = NULL;
    SDL_Surface * display_surface = NULL;
    SDL_Texture * display_text1 = NULL;
    SDL_Surface * display_surface1 = NULL;
    int textW = 0;
    int textH = 0;
    SDL_Rect textRect;

    // main viewport
    SDL_Rect viewPort; // main viewport for the game
    // dashboard
    SDL_Rect dashboard; // dashboard with game info
    SDL_Texture* display;
    SDL_Texture* background;
    bool flag = false;

    // the ship
    Ship theShip;
    SDL_Texture* shipTexture = NULL; // pointer to ship texture (for rendering)
    int shipSpriteSheetWidth, shipSpriteSheetHeight; // dimensions of ship sprite
    SDL_Rect defaultShipSprite; // clips of different sprites (for changing ship appearance)
    SDL_Rect burnSprite;
    bool loadShipSpriteSheet(); // load ship sprite sheet from file
    void freeShipTexture(); // free ship texture data
    bool reachedAsteroid = false;
    int lastAsteroidVisited = -1;
    double accelerationMultiplier;
    int shipAngle = 0; // default 0 degrees (original heading)

    // asteroids
    int numAsteroids = 200;
    vector<Asteroid*> theAsteroids;
    SDL_Texture* asteroidTexture = NULL;
    SDL_Rect defaultAsteroidSprite;
    int asteroidSpriteSheetWidth, asteroidSpriteSheetHeight;
    bool loadAsteroidSpriteSheet();
    void freeAsteroidTexture();

};

#endif
