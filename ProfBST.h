//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.h
//-----------------------------------------------------------------------------

#ifndef PROFBST_H
#define PROFBST_H

#include "util.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
/*
Struct for professor pointers, included all given parameters for a professor.
Each instance has coursestaught vector, left and right pointers for travesal within BST, and
information about each professor, including profid and profanme.
*/
struct Professor
{
	string profId;
	string profName;
	vector<Course*> coursesTaught;
	Professor *left;
	Professor *right;

	Professor() {}
	Professor(string pId, string pName) { 
		profId = pId; 
		profName = pName;
		left = nullptr; right = nullptr; 
	}
};

// Professor BST class
class ProfBST
{
    public:
        ProfBST();
        ~ProfBST();
        void addProfessor(string profId, string profName);
		void publicSearchProfessor(string profId);
        Professor *searchProfessor(string profId);
		void displayProfessorInfo(Professor* p);

    private:
		// add helpers here (if needed)
        Professor *root;
};

#endif