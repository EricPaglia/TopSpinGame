#pragma once
#include <iostream>
#include <ctime>

#include "CircularLinkedList.h"
class TopSpinADT {
public:
	// shifts the pieces 1 to the left
	virtual void shiftLeft(int n) = 0;
	//shifts the pieces 1 to the right
	virtual void shiftRight(int n) = 0;
	//reverses the pieces in the spin mechanism, IE if the 4 in the mechanism are
	// 1,4,3,6 we will have 6,3,4,1
	virtual void spin() = 0;
	//checks to see if the puzzle is solved that is to say the pieces are in numerical order 1 - 20
	virtual bool isSolved() = 0;
};



class TopSpin :public TopSpinADT
{
private:

	LinkedList <int> board;
	int _Size;
	int _spinSize;
	int *index;
	int _index;


public:

	TopSpin(int size = 20, int spinSize = 4) //constructor
	{
		if (size < 0 || spinSize > size) //Check to see if user selected board is valid 
			//if invalid, use default values 
		{
			std::cout << "Invalid parameters. Using default board \n";
			size = 20;
			spinSize = 4;
		}
		_Size = size;
		_spinSize = spinSize;
		index = new int[size];
		_index = 1;
		std::cout << "Constructor \n";

		//std::ostream& operator<< (std::ostream& os, const TopSpin& ts);
	}

	~TopSpin() // destructor
	{

	}

	// shifts the pieces 1 to the left
	void shiftLeft(int n);
	//shifts the pieces 1 to the right
	void shiftRight(int n);
	//reverses the pieces in the spin mechanism, IE if the 4 in the mechanism are
	// 1,4,3,6 we will have 6,3,4,1
	void spin();
	//checks to see if the puzzle is solved that is to say the pieces are in numerical order 1 - 20
	bool isSolved();

	void FillBoard();
	void Display() const;
	void Shuffle(int n);

	friend std::ostream& operator<< (std::ostream& os, const TopSpin &top) { //Overloaded print operator 
		top.Display();
		return os;
	}

};

void TopSpin::FillBoard()
{

	for (int i = 0; i < _Size; i++)
	{
		board.addTail(i + 1); //using addTail instead of addHead so list is increasing order 
		index[i] = i + 1;
	}





	/*do
	{
	std::cout << k.getValue() << " ";
	++k;


	} while (k != board.begin());*/

}

void TopSpin::shiftLeft(int n = 1)
{
	_index-=n; //Decrease index by number of shifts n
	if (_index < 1)
	{
		_index += _Size;
	}

}

void TopSpin::shiftRight(int n = 1)
{
	_index+=n; //increase index by number of shifts n
	if (_index > _Size)
	{
		_index -= _Size;
	}
}

void TopSpin::spin()
{

	int temp(0);
	int low(0), high(0);
	int newIndex = _index;
	//std::cout << "\n newIndex is: " << newIndex << "\n";
	
	//_Size % 2 != 0
	if (false) //If number is odd, perform one less swap to avoid swapping the same number in the end
	{
		for (int i = 0; i < (_spinSize - 1) / 2; i++)
		{
			newIndex = _index + i;
			
			low = board.retrieve(newIndex); //Retrieve the low value

			temp = _index + _spinSize - i - 1; //Position of high value

			if (temp > _Size)
				temp -= _Size;

			high = board.retrieve(temp); //revtreiving high value

			board.replace(_index + i, high);
			board.replace(high, low);
		}

	}
	else
	{
		//std::cout << "LowPosition is: " << LowPosition << "\n";
		for (int i = 0; i < _spinSize / 2; i++)
		{
			newIndex = _index + i;
			if (newIndex > _Size)
				newIndex -= _Size;
			low = board.retrieve(newIndex); //Retrieve the low value

			temp = _index + _spinSize - i - 1; //Position of high value

			if (temp > _Size)
				temp -= _Size;

			high = board.retrieve(temp); //revtreiving high value

			board.replace(newIndex, high);
			board.replace(temp, low);
		}

	}

	//Use Replace and Retrieve

}

bool TopSpin::isSolved()
{
	int current(0), next(0);
	for (int i = 0; i < _Size - 1; i++)
	{
		current = board.retrieve(i + 1);//Start 
		next = board.retrieve(i + 2);//following value 
		if (current != (next - 1))
			//if one of the numbers is not in order return false (game not solved) 
		{
			//std::cout << "\nSorry not Solved\n";
			return false;
		}
	}

	std::cout << "\n Congratz!\n";
	return true;
}

void TopSpin::Display() const
{
	//std::cout << "Index : " << _index << "\n";
	std::cout << "-----------\n";
	std::cout << "| ";
	LinkedList<int>::Iterator k = board.begin() ;
	//Using iterator to print the list 
	
	for (int i = 0; i < _index - 1; i++) //Find the starting node 
	{
		++k;
	}

	for (int i = 0; i < _Size; i++) //print from the starting node 
	{
		std::cout << k.getValue() << " ";
		if (i == 3)
			std::cout << "| ";
		++k;
	}
	
	std::cout << "\n-----------\n";

	
}


void TopSpin::Shuffle(int n)
{
	// n is the number of moves 


	if (_Size > 1)
	{
		for (int i = 0; i < n; i++) 
		{
			srand(time(NULL));//seeding rand
			int dir = rand() % 2; //Random number between --> either 0 or 1
				//dir is direction of shift
			int numShifts = rand() % 19 + 1; //Random number between 1 and 19 --> determines number of shifts

			if (dir > 0)
				shiftRight(numShifts);
			else
			{
				shiftLeft(numShifts);
			}

			spin();

			//Display();
		}
	}

	/*if (_Size > 1)
	{
		size_t i;
		srand(time(NULL));
		for (i = 0; i < _Size - 1; i++)
		{
			size_t j = i + rand() / (RAND_MAX / (_Size - i) + 1);
			int t = index[j];
			index[j] = index[i];
			index[i] = t;
		}
	}*/

}



//std::ostream& operator<< (std::ostream& os, const TopSpin& ts)
//{
//	//TopSpin::Display();
//
//	return os;
//}
//TopSpin a;
//cout << a;