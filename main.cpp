#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

struct Candidate {
    string party;
    string name;
    int age;
    string suburb;
    string postal_code;
    int votes;
};

void displayCandidates(const vector<Candidate>& candidates) {
    // Display header
    cout << "Party" << setw(10) << "Candidate Name" << setw(26) << "Age" << setw(15)
         << "Suburb Postal Code" << setw(20) << "No. Votes" << endl;
    cout << setfill('-') << setw(90) << "-" << endl;

    // Display candidate list
    cout << setfill(' ');
    int count = 1;
    for (const Candidate& candidate : candidates) {
        cout << count++ << ". " << setw(4) << candidate.party << setw(30) << candidate.name << setw(10)
             << candidate.age << setw(25) << candidate.suburb << " " << candidate.postal_code
             << setw(10) << candidate.votes << endl;
    }
}

int main() {
    // Read data from file
    vector<Candidate> candidates;
    ifstream file("candidates.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Candidate candidate;
            stringstream ss(line);
            getline(ss, candidate.party, ',');
            getline(ss, candidate.name, ',');
            ss >> candidate.age;
            ss.ignore();
            getline(ss, candidate.suburb, ',');
            getline(ss, candidate.postal_code, ',');
            ss >> candidate.votes;
            candidates.push_back(candidate);
        }
        file.close();
    } else {
        cout << "Error: Unable to open file." << endl;
        return 1;
    }

    // Display candidates
    if (candidates.empty()) {
        cout << "Error (Empty List): Unable to display number of votes." << endl;
    } else {
        displayCandidates(candidates);
    }

    return 0;
}
