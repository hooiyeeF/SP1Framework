#include "Aray.h"

void Aray::FirstRoomArray(Console& g_console)
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
void Aray::SecondRoomArray(Console& g_console)
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
void Aray::TPRoomArray(Console& g_console)
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
void Aray::EndRoomArray(Console& g_console)
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

void Aray::guarddetectroom1a(Console& g_console)
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
                g_console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
}
void Aray::guarddetectroom1b(Console& g_console)
{
    //49,5
    for (int gx = 46; gx < 53; ++gx)
    {
        for (int gy = 3; gy < 8; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 49 && gy == 5)
            {
                map[gy][gx] = 'G';
            }
            else
            {
                map[gy][gx] = 'G';
                g_console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
}
void Aray::guarddetectroom2(Console& g_console)
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
                g_console.writeToBuffer(gx, gy, " ", 79);
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
                g_console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
}
void Aray::guarddetectroomTP(Console& g_console)
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
                g_console.writeToBuffer(gx, gy, " ", 79);
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
                g_console.writeToBuffer(gx, gy, " ", 79);
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
                g_console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
}
void Aray::guarddetectroomEnd(Console& g_console)
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
                g_console.writeToBuffer(gx, gy, " ", 79);
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
                g_console.writeToBuffer(gx, gy, " ", 79);
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
                g_console.writeToBuffer(gx, gy, " ", 79);
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
                g_console.writeToBuffer(gx, gy, " ", 79);
            }
        }
    }
}

void Aray::removeguarda(Console& g_console)
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
void Aray::removeguardb(Console& g_console)
{
    //49,5
    for (int gx = 46; gx < 53; ++gx)
    {
        for (int gy = 3; gy < 8; ++gy)
        {
            if (map[gy][gx] == '+')
            {

            }
            else if (gx == 49 && gy == 5)
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
void Aray::removeguard2(Console& g_console)
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
void Aray::removeguardTP(Console& g_console)
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
void Aray::removeguardEnd(Console& g_console)
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