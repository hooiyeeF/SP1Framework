// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Map.h"
#include "UI.h"
#include "Aray.h"
#include "time.h"
#pragma comment(lib, "winmm.lib")
#include "Sound.h"
#include "Leaderboard.h"

double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;
int Gtimer = 0;
bool gamestart = false;
bool gameEnd = false;
bool collected = false;
bool StartCDown = false;
double ODDeltaTime = 0;
double ODDeltaTime2 = 0;
double CountDowndt = 0;
double CDownTime = 10;
int testG = 1;

Player chara;
Map room;
UI ui;
Aray arra;
sound S;
Leaderboard lb;

// Game specific variables here
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(80, 30, "Escape the Factory");

void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;    

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;
    chara.setx(g_Console.getConsoleSize().X / 2 - 1);
    chara.sety(g_Console.getConsoleSize().Y / 2);

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);

    arra.FirstRoomArray(g_Console);
    Gtimer = 5;
    S.BGMS();
    
    
   
  
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{  
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: gameplayKBHandler(keyboardEvent);
        break;
    case S_ROOM1: gameplayKBHandler(keyboardEvent);  
        break;
    case S_ROOM2: gameplayKBHandler(keyboardEvent);  
        break;
    case S_ROOM3: gameplayKBHandler(keyboardEvent);
        break;
    case S_ROOM4: gameplayKBHandler(keyboardEvent);
        break;
    case S_TPROOM: gameplayKBHandler(keyboardEvent);
        break;
    case S_PATHROOM: gameplayKBHandler(keyboardEvent);
        break;
    case S_ENDROOM: gameplayKBHandler(keyboardEvent); 
        break;
    case S_CROOM: gameplayKBHandler(keyboardEvent);
        break;
    case S_WIN: gameplayKBHandler(keyboardEvent);  
        break;
    case S_LOSE: gameplayKBHandler(keyboardEvent); 
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN:
        break;
    case S_ROOM1: gameplayMouseHandler(mouseEvent); 
        break;
    case S_ROOM2: gameplayMouseHandler(mouseEvent);
        break;
    case S_ROOM3: gameplayMouseHandler(mouseEvent);
        break;
    case S_ROOM4: gameplayMouseHandler(mouseEvent);
        break;
    case S_TPROOM: gameplayMouseHandler(mouseEvent);
        break;
    case S_PATHROOM: gameplayMouseHandler(mouseEvent);
        break;
    case S_ENDROOM: gameplayMouseHandler(mouseEvent);
        break;
    case S_CROOM: gameplayMouseHandler(mouseEvent);
        break;
    case S_LOSE: gameplayMouseHandler(mouseEvent);
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_UP: key = K_UP; break;
    case VK_DOWN: key = K_DOWN; break;
    case VK_LEFT: key = K_LEFT; break;
    case VK_RIGHT: key = K_RIGHT; break;
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break;
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }    
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    if (gamestart == true && gameEnd == false)
    {
        // get the delta time
        g_dElapsedTime += dt;
        g_dDeltaTime = dt;
    }
    if (room.getKey == true && g_eGameState == S_ROOM1)
    {
        ODDeltaTime = dt;
    }
    if (room.getKey == true && g_eGameState == S_ROOM2)
    {
        ODDeltaTime2 = dt;
    }
    if (g_eGameState == S_ROOM4 && StartCDown == true)
    {
        CountDowndt = dt;
    }

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : GoToGamePlay(); // game logic for the menu screen
            break;
        case S_ROOM1: updateGame(); // gameplay logic when we are in the game
            break;
        case S_ROOM2: updateGame();
            break;
        case S_ROOM3: updateGame();
            break;
        case S_ROOM4: updateGame();
            break;
        case S_TPROOM: updateGame();
            break;
        case S_PATHROOM: updateGame3();
            break;
        case S_ENDROOM: updateGame();
            break;
        case S_CROOM: updateGame2();
            break;
        case S_WIN:
           
            
            processUserInput();
            PlayAgain();
            break;
        case S_LOSE: 
            processUserInput();
            PlayAgain();
            break;
    }
}

