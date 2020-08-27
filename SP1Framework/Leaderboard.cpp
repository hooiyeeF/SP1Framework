#include "Leaderboard.h"


void Leaderboard::saverer(string scor)
{
	ldb.push_back(scor);
}

void Leaderboard::sorterer()
{
	sort(ldb.begin(), ldb.end());
	if (ldb.size() > 1)
	{
		ldb.pop_back();
	}
}