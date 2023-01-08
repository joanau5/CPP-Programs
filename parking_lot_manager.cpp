#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void menu() {
  cout << "----------\n";
  cout << "|  MENU  |\n";
  cout << "----------\n";
  cout << "Please use one of the following commands:\n";
  cout << "  - (CT) check time\n";
  cout << "  - (AT) advance time\n";
  cout << "  - (SS) show spots\n";
  cout << "  - (TS) take spot\n";
  cout << "  - (CP) check price\n";
  cout << "  - (LS) leave spot\n";
  cout << "  - (CS) check stats\n";
  cout << "  - (EX) exit the program\n";
}

void split_str(string const &str, const char delim, vector<string> &out) {
  // create a stream from the string
  stringstream s(str);

  string s2;
  while (getline(s, s2, delim)) {
    out.push_back(s2);  // store the string in s2
  }
}

int main() {
  cout << "----------\n";
  cout << "Hello! Welcome to the parking lot manager.\n";
  cout << "I'll help you find a spot!\n";
  cout << "----------\n\n";
  string input1 = "";
  int open_s[4][6] = {{1, 2, 3, 4, 5, 6},
                      {7, 8, 9, 10, 11, 12},
                      {13, 14, 15, 16, 17, 18},
                      {19, 20, 21, 22, 23, 24}};
  int taken_s[4][6] = {};
  int time_s[4][6] = {};
  string plate_s[4][6] = {};
  string placeholder[4][6] = {};
  int minutes = 0;
  int TOTAL_PARKED = 0;
  int CURRENTLY_PARKED = 0;
  int CLEFT = 0;
  int TOTAL_CHARGED = 0;
  int AVERAGE_CHARGE = 0;
  while (input1 != "EX") {
    menu();
    getline(cin, input1);
    string delimiter = " ";
    if (input1.find("EX") < input1.length()) {
      cout << "Goodbye!";
    } else if (input1.find("CT") < input1.length()) {
      cout << "We have been open for " << minutes << " minutes!\n";
    } else if (input1.find("AT") < input1.length()) {
      const char delim = ' ';
      vector<string> out;
      split_str(input1, delim, out);
      int counter = 0;
      for (const auto &input1 : out) {
        placeholder[1][1] = input1;
        counter++;
      }
      string act = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      string t1 = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      string t2 = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      int num1 = stoi(t1);
      int num2 = stoi(t2);
      if (counter == 2) {
        minutes = minutes + num1;
        for (int row = 0; row < 4; row++) {
          for (int col = 0; col < 6; col++) {
            if (time_s[row][col] == 2) {
              time_s[row][col] = time_s[row][col] + num1 - 2;
            } else if (time_s[row][col] != 0) {
              time_s[row][col] = time_s[row][col] + num1;
            }
          }
        }
      } else {
        minutes = minutes + num2 + (num1 * 60);
        for (int row = 0; row < 4; row++) {
          for (int col = 0; col < 6; col++) {
            if (time_s[row][col] == 2) {
              time_s[row][col] = time_s[row][col] + (num2 + (num1 * 60)) - 2;
            } else if (time_s[row][col] != 0) {
              time_s[row][col] = time_s[row][col] + (num2 + (num1 * 60));
            }
          }
        }
      }
    } else if (input1.find("SS") < input1.length()) {
      string act = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      string t1 = input1.substr(0, input1.find(delimiter));
      if (t1.find('O') != string::npos) {
        cout << "Open spots:\n";
        int rcount = 1;
        for (int row = 0; row < 4; row++) {
          cout << "Row " << rcount << ":";
          rcount++;
          for (int col = 0; col < 6; col++) {
            if (open_s[row][col] != 0) {
              cout << " " << open_s[row][col];
            }
          }
          cout << "\n";
        }
      } else if (t1.find('T') != string::npos) {
        cout << "Taken spots:\n";
        int rcount = 1;
        for (int row = 0; row < 4; row++) {
          cout << "Row " << rcount << ":";
          rcount++;
          for (int col = 0; col < 6; col++) {
            if (taken_s[row][col] != 0) {
              cout << " " << taken_s[row][col];
            }
          }
          cout << "\n";
        }
      } else if (t1.find('A') != string::npos) {
        cout << "Open spots:\n";
        int rcount = 1;
        for (int row = 0; row < 4; row++) {
          cout << "Row " << rcount << ":";
          rcount++;
          for (int col = 0; col < 6; col++) {
            if (open_s[row][col] != 0) {
              cout << " " << open_s[row][col];
            }
          }
          cout << "\n";
        }
        cout << "\n";
        cout << "Taken spots:\n";
        int rcount1 = 1;
        for (int row = 0; row < 4; row++) {
          cout << "Row " << rcount1 << ":";
          rcount1++;
          for (int col = 0; col < 6; col++) {
            if (taken_s[row][col] != 0) {
              cout << " " << taken_s[row][col];
            }
          }
          cout << "\n";
        }
      }
    } else if (input1.find("TS") < input1.length()) {
      string act = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      string row_T = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      string col_T = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      string plate = input1;
      int roww = stoi(row_T) - 1;
      int coll = stoi(col_T) - 1;
      if (open_s[roww][coll] != 0) {
        int spotn = (roww * 6) + coll + 1;
        taken_s[roww][coll] = spotn;
        TOTAL_PARKED++;
        open_s[roww][coll] = 0;
        time_s[roww][coll] = 2;
        plate_s[roww][coll] = plate;
        cout << "Parked " << plate << " in spot " << spotn << ".\n";
      } else {
        int spotn = ((roww - 1) * 6) + coll + 1;
        if (spotn == 25) {
          cout << "Sorry, you've passed all the open spots already!\n";
          break;
        } else {
          for (int col = coll; col < 7; col++) {
            if (col == 6) {
              roww = roww + 1;
              col = 0;
            }
            if (taken_s[roww][col] == 0) {
              int spotn1 = (roww * 6) + col + 1;
              if (spotn1 >= 25) {
                cout << "Sorry, you've passed all the open spots already!\n";
                break;
              }
              taken_s[roww][col] = spotn1;
              TOTAL_PARKED++;
              open_s[roww][col] = 0;
              time_s[roww][col] = 2;
              plate_s[roww][col] = plate;
              cout << "Parked " << plate << " in spot " << spotn1 << ".\n";
              break;
            }
          }
        }
      }
    } else if (input1.find("CP") < input1.length()) {
      string act = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      string pslashr = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      string s_col = input1;
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      int locr = 0, locc = 0;
      if (pslashr == s_col) {
        for (int row = 0; row < 4; row++) {
          for (int col = 0; col < 6; col++) {
            if (plate_s[row][col] == pslashr) {
              locr = row;
              locc = col;
              break;
            }
          }
        }
        int pmin = time_s[locr][locc];
        if (pmin == 2) {
          pmin = 0;
        }
        int fprice = 0;
        float price = 0;
        double rateformin = (10 / double(60));
        if (pmin < 300) {
          price = pmin * rateformin;
          fprice = floor(price);
        } else if (pmin > 365) {
          price = (pmin - 60) * rateformin;
          fprice = floor(price);
        } else {
          fprice = 50;
        }
        int snum = (locr * 6) + locc + 1;
        cout << "Vehicle " << pslashr << " has been in " << snum << " for "
             << pmin << " minutes.\n"
             << "It owes $" << fprice << " at the moment.\n";
      } else {
        locr = stoi(pslashr) - 1;
        locc = stoi(s_col) - 1;
        int pmin = time_s[locr][locc];
        if (pmin == 2) {
          pmin = 0;
        }
        int fprice = 0;
        float price = 0;
        double rateformin = (10 / double(60));
        string plate = plate_s[locr][locc];
        if (pmin < 300) {
          price = pmin * rateformin;
          fprice = floor(price);
        } else if (pmin > 365) {
          price = (pmin - 60) * rateformin;
          fprice = floor(price);
        } else {
          fprice = 50;
        }
        int snum = (locr * 6) + locc + 1;
        cout << "Vehicle " << plate << " has been in " << snum << " for "
             << pmin << " minutes.\n"
             << "It owes $" << fprice << " at the moment.\n";
      }
    } else if (input1.find("LS") < input1.length()) {
      string act = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      string pslashr = input1.substr(0, input1.find(delimiter));
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      string s_col = input1;
      input1.erase(0, input1.find(delimiter) + delimiter.length());
      int locr = 0, locc = 0;
      if (pslashr == s_col) {
        for (int row = 0; row < 4; row++) {
          for (int col = 0; col < 6; col++) {
            if (plate_s[row][col] == pslashr) {
              locr = row;
              locc = col;
              break;
            }
          }
        }
        int pmin = time_s[locr][locc];
        if (pmin == 2) {
          pmin = 0;
        }
        int fprice = 0;
        float price = 0;
        double rateformin = (10 / double(60));
        if (pmin < 300) {
          price = pmin * rateformin;
          fprice = floor(price);
        } else if (pmin > 365) {
          price = (pmin - 60) * rateformin;
          fprice = floor(price);
        } else {
          fprice = 50;
        }
        string plate = plate_s[locr][locc];
        int snum = (locr * 6) + locc + 1;
        open_s[locr][locc] = snum;
        taken_s[locr][locc] = 0;
        time_s[locr][locc] = 0;
        plate_s[locr][locc] = " ";
        CLEFT++;
        TOTAL_CHARGED = TOTAL_CHARGED + fprice;
        cout << "Vehicle " << plate << " left spot " << snum << "." << endl
             << "It was parked there for " << pmin << " minutes and paid $"
             << fprice << ".\n";
      } else {
        locr = stoi(pslashr) - 1;
        locc = stoi(s_col) - 1;
        int pmin = time_s[locr][locc];
        if (pmin == 2) {
          pmin = 0;
        }
        int fprice = 0;
        float price = 0;
        double rateformin = (10 / double(60));
        string plate = plate_s[locr][locc];
        if (pmin < 300) {
          price = pmin * rateformin;
          fprice = floor(price);
        } else if (pmin > 365) {
          price = (pmin - 60) * rateformin;
          fprice = floor(price);
        } else {
          fprice = 50;
        }
        int snum = (locr * 6) + locc + 1;
        open_s[locr][locc] = snum;
        taken_s[locr][locc] = 0;
        time_s[locr][locc] = 0;
        plate_s[locr][locc] = " ";
        CLEFT++;
        TOTAL_CHARGED = TOTAL_CHARGED + fprice;
        cout << "Vehicle " << plate << " left spot " << snum << "." << endl
             << "It was parked there for " << pmin << " minutes and paid $"
             << fprice << ".\n";
      }
    } else if (input1.find("CS") < input1.length()) {
      if (CLEFT != 0) {
        CURRENTLY_PARKED = TOTAL_PARKED - CLEFT;
        AVERAGE_CHARGE = TOTAL_CHARGED / CLEFT;
        cout << "Total vehicles parked: " << TOTAL_PARKED << endl;
        cout << "Vehicles currently parked: " << CURRENTLY_PARKED << endl;
        cout << "Total amount charged: $" << TOTAL_CHARGED << endl;
        cout << "Average charge per vehicle: $" << AVERAGE_CHARGE << endl;
      } else {
        cout << "Total vehicles parked: " << TOTAL_PARKED << endl;
        cout << "Vehicles currently parked: " << TOTAL_PARKED << endl;
        cout << "Total amount charged: $" << TOTAL_CHARGED << endl;
        cout << "Average charge per vehicle: $" << AVERAGE_CHARGE << endl;
      }
    } else {
      cout << "Sorry, that command is invalid.\n";
    }
    cout << "\n";
  }

  return 0;
}