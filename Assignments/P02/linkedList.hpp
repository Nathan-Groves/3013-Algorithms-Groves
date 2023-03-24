
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node
{
  string data;
  Node * next;
  Node * previous;

Node (string d)
{
    data = d;
    next = NULL;
    previous = NULL;
  }
};


class LinkedList
{
  private:
    Node * head;
    Node * tail;
    int listSize;

  public:
    LinkedList()
    {
      head = NULL;
      tail = NULL;
      listSize = 0;
    }

    //Destructor
    ~LinkedList()
    {
      Node * traverse = head;
      while (traverse != NULL)
      {
        head = traverse->next;
        delete traverse;
        traverse = head;
      }
      head = NULL;
    }

    //Insert new nodes at the front of the list
    void insertStringAtFront(string d)
    {
      //Create new node
      Node * temp = new Node(d);
      
      //Check if empty list
      if(head == NULL)
      {
        //If the list is empty, the new node is the head
        head = temp;
        tail = temp;
      }
      else
      {
        //Otherwise, link the new node in and make it new head
        temp-> next = head;
        head -> previous = temp;
        head = temp;
      }

      listSize++;
    }

    //Insert new nodes at the back of the list 
    void insertStringAtEnd(string d)
    {
       //Create new node
      Node * temp = new Node(d);
      
      //Check if empty list
      if(head == NULL)
      {
        //If the list is empty, the new node is the head
        head = temp;
        tail = temp;
      }
      else
      {
        tail->next = temp;
        temp -> previous = tail;
        tail = temp;
      }
      listSize++;
    }

void findString(string key, ofstream & outfile)
{
  Node * traverse = head;
  int compareCount = 1;

  while (traverse->data != key && traverse->next != NULL)
    {
      traverse = traverse->next;
      compareCount++;
    }

  if (traverse->data == key)
  {
    cout << "Found " << key << " after " << compareCount;
    cout << " comparisons using a Linked List" <<  endl;
    outfile << "Found " << key << " after " << compareCount;
    outfile << " comparisons using a Linked List" << endl;
  }
  else
  {
    cout << key << " was not found" << endl;
    outfile << key << " was not found" << endl;
  }
    
}

void displayStringList()
    {
      //Make a temporary pointer to traverse the list
      Node * traverse = head;

      //Run through every item
      while(traverse)
        {
          cout << traverse->data << " ";
          traverse = traverse-> next;
        }
    }

//Function to search for a given value and remove it from the list
void removeString (string d)
{

  if(d == head->data && head == tail)
      {
        //Set head and tail to NULL (will now be an empty list)
        head = NULL;
        tail = NULL;
      }
  else if (d == head -> data)
  {
    Node * temp = head;
    Node * temp2 = NULL;
    temp2 = head -> next;
    temp2 -> previous = head ->previous;
    
    head = temp2; 
    temp = NULL;
    delete temp;
  }

  else if (d == tail -> data)
  {
    Node * temp = tail;
    tail = tail -> previous;
    tail -> next = NULL;
    temp = NULL;
    delete temp;
  }
  
    Node * traverse = head;
    Node * trailing = NULL;
    Node * temp1 = NULL;

    while (traverse && traverse->data != d)
      {
        trailing = traverse;
        traverse = traverse -> next;
      }

  if (traverse != NULL)
  {
   trailing -> next = traverse -> next;
   temp1 = traverse -> next;
    temp1 -> previous = traverse -> previous;
    if (temp1 == tail)
    {
      tail -> previous = trailing;
    }
    traverse = NULL;
    delete traverse;

  }

    listSize--;
}

int size ()
{
   //Make a temporary pointer to traverse the list
      Node * traverse = head;
      int count = 0;
  
      //Run through every item
      while(traverse)
        {
          count++;
          traverse = traverse-> next;
        }

    return count;
}

int matches ()
{
   //Make a temporary pointer to traverse the list
      Node * traverse = head;
      int count = 0;
  
      //Run through every item
      while(traverse)
        {
          if (traverse->data != "")
            {
            count++;
            }
          traverse = traverse-> next;
        }

    return count;
}

/**
   *  overload brackets to change/display value 
   *  at position
   *
   * param: int index - position of value
   * returns: number at specificed index
   */
  string & operator[](int index) {

    int invalidIndex = 0;
    string doesNotExist = "doesNotExist";
		Node* traverse = head;
    //makes sure the position exists
		if (index >= size() || index < 0) {
			//cout << "index does not exist" << endl << endl;
			return doesNotExist;
		}
		else {
			// finds the position in the vector
			for (int i = 0; i < index; i++) {
				traverse = traverse->next;

			}

			return traverse -> data;
		}
	}

int getSize(){
  return listSize;
}

void insertStringInOrder(string d)
    {
      //Create new node
      Node * temp = new Node(d);
      
      //Check if empty list
      if(head == NULL)
      {
        //If the list is empty, the new node is the head
        head = temp;
        tail = temp;
      }
      else
      {
        //If the item to be inserted is less than our current smallest value,
        //insert at the front of the list
        if(temp->data < head->data)
        {
          insertStringAtFront(d);
          }
        else
        {
          //Create a pointer to traverse the list
          //NEVER traverse through head! (You will lose the list)
          Node * traverse = head;
          Node * trailing = NULL;

          //Traverse the list until we find a larger value or
          //hit the end of the list
          while(temp->data > traverse->data && traverse -> next != NULL)
          {
            //Trailing pointer keeps track of the current node (old node)
            trailing = traverse;
            //Traverse moves on to the next node
            traverse = traverse->next;
          }

          //If you reached the end of the list, item to be inserted
          //is the largest value
          if(traverse->next == NULL && temp -> data > traverse -> data)
            insertStringAtEnd(d);
          //Otherwise, insert the node in order at the trailing pointer
          // location
          else
          {
            temp ->next = traverse;
            temp -> previous = trailing;
            trailing->next = temp;
            traverse -> previous = temp;
          }
        }
      }
      
    }//End of insertInOrder



