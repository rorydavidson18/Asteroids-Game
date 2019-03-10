#include "game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../ship/ship.hpp"
#include <iostream>
#include <string>
#include <random>
#include <math.h>
#define PI 3.14159265
using namespace std;

// Initialize Game
Game::Game() {
  srand (time(0));
  accelerationMultiplier=0.25;

  // initialize SDL window and Renderer
  if (SDL_Init(SDL_INIT_VIDEO != 0)) {
      // handle init error
      cout << "SDL Init Error: " << SDL_GetError() << endl;
      initSuccess = false;

  } else {

    // ttf
    TTF_Init();

    // Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
      cout << "Linear texture filtering failed!" << endl;
    }

    // Create game window
		window = SDL_CreateWindow( "SP 3000", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
    if( window == NULL ) {

      // handle window creation error
			cout << "Could not create window! SDL Error: " << SDL_GetError() << endl;
			initSuccess = false;

    } else {

			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
			if( renderer == NULL ) {

        // handle renderer error
				cout << "Could not create renderer! SDL Error: %s\n", SDL_GetError();
				initSuccess = false;

			} else {

        // init ttf rendering (arial font)
        font = TTF_OpenFont("DigitalDream.ttf", 25);

        // Initialize PNG loading
				int imageFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imageFlags ) & imageFlags ) ) {
					cout << "SDL_image failure! SDL_image Error: " << IMG_GetError();
					initSuccess = false;


				}

        // SETUP GAME LAYOUT

        // all black
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);


        // dashboard and main viewPort
        dashboard.x = 0; // dashboard x position
        dashboard.y = (3 * screenHeight) / 4; // dashboard y position
        dashboard.w = screenWidth; // dashboard width
        dashboard.h = screenHeight / 4; // dashboard height
        viewPort.x = 0; // main viewport x position
        viewPort.y = 0; // main viewport y position
        viewPort.w = screenWidth; // main viewport width
        viewPort.h = (3 * screenHeight) / 4; // main viewport height

        // RENDER DISPLAY ON "DASHBOARD" (lower fourth of screen):
        // create target "display" texture to render to dashboard:
        display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dashboard.w, dashboard.h);
        // set background as target
        SDL_SetRenderTarget(renderer, display);
        // all black background
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // black
        SDL_RenderClear( renderer );

        // set up text texture for displaying text
        SDL_Color color = { 0, 255, 0 }; // green
        display_surface = TTF_RenderText_Solid(font, "Space Prospector 3000", color);
        display_text = SDL_CreateTextureFromSurface(renderer, display_surface);
        SDL_QueryTexture(display_text, NULL, NULL, &textW, &textH);
        textRect = {(dashboard.w / 4),(dashboard.h / 4), (dashboard.w / 2), (dashboard.h / 2)};
        SDL_SetRenderTarget(renderer, NULL);
        // copy display texture to dashboard area
        SDL_RenderSetViewport( renderer, &dashboard );
        SDL_RenderCopy(renderer, display, NULL, NULL );
        SDL_RenderCopy(renderer, display_text, NULL, &textRect);
        SDL_RenderPresent( renderer );

        // RENDER MAIN VIEWPORT (top part of screen):
        SDL_RenderSetViewport( renderer, &viewPort );

        // create target "background" texture to render to viewPort:
        background = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screenWidth, screenHeight);
        // set background as target
        SDL_SetRenderTarget(renderer, background);
        // all black background
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        // reset render target
        SDL_SetRenderTarget(renderer, NULL);
        // copy background texture to screen
        SDL_RenderCopy(renderer, background, NULL, NULL);

        // update screen
        SDL_RenderPresent( renderer );


		    }
    }
  }
}

// destructor
Game::~Game() {

}

// Quit Game
void Game::quitGame() {

  // free ship texture
  freeShipTexture();

  // free asteroid texture
  freeAsteroidTexture();

  // close font
  if( font != NULL ) {
    TTF_CloseFont(font);
    font = NULL;
  }
  // text texture
  if( display_text != NULL ) {
    SDL_DestroyTexture(display_text);
    display_text = NULL;
  }
  if( display_surface != NULL ) {
    SDL_FreeSurface(display_surface);
    display_surface = NULL;
  }
  // text texture
  if( display_text1 != NULL ) {
    SDL_DestroyTexture(display_text1);
    display_text1 = NULL;
  }
  if( display_surface1 != NULL ) {
    SDL_FreeSurface(display_surface1);
    display_surface1 = NULL;
  }
  // free background texture
  if( background != NULL ) {
    SDL_DestroyTexture( background );
    background = NULL;
  }



  // Destroy window	and renderer
  SDL_DestroyRenderer( renderer );
  SDL_DestroyWindow( window );
  window = NULL;
  renderer = NULL;

  // Quit SDL subsystems
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

}

