<img src="https://www.colorado.edu/cs/profiles/express/themes/ucb/images/cu-boulder-logo-text-black.svg" alt="CU Boulder Logo" width="500">

# CSCI 2270: Data Structures <br/> University Courses Database Project

## Introduction
The objective of this project is to write an application that reads a list of University courses from a data file and then inserts them into two separate hash tables. The first hash table will use the Open Addressing collision resolution scheme and the second hash table will use the Chaining collision resolution scheme. Users should be able to search the hash tables for a specific course number or display all of the courses. It’s your objective to compare and contrast the hashing collision resolution methods. Additionally, the application should maintain a list of courses taught by each professor by using a binary search tree data structure. Users should be able to search for a professor and view all of the courses taught by the Professor.

## Getting Started
1. Download the project pdf writeup located within this starter repo.<br/>
2. Download the PowerPoint slide deck [Getting Started With GitHub Classroom Workflow](https://docs.google.com/presentation/d/1B0yZb6twQ_NVL8PripCL7AkeIKSrR8_M/edit?usp=sharing&ouid=115561230768383364768&rtpof=true&sd=true).<br/>
3. Download the [GitHub presentation slide deck](https://drive.google.com/file/d/12mMxMGRrpnkSuz08FUlvkhC-9WJ4JHns/view?usp=sharing) created by Asa Ashraf.<br/>
4. View the GitHub lecture videos [Part I](https://drive.google.com/file/d/1P4iqEbt9Nx68-Nq0FxxpdBZCrbkx5cN3/view?usp=sharing) and [Part II](https://drive.google.com/file/d/1EFYq_qJsV3QNcx_W86nz2KFpQUhSn9jF/view?usp=sharing) given by Asa Ashraf.

## Disclaimer
Students are not allowed to share this code or make it public at any time, even after the course has completed.

## Additionals
QUESTION 1: By my tests using both chaining and open addressing collision resolution methods to bulk insert and search from files, it appears that chaining is quicker, because of the ability to be assured that your search will start at an index and cover the size of a linked list in O(n) time. In the case of quadratic probing and insertion, this formula and search can span multiple runs of an entire hash table, before finding the desired element and hitting every index.

QUESTION 2: Using the BST for both hashing mechanisms wasn't a bad decision, but alternatively, I could use a min/max heap, sorted by the number of courses a given professor teaches. This would work well in theory because professors with more courses taught are more likely to be searched, as they are more popular.

QUESTION 3: I believe that I could improve this application by implementing an array doubling algorithm to double the hash table if the user inputs an insufficient size, until all of the data is inputted into the table. This would ensure proper data storage of larger files, where the number of lines in the file could be unknown. 
