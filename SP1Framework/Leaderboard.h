#pragma once
#include "Framework/console.h"
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

class Leaderboard
{
public:
	vector <int> lb;
	void saverer(double);
	void sorterer();
};