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
// memory leaks:
//g++ --std=c++11 -Wall -Werror -pedantic -g -fsanitize=address -fsanitize=undefined main.cpp ProfBst.cpp HashOpenAddressing.cpp HashChaining.cpp

// ./a.out cscicoursesB.csv 700
// DEBUG:
// lldb ./a.out cscicoursesB.csv 700

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Invalid number of arguments." << endl;
    cout << "Usage: ./<a.out> <csv file> <hashTable size>" << endl;
    return -1;
  }
  // init variables
  string fname = argv[1];
  int hsize = stoi(argv[2]);
  string choice;
  int input;
  string year;
  string courseno;
  string profID;
  // initialization of hash tables 
  HashOpenAddressing *openaddtable = new HashOpenAddressing(hsize);
  HashChaining *lltable = new HashChaining(hsize);
  // begin loop
  while (true) {
    display();
    cin >> input;
    if(!cin){
      cout << "invalid choice. Enter a number." <<endl;
      break;
    }
    switch (input) {
      // if uses chooses to bulk insert into hash table
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
// if user chooses to search for a course
    case 2: {
      cout << "Enter a course year(e.g. 2021):" << endl;
      cin >> year;
      cout << "Enter a course number(e.g. 2270):" << endl;
      cin >> courseno;
      // error catching to avoid conversion errors
      try {
        stoi(courseno);
        stoi(year);
      } catch (exception &err) {
        cout << "Invalid input." << endl;
        break;
      }
      cout << "Enter a Professor's ID (e.g. llytellf):" << endl;
      cin >> profID;
      // call both methods to search within both tables!
      cout << "[OPEN ADDRESSING] Search for a course" <<endl;
      cout << "----------------------------------------" <<endl;
      openaddtable->search(stoi(year), stoi(courseno), profID);
      cout << "[CHAINING] Search for a course" <<endl;
      cout << "----------------------------------------" <<endl;
      lltable->search(stoi(year), stoi(courseno), profID);
      break;
    }
// If user would like to search for a professor within BST
    case 3: {
      cout << "Enter a Professor's ID (e.g. nscollan0):" << endl;
      cin >> profID;
      // / search BST here
      cout << "[OPEN ADDRESSING] Search for a professor" <<endl;
      cout << "----------------------------------------" <<endl;
      openaddtable->profDb.publicSearchProfessor(profID);
      cout << "[CHAINING] Search for a professor" <<endl;
      cout << "----------------------------------------" <<endl;
      lltable->profDb.publicSearchProfessor(profID);
      break;
    }
// if user would like to display all courses within either hash table with either collision resolution scheme
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
// exit and call destructors, free all memory
    case 5: {
      // destructors called automatically
      cout << "Goodbye!" << endl;
      return 0;
    }
// avoids invalid user input, sends back to beginning of loop
    default:
      cout << "invalid choice" << endl;
    }
  }
}