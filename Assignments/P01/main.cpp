# /***********************************************************************
#  *
#  *  Author:           Nathan Groves
#  *  Title:            Program 1: AVL Trees
#  *  Course:           3013 Algorithms
#  *  Semester:         Spring 2023
#  *
#  *  Description:
#           Reads in 8 different data values of int/string from a json file
#            into AVL trees and Linked Lists to compare find time complexities.
#           With the given structures a search can be made for a value such as 
#           a person's last name. The number of comparisons it took for each
#           structure to find the value is then printed, as well as the time
#           it took to find them. The idea is to show AVL trees' superior 
#           Olog(n) time complexity in finding specific items
#  *        
#  *
#  ***********************************************************************/


#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "LinkedList.hpp"
#include "bst.hpp"
#include "Timer.hpp"

using namespace std;

using json = nlohmann::json;


//Manager class to contain and access the AVL Trees
class TreeManager: public AvlTree {

  map <string,AvlTree*> manager;
   
public:

TreeManager(){}

~TreeManager(){}

//************************************************************************
// Method Name: intSearch
//
// Purpose: look for number value based on key entered by user
//
// Arguments: key to type of tree, and key to item the user is looking for
//            ofstream
//
// Returns: Nothing
//*************************************************************************
  void intSearch(string treeKey,int searchKey, ofstream & o){
    manager[treeKey]->intSearch(searchKey, o);
  }

//************************************************************************
// Method Name: stringSearch
//
// Purpose:  look for string value based on key entered by user
//
// Arguments: key to type of tree, and key to item the user is looking for
//            ofstream
//
// Returns: Nothing
//*************************************************************************
  void stringSearch(string treeKey, string searchKey, ofstream & o){
    manager[treeKey]->stringSearch(searchKey, o);
  }

//************************************************************************
// Method Name: printStringTree
//
// Purpose:  print out full tree to console 
//
// Arguments: key to type of tree
//
// Returns:   Nothing
//*************************************************************************
  void printStringTree(string key) {
    manager[key]->dumpStringTree();
  }

//************************************************************************
// Method Name: printIntTree
//
// Purpose:  print out full tree to console 
//
// Arguments: key to type of tree
//
// Returns:   Nothing
//*************************************************************************
  void printIntTree(string key) {
    manager[key]->dumpIntTree();
  }

//************************************************************************
// Method Name: addTree
//
// Purpose:  add tree to map of AVL Trees 
//
// Arguments: key to type of tree
//
// Returns:   Nothing
//*************************************************************************
  void addTree(string key){
    manager[key] = new AvlTree(key);
    }

//************************************************************************
// Method Name: addIntToTree
//
// Purpose:  add integer value to specific tree 
//
// Arguments: key to type of tree which the number is being added to
//
// Returns:   Nothing
//*************************************************************************
  void addIntToTree(string key, int item){
    manager[key]->intInsert(item);
  }

//************************************************************************
// Method Name: addStringToTree
//
// Purpose:  add string value to specific tree 
//
// Arguments: key to type of tree which the string is being added to
//
// Returns:   Nothing
//*************************************************************************
  void addStringToTree(string key, string item){
    manager[key]->stringInsert(item);
  }

};


int main() {

  Timer T;

  
  //open input and output files
  //user can manually change out for there own
  //json input file
  ifstream f("random_person_data1.json");
  ofstream o;
  o.open("output.txt");
  
  json random_person_data1 = json::parse(f);

  //create tree manager and add data types for AVL trees
  TreeManager Grove;
  Grove.addTree("id");
  Grove.addTree("first_name");
  Grove.addTree("city");
  Grove.addTree("email");
  Grove.addTree("address");
  Grove.addTree("state");
  Grove.addTree("car");
  Grove.addTree("job_title");

  //create Linked Lists for comparisons
  LinkedList ID_List;
  LinkedList Names_List;
  LinkedList City_List;
  LinkedList Email_List;
  LinkedList Address_List;
  LinkedList State_List;
  LinkedList Car_List;
  LinkedList Job_List;
  

  //loop through json file to add each data member into AVL Trees and Linked Lists
  for (int i=0; i < random_person_data1.size() ; ++i) {
    Grove.addIntToTree("id", random_person_data1[i]["id"]);
    ID_List.insertIntAtEnd(random_person_data1[i]["id"]);
    Grove.addStringToTree("first_name", random_person_data1[i]["first_name"]);
    Names_List.insertStringAtEnd(random_person_data1[i]["first_name"]);
    Grove.addStringToTree("city", random_person_data1[i]["city"]);
    City_List.insertStringAtEnd(random_person_data1[i]["city"]);
    Grove.addStringToTree("email", random_person_data1[i]["email"]);
    Email_List.insertStringAtEnd(random_person_data1[i]["email"]);
    Grove.addStringToTree("address", random_person_data1[i]["address"]);
    Address_List.insertStringAtEnd(random_person_data1[i]["address"]);
    Grove.addStringToTree("state", random_person_data1[i]["state"]);
    State_List.insertStringAtEnd(random_person_data1[i]["state"]);
    Grove.addStringToTree("car", random_person_data1[i]["car"]);
    Car_List.insertStringAtEnd(random_person_data1[i]["car"]);
    Grove.addStringToTree("job_title", random_person_data1[i]["job_title"]);
    Job_List.insertStringAtEnd(random_person_data1[i]["job_title"]);

  }

  //example command to print tree and Linked List
  // Grove.printIntTree("id");
  // ID_List.displayIntList(o);

  
  /* Print out the number of comparisons it takes to find each
  data members for each tree and Linked List, timing how long
  it takes. When searching for item make sure it exists within
  the file exactly as you write it, otherwise it will not be found */
  T.Start();
  Grove.intSearch("id", 430, o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  ID_List.findInt(430, o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Grove.stringSearch("first_name", "Rebekah", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Names_List.findString("Rebekah", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;
  
  T.Start();
  Grove.stringSearch("city", "Roanoke", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  City_List.findString("Roanoke", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Grove.stringSearch("email", "mmatchellkw@liveinternet.ru", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Email_List.findString("mmatchellkw@liveinternet.ru", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Grove.stringSearch("address", "039 Dryden Pass", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Address_List.findString("039 Dryden Pass", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Grove.stringSearch("state", "NE", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  State_List.findString("NE", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Grove.stringSearch("car", "GMC", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Car_List.findString("GMC", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Grove.stringSearch("job_title", "VP Marketing", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  T.Start();
  Job_List.findString("VP Marketing", o);
  T.End();
  cout << "time to search was " << T.Seconds() << " seconds";
  cout << endl << endl;
  o << "time to search was " << T.Seconds() << " seconds";
  o << endl << endl;

  f.close();

  }
