#pragma once
#include "Framework/console.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

class Leaderboard
{
public:
	vector <string> ldb;
	void saverer(string);
	void sorterer();
};