// was initialization successful?
bool Game::isInitSuccessful() {
    return initSuccess;
}

// clear the screen
void Game::clearViewPort() {
  SDL_RenderSetViewport( renderer, &viewPort );
  // set background as target
  SDL_SetRenderTarget(renderer, background);
  // all black background
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);
  SDL_SetRenderTarget(renderer, NULL);
  // copy background texture to screen
  SDL_RenderCopy(renderer, background, NULL, NULL);
}

// clear display in DASHBOARD
void Game::clearDashboard() {
  SDL_RenderSetViewport( renderer, &dashboard );
  // set background as target
  SDL_SetRenderTarget(renderer, display);
  // all black background
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);
  SDL_SetRenderTarget(renderer, NULL);
  // copy background texture to screen
  SDL_RenderCopy(renderer, display, NULL, NULL);
}

// load ship sprite sheet
bool Game::loadShipSpriteSheet() {

    // free texture for ship if it already exists
    freeShipTexture();

    // texture for ship
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    string path = theShip.getSpriteSheetPath();
    SDL_Surface* surface = IMG_Load( "space_ship_sprite.png" ); //path.c_str() );
    if( surface == NULL ) {
        cout << "Cannot load image at " << path.c_str() << "!";
        cout << " SDL_image Error: " << IMG_GetError() << endl;
    } else {
        //Color key image
        SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );
        if( newTexture == NULL ) {
            cout << "Cannot create texture with " << path.c_str();
            cout << "!" << " SDL Error: " << SDL_GetError() << endl;
        } else {

            //Get image dimensions
            int w, h;
            SDL_QueryTexture(newTexture, NULL, NULL, &w, &h);
            shipSpriteSheetWidth = w;
            shipSpriteSheetHeight = h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( surface );
    }

    //SDL_RenderCopy(renderer,newTexture,NULL,NULL);
    //Return success
    shipTexture = newTexture;
    return shipTexture != NULL;

}

// load ship sprites
bool Game::setupShipSprites() {

    // Load sprite sheet texture
    if( !( loadShipSpriteSheet() ) ) {

        cout << "Sprite sheet load fail!" << endl;
        return false;

    } else {
        // default sprite
        int x,y,w,h;
        x = (shipSpriteSheetWidth / 2) - (shipSpriteSheetWidth / 8);
        y = 0;
        w = shipSpriteSheetWidth / 4;
        h = (shipSpriteSheetHeight / 4) - 10;
        defaultShipSprite.x = x;
        defaultShipSprite.y = y;
        defaultShipSprite.w = w;
        defaultShipSprite.h = h;
        burnSprite.x = shipSpriteSheetWidth / 4;
        burnSprite.y = (shipSpriteSheetHeight / 2) + 10;
        burnSprite.w = w;
        burnSprite.h = h;
    }

    return true;
}

void Game::freeShipTexture() {
    // free ship texture
    if( shipTexture != NULL ) {
        SDL_DestroyTexture( shipTexture );
        shipTexture = NULL;
        shipSpriteSheetWidth = 0;
        shipSpriteSheetHeight = 0;
    }
}

void Game::renderShip() {
    SDL_Rect rect;
    rect.x = (viewPort.w / 2) - 25;
    rect.y = (viewPort.h / 2) - 25;
    rect.w = 50;
    rect.h = 50;

    if(theShip.isShipSafe()) {
        SDL_RenderSetViewport( renderer, &viewPort ); // use main viewport
        SDL_SetRenderTarget(renderer, background);
        SDL_Rect ship = defaultShipSprite;
        if(lastKey == 'u')
          ship = burnSprite;
        SDL_RenderCopy( renderer, shipTexture, &ship, &rect); //defaultShipSprite, NULL); // &rect );
        //SDL_RenderCopyEx(renderer,shipTexture, &ship, &rect, shipAngle, NULL, SDL_FLIP_NONE);
        SDL_Delay(100);
    }
}

