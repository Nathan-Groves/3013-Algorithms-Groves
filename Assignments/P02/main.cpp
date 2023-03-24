 /***********************************************************************
#  *
#  *  Author:           Nathan Groves
#  *  Title:            Program 2: Dictionary Look-Up
#  *  Course:           3013 Algorithms
#  *  Semester:         Spring 2023
#  *
#  *  Description:
#  *        Reads in file of strings into a linked list. From there, the
#  *        user is able to search character by character for certain words
#  *        in the list. Autocomplete will suggest up to 10 words that start
#  *        with the string currently being searched by the user. This info,
#  *        the timing, and the number of string matches beyond the 10 first
#  *        are printed to the console. Manually changing the file name should
#  *        allow any file of line-break strings to be searchable.
#  *        
#  *
#  ***********************************************************************/

#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include "linkedList.hpp"

using namespace std;

#define RED termcolor::red


int main() {
    char k;               // holder for character being typed
    string word = "";       // var to concatenate letters to
    int loc;                // location of substring to change its color
    int wordCount;          // count of nums printed
    int numOfMatches;      // num of words in list that match

    Timer T;   // create a timer
    T.Start(); // start it

    LinkedList Dictionary;
    Dictionary.LoadWords("animal_names.txt", Dictionary);


    T.End(); // end the current timer

    // print out how long it took to load the word file
    cout << T.Seconds() << " seconds to read in and print json" << endl;
    cout << T.MilliSeconds() << " milli to read in and print json" << endl;
    cout << T.NanoSeconds() << " nano to read in and print json" << endl;

    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;
    cout << "if a mistype is made or the user wishes to search another word,";
    cout << " simply rerun the program" << endl;


    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {
        T.Start(); // start it
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127) {
            if (word.size() > 0) {
                word = word.substr(0, word.size() - 1);
            }
        } else {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any words in the array that partially match
        // our substr word
        Dictionary.FindWords(Dictionary, word);
        numOfMatches = Dictionary.matches();

        if ((int)k != 32) { // if k is not a space print it
            T.End();
            // Getting the correct precision to print out in c++ is not
            // straight forward. Strings and precision output are convoluted
            // at best. And drive you crazy at worst.
            cout << endl << printf("%.17f", (double)T.NanoSeconds() / 1000000000)  << " seconds to find and load" << endl;
            cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            cout << "Number of Matches: " << numOfMatches << endl;
            cout << "Animals Found: ";
            cout << termcolor::green;
            // This prints out all found word matches

            wordCount = 0;
          
            for (int i = 0; i < Dictionary.getSize(); i++) {
                // find the substring in the word
                loc = Dictionary[i].find(word);
                // if its found
                if (loc != string::npos) {
                    // print one letter at a time turning on red or green
                    //  depending on if the matching subtring is being printed
                    for (int j = 0; j < Dictionary[i].size(); j++) {
                        // if we are printing the substring turn it red
                        if (j >= loc && j <= loc + word.size() - 1) {
                            cout << termcolor::red;
                        } else {
                            cout << termcolor::green;
                        }
                      if (Dictionary[i] != "")
                      {
                        //if not empty string then print
                        cout << Dictionary[i][j];
                      }
                    }
                    cout << termcolor::green;
                }
     // if not empty string then print space and 
    // increment word count to make sure only 10 items are printed
              if (Dictionary[i] != "")
                      {
                        cout << " ";
                        wordCount++;
                      }

            //breaks loop after 10 prints
              if (wordCount >= 10)
              {
                break;
              }

            }
            cout << termcolor::reset << endl;
        }
    }
    return 0;
}
