/*
This project is made by:
		1:Abhishek Agarwal
    	2:Ujjawal Rana
    	3:Aditya Sharma
    	4:Devashish Shukla
*/
#include <bits/stdc++.h>
#include <string.h>
using namespace std;

#define ALPHABET_SIZE 26
#define false 0
#define true 1
#define MAX_WORD_SIZE   50
#define MAX_MEANING_SIZE 1000

//This function maps a number to to the passed character.
//If the letter is in the english alphabet i.e between A-Z or a-z then

//return a corresponding number. Return 0 for 'A' and 'a', 1 for 'B' and'b'
//and so on.

//If the letter is not present in the english alphabet i.e between A-Z or a-z then
//return -1.

int letterToInt(char letter)
{
    //checking if the letter is in uppercase.
  
    if (letter >= 'A' && letter <= 'Z')
    {
        //returning the ascii value of the letter minus the ascii value of the letter 'A'
        return letter - 'A';
      
    }

    else if (letter >= 'a' && letter <= 'z')
    {
        //returning the ascii value of the letter minus the ascii value of the letter 'a'
        return letter - 'a';
      
    }
    
    //returning -1 if the letter isnt in english alphabet.
    return -1;
}


// This is the structure of Trie
// The node of trie contains 
// isEndOfWord 
// stringvalue 
struct trieNode
{
    // A array whose size is 26 and every index of array points to a alphabet like 0th index of array point to 'a' alphabet
    struct trieNode* children[ALPHABET_SIZE];
    
    // isEndOfWord is a bool type variable 
    // if the value of isEndOfWord is true which means the path we follow from root to this node is a valid English word.
    // but if isEndOfWord is false this means this is not a word

    bool isEndOfWord;
  
    // If isEndOfWord is true then the meaning of that word is stored in the value string.
    string value;
};



//Function that creates and returns a pointer of type trieNode. 

struct trieNode* getNode(void)
{
    //dynamically allocating memory for a trieNode using 'new' keyboard
  
    struct trieNode *pNode =  new trieNode;
    
    //initialising all the values of pNode with default values.
  
    pNode->isEndOfWord = false;

    //initialising all the children of pNode with NULL
  
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        //Assigning each child to NULL
        pNode->children[i] = NULL;
    }
    
    //returning a pointer
    return pNode;
}


//Function that inserts a given word into the Trie
//along with it's meaning, if any
//Returns true if the word is successfully entered 

int insert(struct trieNode *root, string word, string meaning)
{
    //storing the root pointer into another variable.
  
    //The variable is named pCrawl as it is a naming convention.
    //Usually, in C language, a lower case p as a variable name prefix can be interpreted for pointer. 
    //Crawl refers to the nature of the pointer which is to crawl around the trie.
  
    struct trieNode *pCrawl = root;

    //Iterating through every letter of the word
    
    for (int i = 0; i < word.length(); i++)
    {
      
        //finding the corresponding index of the letter
        int index = letterToInt(word[i]);
        
        //Checking if child of pCrawl for the letter is null or not
        if (!pCrawl->children[index])
          
            //Assining an empty trieNode to that child
            pCrawl->children[index] = getNode();
        
        //Assigning the child we have entered to pCrawl.
        pCrawl = pCrawl->children[index];
    }
    
    //Assigning true to the variable isEndOfWord to signify that this is a valid word.
    pCrawl->isEndOfWord = true;
  
    //default meaning is kept as an empty string
    pCrawl->value = "";
  
    //if a meaning is passed, assign it to value.
    if(meaning != "null")
    {
        pCrawl->value = meaning;
    }

    //returns true if the insertion is successful
    return true;
}

//Old function to read a file into the trie.
int readWordsFromFile(struct trieNode *root, const char* filename)
{
    FILE *file = fopen(filename, "r");

  
    if (!file)
    {
        printf("could not find/open file \"%s\"\n", filename);
        return false;
    }
  
    char word[MAX_WORD_SIZE];
  
    char meaning[MAX_MEANING_SIZE];

  
    int count = 0;

    while (fscanf(file, "%s %[^\n]", word, meaning) > 1)
    {
        if (!insert(root, word, meaning))
        {
            fclose(file);
          
            return false;
        }

        else
        {
            count++;
        }
    }

    fclose(file);
    //cout << "Welcome to our Dictionary. Our Dictionary right now contains " << count << " words.\n";

    return true;
}

