#include <iostream>
#include <fstream> //read and write stream
#include <string> //for string
#include <limits> //add limits
#include <cctype> //turn input to lowercase
#include <sstream> //to add and overwrite data in one particular part
#include <vector> //vectors
#include <iomanip> //manipulate output 
#include <cstdlib> // for exit()
//can't wait to learn python
using namespace std;

/*
Team name: C+++
Group No.: 5
Group members:
Christian Samuel Cheng - 103075742
Huu Ti Dang – 104101363
Deeya Aridi – 102092737
*/

//Declare the text file as global variables
const string VotersFile = "voters.txt";
const string CandidatesFile = "candidates.txt";
string TempFile = "temp.txt"; //to make overwritting easier
bool candidatesEmpty = false;
string voted, userID;

void CheckFiles() {
    ifstream voters_in(VotersFile);
    ifstream candidates_in(CandidatesFile);
    //If that file doesn't exist
    //open the file
    if (!voters_in.is_open()) {
        cout << "Error: Unable to open " << VotersFile << endl;
    }
    
    //If that file doesn't exist
    if (!candidates_in.is_open()) {
        cout << "Error: Unable to open " << CandidatesFile << endl;
        candidatesEmpty = true;
    //Check if candidates file is empty
    } else {
        candidates_in.ignore(numeric_limits<streamsize>::max());
        //Check the amount of characters inside of that files
        if (candidates_in.gcount() == 0) { 
            candidatesEmpty = true; //if yes
        } else {
            candidatesEmpty = false; //if no
        }
        candidates_in.clear(); //clear the content inside
        candidates_in.seekg(0, ios::beg); //reset the file position 
    }
}

//Login page for voters
bool Login() {
    string pwd; //the password
    
    //Input validation flags
    bool validID = false;
    bool validDOB = false;
    
    do {
        //prompt for id
        cout << "Please enter your ID (6 digits): ";
        cin >> userID;
        
        //Check if the ID has exactly 6 digits
        //And if they are all numbers
        if (userID.length() != 6 || !isdigit(userID[0]) || !isdigit(userID[1]) || !isdigit(userID[2]) ||
            !isdigit(userID[3]) || !isdigit(userID[4]) || !isdigit(userID[5])) {
            cout << "Invalid ID. Please enter a 6-digit numeric ID." << endl; //if not
        } else {
            validID = true; //if yes
        }
    } while (!validID); //keep looping until there is a valid ID
    
    do {
        //prompt for password
        cout << "Please enter your date of birth (DDMMYYYY): "; //password is the date of birth
        cin >> pwd; //this is the password
        
        //Check if the date of birth has exactly 8 digits
        //Check if they are all digits
        if (pwd.length() != 8 || !isdigit(pwd[0]) || !isdigit(pwd[1]) || !isdigit(pwd[2]) ||
            !isdigit(pwd[3]) || !isdigit(pwd[4]) || !isdigit(pwd[5]) || !isdigit(pwd[6]) ||
            !isdigit(pwd[7])) {
            cout << "Invalid date of birth. Please enter an 8-digit numeric date of birth." << endl; //if no
        } else {
            validDOB = true; //if yes
        }
    } while (!validDOB); //looping until there is the password is corrects
    
    //open in read mode
    ifstream inFile(VotersFile);
    string line; 
    
    while (getline(inFile, line)) { //read each line
        stringstream ss(line); //parse each string
        string id, name, dob, suburb; //could have use struct for to create a voter object
        getline(ss, id, ','); //get the id until it reaches a comma
        getline(ss, name, ','); //get the name until it reaches a comma
        getline(ss, dob, ','); //get the Date of Birth until it reaches a comma
        getline(ss, suburb, ','); //get the suburb until it reaches a comma
        getline(ss, voted, ','); ////get the status until it reaches a comma
        
        //0 for not voted, 1 for voted
        if (id == userID && dob == pwd) { //only let it through if both the id and password are valid
            cout << "Welcome, " << name << " ";
            if (voted == "0") {
                cout << "\nYou have not voted" << endl;
            } else {
                cout << "\nYou have voted" << endl;
            }
            inFile.close();
            return true;
        }
    }
    
    inFile.close();
    cout << "Invalid ID or date of birth, access denied" << endl; //if no valid id were to be found
    return false;
}

