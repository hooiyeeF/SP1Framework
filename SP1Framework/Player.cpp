#include "Player.h"

void Player::draw(Console& g_console)
{
	COORD c;
	c.X = x;
	c.Y = y;
	WORD charColor = 0x0F;
	g_console.writeToBuffer(c, (char)1, charColor);
}