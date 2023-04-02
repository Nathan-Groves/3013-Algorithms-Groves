## P03 - Trie Autocomplete
### Nathan Groves
### Description:

This program reads in string data from a json file into a trie, after which the user can use getch to look up a word letter by letter. The first ten autcomplete suggestions are printed, as well as the time to find the strings.

### Files

|   #   | File     | Description                      |
| :---: | -------- | -------------------------------- |
|   1   | main.cpp | Main driver of dictionary autocomplete program. |
|   2   | trie.hpp | trie class definition |
|   4   | timer.hpp | timer definition to time runtimes |
|   5   | dict_w_defs.json | example file to read in |
|   6   | JsonFacade.hpp | facade pattern to simplify json.hpp |
|   7   | mygetch.hpp | getch implementation to fetch user input |
|   8   | termcolor.hpp | character color implementation to highlight parts of words |
|   9   | json.hpp  | nlohmann json definitions |



### Instructions:

- Create trie instance in main, modifying the text file sent for different databases.
- Type in a desired term to search for, going letter by letter.
- rerun the program if you wish to search for another word.




