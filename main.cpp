#include <iostream>
#include <fstream>
#include <string> //for string
#include <limits> //add limits
#include <cctype> //turn input to lowercase

using namespace std;

//Declare the text file as global variables
string VotersFile = "voters.txt";
string CandidatesFile = "candidates.txt";

//S choice
void DisplaySmallestVotes(string& CandidatesFile) {
    // Check if the file exists
    ifstream fileExistsCheck(CandidatesFile);
    if (!fileExistsCheck) {
        cout << "File " << CandidatesFile << " does not exist." << endl;
        return;
    }

    // Open the student file in read mode
    ifstream inFile;
    inFile.open(VotersFile);

    // Check if the file is empty
    if (inFile.peek() == ifstream::traits_type::eof()) {
        cout << "Unable to determine the smallest number - list is empty" << endl;
        inFile.close();
        return; //exit immediately if the file is empty
    }
    inFile.close();
}

//L choice
void DisplayLargestVotes(string& CandidatesFile) {
    // Check if the file exists
    ifstream fileExistsCheck(CandidatesFile);
    if (!fileExistsCheck) {
        cout << "File " << CandidatesFile << " does not exist." << endl;
        return;
    }

    // Open the student file in read mode
    ifstream inFile;

    // Check if the file is empty
    if (inFile.peek() == ifstream::traits_type::eof()) {
        cout << "Unable to determine the largest number - list is empty" << endl;
        inFile.close();
        return; //exit immediately if the file is empty
    }
    inFile.close();
}

//P choice
void PrintNumberForCandidate() {
    // Check if the file exists
    ifstream fileExistsCheck(VotersFile);
    if (!fileExistsCheck) {
        cout << "File " << VotersFile << " does not exist." << endl;
        return;
    }
    
    ofstream outFile;
    //open it in append mode to not overwrite
    outFile.open(VotersFile, fstream::app); 
    
    //Check if it is empty
    if (outFile.tellp() == 0) {
        cout << "Unable to calculate the mean - no data." << endl;
        outFile.close();
        return; // Exit immediately if the file is empty
    }
    outFile.close();
}

//A choice
void AddNumberOfVotesToCandidates() {
    // Check if the file exists
    ifstream fileExistsCheck(CandidatesFile);
    if (!fileExistsCheck) {
        cout << "File " << CandidatesFile << " does not exist." << endl;
        return;
    }

    ofstream outFile;
    //open it in append mode to not overwrite
    outFile.open(CandidatesFile, fstream::app); 
    //check if file is empty
    if (outFile.tellp() == 0) {
        cout << "Unable to calculate the mean - no data." << endl;
        outFile.close();
        return; // Exit immediately if the file is empty
    }
    outFile.close();
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
                cout << "Unknown selection, please try again" << endl;
        }
    } 
}
int main() {
    menu();
    return 0;
}