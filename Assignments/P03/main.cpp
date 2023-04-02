/***********************************************************************
#  *
#  *  Author:           Nathan Groves
#  *  Title:            Program 3: Trie Loop-Up
#  *  Course:           3013 Algorithms
#  *  Semester:         Spring 2023
#  *
#  *  Description:
#  *        Reads in file of strings into a trie. From there, the
#  *        user is able to search character by character for certain words
#  *        in the list. Autocomplete will suggest up to 10 words that start
#  *        with the string currently being searched by the user. This info,
#  *        the timing, and the number of string matches beyond the 10 first
#  *        are printed to the console. Manually changing the file name should
#  *        allow any json file of strings to be searchable.
#  *        
#  *
#  ***********************************************************************/

#include <iostream>
#include "JsonFacade.hpp"  
#include <time.h>
#include <chrono> 
#include "timer.hpp"   
#include "trie.hpp"
#include "mygetch.hpp"
#include "termcolor.hpp"
#include <string>

using namespace std;
using json = nlohmann::json;

 
// Define the character size
#define CHAR_SIZE 128
 


int main(){

  // string animal = "elephant";

  // string animalPart = animal.substr(4, 7);

  // cout << animalPart;
  

  

  char k;
string word = "";
  int dataSize = 0;
    Timer T;
    T.Start();
    JsonFacade J("dict_w_defs.json");   // create instance of json class
    T.End(); 
    double s = T.Seconds();
    long m = T.MilliSeconds();

    cout <<s << " seconds to read in" <<endl;
    cout <<m << " milli to load file" <<endl;
    int index = 0;        // alphabetical order and less by 1
    string key;         // key variable to access json object

    vector<string> keys = J.getKeys();
    
    cout<< "number of terms is " << keys.size() <<endl << endl;
  
    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;
    cout << "if a mistype is made or the user wishes to search another word,";
    cout << " simply rerun the program" << endl;

    Trie* head = new Trie();

//add key to vector and trie
  for (int i = 0; i < keys.size(); i++)
{
    key = J.getKey(i);
    head->insert(key);
     dataSize++;
  
}

 while ((k = getch()) != 'Z') {
        T.Start(); // start it
        // Tests for a backspace or special character and if pressed
        // instructs user to enter letter only.
        if ((int)k == 127 || !isalpha(k)) {
                cout << "Letters only!" << endl;
                continue;
            }
            // make sure letter is lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97){
             k += 32;
            }
   //add character to word to seach for
        word += k;

   if ((int)k != 32) { // if k is not a space print it
            T.End();
     //print search header
       cout << endl << printf("%.17f", (double)T.NanoSeconds() / 1000000000)  << " seconds to find and load" << endl;
            cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;

     //search for word, which prints out matches
     head->allMatches(word, dataSize, keys);
     
     cout << endl << endl;
     cout << termcolor::reset;
 }

 }


  return 0;
}
