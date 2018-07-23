#include <iostream>
#include "CircularLinkedList.h"
#include "TopSpin.h"
using namespace std;

void menu();
int main()
{

	TopSpin Board;

	Board.FillBoard(); //Fill the board in order 
//template <class T>
	cout << Board; 
	
	int numMoves(0);
	cout << "Shuffle the board. Enter the number of random moves: ";
	cin >> numMoves; //let user select number of random moves 

	Board.Shuffle(numMoves); //shuffle the board 
	cout << Board;
	
	for (int i = 0; i < 1; i++)
	{
		menu(); //Display options
		int choice(0); 
		cout << "Select a move: ";
		cin >> choice; //Let user select move 
		if (choice == 1) //if shift is selected, allow user to shift either right or left 
		{
			cout << "1. Shift Left \n2. Shift Right \n3. Quit\n";
			cin >> choice;
			int numShifts(0);
			cout << "Enter the number of shifts you would like to perform: ";
			cin >> numShifts;
			if (choice == 1)
				Board.shiftLeft(numShifts);
			else if (choice == 2)
				Board.shiftRight(numShifts);
			else //if neither of the options are selected, quit the game
			{
				++i; //increase i to break out of loop 
				cout << "Thanks for Playing \n";
			}

			
		}
		else if (choice == 2) //spin
			Board.spin();
		else
		{
			++i;
			cout << "Thanks for Playing \n";
		}

		if (!Board.isSolved()) //After each move, check to see if the obard is solved
			//if false (not solved), decrement i to enter the loop again 
		{
			cout << Board;
			i--;
		}

	}
	return 0;
}

//Board.isSolved();
////Board.Display();
//Board.spin();
////Board.Display();
//cout << Board;
//cout << endl;
////Board.spin();
//Board.Shuffle(7);
////cout << endl << "board has been shuffled" << endl;
////Board.Display();
////Board.Display();
//cout << endl << endl;
////Board.Display(1);
//Board.isSolved();
//cout << endl << endl;

void menu()
{
	cout << "1. Shift \n2. Spin \n3. Quit\n";
}