// Ye Wint Aung
// 29 October 2020
// This program asks for the user to input his/her own sentences or choose from 
// a text file. The chosen chioce of input will then be evaluated if it is a 
// palindrome or not. This program allows the user to repeat.

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

struct Node{
	char data;     	// letters of string
	Node *prev;
	Node *next; 	// reference to next node
};

void greet();
void insert_front(Node* &head, char new_data);
void insert_end(Node* &head, char new_data);
void displayList(Node* node, int result);
void openTextFile(std::vector<std::string>& v, int& lines);
bool isPalindrome(Node* head, Node* tail);
void filterText(std::string &s);
void deleteList(Node* &head);

void greet(){ // greets user and asks if they want to try program
  std::string name;
  std::cout << "Hello, what is your name?" << std::endl;
  std::cin >> name;
  std::cout << "Hi " << name << ", this program searches for palindromes in a given sentence. Would you like to try? [Y/N]" << std::endl;
}

void insert_front(Node* &head, char new_data) // inserts in order
{
   //allocate memory
   Node* newNode = new Node;
  
   //assign character into data
   newNode->data = new_data;
  
   // new node is head
   newNode->next = (head);
   newNode->prev = nullptr;
  
   //previous of head is new node
   if ((head) != nullptr)
   (head)->prev = newNode;
  
   //head points to new node
   (head) = newNode;
}

void insert_end(Node* &head, char new_data) // inserts in backwards order
{
   //allocate memory
   Node* newNode = new Node;
  
   Node* last = head; //last node is head
  
   //assdign character to data
   newNode->data = new_data;
  
   //new node is last node , therefore set next of new node to null
   newNode->next = nullptr;
  
   //check if list is empty, if yes new node will be head of list
   if (head == nullptr) {
   newNode->prev = nullptr;
     head = newNode;
    return;
}
//otherwise traverse to last node
while (last->next != nullptr)
last = last->next;
  
//assign next of last to new node
last->next = newNode;
  
//assign last to previous of new node
newNode->prev = last;
return;
}

void displayList(Node* node, int result){ // displays if linked list is palindrome
    Node* last;
    
   while (node != nullptr) { // run loop while node not empty
      std::cout<<node->data; // output character one by one
      last = node;
      node = node->next;
   }
   if(result == 1){std::cout << " is a palindrome";} // if true, then it is palindrome
    else{std::cout << " is not a palindrome";} // if false, then not palindrome
   std::cout << std::endl;
}

std::string userInput(){ // takes in user input
    std::string sentence;
    std::cin.ignore();
    std::cout << "Enter a phrase or a sentence" << std::endl;
    std::getline(std::cin, sentence); // takes entire line input

    return sentence;
}

void openTextFile(std::vector<std::string>& v, int& lines){ // opens user chosen text file
    int input;
    std::cout << "Pick a text file" << std::endl;
    std::cout << "1. Palindrome Samples" << std::endl;
    std::cout << "2. List of palindromes" << std::endl;
    std::cin >> input;
    std::ifstream myfile;
    std::string textfile;
    if(input == 1) {textfile = "sample.txt";}
    if(input == 2) {textfile = "palindrome.txt";}
    myfile.open(textfile);
    std::string s;
    while(std::getline(myfile, s)){ // contents of text file stored in vector
        v.push_back(s);
        lines++;
    }
    
}

bool isPalindrome(Node* head, Node* tail){ // checks for palindrome
    while (head != nullptr){ // run loop while head is not empty
            
            if(head -> data != tail -> data){ //if first char not equal to last letter, return false
                return false; 
            }
            head = head -> next; // traverse head
            tail = tail  -> next; // traverse tail
    }
    
    return true; // if all characters in head and tail are equal, then it is palidnrome
}

void filterText(std::string &s){ // filters text
    int size = s.size();
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end()); // removes spaces
    transform(s.begin(), s.end(), s.begin(), ::tolower);    // lower case every character
    for (int i = 0; i < size; i++){
        if (ispunct(s[i])) // removes punctuation
        { 
            s.erase(i--, 1); 
            size = s.size(); 
        } 
    }
}

void deleteList(Node* &head){ // deletes linked list
	Node* current = head;
	Node* next;
	while(current != nullptr){
		next = current -> next; // deletes all node in linked list
		delete(current);
		current = next;
	}
	head = nullptr;  // empties head
}

int main(){
    greet();
    Node* headStack = nullptr;
    Node* headQ = nullptr;
    std::string word;
    int input;
    char again;
    std::cin >> again;
    
    while(again == 'y'||again== 'Y'){
		std::cout << "Type '1' to search palindromes from user input or '2' to search palindromes in a given text file" << std::endl;
		std::cin >> input;
		if(input == 1){
			word = userInput();
		}
		std::vector<std::string> v;
		int lines = 0;
		if(input == 2){
			openTextFile(v, lines);
			for (int i = 0; i < lines; i++){
				word = v[i];
				filterText(word);
				for(int i = 0; i < word.length(); i++){
					insert_front(headStack, word[i]);
					insert_end(headQ, word[i]);
				}
				
				Node* tailStack = headQ;
				Node* tailQ = headStack;
				int result = isPalindrome(headStack, tailStack);
				std::cout << "Stack: ";
				displayList(headStack, result);
				result = isPalindrome(headQ, tailQ);
				std::cout << "Queue: ";
				displayList(headQ, result);
				deleteList(headStack);
				deleteList(tailStack);
				deleteList(headQ);
				deleteList(tailQ);
			}
				
		}
		if(input == 1){
			filterText(word);
			for(int i = 0; i < word.length(); i++){
				insert_front(headStack, word[i]);
				insert_end(headQ, word[i]);
			}
			Node* tailStack = headQ;
			Node* tailQ = headStack;
			int result = isPalindrome(headStack, tailStack);
			std::cout << "Stack: ";
			displayList(headStack, result);
			result = isPalindrome(headQ, tailQ);
			std::cout << "Queue: ";
			displayList(headQ, result);
			deleteList(headStack);
			deleteList(tailStack);
			deleteList(headQ);
			deleteList(tailQ);
		}
		std::cout << "Would you like to go again?" << std::endl;
		std::cin >> again;
		if(again == 'N'||again == 'n'){break;}
	}
}
