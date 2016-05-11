#include "WordController.h"
#include <iostream>

WordController::WordController()
{
	this->horizontal = false;
	this->vertical = false;
	//cout << existLetters << endl;
}
bool WordController::CheckIfLetterExist(Word * word, Letter * letter)
{
	for (int i = 0; i < word->letters.size(); i++)
	{
		if (word->letters[i] == letter)
			return true;
	}
	return false;
}
bool WordController::QuickCheck(Field board[15][15], vector <Letter*>* existLetters, Word * word)
{
	//TO DO sprawdzenie sensu pierwszego worda
	horizontal = false;
	vertical = false;
	bool good = false;

	sort(word->letters.begin(), word->letters.end(), Word::compareTwoLeters);
	
	//Jezeli dostawiamy tylko jedna literke sprawdzamy czy sasiaduje ona z czyms
	if (word->letters.size() == 1)
	{
		int pos_x = word->letters[0]->getPositionX();
		int pos_y = word->letters[0]->getPositionY();
		Field * begin = GetField(board, existLetters, pos_x, pos_y);
		if (CheckVertical(board, existLetters, GetLetterOnBoard(board, existLetters, begin)) ||
			CheckHorizontal(board, existLetters, GetLetterOnBoard(board, existLetters, begin)))
			return true;
	}
	//Tutaj sprawdzamy czy podane slowo jest w jednej linii
	for (int i = 0; i < word->letters.size() - 1; i++)
	{
		if (word->letters.at(i)->getPositionX() == word->letters.at(i + 1)->getPositionX())
		{
			vertical = true;
		}
		else
		{
			if (vertical)
			{
				std::string excep = "Not at one line";
				throw excep;
			}
			vertical = false;
		}
		if (word->letters.at(i)->getPositionY() == word->letters.at(i + 1)->getPositionY())
		{
			horizontal = true;
		}
		else
		{
			if (horizontal)
			{
				std::string excep = "Not at one line";
				throw excep;
			}
			horizontal = false;
		}

	}

	if (!vertical && !horizontal)
	{
		std::string excep = "Not at one line or something";
		throw excep;
		return false;
	}
	else
	{
		return true;
	}

}

