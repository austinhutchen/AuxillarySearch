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

}

void HashOpenAddressing::bulkInsert(string filename)
{

}

void HashOpenAddressing::search(int courseYear, int courseNumber, string profId)
{

}

void HashOpenAddressing::displayAllCourses()
{

}

void HashOpenAddressing::displayCourseInfo(Course* c)
{
	
}