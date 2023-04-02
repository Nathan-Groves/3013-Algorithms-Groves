#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "termcolor.hpp"

using namespace std;


// Define the character size
#define CHAR_SIZE 128

 
// A class to store a Trie node
class Trie
{
public:
    bool isLeaf;
    Trie* character[CHAR_SIZE];
 
    // Constructor
    Trie()
    {
        this->isLeaf = false;
 
        for (int i = 0; i < CHAR_SIZE; i++) {
            this->character[i] = nullptr;
        }
    }
 
    void insert(string);
    bool deletion(Trie*&, string);
    bool search(string);
    bool haveChildren(Trie const*);
    void allMatches(string, int, vector<string>);
};
 
// Iterative function to insert a key into a Trie
void Trie::insert(string key)
{
    // start from the root node
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // create a new node if the path doesn't exist
        if (curr->character[key[i]] == nullptr) {
            curr->character[key[i]] = new Trie();
        }
 
        // go to the next node
        curr = curr->character[key[i]];
    }
 
    // mark the current node as a leaf
    curr->isLeaf = true;
}
 
// Iterative function to search a key in a Trie. It returns true
// if the key is found in the Trie; otherwise, it returns false
bool Trie::search(string key)
{
    // return false if Trie is empty
    if (this == nullptr) {
        return false;
    }
 
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // go to the next node
        curr = curr->character[key[i]];
 
        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) {
            return false;
        }
    }
 
    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}

//look for matches inside trie and print them to the console
void Trie::allMatches(string key, int trieSize, vector<string> allKeys)
{

  //variables to keep count of loops, string length, and
  //word matches
  int wordLength;
  bool checkForMatch;
  int m, z = 0;
  int keySize = key.length();
  vector<string> wordMatches;


  
  // return false if Trie is empty
    if (this == nullptr) {
        return;
    }

   for (int i = 0; i < trieSize; i++) {

    //enters if first key is match
     if (allKeys[i][0] == key[0])
     {
       z = 0;
       m = 0;
       checkForMatch = true;

      wordLength = allKeys[i].length();

        while (z <= keySize && keySize <= wordLength)
          {
            //if a char is the only thing not matching then set match 
            //equal to false
          if(allKeys[i][m] != key[m])
          {
            checkForMatch = false;
          }
            //add to matches if all chars are in string
          else if (allKeys[i][m] == key[m] && z == (keySize - 1) && checkForMatch == true)
            {
            wordMatches.push_back(allKeys[i]);
            }
            m++;
            z++;
          }
     }
     
   }

  //printing out first ten matches with colors
  int foundCount = 0;
  int vectorCount = wordMatches.size();
  int matchLength = 0;

  cout << termcolor::reset;
  cout << "Matches: " << vectorCount << endl;
  cout << "Words Found: ";

  for (auto it = wordMatches.begin(); it != wordMatches.end(); ++it)
    {
      matchLength = it->length();
      if (foundCount < 10)
      {
      cout << termcolor::red;  
      cout << key;
      cout << termcolor::green << it->substr(key.length(), matchLength) << " ";
      }
      foundCount++;
      if (foundCount >= 10)
      {
        break;
      }
    }

}
 
// Returns true if a given node has any children
bool Trie::haveChildren(Trie const* curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return true;    // child found
        }
    }
 
    return false;
}
 
// Recursive function to delete a key in the Trie
bool Trie::deletion(Trie*& curr, string key)
{
    // return if Trie is empty
    if (curr == nullptr) {
        return false;
    }
 
    // if the end of the key is not reached
    if (key.length())
    {
        // recur for the node corresponding to the next character in the key
        // and if it returns true, delete the current node (if it is non-leaf)
 
        if (curr != nullptr &&
            curr->character[key[0]] != nullptr &&
            deletion(curr->character[key[0]], key.substr(1)) &&
            curr->isLeaf == false)
        {
            if (!haveChildren(curr))
            {
                delete curr;
                curr = nullptr;
                return true;
            }
            else {
                return false;
            }
        }
    }
 
    // if the end of the key is reached
    if (key.length() == 0 && curr->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!haveChildren(curr))
        {
            // delete the current node
            delete curr;
            curr = nullptr;
 
            // delete the non-leaf parent nodes
            return true;
        }
 
        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            curr->isLeaf = false;
 
            // don't delete its parent nodes
            return false;
        }
    }
 
    return false;
}
