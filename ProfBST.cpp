//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------
/*
BST class to store professors and their associated pointers, which contain given info about any professor.
Included traversal, search, constructor, and destructor methods for effectively finding professor info within the tree.
*/
#include "ProfBST.h"
#include "HashChaining.h"

#include <iostream>

using namespace std;
/*
Constructs the BST safely
@param: N/A
@return: constructed BST with root set to NULL
*/
ProfBST::ProfBST() { root = nullptr; }
/*
DESTRUCTOR HELPER
Recursively destroys the entire tree
@param: root pointer
@return: VOID
*/
void destroyNode(Professor *currNode) {
  if (currNode) {
    destroyNode(currNode->left);
    destroyNode(currNode->right);
    delete currNode;
  }
}
/*
DESTRUCTOR 
simply calls above function to destroy tree on exit-> see description above
@param: N/A
@return: VOID
*/
ProfBST::~ProfBST() { destroyNode(root); }
/*
CREATE PROFESSOR HELPER
Creates an instance of a professor on the heap with given profname and profid
@param: profname, profID
@return: pointer to new professor instance on the heap
*/
Professor *createprof(string profname, string profId){
  return new Professor(profId,profname);
}
/*
ADD HELPER
Recursively adds a professor with given profname and profID to the correct position in the tree
@param: Professor pointer, professor name, and profid
@return: pointer to the position that the new professor is added at within BST
*/
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
/*
ADD PROFESSOR
Simply calls above addhelper to add the professor to correct position within tree
@param: profid, profname
@return: VOID
*/
void ProfBST::addProfessor(string profId, string profName) {
  if(!searchProfessor(profId)){
    // profID is working fine, but only name stored is Liz Naris
    root=addhelper(root, profName,profId);
  }
}
  

/*
SEARCH HELPER
Recursively searches for professor within sorted BST with given profID tag
@param: Iterator pointer starting at root, and profID
@return: Found professor pointer or NULL
*/
Professor * searchhelper(Professor* current, string profId){
  if(!current||current->profId==profId){
  return current;
}
if(current->profId<profId){
    return searchhelper(current->right,profId);
  } 
    return searchhelper(current->left, profId);
}
/*
SEARCH PROFESSOR
Simply calls recursive search method to find the professor with given profid and returns
@param: profID
@return: Found professor pointer or NULL if not found 
*/
Professor *ProfBST::searchProfessor(string profId) {
return searchhelper(root, profId);
}
/*
PUBLIC SEARCH PROFESSOR
Simply calls recursive search method to find the professor with given profid and outputs information after found
@param: profID
@return: N/A, outputs professor information or "prof not found" if professor is NULL and not found within BST  
*/
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
/*
DISPLAY PROFESSOR INFO
Simply displays info associated with a professor.
@param: Professor pointer
@return: VOID, only outputs to the terminal given info about a professor if professor is found, outputs "not found" if NULL
*/
void ProfBST::displayProfessorInfo(Professor *p) {
if(p->coursesTaught.size()==0){
  cout << "No courses taught." <<endl;
}
for(int i=0;i<p->coursesTaught.size();i++){
  cout << p->coursesTaught[i]->courseNum << " " <<p->coursesTaught[i]->courseName << ", " <<p->coursesTaught[i]->year<<endl;
}
}