char Game::getPlayerInput() {
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ){
                /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym ){
                    case SDLK_UP:
                        theShip.moveForward();
                        return 'u';
                        break;
                    case SDLK_DOWN:
                        theShip.moveBackward();
                        return 'd';
                        break;
                    case SDLK_LEFT:
                        theShip.moveLeft();
                        return 'l';
                        break;
                    case SDLK_RIGHT:
                        theShip.moveRight();
                        return 'r';
                        break;
                    case SDLK_q:
                        return 'q';
                        break;
                    default:
                        break;
                }
        }
    }
    return 'n';
}

bool Game::createAsteroids() {

    // asteroid
    Asteroid * A;
    // random values
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> xrand(-ceil(limitWidth / 2),ceil(limitWidth / 2));
    std::uniform_int_distribution<std::mt19937::result_type> yrand(-ceil(limitHeight / 2),ceil(limitHeight / 2));
    int x,y;
    // create asteroids with random positions
    for(int i = 0; i < numAsteroids; ++i) {
        A = new Asteroid();
        A->setMass(1);
        vector<int> p;
        x = xrand(rng);
        y = yrand(rng);
        p.push_back(x);
        p.push_back(y);
        A->setPosition(p);
        A->setVolume(1);
        theAsteroids.push_back(A);
    }

    // Load sprite sheet texture for asteroid
    if( !( loadAsteroidSpriteSheet() ) ) {

        cout << "Sprite sheet load fail!" << endl;
        return false;

    } else {
        // default sprite for asteroids
        int x,y,w,h;
        x = 0;
        y = 0;
        w = asteroidSpriteSheetWidth;
        h = asteroidSpriteSheetHeight;
        defaultAsteroidSprite.x = x;
        defaultAsteroidSprite.y = y;
        defaultAsteroidSprite.w = w;
        defaultAsteroidSprite.h = h;
    }

    return true;

}

// load asteroid sprite sheet
bool Game::loadAsteroidSpriteSheet() {

    // free texture for ship if it already exists
    freeAsteroidTexture();

    // texture for ship
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    //string path = theShip.getSpriteSheetPath();
    SDL_Surface* surface = IMG_Load( "asteroid_image.png" ); //path.c_str() );
    if( surface == NULL ) {
        cout << "Cannot load image at " << endl; //<< path.c_str() << "!";
        cout << " SDL_image Error: " << IMG_GetError() << endl;
    } else {
        //Color key image
        SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0, 0 ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );
        if( newTexture == NULL ) {
            cout << "Cannot create texture with " << endl; // << path.c_str();
            cout << "!" << " SDL Error: " << SDL_GetError() << endl;
        } else {

            //Get image dimensions
            int w, h;
            SDL_QueryTexture(newTexture, NULL, NULL, &w, &h);
            asteroidSpriteSheetWidth = w;
            asteroidSpriteSheetHeight = h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( surface );
    }

    //SDL_RenderCopy(renderer,newTexture,NULL,NULL);
    //Return success
    asteroidTexture = newTexture;
    return asteroidTexture != NULL;

}

void Game::freeAsteroidTexture() {
    // free ship texture
    if( asteroidTexture != NULL ) {
        SDL_DestroyTexture( asteroidTexture );
        asteroidTexture = NULL;
        asteroidSpriteSheetWidth = 0;
        asteroidSpriteSheetHeight = 0;
    }
}

void Game::renderAsteroids() {
    SDL_RenderSetViewport( renderer, &viewPort ); // use main viewport
    SDL_SetRenderTarget(renderer, background);
    int n = theAsteroids.size();
    vector<int> pos;
    SDL_Rect rect[numAsteroids];
    for(int i = 0; i < n; ++i) {
        pos = (theAsteroids[i])->getPosition();
        if( (pos[0] > -25) && (pos[0] < (viewPort.w + 25)) \
        && (pos[1] > -25) && (pos[1] < (viewPort.h + 25))) {

          (rect[i]).x = pos[0] - 25;
          (rect[i]).y = pos[1] - 25;
          (rect[i]).w = 50;
          (rect[i]).h = 50;
            //SDL_RenderCopy( renderer, asteroidTexture, &defaultAsteroidSprite, &rect[i]);
            // rotate asteroids opposite to ship heading (parallax)
          SDL_RenderCopyEx(renderer,asteroidTexture, &defaultAsteroidSprite, &rect[i], (-1 * shipAngle), NULL, SDL_FLIP_NONE);
        }

    }
}

