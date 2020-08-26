#include <iostream>
#include "Sound.h"
#include <Windows.h>
#include "resource.h"


using namespace std;

void sound::BGM()
{
	bool music = PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
}