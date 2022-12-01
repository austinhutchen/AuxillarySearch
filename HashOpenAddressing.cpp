//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"
#include "ProfBST.h"
#include "util.h"
#include <cstddef>

using namespace std;

HashOpenAddressing::HashOpenAddressing(int size) {
  this->hashTableSize = size;
  hashTable = new Course *[hashTableSize];
  for (int i = 0; i < hashTableSize; i++)
    hashTable[i] = nullptr;
}

HashOpenAddressing::~HashOpenAddressing() {
  Course *curr = NULL;
  for (int i = 0; i < hashTableSize; i++) {
    curr = hashTable[i];
    delete curr;
    curr=nullptr;
  }
  delete[] hashTable;
  hashTable=nullptr;
}

int HashOpenAddressing::hash(int courseNumber) {
  return courseNumber % this->hashTableSize;
}

void HashOpenAddressing::bulkInsert(string filename) {
  ProfBST root;
  ifstream fin;
  string line;
  int startindex;
  int collisions = 0;
  string courseno;
  string coursename;
  string year;
  string department;
  string profid;
  string firstname;
  string lastname;
  string fullname;
  int newIndex;
  int searches = 0;
  Course *curr;
  Professor *prof;
  Course *course;
  fin.open(filename);
  // filename is wrong
  if (!fin.is_open()) {
    cout << "FILE READ ERROR. Could not open file." << endl;
    return;
  }
  std::getline(fin, line); // skip the first line
  while (getline(fin, line) && line.length() != 0) {
    // hash the course number
    stringstream parse(line);
    getline(parse, year, ',');
    getline(parse, department, ',');
    getline(parse, courseno, ',');
    getline(parse, coursename, ',');
    getline(parse, profid, ',');
    getline(parse, firstname, ',');
    getline(parse, lastname, '\n');
    // variables stored
    fullname = firstname + " " + lastname;
    // add professor
    profDb.addProfessor(profid, fullname);
    prof = profDb.searchProfessor(profid);
    course =new Course(stoi(year), department, stoi(courseno), coursename, prof);
    prof->coursesTaught.push_back(course);
    // hash insertions
    startindex = hash(stoi(courseno));
    curr = hashTable[startindex];
    int i=0;
    if (curr == NULL) {
      hashTable[startindex] = course;
    } else {
      collisions++;
      searches++;
      // use quadratic probing to resolve collision HERE
      while (i<hashTableSize) {
        i++;
        searches++;
        // hash and check current index
        newIndex = (startindex + (i * i)) % hashTableSize;
        if(hashTable[newIndex]==NULL){
          hashTable[newIndex] = course;
          break;
        }
      }
    }
  }
  cout << "[OPEN ADDRESSING] Hash table populated" << endl;
  cout << "-------------------------------------" << endl;
  cout << "Collisions using open addressing: " << collisions << endl;
  cout << "Search operations using open addressing: " << searches << endl;
}


bool check(int courseNum, int courseYear, string profId,Course *curr) {
  if (curr->courseNum == courseNum && curr->year == courseYear &&curr->prof->profId == profId) {
  return true;
    }
  return false;
}

void HashOpenAddressing::search(int courseYear, int courseNumber,string profId) {
  int index = hash(courseNumber);
  int i = 0;
  // use quadratic probing to search here for the course
  Course *curr = hashTable[index];
  if(curr==NULL){
    cout << "Course not found in Open Addressing." << endl;
    return;
  }
  if(check(courseNumber, courseYear, profId, curr)==true){
    cout << curr->courseNum << " " << curr->courseName << " "<< curr->prof->profName << endl;
    return;
  };
  // not the exact courde, use quadratic probing to move to next possible
  // location and check, increment counter
    // implement circular array mechanism to ensure newINDEX does not fly out of
    // bounds and hits every index
    int newIndex;
    while (hash(i)!=index) {
      i++;
      newIndex = (index + (i * i)) % hashTableSize;
      curr=hashTable[newIndex];
      if(curr==NULL){
    cout << "Course not found in Open Addressing." << endl;
    return;
    }
      if(check(courseNumber, courseYear, profId, curr)==true){
        cout << "Search operations using open addressing: " <<i <<endl;
        cout << curr->courseNum << " " << curr->courseName << " "<< curr->prof->profName << endl;
    return;
    }
    }
}

void HashOpenAddressing::displayAllCourses() {
  int counter =1;
  for (int i = 0; i < this->hashTableSize; i++) {
    if(hashTable[i]!=NULL){
    cout << counter << " " ;
    displayCourseInfo(hashTable[i]);
    counter++;
    }
  }
}

void HashOpenAddressing::displayCourseInfo(Course *c) {
  cout << c->year << " " << c->courseName << " " << c->courseNum << " "<< c->prof->profName << endl;
}
