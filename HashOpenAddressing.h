//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.h
//-----------------------------------------------------------------------------

#ifndef HASHOPENADDRESSING_H
#define HASHOPENADDRESSING_H

#include "util.h"
#include "ProfBST.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
/*
class for hashtable with OA collision resolution scheme, includes helper functions for all 
essential read, write, and storage operations within the double-pointer hash table.
Also included is a pointer to the BST, which stores professors.
*/
class HashOpenAddressing
{
	public:
		HashOpenAddressing(int size);
		~HashOpenAddressing();
		
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