// check if the ship has reached and asteroid
void Game::checkIfShipReachedAsteroid() {
  bool atAsteroid = false;
  int n = theAsteroids.size();
  vector<int> pos;
  for(int i = 0; i < n; ++i) {
      pos = (theAsteroids[i])->getPosition();

      if( pos[0] > ((viewPort.w / 2) - 25) && pos[0] < ((viewPort.w / 2) + 25) ) {
        if( pos[1] > ((viewPort.h / 2) - 25) && pos[1] < ((viewPort.h / 2) + 25) ) {
          atAsteroid = true;

            if ( i != lastAsteroidVisited ) {
              lastAsteroidVisited = i;
              // display asteroid information in DASHBOARD

              // set background as target
              SDL_SetRenderTarget(renderer, display);
              // all black background
              SDL_SetRenderDrawColor(renderer, 0x99, 0x99, 0x99, 0xFF); // black
              SDL_RenderClear( renderer );

              // free resources if necessary
              // text texture
              if( display_text != NULL ) {
                SDL_DestroyTexture(display_text);
                display_text = NULL;
              }
              if( display_surface != NULL ) {
                SDL_FreeSurface(display_surface);
                display_surface = NULL;
              }

              // set up text texture for displaying text
              SDL_Color color = { 255, 0, 0 }; // green
              SDL_Color color1 = { 0, 0, 255 }; // green
              string summary = (theAsteroids[i])->getMaterial().summary();
              summary += "PRESS SPACEBAR TO CONTINUE!!!";
              //cout << summary;
              string name = (theAsteroids[i])->getName();
              string mass = to_string((theAsteroids[i])->getMass());
              mass = "Mass: " + mass;
              display_surface = TTF_RenderText_Blended_Wrapped(font, name.c_str(), color, 1000);
              display_text = SDL_CreateTextureFromSurface(renderer, display_surface);
              display_surface1 = TTF_RenderText_Blended_Wrapped(font, summary.c_str(), color1, 1000);
              display_text1 = SDL_CreateTextureFromSurface(renderer, display_surface1);
              SDL_QueryTexture(display_text, NULL, NULL, &textW, &textH);
              textRect = {0,0,(dashboard.w / 2), (dashboard.h / 2)};
              SDL_SetRenderTarget(renderer, NULL);
              // copy display texture to dashboard area
              SDL_RenderSetViewport( renderer, &dashboard );
              SDL_RenderCopy(renderer, display, NULL, NULL );
              SDL_Rect quad = {0,0,100, 25};
              SDL_RenderCopy(renderer, display_text, NULL, &quad);
              quad = {200,0,400,150};
              SDL_RenderCopy(renderer, display_text1, NULL, &quad);
              SDL_RenderPresent( renderer );
              SDL_Delay(2000);
              reachedAsteroid = true;
              flag = true;

              // wait for space bar
              bool done = false;
              while( not done ) {
                while( SDL_PollEvent( &event ) ) {
                  if( event.type == SDL_KEYDOWN )
                    if( event.key.keysym.sym == SDLK_SPACE )
                      done = true;
                }
              }
          }
          return;
        }
      }

      if(not atAsteroid) {

        flag = false;

        if(reachedAsteroid == true) {
          // clear display in DASHBOARD

          // set background as target
          SDL_SetRenderTarget(renderer, display);
          // all black background
          SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // black
          SDL_RenderClear( renderer );

          // free resources if necessary
          // text texture
          if( display_text != NULL ) {
            SDL_DestroyTexture(display_text);
            display_text = NULL;
          }
          if( display_surface != NULL ) {
            SDL_FreeSurface(display_surface);
            display_surface = NULL;
          }

          // set up text texture for displaying text
          SDL_Color color = { 0, 255, 0 }; // green
          display_surface = TTF_RenderText_Solid(font, "", color); //summary.c_str(), color);
          display_text = SDL_CreateTextureFromSurface(renderer, display_surface);
          SDL_QueryTexture(display_text, NULL, NULL, &textW, &textH);
          textRect = {(dashboard.w / 2),(dashboard.h / 4), (dashboard.w / 2), (dashboard.h / 2)};
          SDL_SetRenderTarget(renderer, NULL);
          // copy display texture to dashboard area
          SDL_RenderSetViewport( renderer, &dashboard );
          SDL_RenderCopy(renderer, display, NULL, NULL );
          SDL_RenderCopy(renderer, display_text, NULL, NULL);
          SDL_RenderPresent( renderer );



        }
        reachedAsteroid = false;
      }

  }
}

