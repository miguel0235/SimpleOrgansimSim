
#include "Tokenizer.h"
#include "Deque.h"

#include <fstream>
#include <iostream>  
#include <string>
#include <iomanip>


using std::ifstream;
using std::cin;
using std::cout;
using std::endl;


bool processText(istream& is, bool interactive = true)
{
	// implement support for 
	// exit ... exit the program
	// add string string ... concatenate two strings
	// add double double ... sum two integers
	// load file ... loads a file containing supported commands
	string line;
	string command;
	string arg1, arg2;
	int darg1;

	//The StomachSize and Total food for the organism
	//This only works because there will only be on organism 
	//at any given time. So we can just have the two variabls here
	//instead of within the List or something similar
	int StomachSize = 11;
	int TotalFood = 0;

	Deque D;


	Tokenizer tkn;

	while (true)
	{
		if (!interactive)
		{
			if (is.eof()) return true;
		}
		else { cout << ">> "; }

		getline(is, line);
		tkn.setString(line);

		tkn.readWord(command);
		if (command == "exit")
		{
			cout << "Exiting ...." << endl;
			return false;
		}
		if (command == "load")
		{
			// load expects a filename .. so read one more word
			if (!tkn.readWord(arg1)) {
				cout << "Missing file name" << endl;
				continue; // skip back to the top of the read loop
			}
			ifstream fin;
			bool status = true;
			fin.open(arg1);
			if (fin.is_open())
			{
				// keeping in mind the note about the definition for the processText fuction
																	// the following line of code is closer to
				// status = processText(fin, b, false);
				status = processText(fin, false);
			}
			else { cout << "Failed to open the file" << endl; }
			fin.close();
			if (!status) return false;
		}
		if (command == "eat")
		{
			tkn.readWord(arg1);
			if (arg1 == "seed")
			{
				//gets what the TotalFood would be after adding the new food to stomach
				int temp = TotalFood + 1;

				//Compares what the new Totalfood would be and if it's not more than 
				//stomach size than it can go in 
				if (temp <= StomachSize)
				{
					D.push_front(arg1, 1);
					TotalFood += 1;

					cout << arg1 << " has been eaten with a size of 1" << endl;
				}
				else
				{
					cout << "Not enough room in stomach" << endl;
				}
			}
			if (arg1 == "leaf")
			{
				//gets what the TotalFood would be after adding the new food to stomach
				int temp = TotalFood + 2;


				//Compares what the new Totalfood would be and if it's not more than 
				//stomach size than it can go in 
				if (temp <= StomachSize)
				{
					D.push_front(arg1,2);
					TotalFood += 2;

					cout << arg1 << " has been eaten with a size of 2" << endl;
				}
				else
				{
					cout << "Not enough room in stomach" << endl;
				}
			}
			if (arg1 == "grass")
			{
				//gets what the TotalFood would be after adding the new food to stomach
				int temp = TotalFood + 5;

				//Compares what the new Totalfood would be and if it's not more than 
				//stomach size than it can go in 
				if (temp <= StomachSize)
				{
					D.push_front(arg1, 5);
					TotalFood += 5;

					cout << arg1 << " has been eaten with a size of 5" << endl;
				}
				else
				{
					cout << "Not enough room in stomach" << endl;
				}
			}
		}
		if (command == "excrete")
		{
			string food;
			int size;

			//Peeks to get the Food item and size for stub responses/subtract 
			//from ammount in stomach
			D.peek_back(food, size);

			//makes sure the removal was successfull
			if (D.pop_back())
			{ 
				//stub responses
				cout << food << " has been excreted!" << endl;

				//resizes the ammount of food in stomach according to removal
				if (food == "seed")
					TotalFood -= size;
				if (food == "leaf")
					TotalFood -= size;
				if (food == "grass")
					TotalFood -= size;

			}
			else
				cout << "Failed to excrete :C" << endl;
		}
		if (command == "vomit")
		{
			string food;
			int size;

			D.peek_front(food, size);

			//makes sure the removal was successfull
			if (D.pop_front())
			{
				//stub responses
				cout << food << " has been vomited!" << endl;

				//resizes the ammount of food in stomach according to removal
				if (food == "seed")
					TotalFood -= size;
				if (food == "leaf")
					TotalFood -= size;
				if (food == "grass")
					TotalFood -= size;
			}
			else
				cout << "Failed to Vomit :C" << endl;
		}
		if (command == "clear")
		{
			//clears items, and resets the ammount in stomach
			D.~Deque();
			TotalFood = 0;

			//stub responses
			cout << "Stomach has been cleared" << endl;
		}
		if (command == "status")
		{
			//Just compares the ammount of food in stomach
			//and gives a status according to the ammount inside
			if (TotalFood == 0)
			{
				cout << "The Grasshopper is starving!" << endl;
				cout << "   Stomach Level- " << TotalFood << "/" << StomachSize << endl;
			}
			if (TotalFood == StomachSize)
			{
				cout << "The Grasshopper is Full!" << endl;
				cout << "   Stomach Level- " << TotalFood << "/" << StomachSize << endl;
			}
			if (TotalFood > 0 && TotalFood < (StomachSize/2))
			{
				cout << "The Grasshopper is still hungry!" << endl;
				cout << "   Stomach Level- " << TotalFood << "/" << StomachSize << endl;
			}
			if (TotalFood > (StomachSize / 2) && TotalFood < StomachSize)
			{
				cout << "The Grasshopper is Moderately Full!" << endl;
				cout << "   Stomach Level- " << TotalFood << "/" << StomachSize << endl;
			}
		}
		if (command == "display")
		{
			D.display(cout);
		}
		if (command == "resize")
		{
			//reads the command for size
			tkn.readInteger(darg1);

			//Empties Stomach
			D.~Deque();

			//Resize Stomach Size
			StomachSize = darg1;
		}
	}


}

void menu();
int main()
{
	menu();
	processText(cin);
	return 0;

}

void menu()
{
	cout << "Grasshopper Simulator" << endl;
	cout << "********Food*********" << endl;
	cout << "   Seed  -size 1" << endl;
	cout << "   Leaf  -size 2" << endl;
	cout << "   Grass -size 5" << endl;
	cout << "******Commands*******" << endl;
	cout << "eat <item>" << endl;
	cout << "excrete" << endl;
	cout << "vomit" << endl;
	cout << "clear" << endl;
	cout << "reize <size>" << endl;
	cout << "status " << endl;	
	cout << "display " << endl;
	cout << "exit" << endl;
	cout << "*********************" << endl;
}