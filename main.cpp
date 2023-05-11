#include <iostream>
using namespace std;

int main() {
    char choice;

    do {
        cout << "Menu Options:" << endl;
        cout << "P - Print numbers for a particular candidate" << endl;
        cout << "A - Add number of votes to a candidate" << endl;
        cout << "S - Display the smallest number of votes candidate" << endl;
        cout << "L - Display the largest number of votes candidate" << endl;
        cout << "Q - Quit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (toupper(choice)) {
            case 'P':
                // code to print numbers for a particular candidate
                break;
            case 'A':
                // code to add number of votes to a candidate
                break;
            case 'S':
                // code to display the smallest number of votes candidate
                break;
            case 'L':
                // code to display the largest number of votes candidate
                break;
            case 'Q':
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (toupper(choice) != 'Q');

    return 0;
}
