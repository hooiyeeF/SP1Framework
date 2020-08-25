#include "UI.h"

void UI::drawUI(Console& g_console)
{
    g_console.writeToBuffer(0, 18, "                                                                                ", 0xFF);
    g_console.writeToBuffer(3, 20, "                  ", 0xFF); //box for toiletpaper
    g_console.writeToBuffer(3, 28, "                  ", 0xFF); //box for toiletpaper
    for (int i = 20; i < 28; ++i)
    {
        g_console.writeToBuffer(3, i, " ", 0xFF); //box for toiletpaper
        g_console.writeToBuffer(20, i, " ", 0xFF); //box for toiletpaper
    }
}

void UI::drawTP(Console& g_console)
{
    for (int ty = 22; ty < 27; ++ty)
    {
        for (int tx = 7; tx < 17; ++tx)
        {
            if (tx == 11 && ty == 22)
            {
                g_console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 12 && ty == 22)
            {
                g_console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 10 && ty == 23)
            {
                g_console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 13 && ty == 23)
            {
                g_console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 11 && ty == 24)
            {
                g_console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 12 && ty == 24)
            {
                g_console.writeToBuffer(tx, ty, " ", 79);
            }
            else if (tx == 11 && ty == 23)
            {
                g_console.writeToBuffer(tx, ty, " ", 0);
            }
            else if (tx == 12 && ty == 23)
            {
                g_console.writeToBuffer(tx, ty, " ", 0);
            }
            else
            {
                g_console.writeToBuffer(tx, ty, " ", 0xFF);
            }
        }
    }
}