// This function checks that the passed word is present in the trie or not
// if the word is not present in the trie then function will return false.
// but if word present in trie then it will print the word and meaning too.

bool search(struct trieNode *root, string word)
{
    //storing the root pointer into another variable
    //The variable is named pCrawl as it is a naming convention.
    //Usually, in C language, a lower case p as a variable name prefix can be interpreted for pointer. 
    //Crawl refers to the nature of the pointer which is to crawl around the trie.
    struct trieNode *pCrawl = root;

    //Iterating through every letter of the word
    for (int i = 0; i < word.length(); i++)
    {
        //finding the corresponding index of the letter
        int index = letterToInt(word[i]);
        
        //Checking if child of pCrawl for the letter is null or not
        if (!pCrawl->children[index])
            //if the child is NULL then return false 
            // signifying that the word is not present
            return false;
        
        //Assigning pCrawl with its child 
        pCrawl = pCrawl->children[index];
    }
    
    //If condition to check 
    //1. The pointer pCrawl is not pointing to a NULL value.
    //2. It is pointing to the end of the word.
    //3. The meaning of the word is present in the trie.
    if (pCrawl != NULL && pCrawl->isEndOfWord && pCrawl->value != "")  
    {
      
        //Printing the meaning if it present
        cout << "The meaning of the word is: \n";
      
        cout << pCrawl->value;
    }
    //Else if the meaning is not present in the dictionary
    else if(pCrawl->value == "" and pCrawl->isEndOfWord)
    {
        cout << "The meaning of this word is yet to be added." << endl;
      
    } else 
    // Else if word is not present and no meaning
    {
      	return false;
    }
    
    //Returning true to signify that the function iss completed successfully
    return true;
}


//This function deletes a word from the trie.
//Returns true if the word was successfully deleted.
//Returns false otherwise.

bool deleteWord(struct trieNode *root, string word)
{
    //storing the root pointer into another variable
    //The variable is named pCrawl as it is a naming convention.
    //Usually, in C language, a lower case p as a variable name prefix can be interpreted for pointer. 
    //Crawl refers to the nature of the pointer which is to crawl around the trie.
  
    struct trieNode *pCrawl = root;

  
    //Iterating through every letter of the word
    for (int i = 0; i < word.length(); i++)
    {
        //finding the corresponding index of the letter
        int index = letterToInt(word[i]);
    
        //Checking if the child is null or not
        if (!pCrawl->children[index])
        {
            //returning false if the word is not found
            return false;
        }
          
        //Assigning pCrawl with it's child
        pCrawl = pCrawl->children[index];
    }
  
  
    //Checking if pCrawl points to a letter which is the end of a word
    if (pCrawl != NULL && pCrawl->isEndOfWord)  {
      
        //Assigning isEndOfWord to false to delete the word from trie
        pCrawl->isEndOfWord = false;
      
        //returning true to mark successful deletion of the word.
        return true;
    }
  	
  	return false;
}
//This function prints whole dictionary in alphabatical order.
//this wors using backtracking.
void alphabeticalOrder(struct trieNode* root, char allWords[], int index, int *c)
{   
    if(*c < 0) return;

  	// pCrawl is a pointer of type trieNode
  	// pCrawl points to the root of trie
    struct trieNode* pCrawl = root;
  
	// Check if pCrawl is NULL and pCrawl is end of a word
    if(pCrawl != NULL && pCrawl->isEndOfWord == true) 
    {
      	//it will print all values stored in array.
        for(int j = 0; j < index; j++) 
        {
          
            cout << allWords[j];
        }

        if(pCrawl->value != "")
            cout << ": ";
        cout << pCrawl->value << "\n";
        (*c)--;
    }

    for(int i = 0; i < ALPHABET_SIZE; i++)  {
        if(pCrawl->children[i] != NULL) {
            allWords[index] = 'a' + i;
          
            alphabeticalOrder(pCrawl->children[i], allWords, index + 1, c);
        }
    }
}

