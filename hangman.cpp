#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <boost/algorithm/string.hpp>

using namespace std;

int main(int argc, char **argv)

{

	const int MAX_WRONG = 8;

	vector<string> words;
	words.push_back("HANGMAN");
	words.push_back("COMPLICATED");
	words.push_back("HELLO");

	srand(static_cast<unsigned int>(time(0)));
	random_shuffle(words.begin(), words.end());
	const string THE_WORD = words[0];
	int wrong = 0;
	string soFar(THE_WORD.size(), '-');
	string used = "";

	cout << "\t\t\tWelcome to Hangman!";
	cout<<"\n\t\t\t-------------------\n\n";
	cout<<"You have exactly " <<(MAX_WRONG - wrong)<< " guesses, goodluck!";


	while ((wrong < MAX_WRONG) && (soFar != THE_WORD))
	{
		cout << "\nYou've used the following letters:\n" << used << endl;
		cout << "So far, the word is: " << soFar << endl;

		char guess;
		cout << "\n\nEnter your guess: ";
		cin >> guess;
		guess = toupper(guess); //make uppercase since secret word in uppercase

        	while (used.find(guess) != string::npos)
        	{
            		cout << "\nYou've already guessed " << guess << endl;
			cout << "Enter your guess: ";
			cin >> guess;
			guess = toupper(guess);
		}

		used += guess;

		if (THE_WORD.find(guess) != string::npos)
		{
			cout << "That's right! " << guess << " is in the word.\n";
				for (unsigned int i = 0; i < THE_WORD.length(); ++i)
				{
					if (THE_WORD[i] == guess)
							{
						soFar[i] = guess;
							}
				}
		}
		else
		{
			++wrong;
			cout << "Sorry, " << guess << " isn't in the word.\n";
			cout<<"You have " <<(MAX_WRONG - wrong)<< " guesses left.\n";
		}
	}

	if (wrong == MAX_WRONG)
	{
		cout << "Game over, you've been hanged!";
	}
	else
	{
		cout << "Congratulation! You've successfully guessed the secret word!";
	}

	cout << "\nThe word was " << THE_WORD<<"\n\n";

	// Rate the game :)
	int rate;
	cout<<"Please take a moment of your time and rate the game\n";
	cout<<"1 - It was fun!\n";
	cout<<"2 - It was ok\n";
	cout<<"3 - It was bad\n";
	cout<<"Your rating: ";
	cin>>rate;

	switch (rate)	// easier rating system
	{
		case 1: cout<<"We are so glad to hear that! thanks for the positive feedback!\n"; break;
		case 2: cout<<"We'll do better next time, thanks for your feedback!\n"; break;
		case 3: cout<<"We are terribly sorry about that, we'll do better next time\n"; break;
		default: cout<<"Haha funny ;)\n"; break;
	}

/*	if (rate == 1) {
		cout<<"\nWe are so glad to hear that! thanks for the positive feedback!\n" << endl;
	}
	else if (rate == 2) {
		cout<<"\nWe'll do better next time, thanks for your feedback!\n" << endl;
	}
	else if (rate == 3) {
		cout<<"\nWe are terribly sorry about that, we'll do better next time\n" << endl;
	}
	else {
		cout<<"\nHaha, you're funny.\n" << endl;
	}*/

	cout<<"Do you want to remove this game? Y/N ";

	// declare strings...
	string removal;
	string removal_long = "yes";
	string removal_short = "y";

	cin>>removal;

	// case insensitive string comparing
	if (boost::iequals(removal, removal_long) || boost::iequals(removal, removal_short) ) {
		cout<<"\nOk =( removing the file..." << endl << endl;
		remove(argv[0]); // remove the file
	}

	system("echo 'bye bye :*'"); // system
	return 0;
}
