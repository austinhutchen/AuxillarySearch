//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"
#include "HashChaining.h"

#include <iostream>

using namespace std;

ProfBST::ProfBST() { root = nullptr; }

void destroyNode(Professor *currNode) {
  if (currNode != NULL) {
    destroyNode(currNode->left);
    destroyNode(currNode->right);
    delete currNode;
    currNode = NULL;
  }
}

ProfBST::~ProfBST() { destroyNode(root); }

Professor *createprof(string profname, string profId){
  return new Professor(profId,profname);
}

Professor* addhelper(Professor *curr, string profName, string profId){
if(curr==NULL){
  // insertion spot found for root
  return createprof(profName, profId);
}
if(profId<curr->profId){
    curr->left = addhelper(curr->left,profName,profId);
  } 
else {
    curr->right = addhelper(curr->right, profName,profId);
  }
  return curr;
}

void ProfBST::addProfessor(string profId, string profName) {
  if(!searchProfessor(profId)){
    // profID is working fine, but only name stored is Liz Naris
    root=addhelper(root, profName,profId);
  }
}
  


Professor * searchhelper(Professor* current, string profId){
  if(!current||current->profId==profId){
  return current;
}
if(current->profId<profId){
    return searchhelper(current->right,profId);
  } 
    return searchhelper(current->left, profId);
}

Professor *ProfBST::searchProfessor(string profId) {
return searchhelper(root, profId);
}

void ProfBST::publicSearchProfessor(string profId) {
Professor *prof = searchProfessor(profId);
if(prof==NULL){
cout << "Prof not found." <<endl;
}
else{
cout << "Name: " << prof->profName <<endl;
displayProfessorInfo(prof);
}
}

void ProfBST::displayProfessorInfo(Professor *p) {
if(p->coursesTaught.size()==0){
  cout << "No courses taught." <<endl;
}
for(int i=0;i<p->coursesTaught.size();i++){
  cout << p->coursesTaught[i]->courseNum << " " <<p->coursesTaught[i]->courseName << ", " <<p->coursesTaught[i]->year<<endl;
}
}
