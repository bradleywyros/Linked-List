#include <string>
#include <iostream>
#include <stdlib.h> 
#include <sstream>
#include<vector>
using namespace std;

//your linked list implementation here
class LinkedList {
  //
    struct Node{
            string value;
            Node* prev;
            Node* next;
        Node() {value = "ok"; prev = NULL; next = NULL;}
        Node(const string & d, Node * p, Node * n) : value(d), prev(p), next(n) {}
    };
    
    // attributes for Linked List
    public:
        Node* head;
        Node* tail;
        int size;
    
    //*******Constructor/Destructor******
    //Initializes the Linked List. Used in the default constructor
    void init(){
        size = 0;
        head = NULL;
        tail = NULL;
    }
    
    // Deletes the entire linked list
    void clear(){
      Node* curr = head;
      Node* temp;
      
      while(curr != NULL){
        temp = curr->next;
        delete curr;
        curr = temp;
        size--;
      }
    }
    
    // Default constructor. Uses init()
    LinkedList(){
      init();
    }
    
    //Constructor 
    LinkedList(Node* head, Node* tail, int size){
      this->head = head;
      this->tail = tail;
      this->size = size;
    }
    
    //Copies a list into another list. Used for assignment operator and copy constructor
    void Set(const LinkedList &set){
      clear();
      Node* curr = set.head;
      
      for(int i = 0; i < set.size; i++){
        insertEND(curr->value);
        curr = curr->next;
      }
    }
    
    // Copy constructor
    LinkedList(const LinkedList &list){
      Set(list);
    }
    
    //Assignment operator
    LinkedList &operator=(const LinkedList &rhs){
      Set(rhs);
      
      return *this;
    }
    
    //Destructor. Deletes the linked list and sets it back to the default.
    ~LinkedList(){
      clear();
      init();
    }
    
    //**********Insertion / Deletion*************
    //Inserts a line at an index
    bool insert(int index, string line){
      Node* curr = head;
      Node* newNode = new Node();
      newNode->value = line;
      int count = 1;
      
      if (index > size + 1 || index < 1) //if index is bigger than the list + 1 or less than 1, ignore
        return false;
      
      if(size == 0){ // if the list is empty, set the size to one and make the head and the tail the same

        head = newNode;
        tail = newNode;
        
        size++;
        
        return true;
      }
 
      if(index == 1){ // if index is 1, move the head up and make the new node the head
  
        newNode->next = head;
  
        head->prev = newNode;
        head = newNode;
        size++;
        
        return true;
      }else if(index == size + 1){ // if the index is equal to the size, add it before the tail
        insertEND(line);
      }else{
        // Loop through the list by counting. Find the index and insert the new node 
        // between the previous and current node
        while(curr != NULL){
         Node* prevNode = curr->prev;
          if(index == count){
            
            newNode->next = curr;           
            curr->prev = newNode;       
            newNode->prev = prevNode;   
            prevNode->next = newNode;
            
            size++;

            return true;
          }
          
          curr = curr->next;
          count++;
          
        }
      }
      
    }
    
    // Insert a new node and make it the tail (add to the end)
    bool insertEND(string line){
      Node* newNode = new Node();
      newNode->value = line;
      
      if(size == 0){ //if the size is zero, make the head and tail equal to the new node
        head = newNode;
        tail = newNode;
        size++;
        
        return true;
        
      }else{ 
        // make the new node the tail by making the tail the new nodes previous
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
      
        size++;
      
        return true;
      }
      
    }
   
   // Erases the node at a given index and reduces the size by one
   bool erase(int index){
     Node* curr = head;
     int count = 1;
     
    if(size < index || index < 1 || size == 0) // if the index is out of range or the list is empty, return false
       return false;
    
     if(index == 1){ // if the index is one, make the next node the head and delete the current
       head = curr->next;
       delete curr;
       head->prev = NULL;
       
       size--;
       
       return true;
     }else if(index == size){ //if the index is the size, make the previous node the tail and delete the end
       curr = tail;
       tail = curr->prev;
       delete curr;
       tail->next = NULL;
      
       size--;
      
       return true;    
     }else{
       //Loop to find the index
       while(curr != NULL){
         if(count == index){ // if you found the index...
          
          // prevents long chains of nexts and prevs
          Node* currPrev = curr->prev; 
          Node* currNext = curr->next;
          
          if(currNext == tail){     // if the next node is the tail make the prev node 
            currPrev->next = tail;  // and tail point to each other, then delete curr
            tail->prev = currPrev;
            tail->next = NULL;
            delete curr;
            
            size--;
          
            return true;
         }else{                 //otherwise, make the prev and next point to each other and delete curr
          currPrev->next = currNext;
          currNext->prev = currPrev;
          delete curr;
          
          size--;
          
          return true;
         }
       }else{
        curr = curr->next;
        count++;
       }
     }
   }
  }
   
