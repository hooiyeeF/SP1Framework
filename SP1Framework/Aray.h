#pragma once
#include "Framework\console.h"

class Aray

{
public:
	char map[18][80];
	void FirstRoomArray(Console& g_console);      // First Room Array
	void SecondRoomArray(Console& g_console);     // Second Room Array
	void TPRoomArray(Console& g_console);         // TP Room Array
	void EndRoomArray(Console& g_console);        // End Room Array
	void guarddetectroom1a(Console& g_console);    // guard detection
	void guarddetectroom1b(Console& g_console);    // guard detection
	void guarddetectroom2(Console& g_console);    // guard detection
	void guarddetectroomTP(Console& g_console);    // guard detection
	void guarddetectroomEnd(Console& g_console);    // guard detection
	void removeguarda(Console& g_console);         // guard removal
	void removeguardb(Console& g_console);         // guard removal
	void removeguard2(Console& g_console);         // guard removal
	void removeguardTP(Console& g_console);         // guard removal
	void removeguardEnd(Console& g_console);         // guard removal
};