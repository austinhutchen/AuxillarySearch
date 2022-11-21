//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"
#include "ProfBST.h"
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
// this will change for open addressing
Course *curr = hashTable[index];
curr->previous=course;
course->next=curr;
hashTable[index]=course;
}
}
}


void HashChaining::search(int courseYear, int courseNumber, string profId)
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
  cout << "[CHAINING] Search for a course" <<endl;
  cout<<"-------------------------------------" << endl;
  Course *head = hashTable[index];
  int count=0;
  Course* curr=head;
  while (curr != NULL) {
    if (curr->courseNum== courseNumber&&curr->prof->profId==profId&&curr->year==courseYear) {
    cout << "Search operations using chaining: " << count << endl;
    cout << curr->courseNum << " "<<curr->courseName<<" " << curr->prof->profName << endl;
    return;
    }
    curr = curr->next;
    count++;
  }
  cout << "Course not found." <<endl;
}

void HashChaining::displayAllCourses()
{ 
int counter=1;
Course *curr;
for(int i=0;i<hashTableSize;i++){
    curr=hashTable[i];
    while(curr!=NULL){
        cout << counter++<< " " ;
        displayCourseInfo(curr);
        curr=curr->next;
    }
}
}

void HashChaining::displayCourseInfo(Course* c)
{
cout << c->year << " "<< c->courseName <<" "<< c->courseNum <<" "<< c->prof->profName<<endl;
}