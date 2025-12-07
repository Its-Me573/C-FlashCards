#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using std::vector;
using std::string;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::getline;
using std::cin;

struct flashCard{
    string question;
    string answer;
};

bool isFileEmpty();
void readingFlashCard(vector<flashCard> &);
void creatingFlashCard(vector<flashCard> &);
void writingToFile(vector<flashCard> &);
int randomVectorIndex(vector<flashCard>);
void useFlashCards(vector<flashCard>);

int main(){
    vector<flashCard> allFlashCards;
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
        cout << allFlashCards[i].answer << endl;
    }
    
}

bool isFileEmpty(){
    ifstream readingFile;
    readingFile.open("flashCard.txt");
    string storingLine = "";

    if(!getline(readingFile, storingLine)){
        return true;
    }else{
        if(storingLine == ""){
            readingFile.close();
            return true;
        }
        else{
            readingFile.close();
            return false;
        }
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

int randomVectorIndex(vector<flashCard> flashCardsStorage){
    int randomIndex;
    std::random_device rand_dev;//creates random seed
    std::mt19937 generator(rand_dev());//seed is input into the generator
    std:: uniform_int_distribution<int> distr(0, flashCardsStorage.size() - 1);

    randomIndex = distr(generator);
    return randomIndex;
}


