#include "WordController.h"
#include <iostream>
WordController::WordController(vector<Letter*>*exL)
{
	existLetters = exL;
	this->horizontal = false;
	this->vertical = false;
}

bool WordController::QuickCheck(Word * word)
{
	horizontal = false;
	vertical = false;
	sort(word->letters.begin(), word->letters.end(), Word::compareTwoLeters);
	for (int i = 0; i < word->letters.size() - 1; i++)
	{
		if (word->letters.at(i)->getPositionX() == word->letters.at(i + 1)->getPositionX())
		{
			vertical = true;
		}
		else
			vertical = false;
		if (word->letters.at(i)->getPositionY() == word->letters.at(i + 1)->getPositionY())
		{
			horizontal = true;
		}
		else
			horizontal = false;

	}
	if (!vertical && !horizontal)
		return false;
	else
		return true;

}
Word * WordController::CheckHorizontal(Field board[15][15], Letter * letter)
{
	return nullptr;
}
Word * WordController::CheckVertical(Field board[15][15], Letter * letter)
{
	Word * temp = new Word();
	int pos_x = letter->getPositionX();
	int pos_y = letter->getPositionY();
	Field * begin = GetField(board, pos_x, pos_y);
	while (GetLetterOnBoard(board, begin) != nullptr)
	{
		pos_y -= 40;
		begin = GetField(board, pos_x, pos_y);
	}

	pos_y += 40;
	begin = GetField(board, pos_x, pos_y);
	while (GetLetterOnBoard(board, begin) != nullptr)
	{
		temp->addLetter(GetLetterOnBoard(board, begin));
		cout << GetLetterOnBoard(board, begin)->GetSign();
		pos_y += 40;
		begin = GetField(board, pos_x, pos_y);
	}
	cout << endl;
	if (temp->letters.size() > 1)
		return temp;
	else
		return nullptr;
}
bool WordController::SolidTest(Field board[15][15], Word * word)
{
	Word * tempWord = new Word();

	if (horizontal)
	{
		int pos_x = word->letters[0]->getPositionX();
		int pos_y = word->letters[0]->getPositionY();
		Field * begin = GetField(board, pos_x, pos_y);
		while (GetLetterOnBoard(board, begin) != nullptr)
		{
			tempWord = CheckVertical(board, GetLetterOnBoard(board, begin));
			//cout << tempWord;
			pos_x += 40;
			begin = GetField(board, pos_x, pos_y);
		}
	}
	else if (vertical)
	{

	}

	delete tempWord;
	return false;
}
int WordController::CountPoints(Field board[15][15], Word * word)
{
	int points = 0;
	int premiaSlowa = 1;
	Field * temp;
	for (int i = 0; i < word->letters.size(); i++)
	{
		temp = GetBoardField(board,word->letters[i]);

		if (temp->bonus == "LiteraX2")
		{
			points += word->letters[i]->GetPoints() * 2;
		}
		else if (temp->bonus == "LiteraX3")
		{
			points += word->letters[i]->GetPoints() * 3;
		}
		else if (temp->bonus == "WyrazX2")
		{
			points += word->letters[i]->GetPoints();
			premiaSlowa *= 2;
		}
		else if (temp->bonus == "WyrazX3")
		{
			points += word->letters[i]->GetPoints();
			premiaSlowa *= 3;
		}
		else
		{
			points += word->letters[i]->GetPoints();
		}
	}
	points *= premiaSlowa;

	return points;
}
Field * WordController::GetField(Field board[15][15], int pos_x, int pos_y)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j].getPositionX() == pos_x && board[i][j].getPositionY() == pos_y)
			{
				return &board[i][j];
			}
		}

	}
	return nullptr;
}
Field * WordController::GetBoardField(Field board[15][15], Letter * letter)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (letter->getPositionX() == board[i][j].getPositionX() && letter->getPositionY() == board[i][j].getPositionY())
			{
				return &board[i][j];
			}
		}

	}
	return nullptr;
}
Letter * WordController::GetLetterOnBoard(Field board[15][15], Field * field)
{
	for (int i = 0; i < existLetters->size(); i++)
	{
		//cout << field->getPositionX() << " " << field->getPositionY()  << endl;
		//cout << existLetters->at(i)->getPositionX() << " " << existLetters->at(i)->getPositionY() << endl;
		if (field->getPositionX() == existLetters->at(i)->getPositionX() && field->getPositionY() == existLetters->at(i)->getPositionY())
		{
			return existLetters->at(i);
		}
	}
	return nullptr;
}

