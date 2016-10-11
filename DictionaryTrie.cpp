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

/* Param: None.
 * Return: None.
 * Create a new Dictionary that uses a Trie back end 
 */
DictionaryTrie::DictionaryTrie(){
//TODO
	// set root to empty set
	root = new DictionaryTrieNode();
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) 
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq) {

	//TODO
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
  //curr = helpFind( curr, word, index );
	
	//letter not in hashmap
	//until the end of the word
	while( index < word.length() - 1 ) {
		
		//if node is not there
		search = curr->letters.find( word.at( index ) );
		if( search == curr->letters.end()  ) {
			//add a new node
			DictionaryTrieNode* next = new DictionaryTrieNode();
			adding = curr->letters.insert( std::pair<char, DictionaryTrieNode* >
																		 (word.at( index ), next) ).first;
			curr = adding->second;
			curr->myCharacter = word.at( index );
		}
		
		else {
			//node with character is there
			curr = search->second;
		}
		index++;
	}
	if( curr->isWord ) {
		return false;
	}
	curr->isWord = true;
	return true;
}

/* Param: string word (word to be searched for)
 * Return: true or false if the word is in the dictionary
 * Finds if a word in the dictionary 
 */
bool DictionaryTrie::find(std::string word) const {

//TODO
//if next letter of word is not in set (call checkInSet)
//		call addToSet
//if next letter of word is in set
//		check for pointer at that character in hashmap
//		*** DictionaryTrieNode.letters.at( key/char )***
	//index of the string
	unsigned static int index = 0;
	//current node
	DictionaryTrieNode* curr = root;
	std::unordered_map<char, DictionaryTrieNode*>::iterator search;

	//curr = helpFind( curr, word, index );
	//find the word
	while( index < word.length() - 1 ) {
		
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
	if( curr->isWord == true && (index == word.length() - 1) ) {
		return true;
	}

	return false;
}

/* Param: DictionaryTrieNode which is the current node being looked at
 *				word which is the string being searched for in the dictionary
 *				index of where it is in the string
 * Return: Pointer to the word node in the dictionary trie or a nullptr 
 *				 if it doesn't exist.
 * Helps the find/insert methods by using recursion to search depth-first down
 *				 the trie
 */
DictionaryTrieNode* DictionaryTrie::helpFind( DictionaryTrieNode* current, 
									std::string word, unsigned int index ) const {
	//Node being currently looked at	
	DictionaryTrieNode* searching = current;
	
	//check that index is out of bounds
	if( index == word.length() ) {
		return searching;
	}

	//check if the character is in the hash map
	if( searching->letters.find( word.at( index ) ) != searching->letters.end() ) {
		index++;
		helpFind( searching->letters.at( word.at( index ) ), word, index );
	}

	return searching;
}

/* Return up to num_completions of the most frequent completions
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
    unsigned int num_completions)
{
  std::vector<std::string> words;
  return words;
}

/* Param: None.
 * Return: None.
 * Destructor for trie 
 */
//TODO
DictionaryTrie::~DictionaryTrie() {
	//traverse trie in in-order using helper method
	delete root;
}


/* Param: None.
 * Return: None.
 * Constructor for Node 
 */
//TODO
DictionaryTrieNode::DictionaryTrieNode() {
	// Initialized all fields of the Node class object
	isWord = false;
	myCharacter = 0;
}

/* Param: Char c is the character being pointed to in the next node
 * Return: A pointer to the next node
 * searchNext method 
 */
//TODO
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
//TODO
DictionaryTrieNode::~DictionaryTrieNode() {
	//delete the hash map
	//iterate through trie
	std::unordered_map<char, DictionaryTrieNode*>::iterator goDown;
	for( goDown = letters.begin(); goDown != letters.end(); goDown++ ) {
		delete goDown->second;
	}
}
