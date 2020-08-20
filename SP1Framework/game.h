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

// struct to store mouse events
// a small subset of MOUSE_EVENT_RECORD
struct SMouseEvent
{
    COORD mousePosition;
    DWORD buttonState;
    DWORD eventFlags;
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
    S_GAME,
    S_NEXTROOM,
    S_TPROOM,
    S_ENDROOM,
    S_WIN,
    S_LOSE,
    S_COUNT,
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void updateGame();          // gameplay logic
void updateGame2();         // 2nd room gameplay logic
void updateGame3();         // 3rd room gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void moveCharacter2();      // moves the character, collision detection, physics, etc in the 2nd room
void moveCharacter3();      // moves the character, collision detection, physics, etc in the 2nd room
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void GoToGamePlay();        // check if user hit space key to start game
void PlayAgain();           // check if user hit key to restart the game
void reset();               // reset player spawn
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderSecondRoom();    // render second game room
void renderTPRoom();
void renderEndRoom();
void FirstRoomArray();      // First Room Array
void SecondRoomArray();     // Second Room Array
void TPRoomArray();         // TP Room Array
void EndRoomArray();        // End Room Array
void renderLoseScreen();
void renderWinScreen();
void renderMap();           // renders the map to the buffer first
void rendertoiletpaper();   //renders the toilet paper when collected
void renderCharacter();     // renders the character into the buffer
void renderGuard();
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderInputEvents();   // renders the status of input events


// keyboard and mouse input event managers
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent);  // define this function for the console to call when there are keyboard events
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent);      // define this function for the console to call when there are mouse events

void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent);   // handles keyboard events for gameplay 
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent); // handles mouse events for gameplay 


#endif // _GAME_H