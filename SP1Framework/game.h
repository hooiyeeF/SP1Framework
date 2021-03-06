#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// struct to store keyboard events
// a small subset of KEY_EVENT_RECORD
struct SKeyEvent
{
    bool keyDown;
    bool keyReleased;
};

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_ROOM1,
    S_ROOM2,
    S_ROOM3,
    S_ROOM4,
    S_TPROOM,
    S_PATHROOM,
    S_ENDROOM,
    S_CROOM,
    S_WIN,
    S_LOSE,
    S_COUNT,
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void updateGame();              // gameplay logic
void updateGame2();             // gameplay logic
void updateGame3();             // gameplay logic
void moveCharacter();           // moves the character, collision detection, physics, etc
void moveCharacter2();          // moves the character, collision detection, physics, etc
void moveCharacter3();          // moves the character, collision detection, physics, etc
void processUserInput();        // checks if you should change states or do something else with the game, e.g. pause, exit
void GoToGamePlay();            // check if user hit space key to start game
void PlayAgain();               // check if user hit key to restart the game
void reset();                   // reset player spawn
void clearScreen();             // clears the current screen and draw from scratch 
void renderMenuScreen();        // renders the splash screen
void renderFirstRoom();         // renders first game room
void renderSecondRoom();        // render second game room
void renderThirdRoom();
void renderFourthRoom();
void renderTPRoom();
void renderPathRoom();
void renderPRInstruction();
void renderEndRoom();
void renderCRoom();
void renderLoseScreen();
void renderWinScreen();
void renderCountDownR4();
void renderFramerate();         // renders debug information, frame rate, elapsed time, etc
void renderToScreen();          // dump the contents of the buffer to the screen, one frame worth of game
void renderInputEvents();       // renders the status of input events

void guardchase();				// guard chase

// keyboard and mouse input event managers
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent);  // define this function for the console to call when there are keyboard events
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent);   // handles keyboard events for gameplay 


#endif // _GAME_H