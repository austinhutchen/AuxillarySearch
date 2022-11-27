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

Professor* addhelper(Professor *curr, Professor *newprof){
if(!curr){
  return newprof;
}
if(curr->profName<newprof->profName){
    curr->right = addhelper(curr->right,newprof);
  } 
if (curr->profName>newprof->profName) {
    curr->left = addhelper(curr->left, newprof);
  }
return curr;
}

void ProfBST::addProfessor(string profId, string profName) {
  //problem below using the root for some reason
  root=addhelper(root, new Professor(profId,profName));
}
  


Professor * searchhelper(Professor* current, string profId){
  if(!current||current->profId==profId){
  return current;
}
if(current->profId<profId){
    current->right = searchhelper(current->right,profId);
  } 
if (current->profId>profId) {
    current->left = searchhelper(current->left, profId);
  }
return current;
}

Professor *ProfBST::searchProfessor(string profId) {
  Professor * prof = searchhelper(root, profId);
return prof;
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