//D choice
//Display candidate list
void DisplayCandidateList() {
    //open in read mode
    ifstream inFile(CandidatesFile);
    string line;
    int count = 1;
    while (getline(inFile, line)) {
        stringstream ss(line); //for parsing the one we extreact
        string party, name;
        getline(ss, party, ','); //get the candidate party
        getline(ss, name, ','); //get the canidate naem
        cout << count << ". " << party << " - " << name << endl; //outputing them
        count++; //add index
    }
    if (count == 1) { //if it doesn't increment
        cout << "Unable to display candidates list - no data" << endl;
    }
    //close the file
    inFile.close();
}

//P choice
void DisplayCandidateVotes() {
    int candidateNumber;
    bool validInput = false; //validation flag

    do {
        DisplayCandidateList(); //Display the candidate list first
        cout << "Enter the candidate number to display their votes: ";
        if (cin >> candidateNumber) { //
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignore the newline character
            
            //open in read mode
            ifstream candidatesFile(CandidatesFile);
            string line;
            int count = 1; //the index
            bool candidateFound = false; //candidate found flag

            //Find the candidate from the input
            while (getline(candidatesFile, line)) {
                if (count == candidateNumber) {
                    candidateFound = true;
                    break;
                }
                count++;
            }

            if (candidateFound) {
                validInput = true;
                stringstream ss(line); //for parsing data
                string party, name, age, suburb, votes; //could've use struct to create the candidate object
                getline(ss, party, ','); //getting the party name form the candidate.txt
                getline(ss, name, ','); //getting the candidate name form the candidate.txt
                getline(ss, age, ','); //getting the candidate age form the candidate.txt
                getline(ss, suburb, ','); //getting the candidate suburb form the candidate.txt
                getline(ss, votes, ','); //getting the candidates votes count form the candidate.txt
                //printing them
                cout << "Party: " << party << endl;
                cout << "Candidate: " << name << endl;
                cout << "Date Of Birth: " << age << endl;
                cout << "Suburb: " << suburb << endl;
                cout << "Votes: " << votes << endl;
            } else {
                cout << "Invalid candidate number, please try again" << endl; //if the candidate number doesn't match
            }

            candidatesFile.close();
        } else {
            cout << "Invalid input, Please enter a numeric candidate number" << endl; //if the enter anything but integer
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the remaining input until the newline character
        }
    } while (!validInput); //only run when there is a Valid input
}

