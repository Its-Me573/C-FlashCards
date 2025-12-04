#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

struct flashCard{
    string question;
    string answer;
};
int main(){
    //read from the saved flash card files
    //i need a text file that stores the current files. 
    //probably having a file that i can read from and write to
    
    //make a vector that hold all of the struct flashcards
    vector<flashCard> allFlashCards = {};

    //ask user to make flash cards and store into strings
    string cardQuestion;
    string cardAnswer;

    //test to see if you can read and write to the same file. write to it first
    //read the first line question, read the 2nd line answer, read the third line which is empty indicating a new card. 
    //if the line after that one is still empty, the file is over

    ifstream readingFromCards;
    readingFromCards.open("flashCard.txt");
    if(readingFromCards.is_open()){
        cout << "Its working" << endl;
    }

    ofstream writingToCards;
    writingToCards.open("flashCard.txt");
    if(writingToCards.is_open()){
        cout << "Its also working" << endl;
    }

    cout << "Write the flash card question: ";
    getline(cin, cardQuestion);
    cout << "Write the flash card answer: ";
    getline(cin, cardAnswer);

    writingToCards << cardQuestion << endl;

    string readFrom;
    if(getline(readingFromCards, readFrom))
        cout << "reading worked, awesome, =)" << endl;
    else 
        cout << "reading didnt work, =(" << endl;

}