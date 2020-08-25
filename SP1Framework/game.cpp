// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Guard.h"
#include "Map.h"
#include "UI.h"
#include "Aray.h"

double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;
char map[18][80];
int Gtimer = 0;
bool gamestart = false;
bool gameEnd = false;
bool collected = false;
int testG = 1;

Guard gara;
Player chara;
Map room;
UI ui;
Aray RAray;

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

    FirstRoomArray();
    Gtimer = 5;
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
    case S_SPLASHSCREEN: gameplayKBHandler(keyboardEvent);// handle gameplay keyboard event
        break;
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_NEXTROOM: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_TPROOM: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_ENDROOM: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_WIN: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_LOSE: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
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
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    case S_NEXTROOM: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    case S_TPROOM: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    case S_ENDROOM: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    case S_LOSE: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
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

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : GoToGamePlay(); // game logic for the menu screen
            break;
        case S_GAME: updateGame(); // gameplay logic when we are in the game
            break;
        case S_NEXTROOM: updateGame();
            break;
        case S_TPROOM: updateGame();
            break;
        case S_ENDROOM: updateGame();
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

void moveCharacter()
{
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && chara.gety() > 0)
    {
        if (map[chara.gety() - 1][chara.getx()] == '-' || map[chara.gety() - 1][chara.getx()] == 'T')
        {
            map[chara.gety() - 1][chara.getx()] = 'P';
            map[chara.gety()][chara.getx()] = '-';
            //Beep(1440, 30);
            chara.ydec();
        }
        else if (map[chara.gety() - 1][chara.getx()] == 'G')
        {
            map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_LEFT].keyDown && chara.getx() > 0)
    {
        if (map[chara.gety()][chara.getx() - 1] == '-' || map[chara.gety()][chara.getx() - 1] == 'T')
        {
            gamestart = true;
            map[chara.gety()][chara.getx() - 1] = 'P';
            map[chara.gety()][chara.getx()] = '-';
            //Beep(1440, 30);
            chara.xdec();
        }
        else if (map[chara.gety()][chara.getx() - 1] == 'G')
        {
            map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyDown && chara.gety() < g_Console.getConsoleSize().Y - 1)
    {
        if (map[chara.gety() + 1][chara.getx()] == '-' || map[chara.gety() + 1][chara.getx()] == 'T')
        {
            map[chara.gety() + 1][chara.getx()] = 'P';
            map[chara.gety()][chara.getx()] = '-';
            //Beep(1440, 30);
            chara.yinc();
        }
        else if (map[chara.gety() + 1][chara.getx()] == 'G')
        {
            map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && chara.getx() < g_Console.getConsoleSize().X - 1)
    {
        if (map[chara.gety()][chara.getx() + 1] == '-' || map[chara.gety()][chara.getx() + 1] == 'T')
        {
            map[chara.gety()][chara.getx() + 1] = 'P';
            map[chara.gety()][chara.getx()] = '-';
            //Beep(1440, 30);
            chara.xinc();
        }
        else if (map[chara.gety()][chara.getx() + 1] == 'G')
        {
            map[chara.gety()][chara.getx()] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (map[2][58] == 'P')
    {
        map[2][58] = '-';
    }
    if (map[15][21] == 'P')
    {
        map[15][21] = '-';
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
        g_eGameState = S_GAME;
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
    gamestart = false;
    gameEnd = false;
    collected = false;
    room.getTP = false;
    chara.setx(g_Console.getConsoleSize().X / 2 - 1);
    chara.sety(g_Console.getConsoleSize().Y / 2);
    init();
}

void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderSplashScreen();
        break;
    case S_GAME: renderGame();
        break;
    case S_NEXTROOM: renderSecondRoom();
        break;
    case S_TPROOM: renderTPRoom();
        break;
    case S_ENDROOM: renderEndRoom();
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
void renderSplashScreen()  // renders the splash screen
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

    c.Y -= 10;
    c.X = g_Console.getConsoleSize().X / 2 - 5;
    g_Console.writeToBuffer(c, " Test : ", 0xB0);

    std::ostringstream ss;
    ss.str("");
    ss << testG << " ";
    c.X = 42;
    c.Y = 15;
    g_Console.writeToBuffer(c, ss.str(), 0xB0);
}
void renderGame()
{
    room.drawR1(g_Console);
    ui.drawUI(g_Console);
    chara.draw(g_Console);
    gara.drawG1(g_Console);

    if (map[chara.gety()][chara.getx()] == 'G')
    {
        map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    if (Gtimer > 0 && Gtimer < 100)
    {
        guarddetectroom1();   
        Gtimer++;
    }
    else if (Gtimer >= 100 && Gtimer < 300)
    {
        removeguard();
        Gtimer++;
    }
    else
    {
        Gtimer = 1;
    }
    
    /* Go to Second room */
    if (chara.getx() == 58 && chara.gety() == 2)
    {
        g_eGameState = S_NEXTROOM;
        SecondRoomArray();

        //character position for second room
        chara.setx(16); 
        chara.sety(4);
    }
}
void renderSecondRoom()
{
    clearScreen(); 
    room.drawR2(g_Console);
    ui.drawUI(g_Console);
    chara.draw(g_Console);
    gara.drawG2(g_Console);

    if (map[chara.gety()][chara.getx()] == 'G')
    {
        map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    if (Gtimer > 0 && Gtimer < 100)
    {
        guarddetectroom2();
        Gtimer++;
    }
    else if (Gtimer >= 100 && Gtimer < 300)
    {
        removeguard2();
        Gtimer++;
    }
    else
    {
        Gtimer = 1;
    }

    /* Go to toilet paper room */
    if (chara.getx() == 62 && chara.gety() == 13)
    {
        g_eGameState = S_TPROOM;
        TPRoomArray();

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
    gara.drawG3(g_Console);

    if (map[chara.gety()][chara.getx()] == 'G')
    {
        map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    if (Gtimer > 0 && Gtimer < 100)
    {
        guarddetectroom3();
        Gtimer++;
    }
    else if (Gtimer >= 100 && Gtimer < 300)
    {
        removeguard3();
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

    /* Go to the last room */
    if (chara.getx() == 40 && chara.gety() == 16 && collected == true)
    {
        g_eGameState = S_ENDROOM;
        EndRoomArray();
        //character position for last room
        chara.setx(40);
        chara.sety(2);
    }
    // Not collected
    else if (chara.getx() == 40 && chara.gety() == 16 && collected == false)
    {
        g_Console.writeToBuffer(30, 25, "Collect the toilet paper before exit !", 0x06);
    }
}
void renderEndRoom()
{
    clearScreen();
    room.drawREnd(g_Console);
    ui.drawUI(g_Console);
    ui.drawTP(g_Console);
    gara.drawG4(g_Console);
    chara.draw(g_Console);

    if (map[chara.gety()][chara.getx()] == 'G')
    {
        map[chara.gety()][chara.getx()] = '-';
        Beep(1440, 30);
        g_eGameState = S_LOSE;
    }
    if (Gtimer > 0 && Gtimer < 100)
    {
        guarddetectroom4();
        Gtimer++;
    }
    else if (Gtimer >= 100 && Gtimer < 300)
    {
        removeguard4();
        Gtimer++;
    }
    else
    {
        Gtimer = 1;
    }

    /* Go to WIN */
    if (chara.getx() == 58 && chara.gety() == 15 )
    {
        g_eGameState = S_WIN;
        gameEnd = true;
    }
}

void renderFramerate()
{
    if ((g_eGameState != S_SPLASHSCREEN) && (g_eGameState != S_WIN) && (g_eGameState != S_LOSE))
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

void renderWinScreen()
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 2;
    c.Y -= 10;
    c.X = c.X / 2 - 14;
    g_Console.writeToBuffer(c, "C O N G R A T U L A T I O N S !", 0x0A);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 6;
    g_Console.writeToBuffer(c, "Y O U  W O N !", 0x0A);
    c.Y += 8;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    g_Console.writeToBuffer(c, "  Time Taken: ", 0xB0);

    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss.str("");
    ss << g_dElapsedTime << "s  ";
    c.X = 44;
    c.Y = 15;
    g_Console.writeToBuffer(c, ss.str(), 0xB0);

    c.Y += 5;
    c.X = g_Console.getConsoleSize().X / 2 - 12;
    g_Console.writeToBuffer(c, "Press <SPACE> to play again", 0x07);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 8;
    g_Console.writeToBuffer(c, "Press <ESC> to exit", 0x07);

}
void renderLoseScreen()
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 2;
    c.Y -= 5;
    c.X = c.X / 2 -4;
    g_Console.writeToBuffer(c, "L O S E !", 0x0A);
    c.Y += 8;
    c.X = g_Console.getConsoleSize().X / 2 - 13;
    g_Console.writeToBuffer(c, "Press <SPACE> to play again", 0x07);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    g_Console.writeToBuffer(c, "Press <ESC> to exit", 0x07);
}

void FirstRoomArray()
{
    //array to detect things
    for (int x = 0; x < 80; ++x)
    {
        for (int y = 0; y < 18; ++y)
        {
            map[y][x] = '-';
        }
    }
    //walls in 4 sides
    for (int i = 0; i < 41; i++)
    {
        map[1][19 + i] = '+';
        map[16][19 + i] = '+';
    }
    for (int j = 0; j < 16; j++)
    {
        map[j + 1][19] = '+';
        map[j + 1][59] = '+';
    }
    /* Starting pt */
    map[15][39] = 'P';

    /* Obstacles (i = horz | j = vert) */

    //box obs in top left corner
    for (int i = 20; i < 23; i++)
    {
        for (int j = 2; j < 4; j++)
        {
            map[j][i] = '+';
        }
    }
    //box obs in the middle of map
    for (int i = 31; i < 36; i++)
    {
        for (int j = 4; j < 6; j++)
        {
            map[j][i] = '+';
        }
    }
    //horz obs in middle left
    for (int i = 24; i < 32; i++)
    {
        map[8][i] = '+';
    }
    //horz obs below E
    for (int i = 54; i < 59; i++)
    {
        map[4][i] = '+';
    }
    // L shape horz obs
    for (int i = 49; i < 54; i++)
    {
        map[11][i] = '+';
    }
    //vert obs beside spawn pt
    for (int j = 14; j < 16; j++)
    {
        map[j][40] = '+';
    }
    //horz obs near spawn pt
    for (int i = 34; i < 40; i++)
    {
        map[14][i] = '+';
    }
    //vert obs near exit pt
    for (int j = 2; j < 6; j++)
    {
        map[j][45] = '+';
    }
    // L shape vert obs
    for (int j = 9; j < 11; j++)
    {
        map[j][49] = '+';
    }
}
void SecondRoomArray()
{
    //array to detect things
    for (int x = 0; x < 80; ++x)
    {
        for (int y = 0; y < 18; ++y)
        {
            map[y][x] = '-';
        }
    }
    //walls in 4 sides
    for (int i = 0; i < 49; i++)
    {
        map[3][i + 15] = '+';
        map[14][i + 15] = '+';
    }
    for (int j = 0; j < 12; j++)
    {
        map[j + 3][15] = '+';
        map[j + 3][63] = '+';
    }
    /* Starting pt */
    map[4][16] = 'P';
    /* Obstacles (i = horz | j = vert) */

    //box obs on top left corner
    for (int i = 16; i < 25; i++)
    {
        for (int j = 6; j < 8; j++)
        {
            map[j][i] = '+';
        }
    }
    //box obs on the right
    for (int i = 50; i < 58; i++)
    {
        for (int j = 7; j < 9; j++)
        {
            map[j][i] = '+';
        }
    }
    //L shape horz obs 
    for (int i = 48; i < 51; i++)
    {
        map[13][i] = '+';
    }
    //reverse L shape horz obs
    for (int i = 25; i < 36; i++)
    {
        map[11][i] = '+';
    }

    // horz obs on top of exit
    for (int i = 57; i < 63; i++)
    {
        map[11][i] = '+';
    }
    //reverse L shape vert obs
    for (int i = 33; i < 36; i++)
    {
        for (int j = 8; j < 11; j++)
        {
            map[j][i] = '+';
        }
    }
    //vert obs on the top of the middle
    for (int j = 4; j < 7; j++)
    {
        map[j][42] = '+';
    }
    //L shape vert obs
    for (int i = 45; i < 48; i++)
    {
        for (int j = 11; j < 14; j++)
        {
            map[j][i] = '+';
        }
    }
}
void TPRoomArray()
{
    //array to detect things
    for (int x = 0; x < 80; ++x)
    {
        for (int y = 0; y < 18; ++y)
        {
            map[y][x] = '-';
        }
    }
    //walls in 4 sides
    for (int i = 0; i < 33; i++)
    {
        map[0][i + 24] = '+';
        map[17][i + 24] = '+';
    }
    for (int j = 0; j < 18; j++)
    {
        map[j][24] = '+';
        map[j][56] = '+';
    }
    /* Starting pt */
    map[1][25] = 'P';
    map[8][49] = 'T';

    /* Walls around toiletpaper spawn pt */
    for (int j = 6; j < 11; j++)
    {
        map[j][47] = '+';
    }
    for (int i = 48; i < 52; i++)
    {
        map[6][i] = '+';
        map[10][i] = '+';
    }
    // vert wall beside spawn pt
    for (int i = 29; i < 32; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            map[j][i] = '+';
        }
    }
    // wall around exit pt
    for (int i = 42; i < 44; i++)
    {
        for (int j = 14; j < 17; j++)
        {
            map[j][i] = '+';
        }
    }
    for (int i = 38; i < 43; i++)
    {
        map[14][i] = '+';
    }
    // thick wall in the middle of the map
    for (int i = 25; i < 34; i++)
    {
        for (int j = 8; j < 10; j++)
        {
            map[j][i] = '+';
        }
    }
    // horz wall on top of the map
    for (int i = 41; i < 46; i++)
    {
        map[3][i] = '+';
    }

}
void EndRoomArray()
{
    //array to detect things
    for (int x = 0; x < 80; ++x)
    {
        for (int y = 0; y < 18; ++y)
        {
            map[y][x] = '-';
        }
    }

    //walls in 4 sides
    for (int i = 0; i < 41; i++)
    {
        map[1][19 + i] = '+';
        map[16][19 + i] = '+';
    }
    for (int j = 0; j < 16; j++)
    {
        map[1 + j][19] = '+';
        map[1 + j][59] = '+';
    }
    /* Starting pt */
    map[2][40] = 'P';

    // thick wall next to the spawn pt
    for (int i = 41; i < 47; i++)
    {
        for (int j = 2; j < 5; j++)
        {
            map[j][i] = '+';
        }
    }
    for (int i = 25; i < 41; i++)
    {
        map[4][i] = '+';
    }

    /* thick wall beside exit pt */
    for (int i = 33; i < 41; i++)
    {
        for (int j = 13; j < 16; j++)
        {
            map[j][i] = '+';
        }
    }
    for (int i = 39; i < 41; i++)
    {
        for (int j = 10; j < 13; j++)
        {
            map[j][i] = '+';
        }
    }
    for (int i = 41; i < 53; i++)
    {
        map[10][i] = '+';
    }

    // vert wall in the middle
    for (int i = 33; i < 35; i++)
    {
        for (int j = 5; j < 11; j++)
        {
            map[j][i] = '+';
        }
    }
    // horz wall at the top left corner
    for (int i = 20; i < 28; i++)
    {
        map[7][i] = '+';
    }

    // horz wall in the middle left 
    for (int i = 26; i < 33; i++)
    {
        map[10][i] = '+';
    }

    for (int j = 11; j < 14; j++)
    {
        map[j][26] = '+';
    }

    //horz wall on top of exit pt
    for (int i = 50; i < 59; i++)
    {
        map[13][i] = '+';
    }

    for (int i = 56; i < 59; i++)
    {
        map[2][i] = '+';
    }
}

void guarddetectroom1()
{
    //50,5
    for (int gx = 47; gx < 54; ++gx)
    {
        for (int gy = 3; gy < 8; ++gy)
        {
            if (map[gy][gx] == '+')
            {
            
            }
            else if (gx == 50 && gy == 5)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_Console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
}
void guarddetectroom2()
{
    //28,5
    for (int gx = 25; gx < 32; ++gx)
    {
        for (int gy = 3; gy < 8; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 28 && gy == 5)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_Console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
    //44,8
    for (int gx = 41; gx < 48; ++gx)
    {
        for (int gy = 6; gy < 11; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 44 && gy == 8)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_Console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
}
void guarddetectroom3()
{
    //36,5
    for (int gx = 33; gx < 40; ++gx)
    {
        for (int gy = 3; gy < 8; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 36 && gy == 5)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_Console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
    //36,11
    for (int gx = 33; gx < 40; ++gx)
    {
        for (int gy = 9; gy < 14; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 36 && gy == 11)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_Console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
    //55,8
    for (int gx = 52; gx < 56; ++gx)
    {
        for (int gy = 6; gy < 11; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 55 && gy == 8)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_Console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
}
void guarddetectroom4()
{
    //20,2
    for (int gx = 20; gx < 24; ++gx)
    {
        for (int gy = 2; gy < 5; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 20 && gy == 2)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_Console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }    
    //20,15
    for (int gx = 20; gx < 24; ++gx)
    {
        for (int gy = 13; gy < 16; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 20 && gy == 15)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_Console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
    //43,7
    for (int gx = 40; gx < 47; ++gx)
    {
        for (int gy = 5; gy < 10; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 43 && gy == 7)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_Console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
    //41,15
    for (int gx = 38; gx < 45; ++gx)
    {
        for (int gy = 13; gy < 16; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 41 && gy == 15)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_Console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
}

void removeguard()
{
    for (int gx = 47; gx < 54; ++gx)
    {
        for (int gy = 3; gy < 8; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 50 && gy == 5)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = '-';
            }
        }
    }
}
void removeguard2()
{
    //28,5
    for (int gx = 25; gx < 32; ++gx)
    {
        for (int gy = 3; gy < 8; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 28 && gy == 5)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = '-';
            }
        }
    }
    //44,8
    for (int gx = 41; gx < 48; ++gx)
    {
        for (int gy = 6; gy < 11; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 44 && gy == 8)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = '-';
            }
        }
    }
}
void removeguard3()
{
    //36,5
    for (int gx = 33; gx < 40; ++gx)
    {
        for (int gy = 3; gy < 8; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 36 && gy == 5)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = '-';
            }
        }
    }
    //36,11
    for (int gx = 33; gx < 40; ++gx)
    {
        for (int gy = 9; gy < 14; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 36 && gy == 11)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = '-';
            }
        }
    }
    //55,8
    for (int gx = 52; gx < 56; ++gx)
    {
        for (int gy = 6; gy < 11; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 55 && gy == 8)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = '-';
            }
        }
    }
}
void removeguard4()
{
    //20,2
    for (int gx = 20; gx < 24; ++gx)
    {
        for (int gy = 2; gy < 5; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 20 && gy == 2)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = '-';
            }
        }
    }
    //20,15
    for (int gx = 20; gx < 24; ++gx)
    {
        for (int gy = 13; gy < 16; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 20 && gy == 15)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = '-';
            }
        }
    }
    //43,7
    for (int gx = 40; gx < 47; ++gx)
    {
        for (int gy = 5; gy < 10; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 43 && gy == 7)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = '-';
            }
        }
    }
    //41,15
    for (int gx = 38; gx < 45; ++gx)
    {
        for (int gy = 13; gy < 16; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 41 && gy == 15)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = '-';
            }
        }
    }
}