void Game::coasting() {
  int n = theAsteroids.size();
  vector<int> pos;
  for(int i = 0; i < n; ++i) {
      pos = (theAsteroids[i])->getPosition();
      pos[1] += (10*accelerationMultiplier); // increase y coords by 10 pixels
      (theAsteroids[i])->setPosition(pos);
  }
}
// example of how to simulate ship moving forward
void Game::stepForward() {
    int n = theAsteroids.size();
    //if(accelerationMultiplier<.25)
    //    accelerationMultiplier = .25;
    vector<int> pos;
    for(int i = 0; i < n; ++i) {
        pos = (theAsteroids[i])->getPosition();
        pos[0] += static_cast<int> (10*accelerationMultiplier * cos((-1*shipAngle + 90) * PI / 180));
        pos[1] += static_cast<int> (10*accelerationMultiplier * sin((-1*shipAngle + 90) * PI / 180));
        (theAsteroids[i])->setPosition(pos);
    }
    if(accelerationMultiplier<=4.75)
        accelerationMultiplier+=.25;
}

void Game::stepBackward() {
    int n = theAsteroids.size();
    //if(accelerationMultiplier>.25)
    //    accelerationMultiplier = -.25;
    vector<int> pos;
    for(int i = 0; i < n; ++i) {
        pos = (theAsteroids[i])->getPosition();
        pos[0] += static_cast<int> (10*accelerationMultiplier * cos((-1*shipAngle + 90) * PI / 180));
        pos[1] += static_cast<int> (10*accelerationMultiplier * sin((-1*shipAngle + 90) * PI / 180));//10*accelerationMultiplier; // decrease y coords by 10 pixels
        (theAsteroids[i])->setPosition(pos);
    }
    if(accelerationMultiplier>=-4.75)
        accelerationMultiplier-=.25;
}

void Game::stepLeft() {
    int n = theAsteroids.size();
    vector<int> pos;
    for(int i = 0; i < n; ++i) {
        pos = (theAsteroids[i])->getPosition();
        pos[0] += 10; // increase x coords by 10 pixels
        (theAsteroids[i])->setPosition(pos);
    }
}

void Game::stepRight() {
    int n = theAsteroids.size();
    vector<int> pos;
    for(int i = 0; i < n; ++i) {
        pos = (theAsteroids[i])->getPosition();
        pos[0] -= 10; // decrease x coords by 10 pixels
        (theAsteroids[i])->setPosition(pos);
    }
}

void Game::updateScreen() {
    SDL_Delay(100); // delay 100 ms
    SDL_SetRenderTarget(renderer, NULL);
    // copy display texture to dashboard area
    SDL_RenderSetViewport( renderer, &dashboard );
    SDL_RenderCopy(renderer, display, NULL, NULL );
    SDL_RenderCopy(renderer, display_text, NULL, &textRect);
    SDL_RenderSetViewport( renderer, &viewPort );
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderPresent( renderer );
}

bool Game::isShipAtAsteroid() {
  return reachedAsteroid;
}

void Game::setLastKey(char k) {
  lastKey = k;
}

// rotation clockwise is positive
void Game::rotateShip(int rotationAngle) {
  shipAngle = (shipAngle + rotationAngle) % 360;

  // rotate asteroids in opposite direction
  int n = theAsteroids.size();
  vector<int> pos;
  for(int i = 0; i < n; ++i) {
      pos = (theAsteroids[i])->getPosition();
      int angle = -1 * rotationAngle;
      pos[0] = pos[0] - (viewPort.w / 2) - 25; // relative to ship position
      pos[1] = pos[1] - (viewPort.h / 2) - 25;
      int x = pos[0];
      int y = pos[1];
      int xr, yr; // rotated coordinates
      xr = static_cast<int> ( (x * cos(angle * PI / 180)) - (y * sin(angle * PI / 180)) );
      yr = static_cast<int> ( (x * sin(angle * PI / 180)) + (y * cos(angle * PI / 180)) );
      pos[0] = xr + (viewPort.w / 2) + 25;
      pos[1] = yr + (viewPort.h / 2) + 25; //pos[1] - 25;
      (theAsteroids[i])->setPosition(pos);
  }
}
