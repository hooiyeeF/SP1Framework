// This is the main file for the game logic and function
// //
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;
char map[15][40];
bool a = false;
bool spawn = false;
bool spawn2 = false;
bool gamestart = false;

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

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
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
    case S_NextRoom: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
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
        case S_NextRoom: updateGame();
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

void moveCharacter()
{    
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && g_sChar.m_cLocation.Y > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;       
    }
    if (g_skKeyEvent[K_LEFT].keyDown && g_sChar.m_cLocation.X > 0)
    {
        gamestart = true;
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;        
    }
    if (g_skKeyEvent[K_DOWN].keyDown && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;        
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;        
    }
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;        
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
    case S_NextRoom: renderSecondRoom();
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
    c.X = c.X / 2 - 9;
 //   g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 -10;
    g_Console.writeToBuffer(c, "Press <Space> to start", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
 //   g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    FirstRoom();        //render first game room
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
    rendertoiletpaper();     // renders toiletpaper *** add bool statement to check if toilet paper is collected then display ***
    while (a == true)
    {
        FirstRoomArray();
    }
    /* Go to Second room */
    if (g_sChar.m_cLocation.X == 58 && g_sChar.m_cLocation.Y == 2)
    {
        g_eGameState = S_NextRoom;

        g_sChar.m_cLocation.X = 16; //character position for second room
        g_sChar.m_cLocation.Y = 4;
    }

}

void renderSecondRoom()
{
    clearScreen(); 
    SecondRoom();       //render second room
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
    rendertoiletpaper();


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
    for (int x = 0; x < 15; ++x)
    {
        for (int y = 0; y < 40; ++y)
        {
            map[x][y] = ' ';
        }
    }
   //player
    map[13][20] = 'P';
    spawnenemy();
    //endpoint
    map[1][38] = 'D';

    //wall
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            map[j][i] = '+';
        }
    }

    for (int i = 1; i < 40; i++)
    {
        for (int j = 14; j < 15; j++)
        {
            map[j][i] = '+';
        }
    }

    for (int i = 1; i < 4; i++)
    {
        for (int j = 1; j < 3; j++)
        {
            map[j][i] = '+';
        }
    }

    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            map[j][i] = '+';
        }
    }

    //obstacles

    for (int i = 39; i < 40; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            map[j][i] = '+';
        }
    }


    for (int i = 1; i < 4; i++)
    {
        for (int j = 1; j < 3; j++)
        {
            map[j][i] = '+';
        }
    }

    for (int i = 12; i < 17; i++)
    {
        for (int j = 3; j < 5; j++)
        {
            map[j][i] = '+';
        }
    }

    for (int i = 5; i < 13; i++)
    {
        map[8][i] = '+';
    }

    for (int i = 35; i < 40; i++)
    {
        map[4][i] = '+';
    }

    for (int i = 30; i < 35; i++)
    {
        map[10][i] = '+';
    }

    for (int j = 12; j < 15; j++)
    {
        map[j][21] = '+';
    }

    for (int i = 15; i < 22; i++)
    {
        map[12][i] = '+';
    }

    for (int j = 1; j < 5; j++)
    {
        map[j][26] = '+';
    }

    for (int j = 8; j < 10; j++)
    {
        map[j][30] = '+';
    }

    a = true;
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
    /* Spawn toilet paper({48,8},{49,8}) */
    g_Console.writeToBuffer(48, 8, "TP", 0xF0);

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

void spawnenemy()
{
    
    while (spawn == false)
    {
        srand(time(NULL));
        int gy = rand() % 40;
        int gx = rand() % 15;
        if (map[gx][gy] == 'P')
        {
            spawn = false;
        }
        else if (map[gx][gy] == '+')
        {
            spawn = false;
        }
        else if (map[gx][gy] == 'D')
        {
            spawn = false;
        }
        else if (map[gx][gy] == 'G')
        {
            spawn = false;
        }
        else
        {
            map[gx][gy] = 'G';
            g_Console.writeToBuffer(gy + 19, gx + 2, "G", FOREGROUND_RED);
            spawn = true;
            int b = rand() % 4;

        }
    }

    while (spawn2 == false)
    {
        srand(time(NULL));
        int gy2 = rand() % 40;
        int gx2 = rand() % 15;
        if (map[gx2][gy2] == 'P')
        {
            spawn = false;
        }
        else if (map[gx2][gy2] == '+')
        {
            spawn = false;
        }
        else if (map[gx2][gy2] == 'D')
        {
            spawn = false;
        }
        else if (map[gx2][gy2] == 'G')
        {
            spawn = false;
        }
        else
        {
            map[gx2][gy2] = 'G';
            g_Console.writeToBuffer(gy2 + 19,gx2 + 2, "G", FOREGROUND_RED);
            spawn2 = true;
            int b = rand() % 4;
        }
    }
}





bool gettoiletpaper()
{
    return true;
}