void print_prefix_search(struct trieNode* root, char allWords[], int index, string prefix)
{
  	// pCrawl is a pointer of type trieNode
  	// pCrawl points to the root of trie
    struct trieNode* pCrawl = root;

  	// Check if pCrawl is NULL and pCrawl is end of a word
    if(pCrawl != NULL && pCrawl->isEndOfWord == true) {
      	// First print the prefix Ex prefix is "aa", then printed value "aa"
        cout << prefix;
		
        // print the remaining allWords
        for(int j = 0; j < index; j++)  {
            cout << allWords[j];
        }
		
      	// print the meaning of the word
        cout << ": ";
        cout << pCrawl->value << "\n";
    }
	
  	// Traverse all the children of the root Node
    for(int i = 0; i < ALPHABET_SIZE; i++)  {
      	// If child Node is not NULL
        if(pCrawl->children[i] != NULL) {
          	// Assign allwords at position index the value of 'a' + i which can vary from a-z
            allWords[index] = 'a' + i;
          	// Again we backtrack to print the remaing words
            print_prefix_search(pCrawl->children[i], allWords, index + 1, prefix);
        }
    }
  	
  	return;
}

void prefix_search(struct trieNode* root, string prefix)
{
  	// pCrawl is a pointer of type trieNode
  	// pCrawl points to the root of trie
    struct trieNode* pCrawl = root;

  	// For loop iterate through prefix length
    for(int i = 0; i < prefix.length(); i++){
        // index contains value of char Ex. a = 1
        int index = letterToInt(prefix[i]);
		
      	// Check if children of root is NULL
        if(!pCrawl->children[index]){

            cout << "No string exist with the given prefix"<<"\n"; 
            return;
        }
      
      	// If children of Node exists, we point pCrawl to that child node
        pCrawl = pCrawl->children[index];
    }
	
  	// temporary array to print found words
    char allWords[50];
  
  	// Utility fuction to print all words with same prefix
    print_prefix_search(pCrawl, allWords, 0, prefix);
}

bool searchSuggestedWord(struct trieNode* root, string word, int count)
{
  	// pCrawl is a pointer of type trieNode
  	// pCrawl points to the root of trie
    struct trieNode *pCrawl = root;

  	// For loop iterate through word length
    for (int i = 0; i < word.length(); i++)
    {
      	// index contains value of char Ex. a = 1
        int index = letterToInt(word[i]);
		
      	// Check if children of root is NULL
        if (!pCrawl->children[index])
            return false;
		
      	// If children of Node exists, we point pCrawl to that child node
        pCrawl = pCrawl->children[index];
    }
	
  	// If word was found in Trie
    if (pCrawl != NULL && pCrawl->isEndOfWord)  {
        if(count == 0)  {
            cout << "Suggested words are: ";
        }
        cout << word << "  ";
    } else {
        return false;
    }
	
  	// return true on sucessfull search
    return true;
}

bool suggestedWords(struct trieNode* root, string word, int number)
{
  	// intitliaze count = 0, shows number of words that are printed
    int count = 0;
	
  	// Create all variations of word
    for(int i = 0; i < word.length(); i++)  
    {
      	// making a temporary copy of temp, as we have to modidy in the below for loop
        string temp = word;
		
      	// For loop iterate through prefix length
        for(int j = 0; j < ALPHABET_SIZE; j++)  
        {
          	
          	// Check if printed words are less than words that have to printed
          	// Convert last letter of word to integer value Ex a = 1
            if(count < number && j != letterToInt(word[word.length() - i - 1])) 
            {
              	
              	// Assign letter to a-z
                temp[word.length() - i - 1] = j + 97;

              	// Check if temp exists
                if(searchSuggestedWord(root, temp, count) and count < number) 
                {
                    count++;
                }
            }
        }
    }
	
  	// If no of found words are zero
    if(count == 0)  
    {
            cout << "\nSorry we couldn't find any words related to " << word << " in our Dictionary.\n";
        return false;
    }
  	// If no of founds words are less than intended
    else if (count < number)   
    {
        cout << "\nWe could only find " << count << " words related to " << word << " in our Dictionary.\n";
        return true;
    }
  	// If no of founds are equal to that were expected
    else   
    {
        return true;
    }
}

void get_Str(struct trieNode *temp,string s, int *n, vector<string> &suggestion_arr)
{

    if(n<=0)return;
  
    if(temp->isEndOfWord and *n>0){
      
        suggestion_arr.push_back(s);
        (*n)--;
    }

    for(int i=0;i<26;i++){
        if(temp->children[i]!=NULL){

            s.push_back((char)(i+'a'));

            get_Str(temp->children[i],s,n,suggestion_arr);

            s.pop_back();
        }
    }
}


void Suggest_Str(struct trieNode* root,string s, int *n, vector<string> &suggestion_arr)
{
    if(*n < 0) return;
    
    struct trieNode *temp=root;

    for(int i=0;i<s.length();i++){

        if(temp->children[letterToInt(s[i])]==NULL){

            get_Str(temp,s.substr(0,i),n,suggestion_arr);
            return ;
        }

        temp=temp->children[letterToInt(s[i])];
    }

    get_Str(temp,s,n,suggestion_arr);

    return;
}