   //**********Line editors***********
   //Edit the line at a given index by reassigning the string
   void edit(int index, string line){
     Node* curr = head;
     int count = 1;
     
     if(index < count || index > size || size == 0) // if the index is out of range or the list is empty, return false
       return;
     
     while(curr != NULL){ 
     // Loop until you find the index and then assign a new line and return 
       if(count == index){
         curr->value = line;
         return;
       }
       count++;
       curr = curr->next;
     }
   }
   
   // Search for a node value that contains your line 
   void search(string search){
     Node* curr = head;
     string line = "";
     int count = 1;
     bool found = false;
     
     if(size == 0) // if the list is empty, ignore and return 
       return;
     
     while(curr != NULL){
       line = curr->value;
       
       // if the search given is found in the line of the curr node, 
       //print out the value of the node and line number, then return 
       if(line.find(search) != string::npos){
         cout << count << " " << line << endl;
         found = true;
       }
         
       curr = curr->next;
       count++;
     }
     
     // if the value wasn't found, then return not found
     if(!found)
      cout << "not found" << endl;
   }
   
   //Prints the List
   void print(){
     Node* curr = head;
     int line = 1;
     string quote = "";
     
     if(head == NULL)
       return;
     
     while(curr != NULL){
       quote = curr->value;
      
      // prints the line number and line 
       cout << line << " " << quote << endl;
       
       curr = curr->next;
       line++;
     }

   }
   
};

vector<string> split(string, char); 
string getQuote(string);

int main(){
  LinkedList list;
  string quote = ""; // used to catch the quote
  string line = "";  // used to catch the cin input
  int index = 0;
  vector<string> inputLines;
  
  // Loop and ask for input until the user enters "quit"
  // Ignores and continues to loop and ask for input if -
  // a) The input command is invalid (misspelled, doesn't exist)
  // b) There are no quotes around the desired input line
  while(true){
   
    getline(cin, line);
    
    if(line == "quit") // only way to break the loop. user must enter quit and terminate the program 
      exit(0);
    
    inputLines = split(line, ' '); // splits the line by spaces, a vector of each word in the line
    quote = getQuote(line); // captures the substring within quotes from the line
    if(quote.size() > 80) // if the quote is greater than 80 characters, ignore and loop back
      continue;
    
    // The first index of the vector will always be an input command
    // For functions that have a quote AND index, convert second index of vector to a number
    // Functions will check if number is valid 
    // If no quote is entered for functions that require a quote, ignore and loop
    if(inputLines[0] == "print"){
      list.print();
    }else if(inputLines[0] == "insertEnd"){
      if(quote.empty()) 
        continue;
      list.insertEND(quote);
    }else if(inputLines[0] == "search"){
      if(quote.empty())
        continue;
      list.search(quote);
    }else if(inputLines[0] == "insert"){
      if(quote.empty())
        continue;
      index = atoi(inputLines[1].c_str());
      list.insert(index, quote);
    }else if(inputLines[0] == "edit"){
      if(quote.empty())
        continue;
      index = atoi(inputLines[1].c_str());
      list.edit(index, quote);
    }else if(inputLines[0] == "delete"){
      index = atoi(inputLines[1].c_str());
      list.erase(index);
    }else  /// If none of the input if valid, ignore and loop
      continue;
  }
  
  
  return 0;
}

// Splits a string and returns a vector of the words in the string
// Really only using first and second array, could make this more efficient to save time/memory
vector<string> split(string s, char dlim){
  std::istringstream ss(s);
  string line;
  vector<string> splitStrings;
  
  while(getline(ss, line, dlim)){
    splitStrings.push_back(line);
  }
  
  return splitStrings;
}

// Takes in a line a returns a substring surrounded by quotes
string getQuote(string s){
  int len = s.length();
  size_t found = s.find('\"');
  size_t lastFound = s.rfind('\"');
  
  // If quotes are incomplete or not there, return an empty string
  if(found != std::string::npos && lastFound != std::string::npos)
    return s.substr(found + 1, lastFound - found - 1);
  else 
    return "";
}
