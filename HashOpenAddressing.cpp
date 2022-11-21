//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"
#include "util.h"

using namespace std;

HashOpenAddressing::HashOpenAddressing(int size)
{
this->hashTableSize=size;
hashTable = new Course *[hashTableSize];
for(int i=0;i<hashTableSize;i++)
    hashTable[i]=nullptr;
}

HashOpenAddressing::~HashOpenAddressing()
{
 Course *curr=NULL;
 Course *course=NULL;
 for (int i = 0; i < hashTableSize; i++) {
        curr = hashTable[i];            
        while (curr != nullptr) {
            course=curr;
            delete course;     
            curr = curr->next;     
        }
    }
    delete[] hashTable;
}

int HashOpenAddressing::hash(int courseNumber)
{
return courseNumber % this->hashTableSize;
}

void HashOpenAddressing::bulkInsert(string filename)
{
ifstream fin;
string line;
int index;
int collisions=0;
string courseno;
string coursename;
string year;
string department;
string profid;
string firstname;
string lastname;
string fullname;
fin.open(filename);
// filename is wrong
if(!fin.is_open()){
cout << "FILE READ ERROR. Could not open file." << endl;
return;
}
std::getline(fin, line); // skip the first line
while(getline(fin,line)&&line.length()!=0){
// hash the course number 
stringstream parse(line);
getline(parse,year,',');
getline(parse,department,',');
getline(parse,courseno,',');
getline(parse,coursename,',');
getline(parse,profid,',');
getline(parse,firstname,',');
getline(parse,lastname,'\n');
// variables stored
index=hash(stoi(courseno));
fullname=firstname+" " +lastname;
Professor *prof= new Professor(profid,fullname);
// add professor to BST here probably
/*
ProfBST root;
root.addProfessor(profid, firstname);
*/
Course *course=new Course(stoi(year),department,stoi(courseno),coursename,prof);
prof->coursesTaught.push_back(course);
//Course(int newYear, string newDepartment, int newCourseNum, string newCourseName, Professor *newProf = nullptr)
if(hashTable[index]==NULL){
// course doesnt exist, add new instance
hashTable[index]= course;
}
else{
// use quadratic probing to resolve collision HERE
collisions++;
int newIndex = (index + collisions*collisions) % this->hashTableSize;
hashTable[newIndex]=course;
}
}

}

void HashOpenAddressing::search(int courseYear, int courseNumber, string profId)
{
    /*[OPEN ADDRESSING] Search for a course -------------------------------------
Search operations using open addressing: 2
2021 COMP SCI I: PROGRAMMING 1300 Rene Fauning
[CHAINING] Search for a course -------------------------------------
Search operations using chaining: 1
2021 COMP SCI I: PROGRAMMING 1300 Rene Fauning
*/
  // Compute the index by using the hash function
  int index = hash(courseNumber);
  cout << "[OPEN ADDRESSING] Search for a course" <<endl;
  cout<<"-------------------------------------" << endl;
  for(int i=0;i<this->hashTableSize;i++){
  Course* curr= hashTable[i];
  if(curr->courseNum==courseNumber&&curr->year==courseYear&&curr->prof->profId==profId){
    displayCourseInfo(curr);
    return ;
  }
  }
  int count=0;
  cout << "Course not found." <<endl;
}

void HashOpenAddressing::displayAllCourses()
{
for(int i=0;i<this->hashTableSize;i++){
  displayCourseInfo(this->hashTable[i]);
  }
}

void HashOpenAddressing::displayCourseInfo(Course* c)
{
    if(c==NULL){
        return;
    }
cout << c->year << " "<< c->courseName <<" "<< c->courseNum <<" "<< c->prof->profName<<endl;
}