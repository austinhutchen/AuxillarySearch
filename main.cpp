//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"
#include "HashOpenAddressing.h"
#include <functional>
#include <iostream>
#include <sstream>
using namespace std;

void display() {
  cout << "=======Main Menu=======" << endl;
  cout << "1. Populate hash tables" << endl;
  cout << "2. Search for a course" << endl;
  cout << "3. Search for a professor" << endl;
  cout << "4. Display all courses" << endl;
  cout << "5. Exit" << endl;
}
// g++ main.cpp ProfBst.cpp HashOpenAddressing.cpp HashChaining.cpp
// ./a.out cscicoursesB.csv 600
// DEBUG:
// lldb ./a.out cscicoursesB.csv 600
// type "run" after above command
int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Invalid number of arguments." << endl;
    cout << "Usage: ./<a.out> <csv file> <hashTable size>" << endl;
    return -1;
  }
  string fname = argv[1];
  int hsize = stoi(argv[2]);
  string choice;
  int input;
  // quadratic probing table
  HashOpenAddressing *openaddtable = new HashOpenAddressing(hsize);
  // doubly linked list
  HashChaining *lltable = new HashChaining(hsize);
  while(true){
  display();
  cin >> input;
  switch (input) {
  case 1: {
    cout << "Which hash table would you like to populate? (O=Open Addressing, "
            "C=Chaining)?"<< endl;
    cin >> choice;
    // if user uses quadratic open addressing
    if (choice == "O" || choice == "o")
      openaddtable->bulkInsert(fname);
    // if user uses ll chaining
    else if (choice == "C" || choice == "c")
      lltable->bulkInsert(fname);
    break;
  }

  case 2: {

  }
  case 3: {
  }

  case 4: {
    cout << "Which hash table would you like to display? (O=Open Addressing, "
            "C=Chaining)?"<< endl;
                cin >> choice;
    // if user uses quadratic open addressing
    if (choice == "O" || choice == "o")
      openaddtable->displayAllCourses();
    // if user uses ll chaining
    else if (choice == "C" || choice == "c")
      lltable->displayAllCourses();
    break;
  }

  case 5: {
    openaddtable->~HashOpenAddressing();
    lltable->~HashChaining();
    cout << "Goodbye!" << endl;

  }
  default:
    return 0;
  }
  }
}