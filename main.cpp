#include <iostream>
#include <fstream>
#include <string> //for string
#include <limits> //add limits
#include <cctype> //turn input to lowercase

using namespace std;

//Declare the text file as global variables
string VotersFile = "voters.txt";
string CandidatesFile = "candidates.txt";

void CheckInput(char choices) {
    // Check if the input is a character
    if (!isalpha(choices)) {
        cout << "Invalid choice, please try again" << endl;
        // Clear the error in cin if you type in something that is not a char
        cin.clear();
        // Ignore all characters up to the \n
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


void CheckFiles() {
    ifstream voters_in(VotersFile);
    ifstream candiates_in(CandidatesFile);
    //if that file doesn't exist
    if (!voters_in.is_open()) {
        cout << "Error: Could not open " << VotersFile << endl;
    }
    
    ifstream candidates_in(CandidatesFile);
    //if that file doesn't exist
    if (!candidates_in.is_open()) {
        cout << "Error: Could not open " << CandidatesFile << endl;
    }
}

//Fix this code so that it fit the criteria of Task 2
//Pass in by reference for it work
void EmptyFile(ifstream& inFile) {
    // Check if the file is empty
    if (inFile.peek() == ifstream::traits_type::eof()) {
        cout << "The List is empty" << endl;
        inFile.close();
        return; //exit immediately if the file is empty
    }
}

//S choice
void DisplaySmallestVotes(string& CandidatesFile) {
    CheckFiles();
    // Open the student file in read mode
    ifstream inFile;
    inFile.open(VotersFile);

    // Check if the file is empty
    EmptyFile(inFile);
}

//L choice
void DisplayLargestVotes(string& CandidatesFile) {
    CheckFiles();
    // Open the student file in read mode
    ifstream inFile;


    // Check if the file is empty

}

//P choice
void PrintNumberForCandidate() {
    CheckFiles();
    
    ofstream outFile;
    //open it in append mode to not overwrite
    outFile.open(VotersFile, fstream::app); 
    
    //Check if it is empty

}

//A choice
void AddNumberOfVotesToCandidates() {
    CheckFiles();
    ofstream outFile;
    //open it in append mode to not overwrite
    outFile.open(CandidatesFile, fstream::app); 

}

void menu() {
    bool not_finished = true;
    char choices;
    while (not_finished == true) {
        cout << "P - Print numbers for a particular candidate\n";
        cout << "A - Add number of votes to a candidate\n";
        cout << "S - Display the smallest number of votes candidate\n";
        cout << "L - Display the largest number of votes candidate\n";
        cout << "Q - Quit\n";
        cout << "Enter your choice: "; 
        cin >> choices; 

        choices = tolower(choices); // Convert input to lowercase

        switch (choices) {
            case 'p':
                PrintNumberForCandidate();
                break;
            case 'a':
                AddNumberOfVotesToCandidates();
                break;
            case 's':
                DisplaySmallestVotes(VotersFile);
                break;
            case 'l':
                DisplayLargestVotes(CandidatesFile);
                break;
            case 'q':
                not_finished = false;
                cout << "Exiting the program";
                break;
            default:
                cout << "Invalid choice, please try again" << endl;
                CheckInput(choices);
        }
    } 
}
int main() {
    menu();
    return 0;
}