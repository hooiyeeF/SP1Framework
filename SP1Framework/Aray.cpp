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
    map[2][54] = '+';
    map[3][54] = '+';
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

    map[2][55] = '+';
    map[3][55] = '+';

    /* wall around exit pt */
    for (int i = 55; i < 59; i++) //horz wall
    {
        map[11][i] = '+';
    }
    for (int j = 4; j < 12; j++) // vert wall
    {
        map[j][55] = '+';
    }

    // box wall beside starting pt
    for (int i = 23; i < 28; i++)
    {
        for (int j = 14; j < 16; j++)
        {
            map[j][i] = '+';
        }
    }

    // box wall on top of starting pt
    for (int i = 20; i < 30; i++)
    {
        for (int j = 10; j < 12; j++)
        {
            map[j][i] = '+';
        }
    }

    map[11][36] = '+';
    map[12][35] = '+';
    map[13][34] = '+';
    map[14][33] = '+';
    map[15][32] = '+';
    map[15][31] = '+';

    // box wall in the center
    for (int i = 25; i < 37; i++)
    {
        for (int j = 6; j < 8; j++)
        {
            map[j][i] = '+';
        }
    }
    // top 'dots wall
    map[4][27] = '+';
    map[2][30] = '+';
    map[3][32] = '+';

    // long vert wall
    for (int i = 37; i < 41; i++)
    {
        for (int j = 4; j < 11; j++)
        {
            map[j][i] = '+';
        }
    }
    // long vert wall connect to the top
    for (int i = 46; i < 50; i++)
    {
        for (int j = 2; j < 8; j++)
        {
            map[j][i] = '+';
        }
    }

    //'ZZ' horz wall
    for (int i = 47; i < 50; i++)
    {
        map[10][i] = '+';
    }
    for (int i = 46; i < 49; i++)
    {
        map[11][i] = '+';
    }
    for (int i = 45; i < 48; i++)
    {
        map[12][i] = '+';
    }
    for (int i = 44; i < 47; i++)
    {
        map[13][i] = '+';
    }
    for (int i = 43; i < 46; i++)
    {
        map[14][i] = '+';
    }

    // horz wall beside 'ZZ' wall (bottom)
    for (int i = 50; i < 57; i++)
    {
        map[13][i] = '+';
    }
}
void Aray::ThirdRoomArray(Console& g_console)
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
void Aray::FourthRoomArray(Console& g_console)
{
    //array to detect things
    for (int x = 0; x < 80; ++x)
    {
        for (int y = 0; y < 18; ++y)
        {
            map[y][x] = '-';
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
        map[j][57] = '+';
        map[j][58] = '+';
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
        map[0][19 + i] = '+';
        map[17][17 + i] = '+';
    }
    for (int j = 0; j < 16; j++)
    {
        map[1 + j][19] = '+';
        map[1 + j][59] = '+';
        map[1 + j][18] = '+';
        map[j][17] = '+';
        map[j][18] = '+';
        map[1 + j][60] = '+';
        map[1 + j][17] = '+';
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
void Aray::CRoomArray(Console& g_console)
{
    //array to detect things
    for (int x = 0; x < 80; ++x)
    {
        for (int y = 0; y < 18; ++y)
        {
            map[y][x] = '-';
        }
    }
    //array to detect things
    for (int x = 0; x < 80; ++x)
    {
        for (int y = 0; y < 18; ++y)
        {
            map[y][x] = '-';
        }
    }

    //walls in 4 sides
    for (int i = 0; i < 78; i++) // top horz wall
    {
        map[3][i + 1] = '+';
    }
    for (int i = 0; i < 73; i++) // bottom left horz wall
    {
        map[9][i + 1] = '+';
    }
    for (int i = 75; i < 79; i++) // bottom left horz wall
    {
        map[9][i] = '+';
    }
    for (int j = 0; j < 6; j++)
    {
        map[j + 3][1] = '+';
        map[j + 3][78] = '+';
    }

    /* Guard path wall */
    for (int i = 4; i < 74; i++)  // top horz wall
    {
        map[12][i] = '+';
    }
    for (int i = 4; i < 76; i++)  // down horz wall
    {
        map[14][i] = '+';;
    }
    for (int j = 12; j < 15; j++) // left vert wall
    {
        map[j][3] = '+';
    }
    for (int j = 10; j < 12; j++) // right short vert wall
    {
        map[j][73] = '+';
    }
    for (int j = 10; j < 15; j++) // right long vert wall
    {
        map[j][75] = '+';
    }

    /* wall near exit */
    for (int i = 72; i < 78; i++)  //horz wall
    {
        map[6][i] = '+';
    }
    for (int i = 72; i < 75; i++)  //vert wall
    {
        map[7][i] = '+';
    }

    // vert wall beside starting pt
    for (int i = 5; i < 7; i++)
    {
        for (int j = 4; j < 7; j++)
        {
            map[j][i] = '+';
        }
    }

    for (int i = 7; i < 12; i++)
    {
        map[8][i] = '+';
    }

    // top 'box' wall near starting pt
    for (int i = 10; i < 13; i++)
    {
        for (int j = 5; j < 7; j++)
        {
            map[j][i] = '+';
        }
    }
    // floating bottom horz wall
    for (int i = 15; i < 20; i++)
    {
        map[7][i] = '+';
    }
    // floating top horz wall
    for (int i = 18; i < 24; i++)
    {
        map[5][i] = '+';
    }
    //vert wall
    for (int j = 7; j < 9; j++)
    {
        map[j][24] = '+';
    }
    //vert wall
    for (int j = 4; j < 7; j++)
    {
        map[j][27] = '+';
    }

    map[5][29] = '+';

    /*  bottom 2 'connected' horz wall*/
    for (int i = 30; i < 35; i++)
    {
        map[7][i] = '+';
    }
    for (int i = 35; i < 38; i++)
    {
        map[8][i] = '+';
    }

    // top horz wall
    for (int i = 33; i < 38; i++)
    {
        map[4][i] = '+';
    }

    // 'box' wall in the middle
    for (int i = 39; i < 46; i++)
    {
        for (int j = 5; j < 8; j++)
        {
            map[j][i] = '+';
        }
    }

    map[7][47] = '+';

    // top box wall
    for (int i = 49; i < 55; i++)
    {
        for (int j = 4; j < 6; j++)
        {
            map[j][i] = '+';
        }
    }

    map[8][51] = '+';

    // bottom box wall
    for (int i = 54; i < 60; i++)
    {
        for (int j = 7; j < 9; j++)
        {
            map[j][i] = '+';
        }
    }
    /* 'dots' wall at the back */
    map[5][57] = '+';
    map[4][59] = '+';
    map[6][61] = '+';
    map[8][62] = '+';
    map[4][63] = '+';
    map[5][64] = '+';
    map[8][64] = '+';
    map[7][65] = '+';
    map[4][66] = '+';
    map[6][66] = '+';
    map[8][67] = '+';
    map[6][68] = '+';
    map[5][69] = '+';
    map[7][69] = '+';
    map[8][70] = '+';
    map[4][71] = '+';
    map[5][74] = '+';
    map[4][75] = '+';
    map[5][76] = '+';

}

void Aray::guarddetect(Console& g_console, int gx, int gy)
{
    //50,5
    //47,54 
    //3,8
    int a = gx;

    int c = a + 4;
    int d = gy;

    int f = d + 3;
    for (int b = a - 3; b < c; ++b)
    {
        for (int e = d - 2; e < f; ++e)
        {
            if (map[e][b] == '+')
            {

            }
            else if (b == gx && e == gy)
            {
                map[e][b] = 'G';
                g_console.writeToBuffer(b, e, (char)1, 0x0c);
            }
            else
            {
                map[e][b] = 'G';
                g_console.writeToBuffer(b, e, " ", 79);
            }
        }
    }
    
}

void Aray::removeguard(Console& g_console, int gx, int gy)
{
    int a = gx;

    int c = a + 4;
    int d = gy;

    int f = d + 3;
    for (int b = a - 3; b < c; ++b)
    {
        for (int e = d - 2; e < f; ++e)
        {
            if (map[e][b] == '+')
            {

            }
            else if (b == gx && e == gy)
            {
                map[e][b] = 'G';
                g_console.writeToBuffer(b, e, (char)1, 0x0c);

            }
            else
            {
                map[e][b] = '-';
            }
        }
    }
}

void Aray::guardmove(Console& g_console)
{
    XA = &xa;
    YA = &ya;
    if (*YA == 15 && *XA != 4)
    {
        *XA--;
    }
    else if (*XA == 4 && *YA != 13)
    {
        *YA--;
    }
    else if (*YA == 13 && *XA != 74)
    {
        *XA++;
    }
    else if (xa == 74)
    {
        *YA++;
    }
    else if (*XA == 74 && *YA == 8)
    {
        
    }
    map[ya][xa] = 'G';
    g_console.writeToBuffer(ya, xa, (char)1, 0x0c);
    
}