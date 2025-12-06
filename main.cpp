#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct flashCard{
    string question;
    string answer;
};

bool isEmpty();//see if the flashCard file is empty
void readingFlashCard(vector<flashCard> &);//reading the flash card
void writingToFile(vector<flashCard>, ofstream);//writing flash card to file
void creatingFlashCard(vector<flashCard> &);//create new flashcard in the vector and add to the file with writingToFile
void useFlashCards(vector<flashCard>);//use the flash cards with random features

int main(){
    vector<flashCard> allFlashCards = {};
    string cardQuestion;
    string cardAnswer;

    string tempCardLine;

    //ask user for their selection
    //1. Use Flash cards
    //2. Make new flash card
    //3. Delete flash card
    cout << "What would you like to do?" << endl;
    cout << "1. Use flash card" << endl
         <<  "2. Make new flash card" << endl 
         << "3. Delete flash card" << endl;
    cout << "->(1,2,3)";

    int userChoice;
    cin >> userChoice;

    cout << "testing file reading" << endl;
    readingFlashCard(allFlashCards);
}

bool isEmpty(){
    ifstream readingFile;
    readingFile.open("flashCard.txt");
    string storingLine = "";

    if(!getline(readingFile, storingLine)){
        return true;
    }else{
        if(storingLine == "")
            return true;
        else
            return false;
    }
}

void readingFlashCard(vector<flashCard> &flashCardsStorage){
    ifstream readingFile;
    readingFile.open("flashCard.txt");
    string tempString;

    int currentIndex = 0;
    while(getline(readingFile, tempString)){
        if(tempString.substr(0, tempString.find('.')) == "Q"){
            flashCardsStorage.push_back(flashCard());
            flashCardsStorage[currentIndex].question = tempString;
            cout << flashCardsStorage[currentIndex].question << endl;
        }else{
            flashCardsStorage[currentIndex].answer = tempString;
            cout << flashCardsStorage[currentIndex].answer << endl;
        }
    }
}