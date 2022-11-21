//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"
#include "HashOpenAddressing.h"
#include "ProfBST.h"
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
// ./a.out cscicoursesB.csv 700
// DEBUG:
// lldb ./a.out cscicoursesB.csv 700
// type "run" after above command
// linked list implementation done, work on quadratic resolution next
// work on BST for professors
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
  string year;
  string courseno;
  string profID;
  HashOpenAddressing *openaddtable = new HashOpenAddressing(hsize);
  HashChaining *lltable = new HashChaining(hsize);
  ProfBST *tree= new ProfBST();
  // begin loop
  while (true) {
    display();
    cin >> input;
    switch (input) {
    case 1: {
      cout << "Which hash table would you like to populate? (O=Open Addressing, C=Chaining)?"<< endl;
      cin >> choice;
      // add professor to BST in both?
      // if user uses quadratic open addressing
      if (choice == "O" || choice == "o")
        openaddtable->bulkInsert(fname);
      // if user uses ll chaining
      else if (choice == "C" || choice == "c")
        lltable->bulkInsert(fname);
      break;
    }

    case 2: {
      cout << "Enter a course year(e.g. 2021):" << endl;
      cin >> year;
      cout << "Enter a course number(e.g. 2270):" << endl;
      cin >> courseno;
      try {
        stoi(courseno);
        stoi(year);
      } catch (exception &err) {
        cout << "Invalid input." << endl;
        break;
      }
      cout << "Enter a Professor's ID (e.g. llytellf):" << endl;
      cin >> profID;
      lltable->search(stoi(year), stoi(courseno), profID);
      openaddtable->search(stoi(year), stoi(courseno), profID);
      break;
    }

    case 3: {
      cout << "--------THIS CASE IS NOT DONE YET, PROCEED CAREFULLY WITH DEBUGGER ---------" << endl;
      cout << "Enter a Professor's ID (e.g. nscollan0):" << endl;
      cin >> profID;
      tree->searchProfessor(profID);
      // profBST->searchprofessor
      break;
    }

    case 4: {
      cout << "Which hash table would you like to display? (O=Open Addressing, C=Chaining)?"<< endl;
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
      tree->~ProfBST();
      cout << "Goodbye!" << endl;
      return 0;
    }

    default:
      cout << "invalid choice" << endl;
      break;
    }
  }
}