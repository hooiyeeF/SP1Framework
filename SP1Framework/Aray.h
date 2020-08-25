#pragma once
#include "Framework\console.h"

class Aray

{
public:
	char map[18][80];
	void FirstRoomArray(Console& g_console);      // First Room Array
	void ThirdRoomArray(Console& g_console);     // Third Room Array
	void TPRoomArray(Console& g_console);         // TP Room Array
	void EndRoomArray(Console& g_console);        // End Room Array
	void CRoomArray(Console& g_console);
	void guarddetect(Console& g_console, int gx, int gy);    // guard detection
	void removeguard(Console& g_console, int gx, int gy);	 // remove guards

};