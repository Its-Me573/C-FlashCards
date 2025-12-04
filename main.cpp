#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct flashCard{
    string question;
    string answer;
};

bool isEmpty();
void readingFlashCard(vector<flashCard> &);
void writingFlashCards(vector<flashCard>);

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
    //expects valid file
    ifstream readingFile;
    readingFile.open("flashCard.txt");

    string storedLine;
    int currentIndex = 0;
    while(getline(readingFile, storedLine)){
        //check for "Q." or "A." in the file
        flashCardsStorage.push_back(flashCard());
        if(storedLine.substr(0,'.') == "Q"){
            //energy and mineral resources will have 14-20 questions
            flashCardsStorage[currentIndex].question = storedLine.substr(storedLine.find('.') + 1);
        }else if(storedLine.substr(0, '.') == "A"){
            flashCardsStorage[currentIndex].answer = storedLine.substr(storedLine.find('.') + 1);
        }
        currentIndex++;
    }
}