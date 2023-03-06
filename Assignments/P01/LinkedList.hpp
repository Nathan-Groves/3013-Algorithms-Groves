
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node
{
  string data;
  int numData;
  Node * next;
  Node * previous;

Node (string d)
{
    data = d;
    next = NULL;
    numData = -1;
    previous = NULL;
  }

Node (int d)

{
  data = "na";
  next = NULL;
  numData = d;
  previous = NULL;
}

};




class LinkedList
{
  private:
    Node * head;
    Node * tail;
  public:
    LinkedList()
    {
      head = NULL;
      tail = NULL;
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
    }

//Insert new nodes at the front of the list
    void insertIntAtFront(int d)
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
    }

//Insert new nodes at the back of the list 
    void insertIntAtEnd(int d)
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
    }

void findInt(int key, ofstream & outfile)
{
  Node * traverse = head;
  int compareCount = 1;

  while (traverse->numData != key && traverse->next != NULL)
    {
      traverse = traverse->next;
      compareCount++;
    }

  if (traverse ->numData == key)
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

void displayIntList(ofstream& outfile)
    {
      //Make a temporary pointer to traverse the list
      Node * traverse = head;

      //Run through every item
      while(traverse)
        {
          outfile << traverse->numData << " ";
          traverse = traverse-> next;
        }
    }

void displayStringList(ofstream& outfile)
    {
      //Make a temporary pointer to traverse the list
      Node * traverse = head;

      //Run through every item
      while(traverse)
        {
          outfile << traverse->data << " ";
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

}


void removeInt (int d)
{

  if(d == head->numData && head == tail)
      {
        //Set head and tail to NULL (will now be an empty list)
        head = NULL;
        tail = NULL;
      }
  else if (d == head -> numData)
  {
    Node * temp = head;
    Node * temp2 = NULL;
    temp2 = head -> next;
    temp2 -> previous = head ->previous;
    
    head = temp2; 
    temp = NULL;
    delete temp;
  }

  else if (d == tail -> numData)
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

    while (traverse && traverse->numData != d)
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

void insertIntInOrder(int d)
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
        if(temp->numData < head->numData)
        {
          insertIntAtFront(d);
          }
        else
        {
          //Create a pointer to traverse the list
          //NEVER traverse through head! (You will lose the list)
          Node * traverse = head;
          Node * trailing = NULL;

          //Traverse the list until we find a larger value or
          //hit the end of the list
          while(temp->numData > traverse->numData && traverse -> next != NULL)
          {
            //Trailing pointer keeps track of the current node (old node)
            trailing = traverse;
            //Traverse moves on to the next node
            traverse = traverse->next;
          }

          //If you reached the end of the list, item to be inserted
          //is the largest value
          if(traverse->next == NULL && temp -> numData > traverse -> numData)
            insertIntAtEnd(d);
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


};
