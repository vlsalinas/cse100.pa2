/**
 *  Name: Niral Patel and Taylor Lew
 *  Date: October 8, 2016
 *  Overview: Creates a dictionary with a Ternary Trie.  Implements insert
 *						and find.
 *  Assignement #:2 
 */

#include "util.h"
#include "DictionaryTrie.h"
#include <unordered_map>
#include <iterator>
#include <vector>
#include <set>

/* Param: None.
 * Return: None.
 * Create a new Dictionary that uses a Trie back end 
 */
DictionaryTrie::DictionaryTrie(){
	// set root to empty set
	root = new DictionaryTrieNode();
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) 
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq) {

	//index of the string
	unsigned int index = 0;

	//current node
	DictionaryTrieNode* curr = this->root;

	//iterators
	std::unordered_map<char, DictionaryTrieNode*>::iterator search;
	std::unordered_map<char, DictionaryTrieNode*>::iterator adding;

	//empty string
	if( word.length() == 0 ) {
		return false;
	}

	//letter not in hashmap
	//until the end of the word
	while( index < word.length() ) {
		char c = word.at( index );	
		//if node is not there
		search = curr->letters.find( c );
		if( search == curr->letters.end()  ) {
			//add a new node
			DictionaryTrieNode* next = new DictionaryTrieNode();
			adding = curr->letters.insert( std::pair<char, DictionaryTrieNode* >
																		 (c, next) ).first;
			curr = adding->second;
			curr->myCharacter = c;
			curr->myString = curr->myString + c;
		}
		
		else {
			//node with character is there
			curr->myString = curr->myString + c;
			curr = search->second;
		}
		index++;
	}

	//check for last node in word path
	if( curr->isWord ) {

		//check for duplicate frequency 
		if( curr->frequency < freq ) {
			curr->frequency = freq;
		}

		return false;
	}

	//insert word node
	DictionaryTrieNode* end = new DictionaryTrieNode();
	adding = curr->letters.insert( std::pair<char, DictionaryTrieNode* >
														 (word.at( word.length() - 1), end) ).first;

	//set isWord label
	curr->isWord = true;
	curr->frequency = freq;
	return true;
}

/* Param: string word (word to be searched for)
 * Return: true or false if the word is in the dictionary
 * Finds if a word in the dictionary 
 */
bool DictionaryTrie::find(std::string word) const {

	unsigned int index = 0;
	//current node
	DictionaryTrieNode* curr = root;
	std::unordered_map<char, DictionaryTrieNode*>::iterator search;

	//find the word
	while( index < word.length() ) {
		
		//search for the character
		search = curr->letters.find( word.at( index ) );
		if( search == curr->letters.end()  ) {
			return false;
		}
		
		else {
			//node with character is there
			curr = search->second;
		}
		index++;
	}
	
	//checking curr
	if( curr->isWord == true ) {
		return true;
	}

	return false;
}

/* Param: std::string prefix (prefix of the words that it will return)
 *				unsigned int num_completions (how many words to return)
 * Return: std::vector<std::string> (vector with most frequent words) 
 * Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix,
    unsigned int num_completions) {

	//vector to be returned
  std::vector<std::string> words;
	//vector with all possible words
	std::set<DictionaryTrieNode *> possibleWords;
	//index for DFS
	unsigned int index = 0;
	//index for finding prefix
	unsigned int searchIndex = 0;
	//current node
	DictionaryTrieNode* curr = root;
	std::unordered_map<char, DictionaryTrieNode*>::iterator search;

	//find the word
	while( searchIndex < prefix.length() ) {
		
		//search for the character
		search = curr->letters.find( prefix.at( searchIndex ) );
		if( search == curr->letters.end()  ) {
			return words;
		}
		
		else {
			//node with character is there
			curr = search->second;
		}
		searchIndex++;
	}

	//search in prefix's subtree	
	possibleWords = subSearch( curr, index );
	unsigned int loops = 0;

	//return the first num_completion elements in a vector
	for (std::set<DictionaryTrieNode* >::iterator adding=
				possibleWords.begin(); adding != possibleWords.end(); ++adding) {
		loops++;
		if( loops >= possibleWords.size() ) {
			break;
		}

		words.push_back( (*adding)->myString );
		adding++;
  }
//	DictionaryTrieNode * firstNode;
//	DictionaryTrieNode * secNode;
//
//	//sort the array
//	for( unsigned int a = 0; a < (index + 1); a++ ) {
//		
//		for( unsigned int b = 0; b < index - a; b++ ) {
//			firstNode = possibleWords[b];
//			secNode = possibleWords[b+1];
//			
//			//compare freq
//			if( firstNode->frequency > secNode->frequency ) {
//				possibleWords[b] = possibleWords[b+1];
//				possibleWords[b+1] = firstNode;
//			}
//		}
//	}

			//	//move to vector
			//	for( unsigned int i = 0; i < num_completions; i++ ) {
			//		DictionaryTrieNode * gotWord = possibleWords[index - i];
			//		words.push_back(gotWord->myString);
			//	}

  return words;
}

/* Param: DictionaryTrieNode * current (current node - where the prefix ends)
 * Return: DictionaryTrieNode * [] (array of DictionaryTrieNode pointers of
 *																	possible words)
 * Uses Depth First Search to get the all the possible words 
 */
std::set<DictionaryTrieNode *> DictionaryTrie::subSearch
											( DictionaryTrieNode * current, unsigned int & index ) {

	std::unordered_map<char, DictionaryTrieNode*>::iterator descend;
	static std::set<DictionaryTrieNode *> found;																	//How to store the frequency and word in the set to return
	
	//search for children
	for( descend = current->letters.begin(); descend != current->letters.end(); 
			++descend ) {

		//recurse to find all words
		subSearch( descend -> second, index );

		//check isWord
		if( current->isWord ) {
			found.insert( current );
			index++;
		}
	}

	return found;
}

/* Param: None.
 * Return: None.
 * Destructor for trie 
 */
DictionaryTrie::~DictionaryTrie() {
	//traverse trie in in-order using helper method
	delete root;
}


/* Param: None.
 * Return: None.
 * Constructor for Node 
 */
DictionaryTrieNode::DictionaryTrieNode() {
	// Initialized all fields of the Node class object
	isWord = false;
	myCharacter = 0;
}

/* Param: Char c is the character being pointed to in the next node
 * Return: A pointer to the next node
 * searchNext method 
 */
DictionaryTrieNode* DictionaryTrieNode::searchNext( char c ) {
	//pointer to be returned
	DictionaryTrieNode * next;

	//assume character is in hashmap
  //gets the value at the key from the hash map
  next = letters.at( c );
  //check for letters(c) exists
	return next;	
}

/* Param: None.
 * Return: None.
 * Destructor for DictionaryTrieNode 
 */
DictionaryTrieNode::~DictionaryTrieNode() {
	//delete the hash map
	//iterate through trie
	std::unordered_map<char, DictionaryTrieNode*>::iterator goDown;
	for( goDown = letters.begin(); goDown != letters.end(); goDown++ ) {
		delete goDown->second;
	}
}
