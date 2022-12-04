//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
//-----------------------------------------------------------------------------
/*
Hash chaining class to insert into the hash chaining table using LL chaining
collision resolution, if spots are filled. Includes insert, search,constructor,
destructor, and displayinfo methods.
*/
#include "HashChaining.h"
#include "ProfBST.h"
#include "util.h"

using namespace std;
/*
Constructs the hash table safely
@param: hash table size
@return: Constructed hash table
*/
HashChaining::HashChaining(int size) {
  this->hashTableSize = size;
  hashTable = new Course *[hashTableSize];
  for (int i = 0; i < hashTableSize; i++)
    hashTable[i] = nullptr;
}
/*
Destroys the chaining hash table and safely frees all pointers
@param:n/a
@retuns: n/a
*/
HashChaining::~HashChaining() {
  Course *curr = NULL;
  Course *next = NULL;
  for (int i = 0; i < hashTableSize; i++) {
    curr = hashTable[i];
    while (curr != NULL) {
      // issue here
      next = curr->next;
      delete curr;
      curr = next;
    }
  }
  delete[] hashTable;
  hashTable = nullptr;
}
/*
Simple hash formula to hash a coursenumber
@param: coursenumber
@retuns: hash value
*/
int HashChaining::hash(int courseNumber) {
  // hash functiong goes here to return key from courseNumber
  return courseNumber % this->hashTableSize;
}
/*
Reads from the given file with filename and inserts all needed data into
hashtable using chaining collision
@param: filename
@retuns: N/A
*/
void HashChaining::bulkInsert(string filename) {
  ifstream fin;
  string line;
  int index;
  string courseno;
  int collisions = 0;
  string coursename;
  string year;
  string department;
  string profid;
  string firstname;
  string lastname;
  string fullname;
  int searches = 0;
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
    // add professor has problem
    profDb.addProfessor(profid, fullname);
    course = new Course(stoi(year), department, stoi(courseno), coursename,
                        profDb.searchProfessor(profid));
    profDb.searchProfessor(profid)->coursesTaught.push_back(course);
    // hash insertions
    index = hash(stoi(courseno));
    if (!hashTable[index]) {
      // course doesnt exist, add new instance
      hashTable[index] = course;
    } else {
      collisions++;
      searches++;
      Course *curr = hashTable[index];
      while (curr->next != NULL) {
        searches++;
        curr = curr->next;
      }
      curr->next = course;
      course->previous = curr;
    }
  }
  fin.close();
  cout << "[CHAINING] Hash table populated" << endl;
  cout << "-------------------------------------" << endl;
  cout << "Collisions using chaining: " << collisions << endl;
  cout << "Search operations using chaining: " << searches << endl;
}

/*
Searches for a course pointer with given parameters, and outputs info if found
@param: courseyear, coursenumber, profid
@retuns: n/a
*/
void HashChaining::search(int courseYear, int courseNumber, string profId) {
  // Compute the index by using the hash function
  int index = hash(courseNumber);
  Course *head = hashTable[index];
  int count = 0;
  Course *curr = head;
  while (curr != NULL) {
    if (curr->courseNum == courseNumber && curr->prof->profId == profId &&
        curr->year == courseYear) {
      cout << "Search operations using chaining: " << count << endl;
      cout << curr->courseNum << " " << curr->courseName << " "
           << curr->prof->profName << endl;
      return;
    }
    curr = curr->next;
    count++;
  }
  cout << "Course not found in Chaining table." << endl;
}
/*
Displays all info of pointers at all indices of the chaining hash table
@param:n/a
@retuns: n/a, only calls displaycourseinfo(), see below description
*/
void HashChaining::displayAllCourses() {
  int counter = 1;
  Course *curr;
  for (int i = 0; i < hashTableSize; i++) {
    curr = hashTable[i];
    while (curr != NULL) {
      cout << counter++ << " ";
      displayCourseInfo(curr);
      curr = curr->next;
    }
  }
}
/*
Displys course info associated with course pointer
@param: Course ptr
@retuns: n/a, only outputs course info using cout
*/
void HashChaining::displayCourseInfo(Course *c) {
  cout << c->year << " " << c->courseName << " " << c->courseNum << " "
       << c->prof->profName << endl;
}