bool check(struct trieNode *root,string s)
{
    struct trieNode *temp=root;

    for(int i=0;i<s.length();i++){

        if(temp->children[letterToInt(s[i])]==NULL){
            return false;
        }

        temp=temp->children[letterToInt(s[i])];
    }

    return temp->isEndOfWord;
}

void spellCheckConsole(struct trieNode *root, string word)
{
     if(check(root,word)){
         cout << "This word is a valid English Word!!!!" << "\n";
     }
  
     else{
       
        cout << "This is not a valid English Word!!!"<< "\n";
       
        cout << "How many word you want as suggestion: ";
        int n = 0, Count=0;
        cin>>n;
       
        Count=n;
       
        vector<string>suggestion_arr;
        Suggest_Str(root, word, &n, suggestion_arr);
       
        cout << "Number of suggested words are " << min((int)suggestion_arr.size(), Count) <<"\n";
       
        for(auto i:suggestion_arr){
            cout<<i<<"\n";
        }
     }
}

void suggestVaryingWords(trieNode *root, string word) {
    cout << "How many word you want as suggestion: ";

    int n = 0, Count=0;
    cin>>n;
       
    Count=n;
       
    vector<string>suggestion_arr;
    Suggest_Str(root, word, &n, suggestion_arr);
       
    cout << "Number of suggested words are " << min((int)suggestion_arr.size(), Count) <<"\n";
       
    for(auto i:suggestion_arr){
            cout<<i<<"\n";
    }
};

void spellCheckFile(struct trieNode *root, string file_name){
    string word;
    ifstream file1(file_name);
    while(file1 >> word) {
        transform (word.begin(), word.end(), word.begin(), ::tolower);
        for (auto c : word)
            if (ispunct(c) && c != '`')
                word.erase(word.find_first_of(c));
    
    if(check(root,word)){
        cout<<"String "<<word<<" is present"<<endl;   
    }
    else{
        cout << word<<" is not a valid English Word!!!"<< "\n";
        cout << "How many word you want as suggestion: ";
        int n,Count=0;
        cin>>n;
       
        Count=n;
       
        vector<string>suggestion_arr;
        Suggest_Str(root, word, &n, suggestion_arr);
       
        cout << "Number of suggested words are " << min((int)suggestion_arr.size(), Count) <<"\n";
       
        for(auto i:suggestion_arr){
            cout<<i<<"\n";
        }
    }
}
}


//Getting input for the trie.
//Using file handling to fetch words from a big text file and inserting
//them into the trie.
//fstream of C++ is used for file handling.

//Taking root of the trie as a parameter
void trie_input(struct trieNode *root)
{
  
    //Count variable to store the total number of words in the dictionary.
    
    int count=0;
  
    //Meaning of all the words is initialised with an empty string 
    
    string meaning="";
    
    //Using ifstream to open the file words_alpha.txt
    ifstream file("dictionary.txt");
  
    //Fetching each word from the file
    string word;
  
        //Looping till the end of file
        while(file >> word) {
          
            //Iterating through every character of the string
            //using speacilised for loop
            for (auto c : word)
            {
                //checking if the character is a punctuation
                if (ispunct(c) && c != '`')
                {
                    //erasing punctuations from the words
                    word.erase(word.find_first_of(c));
                }
              
                //Inserting clean words to the trie     
                insert(root,word,meaning);
            }

            //updating the number of words in the trie  
            count++;
        
        }
  
    //All words from the input file have been added to the trie.
    // Greeting user to the project.    
    cout << "Welcome to our Dictionary. Our Dictionary right now contains " << count << " words.\n";
  
}




