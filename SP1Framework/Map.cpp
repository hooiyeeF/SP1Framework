#include "Map.h"

void Map::drawR1(Console& g_console)
{
    int wallX = 19;
    int wallY = 1;

    //walls in 4 sides
    for (int i = 0; i < 41; i++)
    {
        g_console.writeToBuffer(wallX + i, 1, "+", 0xB20);
        g_console.writeToBuffer(wallX + i, 16, "+", 0xB20);
    }
    for (int j = 0; j < 16; j++)
    {
        g_console.writeToBuffer(19, wallY + j, "+", 0xB20);
        g_console.writeToBuffer(59, wallY + j, "+", 0xB20);
    }
    /* Starting pt */
    g_console.writeToBuffer(39, 15, "S", 0x5E);

    /* Ending pt */
    g_console.writeToBuffer(58, 2, "E", 0x5E);

    /* Obstacles (i = horz | j = vert) */

    //box obs in top left corner
    for (int i = 20; i < 23; i++)
    {
        for (int j = 2; j < 4; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    //box obs in the middle of map
    for (int i = 31; i < 36; i++)
    {
        for (int j = 4; j < 6; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    //horz obs in middle left
    for (int i = 24; i < 32; i++)
    {
        g_console.writeToBuffer(i, 8, "+", 0xB20);
    }
    //horz obs below E
    for (int i = 54; i < 59; i++)
    {
        g_console.writeToBuffer(i, 4, "+", 0xB20);
    }
    // L shape horz obs
    for (int i = 49; i < 54; i++)
    {
        g_console.writeToBuffer(i, 11, "+", 0xB20);
    }
    //vert obs beside spawn pt
    for (int j = 14; j < 16; j++)
    {
        g_console.writeToBuffer(40, j, "+", 0xB20);
    }
    //horz obs near spawn pt
    for (int i = 34; i < 40; i++)
    {
        g_console.writeToBuffer(i, 14, "+", 0xB20);
    }
    //vert obs near exit pt
    for (int j = 2; j < 6; j++)
    {
        g_console.writeToBuffer(45, j, "+", 0xB20);
    }
    // L shape vert obs
    for (int j = 9; j < 11; j++)
    {
        g_console.writeToBuffer(49, j, "+", 0xB20);
    }
}

void Map::drawR2(Console& g_console)
{
    int wallX = 15;
    int wallY = 3;

    //walls in 4 sides
    for (int i = 0; i < 49; i++)
    {
        g_console.writeToBuffer(wallX + i, 3, "+", 0xB20);
        g_console.writeToBuffer(wallX + i, 14, "+", 0xB20);
    }
    for (int j = 0; j < 12; j++)
    {
        g_console.writeToBuffer(15, wallY + j, "+", 0xB20);
        g_console.writeToBuffer(63, wallY + j, "+", 0xB20);
    }
    /* Starting pt */
    g_console.writeToBuffer(16, 4, "S", 0x5E);
    /* Ending pt */
    g_console.writeToBuffer(62, 13, "E", 0x5E);

    /* Obstacles (i = horz | j = vert) */

    //box obs on top left corner
    for (int i = 16; i < 25; i++)
    {
        for (int j = 6; j < 8; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    //box obs on the right
    for (int i = 50; i < 58; i++)
    {
        for (int j = 7; j < 9; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    //L shape horz obs 
    for (int i = 48; i < 51; i++)
    {
        g_console.writeToBuffer(i, 13, "+", 0xB20);
    }
    //reverse L shape horz obs
    for (int i = 25; i < 36; i++)
    {
        g_console.writeToBuffer(i, 11, "+", 0xB20);
    }

    // horz obs on top of exit
    for (int i = 57; i < 63; i++)
    {
        g_console.writeToBuffer(i, 11, "+", 0xB20);
    }
    //reverse L shape vert obs
    for (int i = 33; i < 36; i++)
    {
        for (int j = 8; j < 11; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    //vert obs on the top of the middle
    for (int j = 4; j < 7; j++)
    {
        g_console.writeToBuffer(42, j, "+", 0xB20);
    }
    //L shape vert obs
    for (int i = 45; i < 48; i++)
    {
        for (int j = 11; j < 14; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
}

void Map::drawRTP(Console& g_console)
{
    int wallX = 24;
    int wallY = 0;

    //walls in 4 sides
    for (int i = 0; i < 33; i++)
    {
        g_console.writeToBuffer(wallX + i, 0, "+", 0xB20);
        g_console.writeToBuffer(wallX + i, 17, "+", 0xB20);
    }
    for (int j = 0; j < 18; j++)
    {
        g_console.writeToBuffer(24, wallY + j, "+", 0xB20);
        g_console.writeToBuffer(56, wallY + j, "+", 0xB20);
    }
    /* Starting pt */
    g_console.writeToBuffer(25, 1, "S", 0x5E);
    /* Ending pt */
    g_console.writeToBuffer(40, 16, "E", 0x5E);
    /* Spawn toilet paper */
    if (getTP == false)
    {
        g_console.writeToBuffer(49, 8, "T", 0xF0);
    }

    /* Walls around toiletpaper spawn pt */
    for (int j = 6; j < 11; j++)
    {
        g_console.writeToBuffer(47, j, "+", 0xB20);
    }
    for (int i = 48; i < 52; i++)
    {
        g_console.writeToBuffer(i, 6, "+", 0xB20);
        g_console.writeToBuffer(i, 10, "+", 0xB20);
    }
    // vert wall beside spawn pt
    for (int i = 29; i < 32; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    // wall around exit pt
    for (int i = 42; i < 44; i++)
    {
        for (int j = 14; j < 17; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    for (int i = 38; i < 43; i++)
    {
        g_console.writeToBuffer(i, 14, "+", 0xB20);
    }
    // thick wall in the middle of the map
    for (int i = 25; i < 34; i++)
    {
        for (int j = 8; j < 10; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    // horz wall on top of the map
    for (int i = 41; i < 46; i++)
    {
        g_console.writeToBuffer(i, 3, "+", 0xB20);
    }
}

void Map::drawREnd(Console& g_console)
{
    int wallX = 19;
    int wallY = 1;

    //walls in 4 sides
    for (int i = 0; i < 41; i++)
    {
        g_console.writeToBuffer(wallX + i, 1, "+", 0xB20);
        g_console.writeToBuffer(wallX + i, 16, "+", 0xB20);
    }
    for (int j = 0; j < 16; j++)
    {
        g_console.writeToBuffer(19, wallY + j, "+", 0xB20);
        g_console.writeToBuffer(59, wallY + j, "+", 0xB20);
    }
    /* Starting pt */
    g_console.writeToBuffer(40, 2, "S", 0x5E);

    /* Ending pt */
    g_console.writeToBuffer(58, 15, "E", 0x5E);

    // thick wall next to the spawn pt
    for (int i = 41; i < 47; i++)
    {
        for (int j = 2; j < 5; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    for (int i = 25; i < 41; i++)
    {
        g_console.writeToBuffer(i, 4, "+", 0xB20);
    }

    /* thick wall beside exit pt */
    for (int i = 33; i < 41; i++)
    {
        for (int j = 13; j < 16; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    for (int i = 39; i < 41; i++)
    {
        for (int j = 10; j < 13; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    for (int i = 41; i < 53; i++)
    {
        g_console.writeToBuffer(i, 10, "+", 0xB20);
    }

    // vert wall in the middle
    for (int i = 33; i < 35; i++)
    {
        for (int j = 5; j < 11; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    // horz wall at the top left corner
    for (int i = 20; i < 28; i++)
    {
        g_console.writeToBuffer(i, 7, "+", 0xB20);
    }

    // horz wall in the middle left 
    for (int i = 26; i < 33; i++)
    {
        g_console.writeToBuffer(i, 10, "+", 0xB20);
    }

    for (int j = 11; j < 14; j++)
    {
        g_console.writeToBuffer(26, j, "+", 0xB20);
    }

    //horz wall on top of exit pt
    for (int i = 50; i < 59; i++)
    {
        g_console.writeToBuffer(i, 13, "+", 0xB20);
    }

    for (int i = 56; i < 59; i++)
    {
        g_console.writeToBuffer(i, 2, "+", 0xB20);
    }
}