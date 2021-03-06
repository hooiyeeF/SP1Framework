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

    /* Key spawn pt */
    if (getKey == false)
    {
        g_console.writeToBuffer(58, 15, "K", 0xE5);
    }

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

    /* openable door - vert wall */
    /* door open 'animation' - if else */
    if (getKey == false)
    {
        for (int j = 2; j < 4; j++)
        {
            g_console.writeToBuffer(54, j, "+", 0xB20);
        }
    }
    else if (getKey == true && Dtime > 2) // change color
    {
        for (int j = 2; j < 4; j++)
        {
            g_console.writeToBuffer(54, j, " ", 0x5E);
        }
    }
    else if (getKey == true && Dtime > 1) // door opening
    {
        g_console.writeToBuffer(54, 2, " ", 0x5E);
    }

}

void Map::drawR2(Console& g_console)
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
    g_console.writeToBuffer(20, 15, "S", 0x5E);

    /* Ending pt */
    g_console.writeToBuffer(58, 10, "E", 0x5E);

    /* Key spawn pt */
    if (getKey == false)
    {
        g_console.writeToBuffer(33, 15, "K", 0xE5);
    }

    /* wall around exit pt */
    for (int i = 55; i < 59; i++) //horz wall
    {
        g_console.writeToBuffer(i, 11, "+", 0xB20);
    }
    for (int j = 4; j < 12; j++) // vert wall
    {
        g_console.writeToBuffer(55,j, "+", 0xB20);
    }

    /* openable door - vert wall */
    /* door open 'animation' - if else */
    if (getKey == false)
    {
        for (int j = 2; j < 4; j++) 
        {
            g_console.writeToBuffer(55, j, "+", 0xB20);
        }
    }
    else if (getKey == true && Dtime > 2) // change color
    {
        for (int j = 2; j < 4; j++) 
        {
            g_console.writeToBuffer(55, j, " ", 0x5E);
        }
    }
    else if (getKey == true && Dtime > 1) // door opening
    {
        g_console.writeToBuffer(55, 3, " ", 0x5E);
    }

    // box wall beside starting pt
    for (int i = 23; i < 28; i++)
    {
        for (int j = 14; j < 16; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }

    // box wall on top of starting pt
    for (int i = 20; i < 30; i++)
    {
        for (int j = 10; j < 12; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }

    g_console.writeToBuffer(36, 11, "+", 0xB20);
    g_console.writeToBuffer(35, 12, "+", 0xB20);
    g_console.writeToBuffer(34, 13, "+", 0xB20);
    g_console.writeToBuffer(33, 14, "+", 0xB20);
    g_console.writeToBuffer(32, 15, "+", 0xB20);
    g_console.writeToBuffer(31, 15, "+", 0xB20);

    // box wall in the center
    for (int i = 25; i < 37; i++)
    {
        for (int j = 6; j < 8; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    // top 'dots wall
    g_console.writeToBuffer(27, 4, "+", 0xB20);
    g_console.writeToBuffer(30, 2, "+", 0xB20);
    g_console.writeToBuffer(32, 3, "+", 0xB20);

    // long vert wall
    for (int i = 37; i < 41; i++)
    {
        for (int j = 4; j < 11; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    // long vert wall connect to the top
    for (int i = 46; i < 50; i++)
    {
        for (int j = 2; j < 8; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }

    //'ZZ' horz wall
    for (int i = 47; i < 50; i++) 
    {
        g_console.writeToBuffer(i, 10, "+", 0xB20);
    }
    for (int i = 46; i < 49; i++)
    {
        g_console.writeToBuffer(i, 11, "+", 0xB20);
    }
    for (int i = 45; i < 48; i++)
    {
        g_console.writeToBuffer(i, 12, "+", 0xB20);
    }
    for (int i = 44; i < 47; i++)
    {
        g_console.writeToBuffer(i, 13, "+", 0xB20);
    }
    for (int i = 43; i < 46; i++)
    {
        g_console.writeToBuffer(i, 14, "+", 0xB20);
    }
    
    // horz wall beside 'ZZ' wall (bottom)
    for (int i = 50; i < 57; i++)
    {
        g_console.writeToBuffer(i, 13, "+", 0xB20);
    }

}

void Map::drawR3(Console& g_console)
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

void Map::drawR4(Console& g_console)
{
    int wallX = 23;
    int wallY = 3;

    //walls in 4 sides
    for (int i = 0; i < 33; i++)
    {
        g_console.writeToBuffer(wallX + i, 3, "+", 0xB20);
        g_console.writeToBuffer(wallX + i, 16, "+", 0xB20);
    }
    for (int j = 0; j < 14; j++)
    {
        g_console.writeToBuffer(23, wallY + j, "+", 0xB20);
        g_console.writeToBuffer(55, wallY + j, "+", 0xB20);
    }
    /* Starting pt */
    g_console.writeToBuffer(54, 4, "S", 0x5E);

    /* Ending pt */
    g_console.writeToBuffer(24, 15, "E", 0x5E);

    //horz wall below starting pt
    for (int i = 48; i < 56; i++)
    {
        g_console.writeToBuffer(i, 5, "+", 0xB20);
    }

    //horz wall above exit pt
    for (int i = 24; i < 32; i++)
    {
        g_console.writeToBuffer(i, 14, "+", 0xB20);
    }

    // box wall in the middle of map
    for (int i = 34; i < 47; i++)
    {
        for (int j = 8; j < 12; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }

    // 'dots' wall on the left
    g_console.writeToBuffer(25, 6, "+", 0xB20);
    g_console.writeToBuffer(29, 6, "+", 0xB20);
    g_console.writeToBuffer(28, 7, "+", 0xB20);
    g_console.writeToBuffer(30, 7, "+", 0xB20);
    g_console.writeToBuffer(26, 8, "+", 0xB20);
    g_console.writeToBuffer(29, 8, "+", 0xB20);
    g_console.writeToBuffer(32, 8, "+", 0xB20);
    g_console.writeToBuffer(28, 9, "+", 0xB20);
    g_console.writeToBuffer(30, 9, "+", 0xB20);
    g_console.writeToBuffer(33, 9, "+", 0xB20);
    g_console.writeToBuffer(27, 10, "+", 0xB20);
    g_console.writeToBuffer(31, 10, "+", 0xB20);
    g_console.writeToBuffer(25, 11, "+", 0xB20);
    g_console.writeToBuffer(30, 11, "+", 0xB20);
    g_console.writeToBuffer(33, 11, "+", 0xB20);
    g_console.writeToBuffer(26, 12, "+", 0xB20);
    g_console.writeToBuffer(29, 12, "+", 0xB20);
    g_console.writeToBuffer(32, 12, "+", 0xB20);

    // 'dots' wall on the right
    g_console.writeToBuffer(54, 7, "+", 0xB20);
    g_console.writeToBuffer(48, 8, "+", 0xB20);
    g_console.writeToBuffer(52, 8, "+", 0xB20);
    g_console.writeToBuffer(47, 9, "+", 0xB20);
    g_console.writeToBuffer(50, 9, "+", 0xB20);
    g_console.writeToBuffer(53, 9, "+", 0xB20);
    g_console.writeToBuffer(49, 10, "+", 0xB20);
    g_console.writeToBuffer(51, 10, "+", 0xB20);
    g_console.writeToBuffer(53, 11, "+", 0xB20);
    g_console.writeToBuffer(47, 11, "+", 0xB20);
    g_console.writeToBuffer(48, 12, "+", 0xB20);
    g_console.writeToBuffer(51, 12, "+", 0xB20);
    g_console.writeToBuffer(54, 12, "+", 0xB20);
    g_console.writeToBuffer(50, 13, "+", 0xB20);
    g_console.writeToBuffer(52, 13, "+", 0xB20);
    g_console.writeToBuffer(47, 14, "+", 0xB20);
    g_console.writeToBuffer(51, 14, "+", 0xB20);
    g_console.writeToBuffer(53, 15, "+", 0xB20);
    g_console.writeToBuffer(49, 15, "+", 0xB20);
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

void Map::drawPR(Console& g_console)
{
    int wallX = 1;
    int wallY = 1;

    //walls in 4 sides
    for (int i = 0; i < 78; i++)
    {
        g_console.writeToBuffer(wallX + i, 1, "+", 0xB20);
        g_console.writeToBuffer(wallX + i, 16, "+", 0xB20);
    }
    for (int j = 0; j < 16; j++)
    {
        g_console.writeToBuffer(1, wallY + j, "+", 0xB20);
        g_console.writeToBuffer(78, wallY + j, "+", 0xB20);
    }
    /* Starting pt */
    g_console.writeToBuffer(2, 2, "S", 0x5E);
    /* Ending pt */
    if (hitB == true && hitB2 == true)
    {
        g_console.writeToBuffer(5, 10, "E", 0x5E);
    }
    /* 2 button spawn pt*/
    g_console.writeToBuffer(40, 5, "B", 0xE5);
    g_console.writeToBuffer(51, 13, "B", 0xE5);

    //bottom horz wall
    for (int i = 2; i < 20; i++)
    {
        g_console.writeToBuffer(i, 12, "+", 0xB20);
    }
    // up-c shape 
    for (int j = 5; j < 7; j++)
    {
        g_console.writeToBuffer(39, j, "+", 0xB20);
        g_console.writeToBuffer(41, j, "+", 0xB20);
    }
    g_console.writeToBuffer(40, 6, "+", 0xB20);

    //random dot
    g_console.writeToBuffer(60, 6, "+", 0xB20);

    // down-c shape
    for (int j = 12; j < 14; j++)
    {
        g_console.writeToBuffer(50, j, "+", 0xB20);
        g_console.writeToBuffer(52, j, "+", 0xB20);
    }
    g_console.writeToBuffer(51, 12, "+", 0xB20);

    //2 'dot'
    g_console.writeToBuffer(19, 13, "+", 0xB20);
    g_console.writeToBuffer(19, 14, "+", 0xB20);
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

void Map::drawLR(Console& g_console)
{ 
    int wallX = 1;
    int wallY = 3;

    //walls in 4 sides
    for (int i = 0; i < 78; i++) // top horz wall
    {
        g_console.writeToBuffer(wallX + i, 3, "+", 0xB20);
    }
    for (int i = 0; i < 73; i++) // bottom left horz wall
    {
        g_console.writeToBuffer(wallX + i, 9, "+", 0xB20);
    }
    for (int i = 75; i < 79; i++) // bottom left horz wall
    {
        g_console.writeToBuffer(i, 9, "+", 0xB20); 
    }
    for (int j = 0; j < 6; j++)
    {
        g_console.writeToBuffer(1, wallY + j, "+", 0xB20);
        g_console.writeToBuffer(78, wallY + j, "+", 0xB20);
    }

    /* Guard path wall */
    for (int i = 4; i < 74; i++)  // top horz wall
    {
        g_console.writeToBuffer(i, 12, "+", 0xC30);
    }
    for (int i = 5; i < 76; i++)  // down horz wall
    {
        g_console.writeToBuffer(i, 14, "+", 0xC30);
    }
    for (int j = 12; j < 17; j++) // left vert wall
    {
        g_console.writeToBuffer(3, j, "+", 0xC30);
    }
    for (int j = 10; j < 12; j++) // right short vert wall
    {
        g_console.writeToBuffer(73, j, "+", 0xC30);
    }
    for (int j = 10; j < 15; j++) // right long vert wall
    {
        g_console.writeToBuffer(75, j, "+", 0xC30);
    }
    for (int i = 4; i < 30; i++)  // downer horz wall
    {
        g_console.writeToBuffer(i, 16, "+", 0xC30);
    }
    for (int j = 15; j < 17; j++) // right short vert wall
    {
        g_console.writeToBuffer(30, j, "+", 0xC30);
    }

    /* Starting pt */
    g_console.writeToBuffer(2, 4, "S", 0x5E);

    /* Ending pt */
    g_console.writeToBuffer(77, 8, "E", 0x5E);

    /* wall near exit */
    for (int i = 72; i < 78; i++)  //horz wall
    {
        g_console.writeToBuffer(i, 6, "+", 0xB20);
    }
    for (int i = 72; i < 75; i++)  //vert wall
    {
        g_console.writeToBuffer(i, 7, "+", 0xB20);
    } 

    // vert wall beside starting pt
    for (int i = 5; i < 7; i++)
    {
        for (int j = 4; j < 7; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }

    for (int i = 7; i < 12; i++)
    {
        g_console.writeToBuffer(i, 8, "+", 0xB20);
    }

    // top 'box' wall near starting pt
    for (int i = 10; i < 13; i++)
    {
        for (int j = 5; j < 7; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }
    // floating bottom horz wall
    for (int i = 15; i < 20; i++)
    {
        g_console.writeToBuffer(i, 7, "+", 0xB20);
    }
    // floating top horz wall
    for (int i = 18; i < 24; i++)
    {
        g_console.writeToBuffer(i, 5, "+", 0xB20);
    }
    //vert wall
    for (int j = 7; j < 9; j++)
    {
        g_console.writeToBuffer(24, j, "+", 0xB20);
    }
    //vert wall
    for (int j = 4; j < 7; j++)
    {
        g_console.writeToBuffer(27, j, "+", 0xB20);
    }

    g_console.writeToBuffer(29, 5, "+", 0xB20);

    /*  bottom 2 'connected' horz wall*/
    for (int i = 30; i < 35; i++)
    {
        g_console.writeToBuffer(i, 7, "+", 0xB20);
    }
    for (int i = 35; i < 38; i++)
    {
        g_console.writeToBuffer(i, 8, "+", 0xB20);
    }

    // top horz wall
    for (int i = 33; i < 38; i++)
    {
        g_console.writeToBuffer(i, 4, "+", 0xB20);
    }

    // 'box' wall in the middle
    for (int i = 39; i < 46; i++)
    {
        for (int j = 5; j < 8; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }

    g_console.writeToBuffer(47, 7, "+", 0xB20);

    // top box wall
    for (int i = 49; i < 55; i++)
    {
        for (int j = 4; j < 6; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }

    g_console.writeToBuffer(51, 8, "+", 0xB20);

    // bottom box wall
    for (int i = 54; i < 60; i++)
    {
        for (int j = 7; j < 9; j++)
        {
            g_console.writeToBuffer(i, j, "+", 0xB20);
        }
    }

    /* 'dots' wall at the back */
    g_console.writeToBuffer(57, 5, "+", 0xB20);
    g_console.writeToBuffer(59, 4, "+", 0xB20);
    g_console.writeToBuffer(61, 6, "+", 0xB20);
    g_console.writeToBuffer(62, 8, "+", 0xB20);
    g_console.writeToBuffer(63, 4, "+", 0xB20);
    g_console.writeToBuffer(64, 5, "+", 0xB20);
    g_console.writeToBuffer(64, 8, "+", 0xB20);
    g_console.writeToBuffer(65, 7, "+", 0xB20);
    g_console.writeToBuffer(66, 4, "+", 0xB20);
    g_console.writeToBuffer(66, 6, "+", 0xB20);
    g_console.writeToBuffer(67, 8, "+", 0xB20);
    g_console.writeToBuffer(68, 6, "+", 0xB20);
    g_console.writeToBuffer(69, 5, "+", 0xB20);
    g_console.writeToBuffer(69, 7, "+", 0xB20);
    g_console.writeToBuffer(70, 8, "+", 0xB20);
    g_console.writeToBuffer(71, 4, "+", 0xB20);
    g_console.writeToBuffer(74, 5, "+", 0xB20);
    g_console.writeToBuffer(75, 4, "+", 0xB20);
    g_console.writeToBuffer(76, 5, "+", 0xB20);

}