//A choice
void AddNumberOfVotesToCandidates() {
    int candidateNumber;

    do {
        DisplayCandidateList();
        cout << "Enter the candidate number to add a vote: ";
        if (cin >> candidateNumber) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character

            //open the file in read mode
            ifstream candidatesFile(CandidatesFile);
            string line;
            int count = 1; //the index
            vector<string> candidateData; //create a vector

            // Read the candidate data and update the vote count
            while (getline(candidatesFile, line)) {
                if (count == candidateNumber) {
                    stringstream ss(line); //parsing data from the candidate tables
                    string party, name, age, suburb, votes; //could've use struct to create a candidate object
                    getline(ss, party, ','); //getting the party name form the candidate.txt
                    getline(ss, name, ','); //getting the candidate name form the candidate.txt
                    getline(ss, age, ','); //getting the candidate age form the candidate.txt
                    getline(ss, suburb, ','); //getting the candidate suburb form the candidate.txt
                    getline(ss, votes, ','); //getting the candidates votes count form the candidate.txt
                    int voteCount = stoi(votes); //turn string into integer
                    voteCount++; //adding the index
                    stringstream updatedLine; //for parsing the update data
                    updatedLine << party << "," << name << "," << age << "," << suburb << "," << voteCount; //update the data, more precisely the voteCount
                    candidateData.push_back(updatedLine.str()); //store the updated candidate data
                    //print the updated data
                    cout << party << " - " << name << " now has " << voteCount << " votes." << endl;
                    cout << "Your Vote:" << endl;
                    cout << "Party: " << party << endl;
                    cout << "Candidate: " << name << endl;
                    cout << "Date Of Birth: " << age << endl;
                    cout << "Suburb: " << suburb << endl;
                    cout << "Votes: " << voteCount << endl;

                    // Update the voted status in voters.txt
                    ifstream votersFile(VotersFile); //open the voters.txt in read mode
                    ofstream tempFile(TempFile); //open the temporary file in write mode for overwriting
                    string voterLine;
                    while (getline(votersFile, voterLine)) { //read eachline in the file
                        stringstream voterSS(voterLine); //parse those line from each other
                        string voterID, voterName, voterDOB, voterSuburb, voterVoted; //could've use struct for creating a Voter object
                        getline(voterSS, voterID, ','); //read the id until it reach a comma
                        getline(voterSS, voterName, ','); //read the name until it reach a comma
                        getline(voterSS, voterDOB, ','); //read the date of birth until it reach a comma
                        getline(voterSS, voterSuburb, ','); //read the suburb until it reach a comma
                        getline(voterSS, voterVoted, ','); //read the status until it reach a comma
                        //don't really need the comma at the end as the status is at the end of the file

                        //check if the one the user entered matches the ones in the voters.txt
                        if (voterID == userID) {
                            voted = "1"; //if yes change the status to 1
                            tempFile << voterID << "," << voterName << "," << voterDOB << "," << voterSuburb << "," << voted << endl; // Update voted status to 1
                            //overwrite it to the temporary file
                        } else {
                            tempFile << voterLine << endl; //if it doesn't match write the original voters line to the temporary file
                        }
                    }
                    //close both files
                    votersFile.close();
                    tempFile.close();

                    // Replace the original voters.txt file with the updated one
                    remove(VotersFile.c_str());
                    rename(TempFile.c_str(), VotersFile.c_str());
                } else {
                    candidateData.push_back(line);
                }
                count++; //the count is for the index of candidates
            }
            //close the file
            candidatesFile.close();
            //open in write mode
            ofstream outFile(CandidatesFile);
            for (const string& data : candidateData) {
                outFile << data << endl;
            }
            //close the file
            outFile.close();

            return; // Exit the function after updating the votes
        } else {
            cout << "Invalid input, please enter a numeric candidate number" << endl; //when user enter anything but integer
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the remaining input until the newline character
        }
    } while (true); //only run when true
}

//S choice
void DisplaySmallestVotes(const string& CandidatesFile) {
    ifstream inFile(CandidatesFile);
    string line;
    int smallestVotes = numeric_limits<int>::max();

    while (getline(inFile, line)) {
        stringstream ss(line); //stringstream for parsing line
        string party, name, age, suburb, votes; //could've use struct to create a candidate object
        getline(ss, party, ','); //read the canidate party until it reach a comma
        getline(ss, name, ','); //read the candidate name until it reach a comma
        getline(ss, age, ','); //read the candidate age until it reach a comma
        getline(ss, suburb, ','); //read the canididate suburb until it reach a comma
        getline(ss, votes, ','); //read the votes count until it reach a comma

        int candidateVotes = stoi(votes); //turn string into integer
        if (candidateVotes < smallestVotes) { //iterate through the data to find the lowest amount of vote
            smallestVotes = candidateVotes; //if it is smaller than the ones previously stored it into candidateVotes
        }
    }

    inFile.clear();
    inFile.seekg(0, ios::beg); //place the file point at the start

    cout << "Candidates with the smallest number of votes:" << endl;

    while (getline(inFile, line)) { //read each line in the file
        stringstream ss(line); //parse the data
        string party, name, age, suburb, votes; //could've use struct to creat e the canddiate object
        getline(ss, party, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, suburb, ',');
        getline(ss, votes, ',');

        int candidateVotes = stoi(votes); //turn string to integer
        //print the candidate or candidates with the smallest amount of votes
        if (candidateVotes == smallestVotes) {
            cout << "Party: " << party << endl;
            cout << "Candidate: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Suburb: " << suburb << endl;
            cout << "Votes: " << candidateVotes << endl;
            cout << endl;
        }
    }
    //close the file
    inFile.close();
}

