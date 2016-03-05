#include "Word.h"
#include <iostream>

using namespace std;

Letter Word::allLeters[32];

Word::Word(string word)
{
	
	//letters = new Letter[word.length()];
	this->word = word;
	cout << "Total points: " << TotalPoints();
	
}
int Word::TotalPoints()
{
	int total = 0;
	for (int i = 0; i < word.length(); i++)
	{
		int j = 0;
		while (allLeters[j].GetSign() != word[i])
		{
			j++;
		}
		total += allLeters[j].GetPoints();

	}
	return total;
}