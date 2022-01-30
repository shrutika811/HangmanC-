#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
void displayMessage(string m,bool topB=false,bool bottomB=false)
{
	if(topB)//spaces 10
	{
		cout<<"          !***********************************!"<<"\n";
		cout<<"          !";
    }
    else{
    	cout<<"          !";
	}
    
	bool space=true;
	
	for(int i=m.size();i<35;i++)//i<35 because that much characters can be displayed within this width of top border eg:hello(5) 35-5=30 15 spaces from left n 15 spaces from right
	{
		if(space)
		m=" "+m;
		
		else
		m=m+" ";
		space=!space;
	}
	cout<<m;
	
	if(topB){
			cout<<"!"<<"\n";
			cout<<"          !***********************************!"<<"\n";
	}
	else{
			cout<<"!"<<"\n";
	}
	
}
void hangman(int count_guess=0)
{
	if(count_guess>=1)
	displayMessage("|");
	else
	displayMessage("");
	
	if(count_guess>=2)
	displayMessage("|");
	else
	displayMessage("");
	
	if(count_guess>=3)
	displayMessage("|");
	else
	displayMessage("");
	
	if(count_guess>=4)
	displayMessage("O");
	else
	displayMessage("");
	
	if(count_guess==5)
	displayMessage("/");
	
	
	if(count_guess==6)
	displayMessage("/|");
	
	
	if(count_guess>=7)
	displayMessage("/|\\");
	else
	displayMessage("");
	
	if(count_guess>=8)
	displayMessage("|");
	else
	displayMessage(" ");
	
	if(count_guess==9)
	displayMessage("/");
	
	
	if(count_guess>=10)
	displayMessage("/ \\");
	else
	displayMessage("");
}
void printCharacters(string guessed,char from,char to)
{
	string s;
	for(char ch=from;ch<=to;ch++)
	{
		if(guessed.find(ch)!=string::npos)//checks if the letter is present in guessed string or not//string::npos is a constant static member deifned with value=-1 which means until end of string
		{
			s=s+"  ";
			continue;
		}
		
		s=s+ch;
		s=s+" ";
	}
	displayMessage(s,false,false);
}

void printAvailableCharacters(string guessed)
{
	displayMessage("Letters available for guesses",true,true);
	printCharacters(guessed,'A','M');
	printCharacters(guessed,'N','Z');
}

bool checkWin(string word,string guessed)
{
	string s;
	bool win=true;
	for(int i=0;i<word.size();i++)
	{
		if(guessed.find(word[i])==string::npos)
		{
		    s=s+"_ ";
		    win=false;
		}
		else{
		     s+=word[i];
	   	     s+=" ";
	   }
	}
	
	displayMessage(s,false,true);
	return win;
}
string LoadRandomWord(string path)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path.c_str());
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);
 
        int randomLine = rand() % v.size();//rand() selects any random line of word
 
        word = v.at(randomLine);//assigns the word at that position to guess
        reader.close();
    }
   
    return word;
}
int LeftTries(string wordToGuess,string guesses)
{
	int leftTry=0;
	for(int i=0;i<guesses.size();i++)
	{
		if(wordToGuess.find(guesses[i])==string::npos)
		leftTry++;
	}
	return leftTry;
}
int main()
{
	srand(time(0));//random number vary from each function call
	string guesses;//string of characters which have been guessed
	string wordToGuess;
	wordToGuess=LoadRandomWord("words.txt");

	int tries=0;
	bool win=false;
	do{
		system("cls");
		displayMessage("Hangman",true,true);
		hangman(tries);
		printAvailableCharacters(guesses);
		displayMessage("Guess The Word",true,true);
		win=checkWin(wordToGuess,guesses);
		
		if(win)
		break;
		
		char ch;
		cout<<"          >";
		cin>>ch;
		
		if(guesses.find(ch)==string::npos)
		guesses=guesses+ch;
		
		tries=LeftTries(wordToGuess,guesses);
	}while(tries<11);

      if(win)
        displayMessage("YOU WON!");
    else
        displayMessage("GAME OVER");
 
    system("pause"); 
    getchar();
	return 0;
}