//the same as S choice
//L choice
void DisplayLargestVotes(const string& CandidatesFile) {
    ifstream inFile(CandidatesFile);
    string line;
    int largestVotes = 0;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string party, name, age, suburb, votes;
        getline(ss, party, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, suburb, ',');
        getline(ss, votes, ',');

        int candidateVotes = stoi(votes); //turn string into integer
        if (candidateVotes > largestVotes) {
            largestVotes = candidateVotes;
        }
    }

    inFile.clear();
    inFile.seekg(0, ios::beg);

    cout << "Candidates with the largest number of votes:" << endl;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string party, name, age, suburb, votes;
        getline(ss, party, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, suburb, ',');
        getline(ss, votes, ',');

        int candidateVotes = stoi(votes);

        if (candidateVotes == largestVotes) {
            cout << "Party: " << party << endl;
            cout << "Candidate: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Suburb: " << suburb << endl;
            cout << "Votes: " << candidateVotes << endl;
            cout << endl;
        }
    }

    inFile.close();
}

void menu() {
    //bit of an oversight, should've use string
    char choice;
    bool not_finished = true; //menu finish flag
    do {
        CheckFiles(); //check the files first
        //prompt the menu
        cout << "P - Print numbers for a particular candidate" << endl;
        cout << "D - Display all candidates" << endl;
        cout << "A - Add number of votes to a candidate" << endl;
        cout << "S - Display the smallest number of votes candidate" << endl;
        cout << "L - Display the largest number of votes candidate" << endl;
        cout << "C - Display the largest number of votes candidate" << endl;
        cout << "Q - Quit" << endl;
        cout << "Enter your choice: "; //ask the user for a choice
        cin >> choice;
        //turn them all input to lowercase
        switch (tolower(choice)) {
            case 'p':
                if (candidatesEmpty) { //if empty
                    cout << "the list is empty" << endl;
                } else {
                    DisplayCandidateVotes();
                }
                break;
            case 'd':
                if (candidatesEmpty) { //if empty
                    cout << "Unable to display candidates list - no data" << endl;
                } else {
                    DisplayCandidateList();
                }
                break;
            case 'a':
                if (candidatesEmpty) { //if empty
                    cout << "Unable to calculate the mean - no data" << endl;
                } else {
                    cout << voted << endl;
                    if (voted == "0") { //if they haven't voted yet
                        AddNumberOfVotesToCandidates();
                    } else { //if they have voted
                        cout << "You have already voted" << endl;
                    }
                }
                break;
            case 's':
                if (candidatesEmpty) { //if empty
                    cout << "Unable to determine the smallest number - list is empty" << endl;
                } else {
                    DisplaySmallestVotes(CandidatesFile);
                }
                break;
            case 'l':
                if (candidatesEmpty) { //if empty
                    cout << "Unable to determine the largest number - list is empty" << endl;
                } else {
                    DisplayLargestVotes(CandidatesFile);
                }
                break;
            case 'c':
                not_finished = false;
                cout << "Changing voters..." << endl;
                break;
            case 'q':
                cout << "Goodbye" << endl;
                exit(0); //Actually exiting the program
                break;
            default:
                cout << "Unknown selection, please try again" << endl; //if an invalid choice is made
                break;
        }
    } while (not_finished == true);
}

int main() {
    while (true) {
        bool loggedIn = Login(); //flag to check if they have login
        if (loggedIn) {
            menu();
        } else {
            cout << "Invalid ID, access denied" << endl; //invalid id
        }
    }
    return 0;
}