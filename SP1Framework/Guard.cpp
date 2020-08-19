
#include "Framework\console.h"
#include "Guard.h"


void Guard::drawG1(Console& g_console)
{
	COORD c;
	c.X = 50;
	c.Y = 6;
	WORD charColor = 0x0c;
	g_console.writeToBuffer(c, (char)1, charColor);
};

void Guard::drawG2(Console& g_console)
{
	COORD c;
	c.X = 50;
	c.Y = 6;
	WORD charColor = 0x0c;
	g_console.writeToBuffer(c, (char)1, charColor);
};

void Guard::drawG3(Console& g_console)
{
	COORD c;
	c.X = 50;
	c.Y = 6;
	WORD charColor = 0x0c;
	g_console.writeToBuffer(c, (char)1, charColor);
};