  /**
 * CountLines
 *
 * Description:
 *      Originally wrote this to count size of input file so
 *      I could allocate enough memory for an array of strings.
 * Params:
 *      string file_name - file to get the line count
 *
 * Returns:
 *      int - line count
 */
int CountLines(string file_name) {
    ifstream inFile(file_name);
    return count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n');
}



  /**
 * LoadWords
 *
 * Description:
 *      Loads a file of strings (words, names, whatever) reading them in
 *      with one word per line. So words must be delimited by newlines '\n'
 * Params:
 *      string file_name - file to get the line count
 *      LinkedList & d - list of string values
 *
 * Returns:
 *      none
 */
void LoadWords(string file_name, LinkedList & d) {
    ifstream fin;                   // file to get words
    int count = (CountLines(file_name) + 1); // get size of input file
    string wordHolder;

    fin.open("animal_names.txt"); // open file for reading

    // knowing the size of the file lets us treat
    // it like an array without using .push_back(value)
    for (int i = 0; i < count; i++) {
      fin >> wordHolder;
        d.insertStringAtEnd(wordHolder);
    }
}

/**
 * FindWords
 *
 * Description:
 *      Finds partial matches in an array of strings and returns them. The
 *      match must be from the start of the string
 * Params:
 *       LinkedList & d  - Linked List entity to modify
 *      string          substring   - substring to search for in each word
 *
 * Returns:
 *          none
 */
void FindWords(LinkedList & d, string substring) {
    size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.
    int j, m, z = 0;
    int wordLength = 0;
    int wordSize = substring.length();

    for (int i = 0; i < listSize; i++) { // loop through array
        found = d[i].find(substring);  // check for substr match

              //if string is found in list and equal in first char, continue
        if (found != string::npos && d[i][0] == substring[0]) {

        z = 0;
        m = 0;
          
        wordLength = d[i].length();

          //continues as long as the substring is smaller than the word
          //and checks all chars up till end of the substring
        while (z < wordSize && wordSize <= wordLength)
          {
            //if a char is the only thing not matching then set string to
            //to empty
          if (d[i][m] != substring[m] && z < wordSize && wordSize <= wordLength)
            {
            d[i] = "";
            }
            m++;
            z++;
          }
        }
      //if string not found in beginning then change string to empty
      else 
        {
          d[i] = "";
        }

    }

}


};
