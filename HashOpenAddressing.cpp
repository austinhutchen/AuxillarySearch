//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"
#include "ProfBST.h"
#include "util.h"

using namespace std;

HashOpenAddressing::HashOpenAddressing(int size) {
  this->hashTableSize = size;
  hashTable = new Course *[hashTableSize];
  for (int i = 0; i < hashTableSize; i++)
    hashTable[i] = nullptr;
}

HashOpenAddressing::~HashOpenAddressing() {
  Course *curr = NULL;
  Course *course = NULL;
  for (int i = 0; i < hashTableSize; i++) {
    curr = hashTable[i];
    while (curr != nullptr) {
      course = curr;
      delete course;
      curr = curr->next;
    }
  }
  delete[] hashTable;
}

int HashOpenAddressing::hash(int courseNumber) {
  return courseNumber % this->hashTableSize;
}
void findnewindex(int count, int &newindex,int start,int hsize){
newindex = (start + count * count) % hsize;
}
void HashOpenAddressing::bulkInsert(string filename) {
  ProfBST root;
  ifstream fin;
  string line;
  int index;
  int collisions = 0;
  string courseno;
  string coursename;
  string year;
  string department;
  string profid;
  string firstname;
  string lastname;
  string fullname;
  Professor * temp;
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
    index = hash(stoi(courseno));
    fullname = firstname + " " + lastname;
    Professor *prof = new Professor(profid, fullname);
    Course *course = new Course(stoi(year), department, stoi(courseno), coursename, prof);
    temp=profDb.searchProfessor(profid);
    if(temp==NULL){
      // prof does not exist yet
    profDb.addProfessor(profid,  fullname);
    prof->coursesTaught.push_back(course);
    }
    else{
      // prof already exists
      prof->coursesTaught.push_back(course);
    }

    if (hashTable[index] == NULL) {
      hashTable[index] = course;
    } else {
      // use quadratic probing to resolve collision HERE
      // use circular array to hit all spots?
      // check if newIndex==hashtableSize-1
      int newIndex = (index + collisions * collisions) % this->hashTableSize;
      while(hashTable[newIndex]!=NULL){
      collisions++;
      findnewindex(collisions, newIndex,index, this->hashTableSize);
      }
      if(hashTable[newIndex]==NULL){
      hashTable[newIndex] = course;
      }
    }
  }
}

void HashOpenAddressing::search(int courseYear, int courseNumber,string profId) {
cout << "[OPEN ADDRESSING] Search for a course" << endl;
cout << "-------------------------------------" << endl;
  int index = hash(courseNumber);
  int collisions=1;
  // use quadratic probing to search here for the course
    Course *curr = hashTable[index];
    if(curr==NULL){
        cout << "Course not found in Open Addressing." << endl;
        return;
    }
    else if(curr->courseNum == courseNumber && curr->year == courseYear && curr->prof->profId == profId){
        cout << "Search operations using open addressing:" << collisions<<endl ;
        cout << curr->courseNum << " " << curr->courseName << " "<< curr->prof->profName << " " << curr->prof->profId<< endl;
      }
      // not the exact courde, use quadratic probing to move to next possible location and check, increment counter
    else{
    // implement circular array mechanism to ensure newINDEX does not fly out of bounds and hits every index
    int newIndex ;
      while(curr!=NULL){
      collisions++;
      findnewindex(collisions, newIndex,index, this->hashTableSize);
      curr = hashTable[newIndex];
      // all indices visited, course not found
      if(curr==NULL)
      return;
      else if(curr->courseNum == courseNumber && curr->year == courseYear && curr->prof->profId == profId){
        cout << "Search operations using open addressing:" << collisions<<endl ;
        cout << curr->courseNum << " " << curr->courseName << " "<< curr->prof->profName <<endl;
      }
      }
        cout << "Course not found in Open Addressing." << endl;
        return;
    } 
}

void HashOpenAddressing::displayAllCourses() {
  for (int i = 0; i < this->hashTableSize; i++) {
    displayCourseInfo(hashTable[i]);
  }
}

void HashOpenAddressing::displayCourseInfo(Course *c) {
  if (c == NULL) {
    return;
  }
  cout << c->year << " " << c->courseName << " " << c->courseNum << " "<< c->prof->profName << endl;
}
