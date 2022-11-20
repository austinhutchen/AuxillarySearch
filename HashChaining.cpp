//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"
#include "util.h"

using namespace std;

HashChaining::HashChaining(int size)
{
this->hashTableSize=size;
hashTable = new Course *[hashTableSize];
for(int i=0;i<hashTableSize;i++)
    hashTable[i]=nullptr;
}

HashChaining::~HashChaining()
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

int HashChaining::hash(int courseNumber)
{
// hash functiong goes here to return key from courseNumber
return courseNumber % this->hashTableSize;
}

void HashChaining::bulkInsert(string filename)
{
ifstream fin;
string line;
int index;
string courseno;
string coursename;
string year;
string department;
string profid;
string firstname;
string lastname;
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
Professor *prof;
prof->profId=profid;
prof->profName=firstname;
// create course instance for hash table
Course *course=new Course(stoi(year),department,stoi(courseno),coursename,prof);
prof->coursesTaught.push_back(course);
//Course(int newYear, string newDepartment, int newCourseNum, string newCourseName, Professor *newProf = nullptr)
if(hashTable[index]==NULL){
// course doesnt exist, add new instance
hashTable[index]= course;
}
else{
// something already exists at index, add to end of doubly linked list
// this will change for open addressing
Course *curr = hashTable[index];
curr->previous=course;
course->next=curr;
// insertion of course instance at head of ll successful
}
}
}


void HashChaining::search(int courseYear, int courseNumber, string profId)
{
  // Compute the index by using the hash function
  int index = hash(courseNumber);
  Course *head = hashTable[index];
  Course* curr=head;
  while (curr != NULL) {
    if (curr->courseNum== courseNumber&&curr->prof->profId==profId&&curr->year==courseYear) {
    displayCourseInfo(curr);
    }
    curr = curr->next;
  }
}

void HashChaining::displayAllCourses()
{
Course *curr;
for(int i=0;i<hashTableSize;i++){
    curr=hashTable[i];
    while(curr!=NULL){
        displayCourseInfo(curr);
        curr=curr->next;
    }
}
}

void HashChaining::displayCourseInfo(Course* c)
{
if(c==NULL){
        return;
    }
cout << c->year << " "<< c->courseName <<" "<< c->courseNum <<" "<< c->prof->profName <<endl;
}