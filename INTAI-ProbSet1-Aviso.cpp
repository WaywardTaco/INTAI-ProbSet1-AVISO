
#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

queue<string> readFile (string filename);
void processGame(queue<string> inputQueue);
void queryGame(stack<int> gameStack, int queryCount, int playerScore);
void checkClears(stack<int>* gameStack, int* playerScore);

int main() {

    string inputString;
    queue<string> inputQueue;
    char inputChar;

read_file:

    cout << "Enter Filename: ";
    cin >> inputString;

    inputQueue = readFile(inputString);

    if(inputQueue.empty())
        goto read_file;

    processGame(inputQueue);

    cout << "=== INPUT FINISHED ===" << endl << endl;

    cout << "Would you like to read another file? [Y/N]: ";
    cin >> inputChar;
    cout << endl;

    if(inputChar == 'Y' || inputChar == 'y')
        goto read_file;

    cout << "Exiting application..." << endl;

    return 0;
};

queue<string> readFile (string filename){
    queue<string> inputQueue;
    string inputString;

    fstream file;
    file.open(filename);

    cout << "Reading " << filename << "..." << endl;

    if(!file.good()){
        cout << "Could not read file!" << endl;
        file.close();
        return inputQueue;
    }

    cout << endl;

    while(!file.eof() && inputString != "END"){
        getline(file, inputString);
        inputQueue.push(inputString);
    }

    file.close();

    return inputQueue;
};

void processGame(queue<string> inputQueue){
    stack<int> gameStack;
    int 
        queryCount = 0,
        playerScore = 0,
        length = inputQueue.size()
    ;

    for(int i = 0; i < length; i++){
        if(inputQueue.front() == "END" || inputQueue.front() == "end")
            break;

        if(inputQueue.front() == "Q" || inputQueue.front() == "q"){
            queryGame(gameStack, ++queryCount, playerScore);
            inputQueue.pop();
            continue;
        }

        int 
            pieceLength = inputQueue.front().size()
        ;

        for(int j = 0; j < pieceLength; j++){
            int inputInt = static_cast<int>(inputQueue.front()[j] - '0');
            gameStack.push(inputInt);
        }

        inputQueue.pop();

        checkClears(&gameStack, &playerScore);
    }
};

void queryGame(stack<int> gameStack, int queryCount, int playerScore){
    stack<int> reverseStack;
    int length = gameStack.size();

    for(int i = 0; i < length; i++){
        reverseStack.push(gameStack.top());
        gameStack.pop();
    }

    cout << "Query #" << queryCount << ":" << endl;
    cout << "Player Score: " << playerScore << endl;
    cout << "Current State of the Game:" << endl;

    for(int i = 0; i < length; i++){
        cout << reverseStack.top();
        gameStack.push(reverseStack.top());
        reverseStack.pop();
    }

    cout << endl << endl;

};

void checkClears(stack<int>* gameStack, int* playerScore){

    stack<int> reverseStack;

    int 
        consecutiveGems = 0,
        lastGem = 0,
        reverseLength = 0
    ;

    while(gameStack->size() > 0){

        if(gameStack->top() != lastGem){
            if(consecutiveGems < 3){
                consecutiveGems = 0;
            } else {

                for(int i = 0; i < consecutiveGems; i++)
                    reverseStack.pop();
                
                reverseLength = reverseStack.size();

                for(int i = 0; i < reverseLength; i++){
                    gameStack->push(reverseStack.top());
                    reverseStack.pop();
                }

                *playerScore += consecutiveGems;
                consecutiveGems = 0;
                lastGem = 0;

                continue;
            }
        }

        consecutiveGems++;
        lastGem = gameStack->top();
        reverseStack.push(lastGem);
        gameStack->pop();
    }

    reverseLength = reverseStack.size();

    for(int i = 0; i < reverseLength; i++){
        gameStack->push(reverseStack.top());
        reverseStack.pop();
    }
};