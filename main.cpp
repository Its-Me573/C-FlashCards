#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cctype>
#include <string>

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

int getUserInputInRange(int min, int max, string errorMessage, string inputMessage);
void createFlashCardFile();
bool isFileEmpty();
void loadFlashCardsFromFile(vector<flashCard> &flashCardsStorage);
void creatingFlashCard(vector<flashCard> &flashCardsStorage);
void writingToFile(const vector<flashCard> &flashCardsStorage);
int randomVectorIndex(vector<flashCard> flashCardsStorage);
void useFlashCards(vector<flashCard> flashCardsStorage);
void deleteFlashCard(vector<flashCard> &flashCardsStorage, int indexRemoved);
void printAllCards(const vector<flashCard> &flashCardsStorage);

int main(){
    vector<flashCard> flashCardsStorage;

    ifstream readingFlashCards("flashCards.txt");
    if(!readingFlashCards.is_open()){
        createFlashCardFile();
        readingFlashCards.open("flashCards.txt");
    }
    
    while(true){
        /**
        cout << "1. Create new flash card" << endl
             << "2. Delete Flash Card" << endl
             << "3. Print all flash cards" << endl
             << "4. Use flash cards" << endl
             << "5. Quit" << endl;
        **/

        //string tempStringSelection;
        int menuUserSelection = getUserInputInRange(1, 5, "Invalid selection!", "(1/2/3/4/5): ");
        
        
        
        
        
        /** 
        do{
            cout << "(1/2/3/4/5): ";
            getline(cin, tempStringSelection);
            
            if(tempStringSelection.size() > 1 || //check for 1 in length
               isalpha(tempStringSelection[0]) || //check if input is a character
               stoi(tempStringSelection.substr(0,1)) != 1 && 
               stoi(tempStringSelection.substr(0,1)) != 2 && 
               stoi(tempStringSelection.substr(0,1)) != 3 &&
               stoi(tempStringSelection.substr(0,1)) != 4 &&
               stoi(tempStringSelection.substr(0,1)) != 5){
                
                cout << "Invalid Selection!" << endl;
                continue;
            }
            menuUserSelection = stoi(tempStringSelection.substr(0,1));//set real int input
            break;
        }while(true);
        **/

        /**
        switch(menuUserSelection){// 1-4
            case 1:{//create new flash card
                creatingFlashCard(flashCardsStorage);
            } 
            case 2:{//delete flash card
                printAllCards(flashCardsStorage);
                do{//read the flash card to remove

                }while(true);

            }
            case 3:{//print all flash cards

            }
            case 4:{//Use Flash Cards

            }
            case 5:{//Quit
                return -1;
            }
        }
        **/

    }
}

int getUserInputInRange(int min, int max, string errorMessage, string inputMessage){//will return the valid number within the range, inclusive, "Message: "
    string tempStringStorage;
    cout << inputMessage;
    do{
            getline(cin, tempStringStorage);
            
            if(tempStringStorage.size() > 1 || 
               !isdigit(tempStringStorage[0]) || //is index a digit
               isalpha(tempStringStorage[0]) || //is digit a char
               (stoi(tempStringStorage.substr(0,1)) < min && 
               stoi(tempStringStorage.substr(0,1)) > max)){//is the int withing range
                
                cout << errorMessage << endl;
                continue;
            }
        }while(true);
}

void createFlashCardFile(){
    ofstream openingFile;
    openingFile.open("flashCards.txt");
    openingFile.close();
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

void loadFlashCardsFromFile(vector<flashCard> &flashCardsStorage){
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

void writingToFile(const vector<flashCard> &flashCardsStorage){
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
}

void printAllCards(const vector<flashCard> &flashCardsStorage){
    for(int i = 0; i < flashCardsStorage.size(); i++){
        cout << (i + 1) << ".) " << flashCardsStorage[i].question << endl;
    }
}