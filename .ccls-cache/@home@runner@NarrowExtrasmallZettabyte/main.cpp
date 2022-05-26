#include <iostream>
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
  passenger passenger[8][9];

  void printSeats() {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 11; j++) {
        if (passenger[i][j].isle == true) {
          cout << " ";
        } else {
          if (passenger[i][j].occupied == true) {
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
  }
  void updateSeat(int num1, int seat, string passName) {
    plane[num1][seat].occupied = true;
    plane[num1][seat].name = passName;
  }
};

int main() {
  plane plane;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 11; j++) {
      if ((j == 2) || (j == 7)) {
        plane.passenger[i][j].isle = true;
        plane.passenger[i][j].occupied = true;
      } else {
        plane.passenger[i][j].isle = false;

        plane.passenger[i][j].occupied = false;
      }
    }
  }
  plane.printSeats();
}