Word * WordController::CheckHorizontal(Field board[15][15], vector <Letter*>* existLetters, Letter * letter)
{
	Word * temp = new Word();
	int pos_x = letter->getPositionX();
	int pos_y = letter->getPositionY();
	Field * begin = GetField(board, existLetters, pos_x, pos_y);
	//Jedziemy najbardziej na lewo
	while (GetLetterOnBoard(board,existLetters, begin) != nullptr)
	{
		pos_x -= 40;
		begin = GetField(board, existLetters, pos_x, pos_y);
	}

	pos_x += 40;
	begin = GetField(board, existLetters, pos_x, pos_y);
	// Przechodzimy kolejno po literach w prawo
	while (GetLetterOnBoard(board, existLetters, begin) != nullptr)
	{
		temp->addLetter(GetLetterOnBoard(board, existLetters, begin));
		//cout << GetLetterOnBoard(board, existLetters, begin)->GetSign();
		pos_x += 40;
		begin = GetField(board, existLetters, pos_x, pos_y);
	}
	
	if (temp->letters.size() > 1)
		return temp;
	else
		return nullptr;
}
Word * WordController::CheckVertical(Field board[15][15], vector <Letter*>* existLetters, Letter * letter)
{
	Word * temp = new Word();
	int pos_x = letter->getPositionX();
	int pos_y = letter->getPositionY();
	Field * begin = GetField(board, existLetters, pos_x, pos_y);
	//Idziemy najbardziej do gory
	while (GetLetterOnBoard(board, existLetters, begin) != nullptr)
	{
		pos_y -= 40;
		begin = GetField(board, existLetters, pos_x, pos_y);
	}

	pos_y += 40;
	begin = GetField(board, existLetters, pos_x, pos_y);
	//Przechodzimy kolejno po literach w dol
	while (GetLetterOnBoard(board, existLetters, begin) != nullptr)
	{
		temp->addLetter(GetLetterOnBoard(board, existLetters, begin));
		pos_y += 40;
		begin = GetField(board, existLetters, pos_x, pos_y);
	}
	
	if (temp->letters.size() > 1)
		return temp;
	else
		return nullptr;
}
int WordController::SolidTest(Field board[15][15], vector <Letter*>* existLetters, Word * word)
{
	Word * tempWord = new Word();
	int totalPoints = 0;
	bool good = false;
	for (int i = 0; i < word->letters.size(); i++)
	{
		int pos_x = word->letters[i]->getPositionX();
		int pos_y = word->letters[i]->getPositionY();

		Letter * temp = GetLetterOnBoard(board, existLetters, GetField(board, existLetters, pos_x + 40, pos_y));
		Letter * temp2 = GetLetterOnBoard(board, existLetters, GetField(board, existLetters, pos_x - 40, pos_y));
		Letter * temp3 = GetLetterOnBoard(board, existLetters, GetField(board, existLetters, pos_x, pos_y + 40));
		Letter * temp4 = GetLetterOnBoard(board, existLetters, GetField(board, existLetters, pos_x, pos_y - 40));
		
		// Sprawdzamy czy litera ma jakis sasiadow
		if (temp == nullptr && temp2 == nullptr && temp3 == nullptr && temp4 == nullptr)
		{
			std::string excep = "Alone Letter";
			throw excep;
		}

		// Jezeli jednak cos wystepuje kolo tej litery i nie jest to litera z tego slowa
		if ((temp != nullptr && !CheckIfLetterExist(word, temp)) || (temp2 != nullptr && !CheckIfLetterExist(word, temp2)) ||
			(temp3 != nullptr && !CheckIfLetterExist(word, temp3)) || (temp4 != nullptr && !CheckIfLetterExist(word, temp4)))
		{
			good = true;
		}
		
	}
	if (!good)
	{
		std::string excep = "Slowo nie laczy sie z juz istniejacym";
		throw excep;
	}

	if (horizontal)
	{
		for (int i = 0; i < word->letters.size(); i++)
		{
			int pos_x = word->letters[i]->getPositionX();
			int pos_y = word->letters[i]->getPositionY();
			Field * begin = GetField(board, existLetters, pos_x, pos_y);

			tempWord = CheckVertical(board, existLetters, GetLetterOnBoard(board, existLetters, begin));

			if (tempWord != nullptr)
			{
				wordForCheck.push_back(tempWord);
			}
			if(tempWord != nullptr)
				if (tempWord->letters.size() > 1)
				{
					cout << "\n PUNKTY: " << CountPoints(board, existLetters, tempWord);
					totalPoints += CountPoints(board, existLetters, tempWord);
				}
		}

		int pos_x = word->letters[0]->getPositionX();
		int pos_y = word->letters[0]->getPositionY();
		Field * begin = GetField(board, existLetters, pos_x, pos_y);
		tempWord = CheckHorizontal(board, existLetters, GetLetterOnBoard(board, existLetters, begin));
		if (tempWord != nullptr)
		{
			wordForCheck.push_back(tempWord);
		}
		if (tempWord != nullptr)
			if (tempWord->letters.size() > 1)
			{
				cout << "\n PUNKTY: " << CountPoints(board, existLetters, tempWord);
				totalPoints += CountPoints(board, existLetters, tempWord);
			}
	}
	else if (vertical)
	{
		for (int i = 0; i < word->letters.size(); i++)
		{
			int pos_x = word->letters[i]->getPositionX();
			int pos_y = word->letters[i]->getPositionY();
			Field * begin = GetField(board, existLetters, pos_x, pos_y);

			tempWord = CheckHorizontal(board, existLetters, GetLetterOnBoard(board, existLetters, begin));
			if (tempWord != nullptr)
			{
				wordForCheck.push_back(tempWord);
			}
			if (tempWord != nullptr)
				if (tempWord->letters.size() > 1)
				{
					cout << "\n PUNKTY: " << CountPoints(board, existLetters, tempWord);
					totalPoints += CountPoints(board, existLetters, tempWord);
				}

		}

		int pos_x = word->letters[0]->getPositionX();
		int pos_y = word->letters[0]->getPositionY();
		Field * begin = GetField(board, existLetters, pos_x, pos_y);
		tempWord = CheckVertical(board, existLetters, GetLetterOnBoard(board, existLetters, begin));
		if (tempWord != nullptr)
		{
			wordForCheck.push_back(tempWord);
		}
		if (tempWord != nullptr)
			if (tempWord->letters.size() > 1)
			{
				cout << "\n PUNKTY: " << CountPoints(board, existLetters, tempWord);
				totalPoints += CountPoints(board, existLetters, tempWord);
			}

		
	}
	else //Czyli w przypadku gdy dostawiamy pojednycza literke
	{
		int pos_x = word->letters[0]->getPositionX();
		int pos_y = word->letters[0]->getPositionY();
		Field * begin = GetField(board, existLetters, pos_x, pos_y);
		tempWord = CheckVertical(board, existLetters, GetLetterOnBoard(board, existLetters, begin));
		if (tempWord != nullptr)
		{
			wordForCheck.push_back(tempWord);
		}
		if (tempWord != nullptr)
			if (tempWord->letters.size() > 1)
			{
				cout << "\n PUNKTY: " << CountPoints(board, existLetters, tempWord);
				totalPoints += CountPoints(board, existLetters, tempWord);
			}
		tempWord =  CheckHorizontal(board, existLetters, GetLetterOnBoard(board, existLetters, begin));
		if (tempWord != nullptr)
		{
			wordForCheck.push_back(tempWord);
		}
		if (tempWord != nullptr)
			if (tempWord->letters.size() > 1)
			{
				cout << "\n PUNKTY: " << CountPoints(board, existLetters, tempWord);
				totalPoints += CountPoints(board, existLetters, tempWord);
			}
	}

	//delete tempWord;
	return totalPoints;
}
int WordController::CountPoints(Field board[15][15], vector <Letter*>* existLetters, Word * word)
{
	int points = 0;
	int premiaSlowa = 1;
	Field * temp;
	if (word == nullptr)
		return 0;
	for (int i = 0; i < word->letters.size(); i++)
	{
		temp = GetBoardField(board, existLetters, word->letters[i]);

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
Field * WordController::GetField(Field board[15][15], vector <Letter*>* existLetters, int pos_x, int pos_y)
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
Field * WordController::GetBoardField(Field board[15][15], vector <Letter*>* existLetters, Letter * letter)
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
Letter * WordController::GetLetterOnBoard(Field board[15][15], vector <Letter*>* existLetters, Field * field)
{
	if (field == nullptr)
		return nullptr;
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

