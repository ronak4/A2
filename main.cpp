#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

class passenger {
public:
  string name;
  bool occupied;
  bool isle;

  void printName() { cout << name << endl; }
};

class plane {
public:
  passenger seats[8][11];
  vector<string> passengers;

  void printSeats() {
    cout << endl << "X is for occupied and O is for unoccupied" << endl;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 11; j++) {
        if (seats[i][j].isle == true) {
          cout << " ";
        } else {
          if (seats[i][j].occupied == true) {
            cout << " x";
          } else {
            cout << " 0";
          }
        }
        if (j == 10) {
          cout << "\n";
        }
      }
    }
    showMenu();
  }

  void removePass(string name, string seat) {
    string full = name + " " + seat;
    int row = stoi(seat.substr(0, 1)) - 1;
    int column = charToNum(seat[1]);
    for (int i = 0; i < passengers.size(); i++) {
      if (passengers[i] == full) {
        passengers.erase(passengers.begin() + i);
        seats[row][column].occupied = false;
        seats[row][column].name = "";
      }
    }
  }

  void upgrade(string seat, string name) {
    char answer;
    string newSeat;
    int row = (stoi(seat.substr(0, 1))) - 1;
    int column = charToNum(seat[1]);
    if (seat[0] == '1') {
    } else if ((seat[0] == '2' || seat[0] == '3') && firstClassHelper()) {
      cout << "Would you like to upgrade to first class? (Y/N): ";
      cin >> answer;
      if (answer == 'Y') {
        newSeat = initialSelection('F');
        cout << "Your seat is: " << newSeat << endl;
        removePass(name, seat);
        loadSeat(stoi(newSeat.substr(0, 1)), newSeat[1], name);
        passengers.push_back(name + " " + newSeat);

      } else {
        showMenu();
      }
    } else {
      if (firstClassHelper() && businessClassHelper()) {
        cout << "Would you like to upgrade to first class or business class? "
                "(F/B/N): ";
        cin >> answer;
        if (answer == 'F') {
          newSeat = initialSelection('F');
          cout << "Your seat is: " << newSeat << endl;
          removePass(name, seat);
          loadSeat(stoi(newSeat.substr(0, 1)), newSeat[1], name);
          passengers.push_back(name + " " + newSeat);
        } else if (answer == 'B') {
          newSeat = initialSelection('B');
          cout << "Your seat is: " << newSeat << endl;
          removePass(name, seat);
          loadSeat(stoi(newSeat.substr(0, 1)), newSeat[1], name);
          passengers.push_back(name + " " + newSeat);
        } else {
          showMenu();
        }
      } else if (firstClassHelper()) {
        cout << "Would you like to upgrade to first class? (Y/N): ";
        cin >> answer;
        if (answer == 'Y') {
          newSeat = initialSelection('F');
          cout << "Your seat is: " << newSeat << endl;
          removePass(name, seat);
          loadSeat(stoi(newSeat.substr(0, 1)), newSeat[1], name);
          passengers.push_back(name + " " + newSeat);
        } else {
          showMenu();
        }
      } else if (businessClassHelper()) {
        cout << "Would you like to upgrade to business class? (Y/N): ";
        cin >> answer;
        if (answer == 'Y') {
          newSeat = initialSelection('B');
          cout << "Your seat is: " << newSeat << endl;
          removePass(name, seat);
          loadSeat(stoi(newSeat.substr(0, 1)), newSeat[1], name);
          passengers.push_back(name + " " + newSeat);
        } else {
          showMenu();
        }
      } else {
        cout << "Upgrading ticket is unavailable" << endl;
      }
    }
    showMenu();
  }

  bool firstClassHelper() {
    int counter = 0;
    for (int i = 0; i < 9; i++) {
      if (seats[0][i].occupied == false) {
        counter++;
      }
    }
    if (counter == 0) {
      return false;
    } else if (counter <= 9) {
      return true;
    }
    return true;
  }

  bool businessClassHelper() {
    int counter = 0;
    for (int i = 0; i < 9; i++) {
      if (seats[1][i].occupied == false) {
        counter++;
      }
      if (seats[2][i].occupied == false) {
        counter++;
      }
    }
    if (counter == 0) {
      return false;
    } else if (counter <= 18) {
      return true;
    }
    return true;
  }

  vector<string> emptySeatsAvailable(int low, int high) {
    vector<string> seatsEmpty;
    for (int g = low; g < high; g++) {
      for (int k = 0; k < 11; k++) {
        string curr = "";
        if (!(seats[g][k].occupied) && (!(seats[g][k].isle))) {
          curr.append(to_string(g + 1));

          curr.append(numToChar(k));
          seatsEmpty.push_back(curr);
        }
      }
    }
    return seatsEmpty;
  }

  string initialSelection(char planeClass) {
    vector<string> emptySeats;
    int row;
    int seat;
    int randomNum;
    string result;
    switch (planeClass) {
    case 'F':
      emptySeats = emptySeatsAvailable(0, 1);
      randomNum = randomSelection(emptySeats.size());
      result = emptySeats[randomNum];

      break;
    case 'B':
      emptySeats = emptySeatsAvailable(1, 3);
      randomNum = randomSelection(emptySeats.size());
      result = emptySeats[randomNum];
      break;
    case 'E':
      emptySeats = emptySeatsAvailable(3, 8);
      randomNum = randomSelection(emptySeats.size());
      result = emptySeats[randomNum];
      break;
    }
    return result;
  }

  int randomSelection(int high) {
    srand(time(0));
    int result;
    result = (rand() % (high + 1)) - 1;
    return result;
  }

  string numToChar(int seatNum) {
    char seat;
    string result;
    switch (seatNum) {
    case 0:
      seat = 'A';
      break;
    case 1:
      seat = 'B';
      break;
    case 2:
      seat = 'C';
      break;
    case 3:
      seat = 'D';
      break;
    case 4:
      seat = 'E';
      break;
    case 5:
      seat = 'F';
      break;
    case 6:
      seat = 'G';
      break;
    case 7:
      seat = 'H';
      break;
    case 8:
      seat = 'I';
      break;
    case 9:
      seat = 'J';
      break;
    case 10:
      seat = 'K';
      break;
    default:
      seat = -1;
    }
    result.push_back(seat);
    return result;
  }

  int charToNum(char inp) {
    int seat;
    switch (inp) {
    case 'A':
      seat = 0;
      break;
    case 'B':
      seat = 1;
      break;
    case 'D':
      seat = 3;
      break;
    case 'E':
      seat = 4;
      break;
    case 'F':
      seat = 5;
      break;
    case 'G':
      seat = 6;
      break;
    case 'I':
      seat = 8;
      break;
    case 'J':
      seat = 9;
      break;
    case 'K':
      seat = 10;
      break;
    default:
      seat = -1;
    }
    return seat;
  }

  void updateSeat(int x, char seat, string passName) {
    int seatNum;
    switch (seat) {
    case 'A':
      seatNum = 0;
      break;
    case 'B':
      seatNum = 1;
      break;
    case 'D':
      seatNum = 3;
      break;
    case 'E':
      seatNum = 4;
      break;
    case 'F':
      seatNum = 5;
      break;
    case 'G':
      seatNum = 6;
      break;
    case 'I':
      seatNum = 8;
      break;
    case 'J':
      seatNum = 9;
      break;
    case 'K':
      seatNum = 10;
      break;
    default:
      seatNum = -1;
    }
    string fullSeat;
    fullSeat = to_string(x) + seat;
    removePass(seats[x - 1][seatNum].name, fullSeat);
    passengers.push_back(passName + " " + fullSeat);
    seats[x - 1][seatNum].name = passName;
  }

  void loadSeat(int x, char seat, string passName) {
    int seatNum;
    switch (seat) {
    case 'A':
      seatNum = 0;
      break;
    case 'B':
      seatNum = 1;
      break;
    case 'D':
      seatNum = 3;
      break;
    case 'E':
      seatNum = 4;
      break;
    case 'F':
      seatNum = 5;
      break;
    case 'G':
      seatNum = 6;
      break;
    case 'I':
      seatNum = 8;
      break;
    case 'J':
      seatNum = 9;
      break;
    case 'K':
      seatNum = 10;
      break;
    default:
      seatNum = -1;
    }
    if (seats[x - 1][seatNum].occupied == true) {
      cout << "Error Seat " << x << seat << " is already occupied" << endl;
    } else {
      seats[x - 1][seatNum].occupied = true;
      seats[x - 1][seatNum].name = passName;
    }
  }

  bool printBoardingPass(int row, char seat) {
    int seatNum;
    string planeClass;
    switch (seat) {
    case 'A':
      seatNum = 0;
      break;
    case 'B':
      seatNum = 1;
      break;
    case 'D':
      seatNum = 3;
      break;
    case 'E':
      seatNum = 4;
      break;
    case 'F':
      seatNum = 5;
      break;
    case 'G':
      seatNum = 6;
      break;
    case 'I':
      seatNum = 8;
      break;
    case 'J':
      seatNum = 9;
      break;
    case 'K':
      seatNum = 10;
      break;
    default:
      seatNum = -1;
    }

    // determine class
    if (row == 1) {
      planeClass = "First Class";
    } else if ((row == 2) || (row == 3)) {
      planeClass = " Business Class";
    } else {
      planeClass = "Economy Class";
    }

    if (!(seats[row - 1][seatNum].occupied)) {
      return false;
    } else {
      seats[row - 1][seatNum].printName();
      cout << "Seat:" << row << seat << endl;
      cout << planeClass << endl;
      return true;
    }
  }

  void loadPrevious() {
    ifstream infile;
    infile.open("passengers.txt");

    if (infile.is_open()) {
      string inp;

      while (getline(infile, inp)) {
        string seat;
        string first;
        string surname;
        int seatNum;
        string seatLetter;
        char seatChar;
        string name = "";

        first = inp.substr(0, inp.find_first_of(' '));
        surname =
            inp.substr(inp.find_first_of(' ') + 1,
                       (inp.find_last_of(' ') - inp.find_first_of(' ') - 1));
        name = name.append(first + " " + surname);
        seat = inp.substr(inp.find_last_of(' ') + 1, 2);
        seatLetter = seat.substr(1, 1);
        seatChar = seatLetter[0];
        // cout << seatNum << endl << seatChar << endl << name << endl;
        seatNum = stoi(seat.substr(0, 1));

        // cout << seats[seatNum - 1][charToInt].occupied << endl;

        loadSeat(seatNum, seatChar, name);

        passengers.push_back(first + " " + surname + " " + seat);

        // seats[seatNum - 1][charToInt].printName();
      }
    }
    infile.close();
    showMenu();
  }

  void saveCurrent() {
    ofstream outfile;
    outfile.open("passengers.txt");
    for (string i : passengers) {
      outfile << i << endl;
    }
    outfile.close();
    showMenu();
  }

  void printManifest() {

    cout << "Option 1 - Ascending Order Seat" << endl;
    cout << "Option 2 - Descending Order Seat" << endl;
    cout << "Option 3 - A-Z Order Name" << endl;
    cout << "Option 4 - Z-A Order Name" << endl;
    char in;
    cout << "Input Order type option: ";
    cin >> in;
    cout << endl;
    vector<string> names;

    switch (in) {
    case '1':
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 11; j++) {
          if (seats[i][j].occupied && !seats[i][j].isle) {
            cout << seats[i][j].name << " " << i + 1 << numToChar(j) << endl;
          }
        }
      }
      break;
    case '2':
      for (int i = 7; i >= 0; i--) {
        for (int j = 10; j >= 0; j--) {
          if (seats[i][j].occupied && !seats[i][j].isle) {
            cout << seats[i][j].name << " " << i + 1 << numToChar(j) << endl;
          }
        }
      }
      break;
    case '3':
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 11; j++) {
          if (seats[i][j].occupied && !seats[i][j].isle) {
            names.push_back(seats[i][j].name + " " + to_string(i + 1) +
                            numToChar(j));
          }
        }
      }
      sort(names.begin(), names.end());
      for (int i = 0; i < names.size(); i++) {
        cout << names[i] << endl;
      }
      break;
    case '4':
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 11; j++) {
          if (seats[i][j].occupied && !seats[i][j].isle) {
            names.push_back(seats[i][j].name + " " + to_string(i + 1) +
                            numToChar(j));
          }
        }
      }
      sort(names.begin(), names.end(), greater<>());
      for (int i = 0; i < names.size(); i++) {
        cout << names[i] << endl;
      }
      break;
    default:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 11; j++) {
          if (seats[i][j].occupied && !seats[i][j].isle) {
            cout << seats[i][j].name << " " << i + 1 << numToChar(j) << endl;
          }
        }
      }
    }
    cout << endl;
    showMenu();
  }

  void updateHelper() {
    string seatU;
    cout << "Input Seat Number: ";
    cin >> seatU;
    string name;
    cout << endl << "Input New Passenger Name: ";
    cin.ignore();
    getline(cin, name);
    int row = stoi(seatU.substr(0, 1));
    char seatCharU = seatU[1];
    int seatNum;
    switch (seatCharU) {
    case 'A':
      seatNum = 0;
      break;
    case 'B':
      seatNum = 1;
      break;
    case 'D':
      seatNum = 3;
      break;
    case 'E':
      seatNum = 4;
      break;
    case 'F':
      seatNum = 5;
      break;
    case 'G':
      seatNum = 6;
      break;
    case 'I':
      seatNum = 8;
      break;
    case 'J':
      seatNum = 9;
      break;
    case 'K':
      seatNum = 10;
      break;
    default:
      seatNum = -1;
    }
    if (seats[row - 1][seatNum].occupied) {
      // string oldName = seats[row - 1][seatNum].name;
      cout << "Old passenger name: " << seats[row - 1][seatNum].name << ", ";
      updateSeat(row, seatCharU, name);
      cout << "New passenger name: " << seats[row - 1][seatNum].name << endl;
      upgrade(seatU, seats[row - 1][seatNum].name);
      saveCurrent();
    } else {
      cout << "Error: Seat is empty or doesn't exist" << endl;
      showMenu();
    }
  }

  void boardingPassHelper() {
    int counter = 0;
    for (int i = 0; i < 3; i++) {
      string seat;
      cout << "Input Seat Number: ";
      cin >> seat;
      int seatNum = stoi(seat.substr(0, 1));
      char seatChar = seat[1];
      if (printBoardingPass(seatNum, seatChar)) {
        showMenu();
        break;
      } else {
        cout << "Seat  Unassigned  -  No  Boarding  pass  available.  Try  "
                "Again!"
             << endl;
        counter++;
        if (counter == 3) {
          cout << endl
               << "Boarding pass  is  not  available  at  this  time.  Try  "
                  "Again  later!"
               << endl;
          showMenu();
        }
      }
    }
  }

  void initialise() {
    // initialise plane
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 11; j++) {
        if ((j == 2) || (j == 7)) {
          seats[i][j].isle = true;
          seats[i][j].occupied = true;
        } else {
          seats[i][j].isle = false;
          seats[i][j].occupied = false;
        }
      }
    }
  }

  void cancelTicket() {
    string name;
    string seat;
    cout << "Input Name as on boarding pass: ";
    cin.ignore();
    getline(cin, name);
    cout << endl << "Input Seat Number: ";
    cin >> seat;

    int rowNum = stoi(seat.substr(0, 1));
    int columnNum;

    switch (seat[1]) {
    case 'A':
      columnNum = 0;
      break;
    case 'B':
      columnNum = 1;
      break;
    case 'D':
      columnNum = 3;
      break;
    case 'E':
      columnNum = 4;
      break;
    case 'F':
      columnNum = 5;
      break;
    case 'G':
      columnNum = 6;
      break;
    case 'I':
      columnNum = 8;
      break;
    case 'J':
      columnNum = 9;
      break;
    case 'K':
      columnNum = 10;
      break;
    default:
      columnNum = -1;
    }

    if (seats[rowNum - 1][columnNum].name == name) {
      cout << "Trip Cancelled" << endl;
      removePass(name, seat);
      saveCurrent();
    } else {
      cout << "Error: Seat and Name do not match what is in the system" << endl;
    }
    showMenu();
  }

  string lowerClassSeat(char classChar) {
    string result;
    switch (classChar) {
    case 'F':
      result = initialSelection('B');
    case 'B':
      result = initialSelection('E');
    }
    return result;
  }

  bool lowerClassOpen(char classChar) {
    bool result;
    switch (classChar) {
    case 'F':
      result = emptyPerClass('B');
      break;
    case 'B':
      result = emptyPerClass('E');
      break;
    case 'E':
      result = true;
      break;
    }

    return result;
  }

  bool emptyPerClass(char planeClass) {
    bool result;
    switch (planeClass) {
    case 'F':
      result = (emptySeatsAvailable(0, 1).size() == 0);

      break;
    case 'B':
      result = (emptySeatsAvailable(1, 3).size() == 0);

      break;
    case 'E':
      result = (emptySeatsAvailable(3, 8).size() == 0);
      break;
    }
    return result;
  }

  int seatIntParser(string seat) {
    int result;
    char first;
    first = (char)seat[0];
    result = (int)first - 48;
    return result;
  }

  char charParser(string seat) { return seat[1]; }

  void chooseInitialSeat() {
    string classSelectionFirst;
    string name;
    char charClass;
    string firstOption;
    char row1;
    int rowNum;
    char seatChar;
    string seat;

    // if entire plane is empty
    if (emptySeatsAvailable(0, 8).size() == 0) {
      cout << "The entire flight is full! Next flight takes off in 3 hours!";
    } else { // if not then ask name and class
      cout << "Enter Passenger Name:" << endl;
      cin >> name;
      cout << "Choose a class:" << endl;
      cout << "Please type 'F' for First Class" << endl;
      cout << "Please type 'B' for Business Class" << endl;
      cout << "Please type 'E' for Economy Class" << endl;
      cin >> classSelectionFirst;
      // get char of class
      charClass = (char)classSelectionFirst[0];
      // cout << "char"<< charClass << endl;
      // if it is empty
    
      if (emptyPerClass(charClass)) {
        string input;
        char in;
        cout << "The curernt class is full, do you want a seat in the class "
                "lower?"
             << endl;
        cout << "Enter 'Y' if yes, Enter 'N' if no." << endl;
        cin >> input;
        // if it is also empty
        if (input == "Y") {
          if (lowerClassOpen(charClass)) {

            cout << "There is no seat open in the lower class, next flight is "
                    "in "
                    "3 hours!"
                 << endl;
          } else { // else update the seat
            seat = lowerClassSeat(charClass);
            rowNum = seatIntParser(seat);
            seatChar = charParser(seat);
            updateSeat(rowNum, seatChar, name);
            cout << "seat updated to " << seat << endl;
          }
        } else {
          cout << "There is no seat open in the lower class, next flight is "
                  "in "
                  "3 hours!"
               << endl;
        }
      } else {
        seat = initialSelection(charClass);
        rowNum = seatIntParser(seat);
        seatChar = charParser(seat);
        updateSeat(rowNum, seatChar, name);
        cout << "seat updated to " << seat << endl;
      }
        
        upgrade(seat, name);
    }
  }

  void showMenu() {
    cout << "Main Menu:" << endl;
    cout << "Option 1 - Load Previous" << endl;
    cout << "Option 2 - Save Current" << endl;
    cout << "Option 3 - Display Seating Chart" << endl;
    cout << "Option 4 - Choose Seat" << endl;
    cout << "Option 5 - Update Seat Assignment" << endl;
    cout << "Option 6 - Cancel Seat Assignment" << endl;
    cout << "Option 7 - Print Boarding Pass" << endl;
    cout << "Option 8 - Print Passenger Manifest" << endl;
    cout << "Option 9 - Quit" << endl;

    string in;
    int input;
    cout << "Input Menu Number: ";
    cin >> in;
    input = stoi(in);

    switch (input) {
    case 1:
      loadPrevious();
      break;
    case 2:
      saveCurrent();
      break;
    case 3:
      printSeats();
      break;
    case 4:
      chooseInitialSeat();
      break;
    case 5:
      updateHelper();
      break;
    case 6:
      cancelTicket();
      break;
    case 7:
      boardingPassHelper();
      break;
    case 8:
      printManifest();
      break;
    case 9:
      exit(1);
    default:
      cout << endl << "please choose an option from the menu" << endl << endl;
      showMenu();
    }
  }
};

int main() {
  plane p1;
  p1.initialise();
  p1.showMenu();
}