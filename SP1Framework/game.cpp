// This is the main file for the game logic and function
// //
//
#include "game.h"
#include "Framework\console.h"
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Guard.h"

double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;
char map[16][41];
char map2[12][49];
char map3[18][33];
bool gamestart = false;


Guard gara;
Player chara;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(80, 30, "Escape the Factory");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;    

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;
    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2 - 1;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    chara.x = g_Console.getConsoleSize().X / 2 - 1;
    chara.y = g_Console.getConsoleSize().Y / 2;

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);

    FirstRoomArray();
    SecondRoomArray();
    TPRoomArray();
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
    if (gamestart == true)
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
        case S_NEXTROOM: updateGame2();
            break;
        case S_TPROOM: updateGame3();
            break;
        case S_ENDROOM: updateGame4();
            break;
        case S_LOSE: 
            processUserInput();
            PlayAgain();
            break;
    }
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void updateGame()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void updateGame2()
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter2();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void updateGame3()
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter3();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}
void updateGame4()
{
}

void moveCharacter()
{
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && chara.y > 0)
    {
        if (map[chara.y - 2][chara.x - 19] == '-')
        {
            map[chara.y - 2][chara.x - 19] = 'P';
            map[chara.y - 1][chara.x - 19] = '-';
            //Beep(1440, 30);
            chara.y--;
        }
        else if (map[chara.y - 2][chara.x - 19] == 'G')
        {
            map[chara.y - 1][chara.x - 19] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_LEFT].keyDown && chara.x > 0)
    {
        if (map[chara.y - 1][chara.x - 20] == '-')
        {
            gamestart = true;
            map[chara.y - 1][chara.x - 20] = 'P';
            map[chara.y - 1][chara.x - 19] = '-';
            //Beep(1440, 30);
            chara.x--;
        }
        if (map[chara.y - 1][chara.x - 20] == 'G')
        {
            map[chara.y - 1][chara.x - 19] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyDown && chara.y < g_Console.getConsoleSize().Y - 1)
    {
        if (map[chara.y][chara.x - 19] == '-')
        {
            map[chara.y][chara.x - 19] = 'P';
            map[chara.y - 1][chara.x - 19] = '-';
            //Beep(1440, 30);
            chara.y++;
        }
        if (map[chara.y][chara.x - 19] == 'G')
        {
            map[chara.y - 1][chara.x - 19] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && chara.x < g_Console.getConsoleSize().X - 1)
    {
        if (map[chara.y - 1][chara.x - 18] == '-')
        {
            map[chara.y - 1][chara.x - 18] = 'P';
            map[chara.y - 1][chara.x - 19] = '-';
            //Beep(1440, 30);
            chara.x++;
        }
        if (map[chara.y - 1][chara.x - 18] == 'G')
        {
            map[chara.y - 1][chara.x - 19] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
    }
    if (map[1][39] == 'P')
    {
        map[1][39] = '-';
    }
}

void moveCharacter2()
{
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && chara.y > 0)
    {
        if (map2[chara.y - 4][chara.x - 15] == '-')
        {
            map2[chara.y - 4][chara.x - 15] = 'P';
            map2[chara.y - 3][chara.x - 15] = '-';
            //Beep(1440, 30);
            chara.y--;
        }
        if (map2[chara.y - 4][chara.x - 15] == 'G')
        {
            map2[chara.y - 3][chara.x - 15] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_LEFT].keyDown && chara.x > 0)
    {
        if (map2[chara.y - 3][chara.x - 16] == '-')
        {
            map2[chara.y - 3][chara.x - 16] = 'P';
            map2[chara.y - 3][chara.x - 15] = '-';
            //Beep(1440, 30);
            chara.x--;
        }
        if (map2[chara.y - 3][chara.x - 16] == 'G')
        {
            map2[chara.y - 3][chara.x - 15] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyDown && chara.y < g_Console.getConsoleSize().Y - 1)
    {
        if (map2[chara.y - 2][chara.x - 15] == '-')
        {
            map2[chara.y - 2][chara.x - 15] = 'P';
            map2[chara.y - 3][chara.x - 15] = '-';
            //Beep(1440, 30);
            chara.y++;
        }
        if (map2[chara.y - 2][chara.x - 15] == 'G')
        {
            map2[chara.y - 3][chara.x - 15] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && chara.x < g_Console.getConsoleSize().X - 1)
    {
        if (map2[chara.y - 3][chara.x - 14] == '-')
        {
            map2[chara.y - 3][chara.x - 14] = 'P';
            map2[chara.y - 3][chara.x - 15] = '-';
            //Beep(1440, 30);
            chara.x++;
        }
        if (map2[chara.y - 3][chara.x - 14] == 'G')
        {
            map2[chara.y - 3][chara.x - 15] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
    }
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
    }
    if (map2[12][48] == 'P')
    {
        map2[12][48] = '-';
    }
    
}

void moveCharacter3()
{
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && chara.y > 0)
    {
        if (map3[chara.y - 1][chara.x - 24] == '-')
        {
            map3[chara.y - 1][chara.x - 24] = 'P';
            map3[chara.y][chara.x - 24] = '-';
            //Beep(1440, 30);
            chara.y--;
        }
        if (map3[chara.y - 1][chara.x - 24] == 'G')
        {
            map3[chara.y][chara.x - 24] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        if (map3[chara.y - 1][chara.x - 24] == 'T')
        {
            map3[chara.y - 1][chara.x - 24] = 'P';
            map3[chara.y][chara.x - 24] = '-';
            Beep(1440, 30);
            chara.y--;
            gettoiletpaper();
        }
    }
    if (g_skKeyEvent[K_LEFT].keyDown && chara.x > 0)
    {
        if (map3[chara.y][chara.x - 25] == '-')
        {
            map3[chara.y][chara.x - 25] = 'P';
            map3[chara.y][chara.x - 24] = '-';
            //Beep(1440, 30);
            chara.x--;
        }
        if (map3[chara.y][chara.x - 25] == 'G')
        {
            map3[chara.y][chara.x - 24] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        if (map3[chara.y - 1][chara.x - 24] == 'T')
        {
            map3[chara.y][chara.x - 25] = 'P';
            map3[chara.y][chara.x - 24] = '-';
            Beep(1440, 30);
            chara.x--;
            gettoiletpaper();
        }
    }
    if (g_skKeyEvent[K_DOWN].keyDown && chara.y < g_Console.getConsoleSize().Y - 1)
    {
        if (map3[chara.y + 1][chara.x - 24] == '-')
        {
            map3[chara.y + 1][chara.x - 24] = 'P';
            map3[chara.y][chara.x - 24] = '-';
            //Beep(1440, 30);
            chara.y++;
        }
        if (map3[chara.y + 1][chara.x - 24] == 'G')
        {
            map3[chara.y][chara.x - 24] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        if (map3[chara.y - 1][chara.x - 24] == 'T')
        {
            map3[chara.y + 1][chara.x - 24] = 'P';
            map3[chara.y][chara.x - 24] = '-';
            Beep(1440, 30);
            chara.y++;
            gettoiletpaper();
        }
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && chara.x < g_Console.getConsoleSize().X - 1)
    {
        if (map3[chara.y][chara.x - 23] == '-')
        {
            map3[chara.y][chara.x - 23] = 'P';
            map3[chara.y][chara.x - 24] = '-';
            //Beep(1440, 30);
            chara.x++;
        }
        if (map3[chara.y][chara.x - 23] == 'G')
        {
            map3[chara.y][chara.x - 24] = '-';
            Beep(1440, 30);
            g_eGameState = S_LOSE;
        }
        if (map3[chara.y - 1][chara.x - 24] == 'T')
        {
            map3[chara.y][chara.x - 23] = 'P';
            map3[chara.y][chara.x - 24] = '-';
            Beep(1440, 30);
            chara.x++;
            gettoiletpaper();
        }
    }
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
    }
    if (map3[16][16] == 'P')
    {
        map3[16][16] = '-';
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
        g_eGameState = S_SPLASHSCREEN;

    reset();
}
void reset()
{
    chara.x = g_Console.getConsoleSize().X / 2 - 1;
    chara.y = g_Console.getConsoleSize().Y / 2;
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
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
    case S_LOSE: renderLoseScreen();
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
   // if (gettoiletpaper() == true)
     //   rendertoiletpaper();
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
}

void renderGame()
{
    FirstRoom();        //render first game room
    renderMap();        // renders the map to the buffer first
    //renderCharacter();  // renders the character into the buffer
    chara.draw(g_Console);
    gara.drawG1(g_Console);
    //rendertoiletpaper();     // renders toiletpaper *** add bool statement to check if toilet paper is collected then display ***
    /* Go to Second room */
    if (chara.x == 58 && chara.y == 2)
    {
        g_eGameState = S_NEXTROOM;

        chara.x = 16; //character position for second room
        chara.y = 4;
    }
}

void renderSecondRoom()
{
    clearScreen(); 
    SecondRoom();       //render second room
    renderMap();        // renders the map to the buffer first
    //renderCharacter();  // renders the character into the buffer
    chara.draw(g_Console);
    gara.drawG2(g_Console);
  //  rendertoiletpaper();

    /* Go to toilet paper room */
    if (chara.x == 62 && chara.y == 13)
    {
        g_eGameState = S_TPROOM;

        chara.x = 25; //character position for toilet paper room
        chara.y = 1;
    }
}

void renderTPRoom()
{
    clearScreen();
    TPRoom();            //render Toilet paper room
    renderMap();         // renders the map to the buffer first
    //renderCharacter();   // renders the character into the buffer
    chara.draw(g_Console);
    gara.drawG3(g_Console);

    if (chara.x == 49 && chara.y == 8)
    {
        rendertoiletpaper();
    }

    /* Go to the last room */
    if (chara.x == 40 && chara.y == 16)
    {
        g_eGameState = S_ENDROOM;

        chara.x = 40; //character position for last room
        chara.y = 2;
    }
}

void renderEndRoom()
{
    clearScreen();
    EndRoom();            //render Toilet paper room
    renderMap();         // renders the map to the buffer first
    rendertoiletpaper();
    chara.draw(g_Console);   // renders the character into the buffer
}

void renderMap()
{
    // Set up sample colours, and output shadings
    //const WORD colors[] = {
    //    0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
    //   0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    //};

    g_Console.writeToBuffer(0, 18, "                                                                                ", 0xFF);
    g_Console.writeToBuffer(23, 20, "                  ", 0xB2); // 6 space for each sprint **total of 3 sprints/ 18 spaces
    g_Console.writeToBuffer(23, 21, "                  ", 0xB2); // 6 space for each sprint **total of 3 sprints / 18 spaces
    g_Console.writeToBuffer(3, 20, "                  ", 0xFF); //box for toiletpaper
    g_Console.writeToBuffer(3, 28, "                  ", 0xFF); //box for toiletpaper
    for (int i = 20; i < 28; ++i)
    {
        g_Console.writeToBuffer(3, i, " ", 0xFF); //box for toiletpaper
        g_Console.writeToBuffer(20, i, " ", 0xFF); //box for toiletpaper
    }
}

void rendertoiletpaper()
{
    for (int ty = 22; ty < 27; ++ty)
    {
        for (int tx = 7; tx < 17; ++tx)
        {
            if (tx == 11 && ty == 22)
            {
                g_Console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 12 && ty == 22)
            {
                g_Console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 10 && ty == 23)
            {
                g_Console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 13 && ty == 23)
            {
                g_Console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 11 && ty == 24)
            {
                g_Console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 12 && ty == 24)
            {
                g_Console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 11 && ty == 23)
            {
                g_Console.writeToBuffer(tx, ty, " ", 0);
            }
            else if (tx == 12 && ty == 23)
            {
                g_Console.writeToBuffer(tx, ty, " ", 0);
            }
            else
            {
                g_Console.writeToBuffer(tx, ty, " ", 0xFF);
            }
        }
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0F;
    /*if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }*/
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
} 

void renderGuard()
{
    //Draw the location of the guard
    WORD charColor = 0x0D;
        if (g_sChar.m_bActive)
        {
            charColor = 0x0C;
        }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1,charColor);
}

void renderFramerate()
{
    if (g_eGameState != S_SPLASHSCREEN)
    {
        COORD c;
        // displays the framerate
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(3);
        ss << 1.0 / g_dDeltaTime << "fps";
        c.X = g_Console.getConsoleSize().X - 9;
        c.Y = 0;
        g_Console.writeToBuffer(c, ss.str());

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
        /*  if (g_skKeyEvent[i].keyDown)
                ss << key << " pressed";
            else if (g_skKeyEvent[i].keyReleased)
                ss << key << " released";
            else
                ss << key << " not pressed";*/

        COORD c = { startPos.X, startPos.Y + i };
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }
    // mouse events
    if (g_eGameState != S_SPLASHSCREEN)
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

void FirstRoom()
{   
    int wallX = 19;
    int wallY = 1;

    //walls in 4 sides
    for (int i = 0; i < 41; i++)
    {
        g_Console.writeToBuffer(wallX + i, 1, "+", 0xB20);
        g_Console.writeToBuffer(wallX + i, 16, "+", 0xB20);
    }
    for (int j = 0; j < 16; j++)
    {
        g_Console.writeToBuffer(19, wallY + j, "+", 0xB20);
        g_Console.writeToBuffer(59, wallY + j, "+", 0xB20);
    }
    /* Starting pt */ 
    g_Console.writeToBuffer(39, 15, "S", 0x5E);

    /* Ending pt */
    g_Console.writeToBuffer(58, 2, "E", 0x5E);

    /* Obstacles (i = horz | j = vert) */  
   
    //box obs in top left corner
    for (int i = 20; i < 23; i++)
    {
        for (int j = 2; j < 4; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    //box obs in the middle of map
    for (int i = 31; i < 36; i++)
    {
        for (int j = 4; j < 6; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    //horz obs in middle left
    for (int i = 24; i < 32; i++)
    {
        g_Console.writeToBuffer(i, 8, "+", 0xB20);
    }
    //horz obs below E
    for (int i = 54; i < 59; i++)
    {
        g_Console.writeToBuffer(i, 4, "+", 0xB20);
    }
    // L shape horz obs
    for (int i = 49; i < 54; i++)
    {
        g_Console.writeToBuffer(i, 11, "+", 0xB20);
    }
    //vert obs beside spawn pt
    for (int j = 14; j < 16; j++)
    {
        g_Console.writeToBuffer(40, j, "+", 0xB20);
    }
    //horz obs near spawn pt
    for (int i = 34; i < 40; i++)
    {
        g_Console.writeToBuffer(i, 14, "+", 0xB20);
    }
    //vert obs near exit pt
    for (int j = 2; j < 6; j++)
    {
        g_Console.writeToBuffer(45, j, "+", 0xB20);
    }
    // L shape vert obs
    for (int j = 9; j < 11; j++)
    {
        g_Console.writeToBuffer(49, j, "+", 0xB20);
    }
        

   
}

void FirstRoomArray()
{
    //array to detect things
    for (int x = 0; x < 16; ++x)
    {
        for (int y = 0; y < 41; ++y)
        {
            map[x][y] = '-';
        }
    }
    //player
    map[14][20] = 'P';
    //Guard
    map[4][31] = 'G';

    //wall
    for (int i = 0; i < 41; i++)
    {
        map[0][i] = '+';
        map[15][i] = '+';
    }
    for (int j = 0; j < 16; j++)
    {
        map[j][0] = '+';
        map[j][40] = '+';
    }
    /* Obstacles (i = horz | j = vert) */

    //box obs in top left corner
    for (int i = 1; i < 4; i++)
    {
        for (int j = 1; j < 3; j++)
        {
            map[j][i] = '+';
        }
    }

    //box obs in the middle of map
    for (int i = 12; i < 17; i++)
    {
        for (int j = 3; j < 5; j++)
        {
            map[j][i] = '+';
        }
    }

    //horz obs in middle left
    for (int i = 5; i < 13; i++)
    {
        map[7][i] = '+';
    }

    //horz obs below E
    for (int i = 35; i < 40; i++)
    {
        map[3][i] = '+';
    }

    // L shape horz obs
    for (int i = 30; i < 35; i++)
    {
        map[10][i] = '+';
    }

    //vert obs beside spawn pt
    for (int j = 13; j < 15; j++)
    {
        map[j][21] = '+';
    }

    //horz obs near spawn pt
    for (int i = 15; i < 21; i++)
    {
        map[13][i] = '+';
    }

    //vert obs near exit pt
    for (int j = 1; j < 5; j++)
    {
        map[j][26] = '+';
    }
    // L shape vert obs
    for (int j = 8; j < 10; j++)
    {
        map[j][30] = '+';
    }
}

void SecondRoom()
{
    int wallX = 15;
    int wallY = 3;

    //walls in 4 sides
    for (int i = 0; i < 49; i++)
    {
        g_Console.writeToBuffer(wallX + i, 3, "+", 0xB20);
        g_Console.writeToBuffer(wallX + i, 14, "+", 0xB20);
    }
    for (int j = 0; j < 12; j++)
    {
        g_Console.writeToBuffer(15, wallY + j, "+", 0xB20);
        g_Console.writeToBuffer(63, wallY + j, "+", 0xB20);
    }
    /* Starting pt */
    g_Console.writeToBuffer(16, 4, "S", 0x5E);
    /* Ending pt */
    g_Console.writeToBuffer(62, 13, "E", 0x5E);

    /* Obstacles (i = horz | j = vert) */

    //box obs on top left corner
    for (int i = 16; i < 25; i++)
    {
        for (int j = 6; j < 8; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    //box obs on the right
    for (int i = 50; i < 58; i++)
    {
        for (int j = 7; j < 9; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    //L shape horz obs 
    for (int i = 48; i < 51; i++)
    {
        g_Console.writeToBuffer(i, 13, "+", 0xB20);
    }
    //reverse L shape horz obs
    for (int i = 25; i < 36; i++)
    {
        g_Console.writeToBuffer(i, 11, "+", 0xB20);
    }

    // horz obs on top of exit
    for (int i = 57; i < 63; i++)
    {
        g_Console.writeToBuffer(i, 11, "+", 0xB20);
    }
    //reverse L shape vert obs
    for (int i = 33; i < 36; i++)
    {
        for (int j = 8; j < 11; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    //vert obs on the top of the middle
    for (int j = 4; j < 7; j++)
    {
        g_Console.writeToBuffer(42, j, "+", 0xB20);
    }
    //L shape vert obs
    for (int i = 45; i < 48; i++)
    {
        for (int j = 11; j < 14; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
}

void SecondRoomArray()
{
    //array to detect things
    for (int x = 0; x < 12; ++x)
    {
        for (int y = 0; y < 49; ++y)
        {
            map2[x][y] = '-';
        }
    }
    //walls in 4 sides
    for (int i = 0; i < 49; i++)
    {
        map2[0][i] = '+';
        map2[11][i] = '+';
    }
    for (int j = 0; j < 12; j++)
    {
        map2[j][0] = '+';
        map2[j][48] = '+';
    }
    /* Starting pt */
    map2[1][1] = 'P';
    //Guard
    map2[2][13] = 'G';
    map2[5][29] = 'G';

    /* Obstacles (i = horz | j = vert) */

    //box obs on top left corner
    for (int i = 1; i < 10; i++)
    {
        for (int j = 3; j < 5; j++)
        {
            map2[j][i] = '+';
        }
    }

    //box obs on the right
    for (int i = 35; i < 43; i++)
    {
        for (int j = 4; j < 6; j++)
        {
            map2[j][i] = '+';
        }
    }

    //L shape horz obs 
    for (int i = 33; i < 36; i++)
    {
        map2[10][i] = '+';
    }

    //reverse L shape horz obs
    for (int i = 10; i < 21; i++)
    {
        map2[8][i] = '+';
    }

    // horz obs on top of exit
    for (int i = 42; i < 48; i++)
    {
        map2[8][i] = '+';
    }

    //reverse L shape vert obs
    for (int i = 18; i < 21; i++)
    {
        for (int j = 5; j < 8; j++)
        {
            map2[j][i] = '+';
        }
    }

    //vert obs on the top of the middle
    for (int j = 1; j < 4; j++)
    {
        map2[j][27] = '+';
    }

    //L shape vert obs
    for (int i = 30; i < 33; i++)
    {
        for (int j = 8; j < 11; j++)
        {
            map2[j][i] = '+';
        }
    }
}

void TPRoom()
{
    int wallX = 24;
    int wallY = 0;

    //walls in 4 sides
    for (int i = 0; i < 33; i++)
    {
        g_Console.writeToBuffer(wallX + i, 0, "+", 0xB20);
        g_Console.writeToBuffer(wallX + i, 17, "+", 0xB20);
    }
    for (int j = 0; j < 18; j++)
    {
        g_Console.writeToBuffer(24, wallY + j, "+", 0xB20);
        g_Console.writeToBuffer(56, wallY + j, "+", 0xB20);
    }
    /* Starting pt */
    g_Console.writeToBuffer(25, 1, "S", 0x5E);
    /* Ending pt */
    g_Console.writeToBuffer(40, 16, "E", 0x5E);
    /* Spawn toilet paper */
    g_Console.writeToBuffer(49, 8, "T", 0xF0);

    /* Walls around toiletpaper spawn pt */
    for (int j = 6; j < 11; j++)
    {
        g_Console.writeToBuffer(47, j, "+", 0xB20);
    }
    for (int i = 48; i < 52; i++)
    {
        g_Console.writeToBuffer(i, 6, "+", 0xB20);
        g_Console.writeToBuffer(i, 10, "+", 0xB20);
    }
    // vert wall beside spawn pt
    for (int i = 29; i < 32; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    // wall around exit pt
    for (int i = 42; i < 44; i++)
    {
        for (int j = 14; j < 17; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    for (int i = 38; i < 43; i++)
    {
        g_Console.writeToBuffer(i, 14, "+", 0xB20);
    }
    // thick wall in the middle of the map
    for (int i = 25; i < 34; i++)
    {
        for (int j = 8; j < 10; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    // horz wall on top of the map
    for (int i = 41; i < 46; i++)
    {
        g_Console.writeToBuffer(i, 3, "+", 0xB20);
    }
}

void TPRoomArray()
{
    
    //array to detect things
    for (int x = 0; x < 18; ++x)
    {
        for (int y = 0; y < 33; ++y)
        {
            map3[x][y] = '-';
        }
    }
    //walls in 4 sides
    for (int i = 0; i < 33; i++)
    {
        map3[0][i] = '+';
        map3[17][i] = '+';
    }
    for (int j = 0; j < 18; j++)
    {
        map3[j][0] = '+';
        map3[j][32] = '+';
    }
    /* Starting pt */
    map3[1][1] = 'P';

    /* Spawn toilet paper({48,8},{49,8}) */
    map3[7][25] = 'T';
    //spawn guards
    map3[5][12] = 'G';
    map3[11][12] = 'G';
    map3[8][31] = 'G';

    /* Walls around toiletpaper spawn pt */
    for (int j = 6; j < 11; j++)
    {
        map3[j][23] = '+';
    }
    for (int i = 24; i < 28; i++)
    {
        map3[6][i] = '+';
        map3[10][i] = '+';
    }
    // vert wall beside spawn pt
    for (int i = 5; i < 8; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            map3[j][i] = '+';
        }
    }
    // wall around exit pt
    for (int i = 18; i < 20; i++)
    {
        for (int j = 14; j < 17; j++)
        {
            map3[j][i] = '+';
        }
    }
    for (int i = 14; i < 19; i++)
    {
        map3[14][i] = '+';
    }
    // thick wall in the middle of the map
    for (int i = 1; i < 10; i++)
    {
        for (int j = 8; j < 10; j++)
        {
            map3[j][i] = '+';
        }
    }
    // horz wall on top of the map
    for (int i = 17; i < 22; i++)
    {
        map3[3][i] = '+';
    }
    for (int x = 0; x < 18; ++x)
    {
        for (int y = 0; y < 33; ++y)
        {
            std::cout << map3[x][y];
        }
        std::cout << "" << std::endl;
    }
}

void EndRoom()
{
    int wallX = 19;
    int wallY = 1;

    //walls in 4 sides
    for (int i = 0; i < 41; i++)
    {
        g_Console.writeToBuffer(wallX + i, 1, "+", 0xB20);
        g_Console.writeToBuffer(wallX + i, 16, "+", 0xB20);
    }
    for (int j = 0; j < 16; j++)
    {
        g_Console.writeToBuffer(19, wallY + j, "+", 0xB20);
        g_Console.writeToBuffer(59, wallY + j, "+", 0xB20);
    }
    /* Starting pt */
    g_Console.writeToBuffer(40, 2, "S", 0x5E);

    /* Ending pt */
    g_Console.writeToBuffer(58, 15, "E", 0x5E);

    // thick wall next to the spawn pt
    for (int i = 41; i < 47; i++)
    {
        for (int j = 2; j < 5; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    for (int i = 25; i < 41; i++)
    {
        g_Console.writeToBuffer(i, 4, "+", 0xB20);
    }

    /* thick wall beside exit pt */
    for (int i = 33; i < 41; i++)
    {
        for (int j = 13; j < 16; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    for (int i = 39; i < 41; i++)
    {
        for (int j = 10; j < 13; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    for (int i = 41; i < 53; i++)
    {
        g_Console.writeToBuffer(i, 10, "+", 0xB20);
    }

    // vert wall in the middle
    for (int i = 33; i < 35; i++)
    {
        for (int j = 5; j < 11; j++)
        {
            g_Console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    // horz wall at the top left corner
    for (int i = 20; i < 28; i++)
    {
        g_Console.writeToBuffer(i, 7, "+", 0xB20);
    }

    // horz wall in the middle left 
    for (int i = 26; i < 33; i++)
    {
        g_Console.writeToBuffer(i, 10, "+", 0xB20);
    }

    for (int j = 11; j < 14; j++)
    {
        g_Console.writeToBuffer(26, j, "+", 0xB20);
    }

    //horz wall on top of exit pt
    for (int i = 50; i < 59; i++)
    {
        g_Console.writeToBuffer(i, 13, "+", 0xB20);
    }

    for (int i = 56; i < 59; i++)
    {
         g_Console.writeToBuffer(i, 2, "+", 0xB20);
    }
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

void resetroom()
{
    char map[15][40];                   //Resets array
    for (int x = 0; x < 15; ++x)
    {
        for (int y = 0; y < 40; ++y)
        {
            map[x][y] = ' ';
        }
    }
    g_Console.clearBuffer(0);          //Resets the whole map

}

bool gettoiletpaper()
{
    return true;
}