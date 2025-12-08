#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cctype>

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
void readingCardFile(vector<flashCard> &);
void creatingFlashCard(vector<flashCard> &);
void writingToFile(vector<flashCard> &);
int randomVectorIndex(vector<flashCard>);
void useFlashCards(vector<flashCard>);
void deleteFlashCard(vector<flashCard> &, int);
void printAllCards(vector<flashCard>);

int main(){
    vector<flashCard> flashCardsHolder;
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

void readingCardFile(vector<flashCard> &flashCardsStorage){
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
    readingFile.close();
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
    writingFile.close();
}

int randomVectorIndex(vector<flashCard> flashCardsStorage){
    int randomIndex;
    std::random_device rand_dev;//creates random seed
    std::mt19937 generator(rand_dev());//seed is input into the generator
    std:: uniform_int_distribution<int> distr(0, flashCardsStorage.size() - 1);

    randomIndex = distr(generator);
    return randomIndex;
}

void useFlashCards(vector<flashCard> flashCardsStorage){
    bool firstRun = true;
    while(true){
        if(firstRun){
            cout << "Press enter to use flash cards, press 'q' to quit: ";
            firstRun = false;
        }else{
            cout << "q/enter: ";
        }
        string userInput = "";
        getline(cin, userInput);
        
        if(std::tolower(userInput[0]) == 'q'){
            return;
        }

        int currentRandomIndex = randomVectorIndex(flashCardsStorage);
        cout << flashCardsStorage[currentRandomIndex].question << endl;
        cout << "Press enter to show answer";
        string tempContinue;
        getline(cin, tempContinue);
        cout << flashCardsStorage[currentRandomIndex].answer << endl;
    }
    
}

void deleteFlashCard(vector<flashCard> &flashCardsStorage, int indexRemoved){
    flashCardsStorage.erase(flashCardsStorage.begin() + (indexRemoved - 1));
    writingToFile(flashCardsStorage);
}

void printAllCards(vector<flashCard> flashCardsStorage){
    for(int i = 0; i < flashCardsStorage.size(); i++){
        cout << (i + 1) << ".) " << flashCardsStorage[i].question << endl;
    }
}
