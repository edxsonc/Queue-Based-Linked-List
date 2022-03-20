/*
    Name: Edison Caceres Alejo
    Date: 3/15/2022
    This program allows a user to enter a list of up to 25 integers, and then uses a queue-based linked list to read the numbers and remove the duplicates.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct entry{
    int value; //initializes a data in of type int
    struct entry *nextPtr; //initializes a pointer of type entry
};

struct entry *getEntry(){
    struct entry *newPtr;
    newPtr = new struct entry; // on heap
    newPtr->value = 0; // initialize to default
    newPtr->nextPtr = NULL; // ditto
    return newPtr;
}

//this function enqueues an integer value to q
void enqueue(int q[], int index, int value){
    q[index] = value;
}

//this function dequeues an integer value from q
int dequeue(int q[], int index){
    return q[index];
}

//this function loops through q and returns true if "value" is in the queue
bool isDuplicate(int q[], int value, int elements){
    for(int i = 0; i < elements; ++i){
        if(q[i] == '\0') return false;
        if(q[i] == value){
            return true;
        }
    }
    return false;
}

int main(){

    ifstream inputFile; //initalizes a file for reading
    string inputFileName; //initalizes a name for the file for reading

    cout<<"Enter the name of the input file -> ";
    cin>>inputFileName;

    inputFile.open(inputFileName);
    if(inputFile.fail()){
        cout<<"There was an error opening this input file."<<endl;
        return 0;
    }
    else{
        cout<<"File opened."<<endl;
    }

    struct entry *headPtr; //points to first element read from input file
    struct entry *tailPtr; //points to last element in file
    struct entry *auxPtr; //points to the new nodes
    int queue[25]; //stores integers read that are NOT duplicates
    int inputInteger; //used to read integers from input file
    int elementCounter = 0; //counts the total amounto of integers read, does not include duplicates

    headPtr = NULL;
    tailPtr = NULL;
    auxPtr = NULL;

    inputFile>>inputInteger;
    auxPtr = getEntry();
    auxPtr -> value = inputInteger;
    headPtr = tailPtr = auxPtr;
    enqueue(queue, elementCounter, inputInteger);
    elementCounter++;
    inputFile>>inputInteger;

    while(!inputFile.eof() and inputInteger > 0){
        if(elementCounter >= 25){
            cout<<"The maximum elements the queue can store has been reached."<<endl;
            break;
        }
        auxPtr = getEntry();
        auxPtr -> value = inputInteger;
        tailPtr -> nextPtr = auxPtr;
        tailPtr = auxPtr;
        if(!isDuplicate(queue, inputInteger, elementCounter)){
            enqueue(queue, elementCounter, inputInteger);
            elementCounter++;
        }
        inputFile>>inputInteger;
    }

    int newLine = 0; //counter for integers outputted. Resets at to zero at 10. 
    cout<<"Values in queue: "<<endl;
    for(int i = 0; i < elementCounter; i++){
        cout<<setw(10)<<dequeue(queue, i);
        newLine++;
        if(newLine == 10){
            cout<<endl;
            newLine = 0;
        }
    }
    cout<<endl;
    inputFile.close();
    return 0; 
}