//Main function of the program
int main()  {
    
    //Creating root for the trie.
    struct trieNode *root = getNode();

    //Inserting all the values of the input file to our trie.
    trie_input(root);

    
    string command;
  
    //Using a do while loop to take instructions from the user.
    do  {
      
        //Giving user multiple options to choose from.
        
        cout << "\nWhat would you like to do?\n";
      
        //All of the options below are thoroughly explained below.
      
        cout << "1. Insert a word.\n";
      
        cout << "2. Search the meaning of a word.\n";
      
        cout << "3. Delete a word.\n";
      
        cout << "4. Print dictionary in alphabetical order.\n";
      
        cout << "5. Prefix search.\n";
      
        cout << "6. Show suggested words (Same Length).\n";

        cout << "7. Show suggested words (Varying Length) (Common Prefix).\n";
      
        cout << "8. Spell Checker. \n";
      
        cout << "\n";
      
        fflush(stdin);

        //Taking choice of user as input.
        int call;
        int cc = 0;
        cin >> call;
        cout << "\n";
        
        //Declaring word and meaning strings
        string word;
        string meaning;

      
        //Switch case on the user choice
        switch(call)    {
    
            
            case 1: 
            
                    //Inserting a word into the dictionary along with it's meaning.
                    //This will firstly search in the trie for the entered word.

                    //Three cases could be possible here:-
                    //Case 1 - The word is not found - 
                    //         In this case just add the word to the trie along with it's meaning


                    //Case 2 - The word is found without any meaning
                    //         In this case just add the meaning corresponding to the word.

                    //Case 3 - The word is found with a meaning
                    //         In this case, change the meaning to the new meaning.

                    //Note:-
                    //Pass "null" while inputting meaning if you dont want to store only the word without meaning.
            
                    
                    //getting word input from user.
                    cout << "Enter the word you would like to insert: ";
            
                    cin >> word;
            
                    //getting meaning input from the user
                    cout << "Enter its meaning: ";
            
                    cin >> meaning;

                    //Inserting the word and meaning into the dictionary
                    if(insert(root, word, meaning)) 
                    {
                        //confirmation image.
                        cout << word << " has been added to the Dictionary.\n";
                    }

                    break;

            case 2: 
                    cout << "Enter the word you would like to search: ";
                    cin >> word;

                    if(!search(root, word))  {
                        cout << "Sorry, the word you searched for doesn't exist." << endl;
                        cout << "Would you like to add it to the Dictionary.(Yes/No) ";

                        string add;
                        cin >> add;

                        if(add == "yes" || add == "Yes" || command == "YES")  {
                            cout << "Enter its meaning: "<< endl;
                            
                            cout<< "(Type 'null' if you don't want to enter any meaning"  <<endl;
                            
                            cin >> meaning;

                            if(insert(root, word, meaning)) {
                            cout << word << " has been added to the Dictionary.\n";
                            }
                        }
                    }

                    break;

            case 3: 
                    cout << "Which word would you like to delete? ";
                    cin >> word;

                    if(deleteWord(root, word))  {
                        cout << word << " has been successfully deleted from the Dictionary.\n";
                    }

                    else    {
                        cout << "No such word exists in the Dictionary.\n";
                    }

                    break;

            case 4: 
                    char allWords[50];

                    cout<<"Enter the number of words to be printed.\n";
                    cin>>cc;

                    alphabeticalOrder(root, allWords, 0, &cc);
                    cout << "\n";

                    break;

            case 5: 
                    cout << "Enter the word you would like to use as a prefix: ";
                    cin >> word;
                    cout << "\n";

                    prefix_search(root, word);


                    break;            

            case 6: 
                    cout << "Enter the word for whose suggested words you want to see of same length: ";
                    
                    cin >> word;
                    int number;
            
                    cout << "How many suggested words do you want to see: ";
                    cin >> number;

                    suggestedWords(root, word, number);

                    break;

            case 7: 
                    cout << "Enter the word for whose suggested words you want to see of varying length: ";
                    
                    cin >> word;
            
                    suggestVaryingWords(root, word);

                    break;
            
            case 8:
                    cout << "Choose one of the following options -: " << "\n";
                    cout << "1 - Use Spell Checker for Console." << "\n"; 
                    cout << "2 - Use Spell Checker for file." << "\n";
            
                    int choice;
                    cin>>choice;
            
                    if(choice == 1){
                        cout << "Enter a word to check if it exists or not and recieve suggested words if it doesn't exist"<< "\n";
                      
                        cin>>word;
                        spellCheckConsole(root,word);
                        
                    }
            
                    else if(choice == 2){
                        cout<<"Enter the name of the input file to get suggestions for the wrong words" << "\n";                     
                        cin>>word;

                        spellCheckFile(root, word);
                    }
                                 
                  
                    break;

            default: cout << "Enter a valid entry.";
        }

    fflush(stdin);
        cout << "\n\nWould you like to continue or exit?(Yes/N0) ";
        cin >> command;
    }

    while(command == "yes" || command == "Yes" || command == "YES");

    cout << "Thanks for using our Dictionary.\n";
  
    return 0;
}