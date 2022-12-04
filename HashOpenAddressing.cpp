//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------
/*
Hash OA class to insert into the hash chaining table using quadratic probing
collision resolution, if spots are filled. Includes insert, search,constructor,
destructor, and displayinfo methods.
*/
#include "HashOpenAddressing.h"
#include "HashChaining.h"
#include "ProfBST.h"
#include "util.h"
#include <__nullptr>
#include <cstddef>

using namespace std;
/*
Constructs the hash table safely
@param: hash table size
@return: Constructed hash table
*/
HashOpenAddressing::HashOpenAddressing(int size) {
  this->hashTableSize = size;
  hashTable = new Course *[hashTableSize];
  for (int i = 0; i < hashTableSize; i++)
    hashTable[i] = nullptr;
}
/*
Destroys the hash table and safely frees all pointers
@param:n/a
@retuns: n/a
*/
HashOpenAddressing::~HashOpenAddressing() {
  Course *curr = NULL;
  for (int i = 0; i < hashTableSize; i++) {
    curr = hashTable[i];
    delete curr;
    curr = nullptr;
  }
  delete[] hashTable;
  hashTable = nullptr;
}
/*
Simple hash formula to hash a coursenumber
@param: coursenumber
@retuns: hash value
*/
int HashOpenAddressing::hash(int courseNumber) {
  return courseNumber % this->hashTableSize;
}
/*
Reads from the given file with filename and inserts all needed data into
hashtable using OA collision
@param: filename
@retuns: N/A
*/
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
  int searches = 0;
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
    course =
        new Course(stoi(year), department, stoi(courseno), coursename, prof);
    prof->coursesTaught.push_back(course);
    // hash insertions
    startindex = hash(course->courseNum);
    int i = 0;
    if (hashTable[startindex] == NULL) {
      hashTable[startindex] = course;
    } else {
      collisions++;
      // use quadratic probing to resolve collision HERE
      while (hashTable[startindex] != nullptr) {
        // hash and check current index
        i++;
        startindex = (startindex + (i * i)) % hashTableSize;
      }
      hashTable[startindex] = course;
      searches += i;
    }
  }
  cout << "[OPEN ADDRESSING] Hash table populated" << endl;
  cout << "-------------------------------------" << endl;
  cout << "Collisions using open addressing: " << collisions << endl;
  cout << "Search operations using open addressing: " << searches << endl;
}

/*
Simple check that returns true if passed course pointer fulfills the search
conditions
@param: coursenum, courseyear, profid, courseptr
@retuns: true/false
*/
bool check(int courseNum, int courseYear, string profId, Course *curr) {
  if (curr->courseNum == courseNum && curr->year == courseYear &&
      curr->prof->profId == profId) {
    return true;
  }
  return false;
}
/*
Searches for a course pointer with given parameters, and outputs info if found
@param: courseyear, coursenumber, profid
@retuns: n/a
*/
void HashOpenAddressing::search(int courseYear, int courseNumber,
                                string profId) {
  int index = hash(courseNumber);
  int i = 0;
  // use quadratic probing to search here for the course
  Course *curr = hashTable[index];
  if (curr == NULL) {
    cout << "Course not found in Open Addressing." << endl;
    return;
  }
  if (check(courseNumber, courseYear, profId, curr) == true) {
    cout << curr->courseNum << " " << curr->courseName << " "
         << curr->prof->profName << endl;
    return;
  };
  // location and check, increment counter
  // implement circular array mechanism to ensure newINDEX does not fly out of
  while (hashTable[index] != nullptr) {
    i++;
    index = (index + (i * i)) % hashTableSize;
    curr = hashTable[index];
    if (curr == NULL) {
      cout << "Course not found in Open Addressing." << endl;
      return;
    }
    if (check(courseNumber, courseYear, profId, curr) == true) {
      cout << "Search operations using open addressing: " << i << endl;
      cout << curr->courseNum << " " << curr->courseName << " "
           << curr->prof->profName << endl;
      return;
    }
  }
}
/*
Displays all indices of the hash table
@param:n/a
@retuns: n/a, only calls displaycourseinfo(), see below description
*/
void HashOpenAddressing::displayAllCourses() {
  for (int i = 0; i < this->hashTableSize; i++) {
    if (hashTable[i] != NULL) {
      displayCourseInfo(hashTable[i]);
    }
  }
}
/*
Displys course info associated with course pointer
@param: Course ptr
@retuns: n/a, only outputs course info using cout
*/
void HashOpenAddressing::displayCourseInfo(Course *c) {
  cout << c->year << " " << c->courseName << " " << c->courseNum << " "
       << c->prof->profName << endl;
}
