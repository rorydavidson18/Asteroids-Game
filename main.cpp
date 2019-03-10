#include "game/game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

int main( int argc, char* args[] ) {

  cout << "Hello, and welcome to SP3000!\n" << endl;
  cout << "This is a space material gathering game.\n" << endl;
  cout << "To play the game, uses the arrow keys to move the ship.\n" << endl;
  cout << "If you want to quit the game, just press 'Q'." << endl;
  cout << "Press any key to continue...";
  cin.get();
  cout << endl;

  Game g; // new game object
  char input; // player input
  //bool flag;



  // check if initialization successful first
  if( !( g.isInitSuccessful() ) ) {
    cout << "Game Init Failed!" << endl;
    return 1;
  } else {

    // main game loop flag
    bool quit = false;

    // clear screen and setup game layout
    g.clearViewPort();
    g.setupShipSprites();

    // create asteroids
    g.createAsteroids();

    // render ship and asteroids
    g.renderAsteroids();
    g.renderShip();

    // draw to screen
    g.updateScreen();

    // running the game
    while( !quit ) {

      // check if the ship has encountered an asteroid and manage this
      g.checkIfShipReachedAsteroid();

      // get keyboard input from player
      input = g.getPlayerInput();
      g.setLastKey(input);
      switch(input) {
        case 'q':
          quit = true; // user quitting
          break;
        case 'u':
          g.stepForward(); // moving forward
          g.clearViewPort();
          // render ship and asteroids
          g.renderAsteroids();
          g.renderShip();
          // draw to screen
          g.updateScreen();
          break;
        case 'd':
          g.stepBackward(); // moving forward
          g.clearViewPort();
          // render ship and asteroids
          g.renderAsteroids();
          g.renderShip();
          // draw to screen
          g.updateScreen();
          break;
        case 'l':
          //g.stepLeft(); // moving backward
          g.rotateShip(-5);
          g.clearViewPort();
          // render ship and asteroids
          g.renderAsteroids();
          g.renderShip();
          // draw to screen
          g.updateScreen();
          break;
        case 'r':
          //g.stepRight(); // moving backward
          g.rotateShip(5);
          g.clearViewPort();
          // render ship and asteroids
          g.renderAsteroids();
          g.renderShip();
          // draw to screen
          g.updateScreen();
          break;
        default:
          g.coasting();
          g.clearViewPort();
          // render ship and asteroids
          g.renderAsteroids();
          g.renderShip();
          // draw to screen
          g.updateScreen();
          break;
      }
    } // end game loop

  }

  cout << endl << endl << "Thanks for playing Space Prosector 3000!" << endl;
  g.quitGame();
  return 0;
}
