#include <iostream>
#include <fstream>
using namespace std;

struct TrieNode {

	// Store address of a character
	TrieNode* Trie[256];

	// Check if the character is
	// last character of a string or not
	bool isEnd;

	// Constructor function
	//function to initialize everything with NULL
	TrieNode()
	{
		for (int i = 0; i < 256; i++) {

			Trie[i] = NULL;
		}
		isEnd = false;
	}
};

// Function to insert a string into Trie
void InsertTrie(TrieNode* root, string s)
{

	TrieNode* temp = root;

	// Traverse the string, s
	for (int i = 0; i < s.length(); i++) {

		if (temp->Trie[s[i]] == NULL) {

			// Initialize a node
			temp->Trie[s[i]] = new TrieNode();
		}

		// Update temp
		temp = temp->Trie[s[i]];
	}

	// Mark the last character of
	// the string to true
	temp->isEnd = true;
}

// Function to print suggestions of the string
void printSuggestions(TrieNode* root, string res)
{
	// If current character is the last character of a string
	if (root->isEnd == true) {

		cout << res << " ";
	}

	// Iterate over all possible characters of the string
	for (int i = 0; i < 256; i++) {

		// If current character present in the Trie
		if (root->Trie[i] != NULL) {

			// Insert current character into Trie
			res.push_back(i);
			printSuggestions(root->Trie[i], res);
			res.pop_back();
		}
	}
}

// Function to check if the string is present in Trie or not
bool checkPresent(TrieNode* root, string key, int check)
{

	// Traverse the string
	for (int i = 0; i < key.length(); i++) {

		// If current character not present in the Trie
		if (root->Trie[key[i]] == NULL) {
            if(check == 1) //if the word is searched for checking spelling only we will give suggestions
            {
            cout<<"the spelling may be wrong\nThe word suggessions are : \n";
            printSuggestions(root, key.substr(0, i));
            }
			return false;
		}

		// Update root
		root = root->Trie[key[i]];
	}
	if (root->isEnd == true) {

		return true;
	}
	if(check == 1)//if the word is searched for checking spelling only we will give suggestions
        printSuggestions(root, key);

	return false;
}

void intro() //brief introduction
{
    cout<<"                                                                    WELCOME"<<endl;
    cout<<"                             Here we use trie data structure to store the words and check the correct spelling"<<endl;
}

void outro() //brief outro
{
    cout<<endl<<endl<<"                                                                    THANK YOU"<<endl<<endl;
}

int main() //driver function
{
    intro(); //printing the intro
    fstream words;
    TrieNode* root = new TrieNode(); //initializing the trie

    words.open("words.txt", ios::in); //opening the all words file
    //words.txt is the file consisting all the words
    string tp;
    while(getline(words, tp))
    { //read data from file object and put it into string.
         InsertTrie(root, tp);//inserting the data of the string
    }
    words.close();//closing the file

    int ch; //variable for switch case
    string key;
    int c = 1; //variable for while loop

    while(c)
    {
    cout<<"\n\n1. define a new word\n2. check the spelling a word\nEnter your choice : ";
    cin>>ch; //getting the choice
    switch(ch)
    {
        case 1: cout<<"\nEnter the word you want to define : ";
                     cin>>key;
                     if(!checkPresent(root, key, 0)) //checking if the word is already present
                     {
                        InsertTrie(root, key);
                        cout<<"word added successfully.";
                     }
                     break;
        case 2: cout<<"\nEnter the word you want to check : ";
                     cin>>key;
                     //checking if the word is already present
                    if(checkPresent(root, key, 1)) //and printing the suggesting words
                        cout<<"YES, the word is present";
                    break;
        default: cout<<"Enter only 1 or 2";
    }
    cout<<"\n\nDo you want to continue?(1/0) : " ;
    cin>>c; //getting the variable for while loop
    }

    outro(); //printing the outro
}
