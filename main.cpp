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
void creatingFlashCard(vector<flashCard> &);//create new flashcard in the vector and add to the file with writingToFile
void writingToFile(vector<flashCard> &);//writing flash card to file
void useFlashCards(vector<flashCard>);//use the flash cards with random features

int main(){
    vector<flashCard> allFlashCards;
    string cardQuestion;
    string cardAnswer;

    string tempCardLine;

    //ask user for their selection
    //1. Use Flash cards
    //2. Make new flash card
    //3. Delete flash card
    /**
    cout << "What would you like to do?" << endl;
    cout << "1. Use flash card" << endl
         <<  "2. Make new flash card" << endl 
         << "3. Delete flash card" << endl;
    cout << "->(1,2,3)";

    string userChoice;
    getline(cin, userChoice);
    int optionSeleceted = stoi(userChoice);
    **/
    readingFlashCard(allFlashCards);
    creatingFlashCard(allFlashCards);
    writingToFile(allFlashCards);
    
    
    for(int i = 0; i < allFlashCards.size(); i++){
        cout << allFlashCards[i].question << endl;
        cout << allFlashCards[i].question << endl;
    }
    
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
            flashCardsStorage[currentIndex].question = tempString.substr(tempString.find('.') + 1);
        }else{
            flashCardsStorage[currentIndex].answer = tempString.substr(tempString.find('.') + 1);
            currentIndex++;
        }
    }
}

void creatingFlashCard(vector<flashCard> &flashCardsStorage){
    //ask use for 2 strings of flash cards
    flashCardsStorage.push_back(flashCard());
    string flashCardHolder;
   
    cout << "Write your question: ";
    getline(cin, flashCardHolder);
    flashCardsStorage[flashCardsStorage.size() - 1].question = flashCardHolder;

    cout << "Write the answer: ";
    getline(cin, flashCardHolder);
    flashCardsStorage[flashCardsStorage.size() - 1].answer = flashCardHolder;
}

void writingToFile(vector<flashCard> &flashCardsStorage){
    ofstream writingFile;
    writingFile.open("flashCard.txt");

    for(int i = 0; i < flashCardsStorage.size(); i++){
        writingFile << "Q." << flashCardsStorage[i].question << endl;
        writingFile << "A." << flashCardsStorage[i].answer << endl;
    }
}