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
        //add logic to check for an empty file, keep content in file if not empty

        cout << "1. Create new flash card" << endl
             << "2. Delete Flash Card" << endl
             << "3. Print all flash cards" << endl
             << "4. Use flash cards" << endl
             << "5. Quit" << endl;

        int menuUserSelection = getUserInputInRange(1, 5, "(1/2/3/4/5): ", "Invalid selection!\n");        
        

        if(!isFileEmpty()){
            loadFlashCardsFromFile(flashCardsStorage);
        }
        switch(menuUserSelection){// 1-4
            case 1:{//create new flash card
                if(isFileEmpty()){//if the array is empty
                    creatingFlashCard(flashCardsStorage);
                    writingToFile(flashCardsStorage);
                }else{
                    creatingFlashCard(flashCardsStorage);
                    writingToFile(flashCardsStorage);
                }
                break;
            } 
            case 2:{//delete flash card
                if(isFileEmpty()){
                    cout << "There are no flash cards to delete" << endl << endl;
                }else{
                    printAllCards(flashCardsStorage);
                    int flashCardBeingDeleted = getUserInputInRange(1, flashCardsStorage.size(), "What flash card would you like to delete: ", "Invalid Selection");
                    deleteFlashCard(flashCardsStorage, flashCardBeingDeleted);
                    writingToFile(flashCardsStorage);
                }
                break;
            }
            case 3:{//print all flash cards
                //if there are no flash cards, say there arent and ask user if they want to make any
                if(isFileEmpty()){
                    cout << "There are no flash cards to print" << endl << endl;
                }else{
                    printAllCards(flashCardsStorage);
                }
                break;
            }
            case 4:{//Use Flash Cards
                //if there arent any flashcards, prompt the user with the error and prompt that they need to make some
                if(isFileEmpty()){
                    cout << "There are no flash cards to use." << endl << endl;
                }else{
                    loadFlashCardsFromFile(flashCardsStorage);
                    useFlashCards(flashCardsStorage);
                }
                break;
            }
            case 5:{//Quit
                break;
            }
        }
    }
}

int getUserInputInRange(int min, int max, string inputMessage, string errorMessage){//will return the valid number within the range, inclusive, "Message: "
    string tempStringStorage;
    int returningValidInt;
    do{
            cout << inputMessage;
            getline(cin, tempStringStorage);
            
            if(tempStringStorage.size() > 1 || 
               !isdigit(tempStringStorage[0]) || //is index a digit
               isalpha(tempStringStorage[0]) || //is digit a char
               (stoi(tempStringStorage.substr(0,1)) < min || 
               stoi(tempStringStorage.substr(0,1)) > max)){//is the int withing range
                
                cout << errorMessage << endl;
                continue;
            }
            returningValidInt = stoi(tempStringStorage.substr(0,1));
            break;
        }while(true);
    return returningValidInt;
}

void createFlashCardFile(){
    ofstream openingFile;
    openingFile.open("flashCards.txt");
    openingFile.close();
}

bool isFileEmpty(){
    ifstream readingFile;
    readingFile.open("flashCards.txt");
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
    readingFile.open("flashCards.txt");
    string tempString;
    
    vector<flashCard> tempVector;
    int currentIndex = 0;
    while(getline(readingFile, tempString)){
        if(tempString.substr(0, tempString.find('.')) == "Q"){
            tempVector.push_back(flashCard());
            tempVector[currentIndex].question = tempString.substr(tempString.find('.') + 1);
        }else if(tempString.substr(0, tempString.find('.')) == "A"){
            tempVector[currentIndex].answer = tempString.substr(tempString.find('.') + 1);
            currentIndex++;
        }
    }
    flashCardsStorage = tempVector;
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
    cout << endl;
}

void writingToFile(const vector<flashCard> &flashCardsStorage){
    ofstream writingFile;
    writingFile.open("flashCards.txt");

    for(int i = 0; i < flashCardsStorage.size(); i++){
        writingFile << "Q." << flashCardsStorage[i].question << endl;
        writingFile << "A." << flashCardsStorage[i].answer << endl;
    }
    writingFile.close();
}
//to do: if the current random was the previous random index, make a new index
// until soemthing differnet shows up
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
    cout << endl;
}