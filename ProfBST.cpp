//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;

ProfBST::ProfBST() { root = NULL; }

void destroyNode(Professor *currNode) {
  if (currNode != NULL) {
    destroyNode(currNode->left);
    destroyNode(currNode->right);

    delete currNode;
    currNode = NULL;
  }
}

ProfBST::~ProfBST() { destroyNode(root); }

void ProfBST::addProfessor(string profId, string profName) {






}

Professor *ProfBST::searchProfessor(string profId) {
// hash id, find location, and search within chain




}

void ProfBST::publicSearchProfessor(string profId) {}

void ProfBST::displayProfessorInfo(Professor *p) {}
