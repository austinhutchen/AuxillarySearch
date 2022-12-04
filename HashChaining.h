//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.h
//-----------------------------------------------------------------------------

#ifndef HASHCHAINING_H
#define HASHCHAINING_H

#include "ProfBST.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
/*
class for hashtable with chaining collision resolution scheme, includes helper functions for all 
essential read, write, and storage operations within the double-pointer hash table.
Also included is a pointer to the BST, which stores professors.
*/
class HashChaining
{
	public:
		HashChaining(int size);
		~HashChaining();
		
        void search(int courseYear, int courseNumber, string profId);		
		void bulkInsert(string filename);
		
        void displayAllCourses();
		void displayCourseInfo(Course* c);
		
		int hash(int courseNumber);

		ProfBST profDb;
		
	private:
		int hashTableSize;
		Course **hashTable;
};

#endif