void updateGame()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void updateGame2()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter2();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void updateGame3()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter3();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}
void moveCharacter()
{
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && chara.gety() > 0)
    {
        if (arra.map[chara.gety() - 1][chara.getx()] == '-' || arra.map[chara.gety() - 1][chara.getx()] == 'T')
        {
            arra.map[chara.gety() - 1][chara.getx()] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            //Beep(1440, 30);
            chara.ydec();
        }
        else if (arra.map[chara.gety() - 1][chara.getx()] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_LEFT].keyDown && chara.getx() > 0)
    {
        if (arra.map[chara.gety()][chara.getx() - 1] == '-' || arra.map[chara.gety()][chara.getx() - 1] == 'T')
        {
            gamestart = true;
            arra.map[chara.gety()][chara.getx() - 1] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            //Beep(1440, 30);
            chara.xdec();
        }
        else if (arra.map[chara.gety()][chara.getx() - 1] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyDown && chara.gety() < g_Console.getConsoleSize().Y - 1)
    {
        if (arra.map[chara.gety() + 1][chara.getx()] == '-' || arra.map[chara.gety() + 1][chara.getx()] == 'T')
        {
            arra.map[chara.gety() + 1][chara.getx()] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            //Beep(1440, 30);
            chara.yinc();
        }
        else if (arra.map[chara.gety() + 1][chara.getx()] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && chara.getx() < g_Console.getConsoleSize().X - 1)
    {
        if (arra.map[chara.gety()][chara.getx() + 1] == '-' || arra.map[chara.gety()][chara.getx() + 1] == 'T')
        {
            arra.map[chara.gety()][chara.getx() + 1] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            //Beep(1440, 30);
            chara.xinc();
        }
        else if (arra.map[chara.gety()][chara.getx() + 1] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (arra.map[2][58] == 'P')
    {
        arra.map[2][58] = '-';
    }
    if (arra.map[15][21] == 'P')
    {
        arra.map[15][21] = '-';
    }
}

void moveCharacter2()
{
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && chara.gety() > 0)
    {
        if (arra.map[chara.gety() - 1][chara.getx()] == '-' || arra.map[chara.gety() - 1][chara.getx()] == 'T')
        {
            arra.map[chara.gety() - 1][chara.getx()] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            //Beep(1440, 30);
            arra.guardmove(g_Console);
            chara.ydec();

        }
        else if (arra.map[chara.gety() - 1][chara.getx()] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        else
        {
            arra.guardmove(g_Console);
        }
    }
    if (g_skKeyEvent[K_LEFT].keyDown && chara.getx() > 0)
    {
        if (arra.map[chara.gety()][chara.getx() - 1] == '-' || arra.map[chara.gety()][chara.getx() - 1] == 'T')
        {
            gamestart = true;
            arra.map[chara.gety()][chara.getx() - 1] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            arra.guardmove(g_Console);
            //Beep(1440, 30);
            chara.xdec();
        }
        else if (arra.map[chara.gety()][chara.getx() - 1] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        else
        {
            arra.guardmove(g_Console);
        }
    }
    if (g_skKeyEvent[K_DOWN].keyDown && chara.gety() < g_Console.getConsoleSize().Y - 1)
    {
        if (arra.map[chara.gety() + 1][chara.getx()] == '-' || arra.map[chara.gety() + 1][chara.getx()] == 'T')
        {
            arra.map[chara.gety() + 1][chara.getx()] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            arra.guardmove(g_Console);
            //Beep(1440, 30);
            chara.yinc();
        }
        else if (arra.map[chara.gety() + 1][chara.getx()] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        else
        {
            arra.guardmove(g_Console);
        }
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && chara.getx() < g_Console.getConsoleSize().X - 1)
    {
        if (arra.map[chara.gety()][chara.getx() + 1] == '-' || arra.map[chara.gety()][chara.getx() + 1] == 'T')
        {
            arra.map[chara.gety()][chara.getx() + 1] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            arra.guardmove(g_Console);
            //Beep(1440, 30);
            chara.xinc();
        }
        else if (arra.map[chara.gety()][chara.getx() + 1] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        else
        {
            arra.guardmove(g_Console);
        }
    }
    if (arra.map[2][58] == 'P')
    {
        arra.map[2][58] = '-';
    }
    if (arra.map[15][21] == 'P')
    {
        arra.map[15][21] = '-';
    }
}

void moveCharacter3()
{
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && chara.gety() > 0)
    {
        if (arra.map[chara.gety() - 1][chara.getx()] == '-' || arra.map[chara.gety() - 1][chara.getx()] == 'T')
        {
            arra.map[chara.gety() - 1][chara.getx()] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            //Beep(1440, 30);
            guardchase();
            chara.ydec();

        }
        else if (arra.map[chara.gety() - 1][chara.getx()] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        else
        {
            guardchase();
        }
    }
    if (g_skKeyEvent[K_LEFT].keyDown && chara.getx() > 0)
    {
        if (arra.map[chara.gety()][chara.getx() - 1] == '-' || arra.map[chara.gety()][chara.getx() - 1] == 'T')
        {
            gamestart = true;
            arra.map[chara.gety()][chara.getx() - 1] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            guardchase();
            //Beep(1440, 30);
            chara.xdec();
        }
        else if (arra.map[chara.gety()][chara.getx() - 1] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        else
        {
            guardchase();
        }
    }
    if (g_skKeyEvent[K_DOWN].keyDown && chara.gety() < g_Console.getConsoleSize().Y - 1)
    {
        if (arra.map[chara.gety() + 1][chara.getx()] == '-' || arra.map[chara.gety() + 1][chara.getx()] == 'T')
        {
            arra.map[chara.gety() + 1][chara.getx()] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            guardchase();
            //Beep(1440, 30);
            chara.yinc();
        }
        else if (arra.map[chara.gety() + 1][chara.getx()] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        else
        {
            guardchase();
        }
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && chara.getx() < g_Console.getConsoleSize().X - 1)
    {
        if (arra.map[chara.gety()][chara.getx() + 1] == '-' || arra.map[chara.gety()][chara.getx() + 1] == 'T')
        {
            arra.map[chara.gety()][chara.getx() + 1] = 'P';
            arra.map[chara.gety()][chara.getx()] = '-';
            guardchase();
            //Beep(1440, 30);
            chara.xinc();
        }
        else if (arra.map[chara.gety()][chara.getx() + 1] == 'G')
        {
            arra.map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        else
        {
            guardchase();
        }
    }
    if (arra.map[2][58] == 'P')
    {
        arra.map[2][58] = '-';
    }
    if (arra.map[15][21] == 'P')
    {
        arra.map[15][21] = '-';
    }
}


void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;    
}
void GoToGamePlay()
{
    // go to gameplay if player hits the space key
    if (g_skKeyEvent[K_SPACE].keyReleased)
        g_eGameState = S_ROOM1;
}
void PlayAgain()
{
    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        g_eGameState = S_SPLASHSCREEN;
        testG++;
        reset();
    }  
}
void reset()
{
    g_dElapsedTime = 0.0;
    CDownTime = 10;
    gamestart = false;
    gameEnd = false;
    collected = false;
    StartCDown = false;
    room.getTP = false;
    room.Dtime = 3;
    room.getKey = false;
    chara.setx(g_Console.getConsoleSize().X / 2 - 1);
    chara.sety(g_Console.getConsoleSize().Y / 2);
    init();
}

void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderMenuScreen();
    //case S_SPLASHSCREEN: renderWinScreen();
        break;
    case S_ROOM1: renderFirstRoom();
        break;
    case S_ROOM2: renderSecondRoom();
        break;
    case S_ROOM3: renderThirdRoom();
        break;
    case S_ROOM4: 
        renderFourthRoom();
        renderCountDownR4();
        break;
    case S_TPROOM: renderTPRoom();
        break;
    case S_PATHROOM: renderPathRoom();
        break;
    case S_ENDROOM: renderEndRoom();
        break;
    case S_CROOM: renderCRoom();
        break;
    case S_WIN: renderWinScreen();
        break;
    case S_LOSE: renderLoseScreen();
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderMenuScreen() 
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 2;
    c.Y -= 10;
    c.X = c.X / 2 - 6;
    g_Console.writeToBuffer(c, "E S C A P E", 0x0A);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 3;
    g_Console.writeToBuffer(c, "T H E", 0x0A);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 7;
    g_Console.writeToBuffer(c, "F A C T O R Y", 0x0A);
    c.Y += 10;
    c.X = g_Console.getConsoleSize().X / 2 - 12;
    g_Console.writeToBuffer(c, "Bob needs toilet paper.", 0x07);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 27;
    g_Console.writeToBuffer(c, "Help him to get toilet paper and escape the factory!", 0x07);
    c.Y += 5;
    c.X = g_Console.getConsoleSize().X / 2 - 12;
    g_Console.writeToBuffer(c, "Press <Space> to start", 0x5E);

    /* Playtest counter*/
    c.Y -= 10;
    c.X = g_Console.getConsoleSize().X / 2 - 5;
    g_Console.writeToBuffer(c, " Test : ", 0xB0);

    std::ostringstream ss;
    ss.str("");
    ss << testG << " ";
    c.X = 43;
    c.Y = 15;
    g_Console.writeToBuffer(c, ss.str(), 0xB0);

    c.Y -= 14;
    c.X = g_Console.getConsoleSize().X / 2 +19;
    g_Console.writeToBuffer(c, " Arrow keys to move ", 0xE5);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 + 19;
    g_Console.writeToBuffer(c, " E - Exit ", 0xE5); 
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 + 19;
    g_Console.writeToBuffer(c, "   - Guard ", 0xE5);
    c.X = 60;
    c.Y = 4;
    g_Console.writeToBuffer(c, (char)1, 0x0C);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 + 19;
    g_Console.writeToBuffer(c, " K - Key ", 0xE5);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 + 19;
    g_Console.writeToBuffer(c, " T - Toilet paper ", 0xE5);
}
void renderFirstRoom()
{
    room.drawR1(g_Console);
    ui.drawUI(g_Console);
    chara.draw(g_Console);
    

    if (arra.map[chara.gety()][chara.getx()] == 'G')
    {
        arra.map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    if (Gtimer > 0 && Gtimer < 100)
    {

        arra.guarddetect(g_Console, 50, 5);
        Gtimer++;

    }
    else if (Gtimer >= 100 && Gtimer < 200)
    {
        arra.removeguard(g_Console, 50, 5);
        Gtimer++;
    }
    else if (Gtimer >= 200 && Gtimer < 300)
    {
        arra.guarddetect(g_Console, 49, 5);
        Gtimer++;
    }
    else if (Gtimer >= 300 && Gtimer < 400)
    {
        arra.removeguard(g_Console, 49, 5);
        Gtimer++;
    }
    else
    {
        Gtimer = 1;
    }

    // key collected
    if (chara.getx() == 58 && chara.gety() == 15)
    {
        room.getKey = true;
        arra.map[2][54] = '-';
        arra.map[3][54] = '-';
    }
    if (room.getKey == true)
    {
        room.Dtime -= ODDeltaTime;
    }
    
    /* Go to Second room */
    if (chara.getx() == 58 && chara.gety() == 2)
    {
        g_eGameState = S_ROOM2;
        arra.SecondRoomArray(g_Console);
        room.getKey = false;
        room.Dtime = 3;
        //character position for second room
        chara.setx(20); 
        chara.sety(15);
    }
}
void renderSecondRoom()
{
    clearScreen();
    room.drawR2(g_Console);
    ui.drawUI(g_Console);
    chara.draw(g_Console);

    // key collected
    if (chara.getx() == 33 && chara.gety() == 15)
    {
        room.getKey = true;
        arra.map[2][55] = '-';
        arra.map[3][55] = '-';
    }
    if (room.getKey == true) 
    {
        room.Dtime -= ODDeltaTime2;
    }
    if (arra.map[chara.gety()][chara.getx()] == 'G')
    {
        arra.map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    if (Gtimer > 0 && Gtimer < 100)
    {

        arra.guarddetect(g_Console, 39, 13);
        arra.removeguard(g_Console, 24, 4);
        arra.guarddetect(g_Console, 52, 3);
        Gtimer++;

    }
    else if (Gtimer >= 100 && Gtimer < 200)
    {
        arra.guarddetect(g_Console, 39, 13);
        arra.guarddetect(g_Console, 24, 4);
        arra.removeguard(g_Console, 52, 3);
        Gtimer++;
    }
    else if (Gtimer >= 200 && Gtimer < 300)
    {
        arra.removeguard(g_Console, 39, 13);
        arra.removeguard(g_Console, 24, 4);
        arra.guarddetect(g_Console, 52, 3);
        Gtimer++;
    }
    else if (Gtimer >= 300 && Gtimer < 400)
    {
        arra.removeguard(g_Console, 39, 13);
        arra.guarddetect(g_Console, 24, 4);
        arra.removeguard(g_Console, 52, 3);
        Gtimer++;
    }
    else
    {
        Gtimer = 1;
    }

    /* Go to Third room */
    if (chara.getx() == 58 && chara.gety() == 10)
    {
        g_eGameState = S_ROOM3;
        arra.ThirdRoomArray(g_Console);

        //character position for third room
        chara.setx(16);
        chara.sety(4);
    }
}
void renderThirdRoom()
{
    clearScreen(); 
    room.drawR3(g_Console);
    ui.drawUI(g_Console);
    chara.draw(g_Console);

    if (arra.map[chara.gety()][chara.getx()] == 'G')
    {
        arra.map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    if (Gtimer > 0 && Gtimer < 100)
    {
        arra.guarddetect(g_Console, 28, 5);
        arra.removeguard(g_Console, 44, 8);

        Gtimer++;
    }
    else if (Gtimer >= 100 && Gtimer < 300)
    {
        arra.removeguard(g_Console, 28, 5);
        arra.guarddetect(g_Console, 44, 8);
        Gtimer++;
    }
    else
    {
        Gtimer = 1;
    }

    /* Go to Fourth room */
    if (chara.getx() == 62 && chara.gety() == 13)
    {
        g_eGameState = S_ROOM4;
        arra.FourthRoomArray(g_Console);
        //character position for fourth room
        chara.setx(54); 
        chara.sety(4);
    }
}
void renderFourthRoom()
{
    clearScreen();
    room.drawR4(g_Console);
    ui.drawUI(g_Console);
    chara.draw(g_Console);

    // Count down
    if (chara.getx() == 53 && chara.gety() == 4)
    {
        StartCDown = true;
    }
    if (StartCDown == true)
    {
        CDownTime -= CountDowndt;
    }
    if (CDownTime < 0)
    {
        g_eGameState = S_LOSE;
    }

    /* Go to toilet paper room */
    if (chara.getx() == 24 && chara.gety() == 15)
    {
        g_eGameState = S_TPROOM;
        arra.TPRoomArray(g_Console);

        //character position for toilet paper room
        chara.setx(25);
        chara.sety(1);
    }
}
void renderTPRoom()
{
    clearScreen();
    room.drawRTP(g_Console);
    ui.drawUI(g_Console);
    chara.draw(g_Console);

    if (arra.map[chara.gety()][chara.getx()] == 'G')
    {
        arra.map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    if (Gtimer > 0 && Gtimer < 50)
    {
        arra.guarddetect(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        arra.removeguard(g_Console, 55, 10);
        Gtimer++;
    }
    else if (Gtimer >= 50 && Gtimer < 100)
    {
        arra.guarddetect(g_Console, 36, 11);
        arra.removeguard(g_Console, 55, 10);
        arra.removeguard(g_Console, 36, 5);
        Gtimer++;
    }
    else if (Gtimer >= 100 && Gtimer < 150)
    {
        arra.guarddetect(g_Console, 55, 9);
        arra.removeguard(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        Gtimer++;
    }
    else if (Gtimer >= 150 && Gtimer < 200)
    {
        arra.guarddetect(g_Console, 36, 11);
        arra.removeguard(g_Console, 55, 9);
        arra.removeguard(g_Console, 36, 5);
        Gtimer++;
    }
    else if (Gtimer >= 200 && Gtimer < 250)
    {
        arra.guarddetect(g_Console, 55, 8);
        arra.removeguard(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        Gtimer++;
    }
    else if (Gtimer >= 250 && Gtimer < 300)
    {
        arra.guarddetect(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        arra.removeguard(g_Console, 55, 8);
        Gtimer++;
    }
    else if (Gtimer >= 300 && Gtimer < 350)
    {
        arra.guarddetect(g_Console, 55, 7);
        arra.removeguard(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        Gtimer++;
    }
    else if (Gtimer >= 350 && Gtimer < 400)
    {
        arra.guarddetect(g_Console, 36, 11);
        arra.removeguard(g_Console, 55, 7);
        arra.removeguard(g_Console, 36, 5);
        Gtimer++;
    }
    else if (Gtimer >= 400 && Gtimer < 450)
    {
        arra.removeguard(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        arra.guarddetect(g_Console, 55, 6);
        Gtimer++;
    }
    else if (Gtimer >= 450 && Gtimer < 500)
    {
        arra.guarddetect(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        arra.removeguard(g_Console, 55, 6);
        Gtimer++;
    }
    else if (Gtimer >= 500 && Gtimer < 550)
    {
        arra.guarddetect(g_Console, 36, 11);
        arra.guarddetect(g_Console, 55, 7);
        arra.removeguard(g_Console, 36, 5);
        Gtimer++;
    }
    else if (Gtimer >= 550 && Gtimer < 600)
    {
        arra.removeguard(g_Console, 55, 7);
        arra.removeguard(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        Gtimer++;
    }
    else if (Gtimer >= 600 && Gtimer < 650)
    {
        arra.guarddetect(g_Console, 55, 8);
        arra.removeguard(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        Gtimer++;
        
    }
    else if (Gtimer >= 650 && Gtimer < 700)
    {
        arra.guarddetect(g_Console, 36, 11);
        arra.removeguard(g_Console, 55, 8);
        arra.removeguard(g_Console, 36, 5);
        Gtimer++;
    }
    else if (Gtimer >= 700 && Gtimer < 750)
    {
        arra.guarddetect(g_Console, 55, 9);
        arra.removeguard(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        Gtimer++;
    }
    else if (Gtimer >= 750 && Gtimer < 800)
    {
        arra.guarddetect(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        arra.removeguard(g_Console, 55, 9);
        Gtimer++;
    }
    else if (Gtimer >= 800 && Gtimer < 850)
    {
        arra.guarddetect(g_Console, 36, 11);
        arra.removeguard(g_Console, 36, 5);
        arra.guarddetect(g_Console, 55, 10);
        Gtimer++;

    }
    else if (Gtimer >= 850 && Gtimer < 900)
    {
        arra.removeguard(g_Console, 36, 5);
        arra.removeguard(g_Console, 36, 11);
        arra.removeguard(g_Console, 55, 10);

        Gtimer++;
    }
    else
    {
        Gtimer = 1;
    }

    if (chara.getx() == 49 && chara.gety() == 8)
    {
        collected = true;
        room.getTP = true;
    }
    // draw toilet paper
    if (collected == true)
    {
        ui.drawTP(g_Console);
    }

    /* Go to the path room */
    if (chara.getx() == 40 && chara.gety() == 16 && collected == true)
    {
        g_eGameState = S_PATHROOM;
        arra.PRArray(g_Console);
        //character position for last room
        chara.setx(2); 
        chara.sety(2);
    }
    // Not collected
    else if (chara.getx() == 40 && chara.gety() == 16 && collected == false)
    {
        g_Console.writeToBuffer(30, 25, "Collect the toilet paper before exit !", 0x06);
    }
}
void renderPathRoom()
{
    clearScreen();
    ui.drawUI(g_Console);
    ui.drawTP(g_Console);
    room.drawPR(g_Console);
    chara.draw(g_Console);
    arra.guardschasing(g_Console);

    if (arra.map[chara.gety()][chara.getx()] == 'G')
    {
        arra.map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    /* Go to next room */
    if (chara.getx() == 52 && chara.gety() == 12)
    {
        g_eGameState = S_ENDROOM;
        arra.EndRoomArray(g_Console);
        //character position for the next room
        chara.setx(25);
        chara.sety(1);
    }
}
void renderEndRoom()
{
    clearScreen();
    room.drawREnd(g_Console);
    ui.drawUI(g_Console);
    ui.drawTP(g_Console);
    chara.draw(g_Console);

    if (arra.map[chara.gety()][chara.getx()] == 'G')
    {
        arra.map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    if (Gtimer > 0 && Gtimer < 100)
    {
        arra.removeguard(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.removeguard(g_Console, 46, 7);
        arra.removeguard(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 50 && Gtimer < 100)
    {
        arra.guarddetect(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.guarddetect(g_Console, 47, 7);
        arra.removeguard(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 100 && Gtimer < 150)
    {
        arra.removeguard(g_Console, 20, 2);
        arra.guarddetect(g_Console, 20, 15);
        arra.removeguard(g_Console, 47, 7);
        arra.guarddetect(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 150 && Gtimer < 200)
    {
        arra.guarddetect(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.removeguard(g_Console, 48, 7);
        arra.removeguard(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 200 && Gtimer < 250)
    {
        arra.guarddetect(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.guarddetect(g_Console, 49, 7);
        arra.removeguard(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 250 && Gtimer < 300)
    {
        arra.removeguard(g_Console, 20, 2);
        arra.guarddetect(g_Console, 20, 15);
        arra.removeguard(g_Console, 49, 7);
        arra.guarddetect(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 300 && Gtimer < 350)
    {
        arra.removeguard(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.guarddetect(g_Console, 50, 7);
        arra.removeguard(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 350 && Gtimer < 400)
    {
        arra.guarddetect(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.removeguard(g_Console, 50, 7);
        arra.guarddetect(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 400 && Gtimer < 450)
    {
        arra.removeguard(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.guarddetect(g_Console, 49, 7);
        arra.removeguard(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 450 && Gtimer < 500)
    {
        arra.guarddetect(g_Console, 20, 2);
        arra.guarddetect(g_Console, 20, 15);
        arra.removeguard(g_Console, 49, 7);
        arra.guarddetect(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 500 && Gtimer < 550)
    {
        arra.removeguard(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.guarddetect(g_Console, 48, 7);
        arra.removeguard(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 550 && Gtimer < 600)
    {
        arra.guarddetect(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.removeguard(g_Console, 48, 7);
        arra.guarddetect(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 600 && Gtimer < 650)
    {
        arra.removeguard(g_Console, 20, 2);
        arra.guarddetect(g_Console, 20, 15);
        arra.removeguard(g_Console, 47, 7);
        arra.removeguard(g_Console, 41, 15);
        Gtimer++;

    }
    else if (Gtimer >= 650 && Gtimer < 700)
    {
        arra.guarddetect(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.guarddetect(g_Console, 47, 7);
        arra.removeguard(g_Console, 41, 15);
        Gtimer++;
    }
    else if (Gtimer >= 700 && Gtimer < 750)
    {
        arra.removeguard(g_Console, 20, 2);
        arra.removeguard(g_Console, 20, 15);
        arra.removeguard(g_Console, 47, 7);
        arra.guarddetect(g_Console, 41, 15);
        Gtimer++;
    }
    else
    {
        Gtimer = 1;
    }

    /* Go to ChaseRoom */
    if (chara.getx() == 58 && chara.gety() == 15 )
    {
        g_eGameState = S_CROOM;
        arra.CRoomArray(g_Console);
        //character position for last room
        chara.setx(2);
        chara.sety(4);
    }
}
void renderCRoom()
{
    clearScreen();
    room.drawLR(g_Console);
    ui.drawUI(g_Console);
    ui.drawTP(g_Console);
    chara.draw(g_Console);
    arra.guardslast(g_Console);
    if (arra.map[chara.gety()][chara.getx()] == 'G')
    {
        arra.map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    /* Go to WIN */
    if (chara.getx() == 77 && chara.gety() == 8)
    {
        g_eGameState = S_WIN;
        S.BGM();
        S.Win();
        gameEnd = true;
    }
}
void renderWinScreen()
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 2;
    c.Y -= 11;
    c.X = c.X / 2 - 15;
    g_Console.writeToBuffer(c, "C O N G R A T U L A T I O N S !", 0x0A);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 7;
    g_Console.writeToBuffer(c, "Y O U  W O N !", 0x0A);
    c.Y = 8;
    c.X = g_Console.getConsoleSize().X / 2 - 11;
    g_Console.writeToBuffer(c, "  Time Taken: ", 0xB0);

    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss.str("");
    ss << g_dElapsedTime << "s  ";
    c.X = 43;
    c.Y = 8;
    g_Console.writeToBuffer(c, ss.str(), 0xB0);

    c.X = g_Console.getConsoleSize().X / 2 - 7;
    c.Y = 10;
    g_Console.writeToBuffer(c, " LEADERBOARD ", 0x0F);

    c.Y = 11;
    lb.saverer(g_dElapsedTime);
    lb.sorterer();

    for (int i : lb.lb)
    {
        g_Console.writeToBuffer(c, i, 0x0F);
        c.Y++;
    }

    c.Y += 5;
    c.X = g_Console.getConsoleSize().X / 2 - 14;
    g_Console.writeToBuffer(c, "Press <SPACE> to play again", 0x07);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    g_Console.writeToBuffer(c, "Press <ESC> to exit", 0x07);

}
void renderLoseScreen()
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 2;
    c.Y -= 5;
    c.X = c.X / 2 - 4;
    g_Console.writeToBuffer(c, "L O S E !", 0x0A);
    c.Y += 8;
    c.X = g_Console.getConsoleSize().X / 2 - 13;
    g_Console.writeToBuffer(c, "Press <SPACE> to play again", 0x07);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    g_Console.writeToBuffer(c, "Press <ESC> to exit", 0x07);
}

void renderCountDownR4()
{
    COORD c;
    std::ostringstream ss, ss1;
    ss1 << std::fixed << std::setprecision(1);
    ss.str("");
    ss1.str("");
    ss << " Go To 'E' before time up! " ;
    c.X = 27;
    c.Y = 1;
    g_Console.writeToBuffer(c, ss.str(), 0x0F);
    ss1 << CDownTime << "s ";
    c.X = 40;
    c.Y = 2;
    if (CDownTime > 5)
    {
        g_Console.writeToBuffer(c, ss1.str(), 0x0F);
    }
    else
    {
        g_Console.writeToBuffer(c, ss1.str(), 0x0C);
    }
}
void renderFramerate()
{
    if ((g_eGameState != S_SPLASHSCREEN) && (g_eGameState != S_ROOM4) && (g_eGameState != S_WIN) && (g_eGameState != S_LOSE))
    {
        COORD c;
        // displays the framerate
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(3);
      /*  ss << 1.0 / g_dDeltaTime << "fps";
        c.X = g_Console.getConsoleSize().X - 9;
        c.Y = 0;
        g_Console.writeToBuffer(c, ss.str());*/

        // displays the elapsed time
        ss.str("");
        ss << g_dElapsedTime << "secs";
        c.X = 64;
        c.Y = 20;
        g_Console.writeToBuffer(c, ss.str(), 0x0F);
    }
    
}
void renderInputEvents()
{
    // keyboard events 
    COORD startPos = {50, 2};
    std::ostringstream ss;
    std::string key;
    for (int i = 0; i < K_COUNT; ++i)
    {
        ss.str("");
        switch (i)
        {
        case K_UP: key = "UP";
            break;
        case K_DOWN: key = "DOWN";
            break;
        case K_LEFT: key = "LEFT";
            break;
        case K_RIGHT: key = "RIGHT";
            break;
        case K_SPACE: key = "SPACE";
            break;
        default: continue;
        }

        COORD c = { startPos.X, startPos.Y + i };
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }
    // mouse events
    if ((g_eGameState != S_SPLASHSCREEN) && (g_eGameState != S_WIN) && (g_eGameState != S_LOSE))
    {
        ss.str("");
        ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
        g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
        ss.str("");

        switch (g_mouseEvent.eventFlags)
        {
        case 0:
            if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                ss.str("Left Button Pressed");
                g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
            }
            else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
            {
                ss.str("Right Button Pressed");
                g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
            }
            else
            {
                ss.str("Some Button Pressed");
                g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
            }
            break;
        case DOUBLE_CLICK:
            ss.str("Double Clicked");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
            break;
        case MOUSE_WHEELED:
            if (g_mouseEvent.buttonState & 0xFF000000)
                ss.str("Mouse wheeled down");
            else
                ss.str("Mouse wheeled up");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
            break;
        default:
            break;
        }
    }
}


void guardchase()
{
    
    if (chara.getx() > arra.gx1 && arra.map[arra.gy1][arra.gx1 + 2] == '-')
    {
        arra.map[arra.gy1][arra.gx1] = '-';
        arra.gx1++;
    }
    else if (chara.getx() < arra.gx1 && arra.map[arra.gy1][arra.gx1 - 2] == '-')
    {
        arra.map[arra.gy1][arra.gx1] = '-';
        arra.gx1--;
    }
    else if (chara.gety() > arra.gy1 && arra.map[arra.gy1 + 2][arra.gx1] == '-')
    {
        arra.map[arra.gy1][arra.gx1] = '-';
        arra.gy1++;
    }
    else if (chara.gety() < arra.gy1 && arra.map[arra.gy1 - 2][arra.gx1] == '-')
    {
        arra.map[arra.gy1][arra.gx1] = '-';
        arra.gy1--;
    }
    if (chara.gety() > arra.gy2 && arra.map[arra.gy2 + 1][arra.gx2] == '-')
    {
        arra.map[arra.gy2][arra.gx2] = '-';
        arra.gy2++;
    }
    else if (chara.gety() < arra.gy2 && arra.map[arra.gy2 - 1][arra.gx2] == '-')
    {
        arra.map[arra.gy2][arra.gx2] = '-';
        arra.gy2--;
    }
    else if (chara.getx() > arra.gx2 && arra.map[arra.gy2][arra.gx2 + 1] == '-')
    {
        arra.map[arra.gy2][arra.gx2] = '-';
        arra.gx2++;
    }
    else if (chara.getx() < arra.gx2 && arra.map[arra.gy2][arra.gx2 - 1] == '-')
    {
        arra.map[arra.gy2][arra.gx2] = '-';
        arra.gx2--;
    }

    
}



